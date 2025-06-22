#pragma once

#include <SFML/Graphics.hpp>

class Node : public sf::Drawable{

    public :
        Node(const float& nodeSize, const sf::Vector2f& mouse_position);

        Node();

        void addNeighbour(Node* neighbour);

        const std::vector<Node*>& getAdjacencyList();

        bool contains(sf::Vector2f mouse_position);

        sf::Vector2f getPosition();

        void changeColor(sf::Color color);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private: 
        sf::CircleShape circle;
        std::vector<Node*> adjacencyList;
};