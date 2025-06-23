#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>

#include "button.hpp"
#include "node.hpp"
#include "traversal.hpp"
#include "draw.hpp"
#include "types.hpp"
#include "graphInputHandler.hpp"

extern const sf::Font font;

void runGraphBuilder(sf::RenderWindow& window){
    bool wantToExit = false;

    //set to false to not create a node as soon as we enter
    bool hasReleasedM1 = false;
    bool hasReleasedM2 = true;
    Node* startingNode = nullptr;
    sf::Color startingNodeColor({139, 0, 0});
    Node* nodeToLink1 = nullptr;
    Node* nodeToLink2 = nullptr;
    sf::RectangleShape graphWindow({window.getSize().x - 200.f, window.getSize().y - 100.f});

    //defined in types.hpp
    NodeList nodeList;
    EdgeList edges;
    ButtonList actionButtons;

    graphWindow.setFillColor({30, 30, 46});
    graphWindow.setPosition({15.f,15.f});
    graphWindow.setOutlineThickness(-5.f);
    graphWindow.setOutlineColor({100,100,100});

    sf::Text text(font); // a font is required to make a text object
    text.setString("Create a node with m1, create edges with m2");
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor({240, 240, 240});
    text.setPosition({40.f, 550.f});

    sf::Vector2f buttonSize = {100.f, 100.f};
    Button bfsButton(buttonSize, {650.f, 15.f}, "BFS");         
    Button dfsButton(buttonSize, {650.f, 148.33f}, "DFS");      
    Button resetButton(buttonSize, {650.f, 281.66f}, "Reset");  
    Button clearButton(buttonSize, {650.f, 415.f}, "Clear");
    Button returnButton({100.f, 40.f}, {650.f, 535.f}, "Return");

    actionButtons.emplace_back(std::make_unique<actionButton>(actionType::bfs, bfsButton));
    actionButtons.emplace_back(std::make_unique<actionButton>(actionType::dfs, dfsButton));
    actionButtons.emplace_back(std::make_unique<actionButton>(actionType::reset, resetButton));
    actionButtons.emplace_back(std::make_unique<actionButton>(actionType::clear, clearButton));
    actionButtons.emplace_back(std::make_unique<actionButton>(actionType::exit, returnButton));

    std::vector<Node*> visitOrder;
    actionType currentAction = actionType::none;

    size_t currentVisitIndex = 0;
    sf::Clock traversalClock;

    while(!wantToExit && window.isOpen()){

        window.clear({20, 20, 20});

        //check window closed (always necessary), exit, release of m1, m2
        while (const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    wantToExit = true;
                }
            }
            else if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonReleased>()){
                if(mouseButtonPressed->button == sf::Mouse::Button::Left){
                    hasReleasedM1 = true;
                }
                else if(mouseButtonPressed->button == sf::Mouse::Button::Right){
                    hasReleasedM2 = true;
                }
            }
        }

        sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

        currentAction = getCurrentAction(currentAction, mouse_position, actionButtons);

        if(currentAction == actionType::none){
            if(startingNode != nullptr){
                startingNode->changeColor(startingNodeColor);
            }
        }

        //TODO: run bfs once, then go to drawing state to print the things
        if(currentAction == actionType::bfs){
            if(startingNode == nullptr){
                currentAction = actionType::none;
            }
            else{
                visitOrder = bfs(startingNode);
                if (currentVisitIndex < visitOrder.size() && traversalClock.getElapsedTime().asMilliseconds() > 500){
                    visitOrder[currentVisitIndex]->changeColor({207, 255, 4});
                    currentVisitIndex++;
                    traversalClock.restart();
                }
            }

        }
        if(currentAction == actionType::dfs){
            if(startingNode == nullptr){
                currentAction = actionType::none;
            }
            else{
                visitOrder = dfs(startingNode);
                if (currentVisitIndex < visitOrder.size() && traversalClock.getElapsedTime().asMilliseconds() > 500){
                    visitOrder[currentVisitIndex]->changeColor({207, 255, 4});
                    currentVisitIndex++;
                    traversalClock.restart();
                }
            }

        }

        if(currentAction == actionType::reset){
            for (auto& node : nodeList){
                node.get()->changeColor({178, 102, 255});
            }
            if(startingNode != nullptr){
                startingNode->changeColor(startingNodeColor);
            }
            currentVisitIndex = 0;
            currentAction = actionType::none;
        }
        
        if(currentAction == actionType::clear){
            nodeList.clear();
            nodeList.shrink_to_fit();
            edges.clear();
            edges.shrink_to_fit();
            startingNode = nullptr;
            currentVisitIndex = 0;
            currentAction = actionType::none;
        }

        //create nodes, in graphWindow bounds
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && hasReleasedM1){
            if(graphWindow.getGlobalBounds().contains(mouse_position)){
                hasReleasedM1 = false;
                float nodeSize = 15.f;
                nodeList.emplace_back(std::make_unique<Node>(nodeSize, mouse_position));
                if(startingNode == nullptr){
                    startingNode = nodeList.at(0).get();
                    startingNode->changeColor({255, 99, 71});
                }
            }
        }

        //link two nodes together
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && hasReleasedM2){
            hasReleasedM2 = false;
            for(auto& nodeptr : nodeList){
                Node& node = *nodeptr;

                if (node.contains(mouse_position)){
                    node.changeColor({255, 99, 71});
                    if(nodeToLink1 == nullptr){
                        nodeToLink1 = &node;
                        break;
                    }
                    else if(nodeToLink1 == &node){
                        //do nothing
                        break;
                    }
                    else{
                        nodeToLink2 = &node;
                        nodeToLink1->addNeighbour(nodeToLink2);
                        nodeToLink2->addNeighbour(nodeToLink1);

                        nodeToLink1->changeColor({0, 153, 255});
                        nodeToLink2->changeColor({0, 153, 255});

                        edges.emplace_back(nodeToLink1, nodeToLink2);

                        nodeToLink1 = nullptr;
                        nodeToLink2 = nullptr;
                        break;
                    }
                }

            }
        }
        drawGraphBuilder(window, graphWindow, edges, nodeList, actionButtons, text);
    }
}


