#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>

#include "../headers/button.hpp"
#include "../headers/node.hpp"
#include "../headers/traversal.hpp"


enum class traversalAlgo{none, dfs, bfs, reset, clear};

std::vector<Node*> dfs(Node* startNode);

void runGraphBuilder(sf::RenderWindow& window){
    bool wantToExit = false;

    //set to false to not create a node as soon as we enter
    bool hasReleasedM1 = false;
    bool hasReleasedM2 = true;
    Node* startingNode = nullptr;
    sf::Color startingNodeColor({139, 0, 0});
    Node* nodeToLink1 = nullptr;
    Node* nodeToLink2 = nullptr;
    std::vector<std::unique_ptr<Node>> nodeList;
    std::vector<std::pair<Node*, Node*>> edges;
    sf::RectangleShape graphWindow({window.getSize().x - 200.f, window.getSize().y - 100.f});

    graphWindow.setFillColor({30, 30, 46});
    graphWindow.setPosition({15.f,15.f});
    graphWindow.setOutlineThickness(-5.f);
    graphWindow.setOutlineColor({100,100,100});


    std::vector<Button*> buttonList;
    sf::Vector2f buttonSize = {100.f, 100.f};
    Button bfsButton(buttonSize, {650.f, 15.f}, "BFS");         
    Button dfsButton(buttonSize, {650.f, 148.33f}, "DFS");      
    Button resetButton(buttonSize, {650.f, 281.66f}, "Reset");  
    Button clearButton(buttonSize, {650.f, 415.f}, "Clear");
    buttonList.emplace_back(&bfsButton);
    buttonList.emplace_back(&dfsButton);
    buttonList.emplace_back(&resetButton);
    buttonList.emplace_back(&clearButton);

    std::vector<Node*> visitOrder;
    traversalAlgo currentAlgo = traversalAlgo::none;

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

        if(bfsButton.clicked(mouse_position)){
            currentVisitIndex = 0;
            currentAlgo = traversalAlgo::bfs;
        }

        if(dfsButton.clicked(mouse_position)){
            currentVisitIndex = 0;
            currentAlgo = traversalAlgo::dfs;
        }

        if(resetButton.clicked(mouse_position)){
            currentVisitIndex = 0;
            currentAlgo = traversalAlgo::reset;
        }

        if(clearButton.clicked(mouse_position)){
            currentVisitIndex = 0;
            currentAlgo = traversalAlgo::clear;
        }

        if(currentAlgo == traversalAlgo::none){
            if(startingNode != nullptr){
                startingNode->changeColor(startingNodeColor);
            }
        }

        if(currentAlgo == traversalAlgo::bfs){
            if(startingNode == nullptr){
                currentAlgo = traversalAlgo::none;
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
        if(currentAlgo == traversalAlgo::dfs){
            if(startingNode == nullptr){
                currentAlgo = traversalAlgo::none;
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

        if(currentAlgo == traversalAlgo::reset){
            for (auto& node : nodeList){
                node.get()->changeColor({178, 102, 255});
            }
            if(startingNode != nullptr){
                startingNode->changeColor(startingNodeColor);
            }
            currentVisitIndex = 0;
            currentAlgo = traversalAlgo::none;
        }
        
        if(currentAlgo == traversalAlgo::clear){
            nodeList.clear();
            nodeList.shrink_to_fit();
            edges.clear();
            edges.shrink_to_fit();
            startingNode = nullptr;
            currentVisitIndex = 0;
            currentAlgo = traversalAlgo::none;
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
        window.draw(graphWindow);

        for (const auto& nodePair : edges){
            Node* node1 = nodePair.first;
            Node* node2 = nodePair.second;

            sf::VertexArray line (sf::PrimitiveType::Lines, 2);

            line[0].position = node1->getPosition();
            line[0].color = {200, 200, 200};

            line[1].position = node2->getPosition();
            line[1].color = {200, 200, 200};
            window.draw(line);
        }

        for(auto& nodeptr : nodeList){
            Node& node = *nodeptr;
            window.draw(node);
        }

        for(Button* buttonPtr : buttonList){
            Button button = *buttonPtr;
            window.draw(button);
        }


        window.display();
    }
}


