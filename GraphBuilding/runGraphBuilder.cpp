#include <SFML/Graphics.hpp>
#include <vector>


class Node : public sf::Drawable{

    public :
        Node(const float& nodeSize, const sf::Vector2f& mouse_position)
        : circle(nodeSize){
            circle.setOrigin({nodeSize, nodeSize});
            circle.setPosition(mouse_position);
            circle.setOutlineThickness(4.f);
            circle.setFillColor({157, 157, 163});
            circle.setOutlineColor({86, 86, 105});
        }

        Node(){}

        void addNeighbour(Node* neighbour){

            for(Node* node : adjacencyList){
                if (node == neighbour){
                    return;
                }
            }
            adjacencyList.emplace_back(neighbour);
        }

        const std::vector<Node*>& getAdjacencyList(){
            return adjacencyList;
        }

        bool contains(sf::Vector2f mouse_position){
            return circle.getGlobalBounds().contains(mouse_position);
        }

        sf::Vector2f getPosition(){
            return circle.getPosition();
        }

        void changeColor(sf::Color color){
            circle.setFillColor(color);
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override{
            target.draw(circle, states);
        }
    private: 
        sf::CircleShape circle;
        std::vector<Node*> adjacencyList;
};

void runGraphBuilder(sf::RenderWindow& window){
    bool wantToExit = false;

    //set to false to not create a node as soon as we enter
    bool hasReleasedM1 = false;
    bool hasReleasedM2 = true;
    Node* nodeToLink1 = nullptr;
    Node* nodeToLink2 = nullptr;
    std::vector<Node> nodeList;
    std::vector<std::pair<Node*, Node*>> edges;

    while(!wantToExit && window.isOpen()){

        window.clear({0,0,0});

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

        //create nodes
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && hasReleasedM1){
            hasReleasedM1 = false;
            float nodeSize = 20.f;
            Node node(nodeSize, mouse_position);
            nodeList.emplace_back(node);
        }

        //link two nodes together
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && hasReleasedM2){
            hasReleasedM2 = false;
            for(Node& node : nodeList){
                if (node.contains(mouse_position)){
                    node.changeColor(sf::Color::Red);
                    if(nodeToLink1 == nullptr){
                        nodeToLink1 = &node;
                        break;
                    }
                    else{
                        nodeToLink2 = &node;
                        nodeToLink1->addNeighbour(nodeToLink2);
                        nodeToLink2->addNeighbour(nodeToLink1);

                        nodeToLink1->changeColor(sf::Color::Cyan);
                        nodeToLink2->changeColor(sf::Color::Cyan);

                        edges.emplace_back(nodeToLink1, nodeToLink2);

                        nodeToLink1 = nullptr;
                        nodeToLink2 = nullptr;
                        break;
                    }
                }

            }
        }

        for(Node& node : nodeList){
            window.draw(node);
        }
        for (const auto& nodePair : edges){
            Node* node1 = nodePair.first;
            Node* node2 = nodePair.second;

            sf::VertexArray line (sf::PrimitiveType::Lines, 2);

            line[0].position = node1->getPosition();
            line[1].position = node2->getPosition();
            window.draw(line);
        }

        window.display();
    }
}

