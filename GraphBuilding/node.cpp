#include <SFML/Graphics.hpp>

#include "../headers/node.hpp"


    Node::Node(const float& nodeSize, const sf::Vector2f& mouse_position)
    : circle(nodeSize){
        circle.setOrigin({nodeSize, nodeSize});
        circle.setPosition(mouse_position);
        circle.setFillColor({178, 102, 255});
    }

    Node::Node(){}

    void Node::addNeighbour(Node* neighbour){

        for(Node* node : adjacencyList){
            if (node == neighbour){
                return;
            }
        }
        adjacencyList.emplace_back(neighbour);
    }

    const std::vector<Node*>& Node::getAdjacencyList(){
        return adjacencyList;
    }

    bool Node::contains(sf::Vector2f mouse_position){
        return circle.getGlobalBounds().contains(mouse_position);
    }

    sf::Vector2f Node::getPosition(){
        return circle.getPosition();
    }

    void Node::changeColor(sf::Color color){
        circle.setFillColor(color);
    }

    void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(circle, states);
    }

