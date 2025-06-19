#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <thread>

#include "headers/sorting.hpp"
#include "headers/draw.hpp"
#include "headers/initialize.hpp"
#include "headers/stepStruct.hpp"
#include "headers/sortingVisualiser.hpp"
#include "headers/button.hpp"

enum class Windows {menu, sorting, graph};
extern const sf::Font font("C:/Windows/fonts/arial.ttf");

class Node : public sf::Drawable{

    public :
        Node(const float& nodeSize, const sf::Vector2f& mouse_position)
        : circle(nodeSize){
            circle.setOrigin({nodeSize, nodeSize});
            circle.setPosition(mouse_position);
        }

        void addNeighbour(Node* neighbour){
            adjacencyList.emplace_back(neighbour);
        }

        const std::vector<Node*>& getAdjacencyList(){
            return adjacencyList;
        }

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override{
            target.draw(circle, states);
        }
    private: 
        sf::CircleShape circle;
        std::vector<Node*> adjacencyList;
};


int main()
{
    Windows currentWindow = Windows::menu;
    SortingAlgorithm algoToRun = SortingAlgorithm::insertionSort;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");

    sf::Vector2f buttonSize = {200.f, 100.f};
    Button insertionSortButton(buttonSize, {100.f, 50.f}, "insertion sort");
    Button mergeSortButton(buttonSize, {100.f, 200.f}, "merge sort");
    Button graphButton(buttonSize, {400.f, 50.f}, "Graph builder");

    //loop to keep open
    while(window.isOpen()){

        while (const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        switch (currentWindow){
            case Windows::menu: {
                window.clear(sf::Color(50,50,50));

                sf::Text text(font); // a font is required to make a text object
                text.setString("menu ");
                text.setCharacterSize(24); // in pixels, not points!
                text.setFillColor(sf::Color::Red);

                sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

                if(insertionSortButton.clicked(mouse_position)){
                    currentWindow = Windows::sorting;
                    algoToRun = SortingAlgorithm::insertionSort;
                }
                if(mergeSortButton.clicked(mouse_position)){
                    currentWindow = Windows::sorting;
                    algoToRun = SortingAlgorithm::mergeSort;
                }
                if(graphButton.clicked(mouse_position)){
                    currentWindow = Windows::graph;
                }

                window.draw(insertionSortButton);
                window.draw(mergeSortButton);
                window.draw(graphButton);
                window.draw(text);
                window.display();

                break;
            }

            case Windows::graph:{

                bool wantToExit = false;
                std::vector<sf::CircleShape> nodeList(10);

                while(!wantToExit && window.isOpen()){

                    window.clear({0,0,0});

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
                    }

                    sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        float nodeSize = 20.f;
                        sf::CircleShape node(nodeSize);
                        node.setOrigin({nodeSize, nodeSize});
                        node.setPosition(mouse_position);
                        nodeList.emplace_back(node);
                    }

                    for(sf::CircleShape node : nodeList){
                        window.draw(node);
                    }
                    window.display();
                }
                currentWindow = Windows::menu;
                break;
            }

            case Windows::sorting: {
                //run sorting algo and when it is done, go back to menu
                runSortAlgo(window, algoToRun);
                currentWindow = Windows::menu;
                break;
            }

        }
    }
}

