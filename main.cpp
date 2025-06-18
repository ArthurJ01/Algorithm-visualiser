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

enum class Windows {menu, sorting};
extern const sf::Font font("C:/Windows/fonts/arial.ttf");

int main()
{
    Windows currentWindow = Windows::menu;
    SortingAlgorithm algoToRun = SortingAlgorithm::insertionSort;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");

    
    sf::Vector2f buttonSize = {200.f, 100.f};
    Button insertionSortButton(buttonSize, {100.f, 50.f}, "insertion sort");
    Button MergeSortButton(buttonSize, {100.f, 200.f}, "merge sort");

    //loop to keep open
    while(window.isOpen()){

        while (const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        switch (currentWindow){
            case Windows::menu: {
                window.clear(sf::Color(100,100,100));

                sf::Text text(font); // a font is required to make a text object
                text.setString("menu ");
                text.setCharacterSize(24); // in pixels, not points!
                text.setFillColor(sf::Color::Red);
                text.setStyle(sf::Text::Bold | sf::Text::Underlined);

                sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

                if(insertionSortButton.clicked(mouse_position)){
                    currentWindow = Windows::sorting;
                    algoToRun = SortingAlgorithm::insertionSort;
                }

                if(MergeSortButton.clicked(mouse_position)){
                    currentWindow = Windows::sorting;
                    algoToRun = SortingAlgorithm::mergeSort;
                }

                window.draw(insertionSortButton);
                window.draw(MergeSortButton);
                window.draw(text);
                window.display();

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

