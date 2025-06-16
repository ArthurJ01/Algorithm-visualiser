#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <thread>

#include "headers/sorting.hpp"
#include "headers/draw.hpp"
#include "headers/initialize.hpp"
#include "headers/stepStruct.hpp"
#include "headers/sortingVisualiser.hpp"

enum class Windows { menu, sorting};

int main()
{
    Windows currentWindow = Windows::menu;
    SortingAlgorithm algoToRun = SortingAlgorithm::insertionSort;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");

    

    //loop to keep open
    while(window.isOpen()){

        while (const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    currentWindow = Windows::sorting;
                }
            }  
        }
        switch (currentWindow){
            case Windows::menu: {

                //TODO: import a font to the project or smth (maybe it can be like this though)
                sf::Font font("C:/Windows/fonts/arial.ttf");
                window.clear(sf::Color(100,100,100));

                sf::Text text(font); // a font is required to make a text object
                text.setString("menu ");
                text.setCharacterSize(24); // in pixels, not points!
                text.setFillColor(sf::Color::Red);
                text.setStyle(sf::Text::Bold | sf::Text::Underlined);

                sf::RectangleShape insertionSortButton({200.f, 100.f});
                insertionSortButton.setPosition({100.f, 50.f}); 

                sf::Text insertionButtonText (font); // a font is required to make a text object
                insertionButtonText.setString("insertion sort ");
                insertionButtonText.setCharacterSize(24);
                insertionButtonText.setFillColor(sf::Color::Red);
                {
                    float position_x = insertionSortButton.getPosition().x + (insertionSortButton.getSize().x / 2);
                    float position_y = insertionSortButton.getPosition().y + (insertionSortButton.getSize().y / 2);
                    insertionButtonText.setOrigin({insertionButtonText.getGlobalBounds().getCenter()});
                    insertionButtonText.setPosition({position_x, position_y});
                }


                sf::RectangleShape MergeSortButton({200.f, 100.f});
                MergeSortButton.setPosition({100.f, 200.f}); 

                sf::Text mergeButtonText (font); // a font is required to make a text object
                mergeButtonText.setString("merge sort ");
                mergeButtonText.setCharacterSize(24);
                mergeButtonText.setFillColor(sf::Color::Red);
                {
                    float position_x = MergeSortButton.getPosition().x + (MergeSortButton.getSize().x / 2);
                    float position_y = MergeSortButton.getPosition().y + (MergeSortButton.getSize().y / 2);
                    mergeButtonText.setOrigin({mergeButtonText.getGlobalBounds().getCenter()});
                    mergeButtonText.setPosition({position_x, position_y});
                }
              
                sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

                if(insertionSortButton.getGlobalBounds().contains(mouse_position)){
                    insertionSortButton.setFillColor(sf::Color::Yellow);
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        currentWindow = Windows::sorting;
                        algoToRun = SortingAlgorithm::insertionSort;
                    } 
                }
                else{
                    insertionSortButton.setFillColor(sf::Color::White);
                }

                if(MergeSortButton.getGlobalBounds().contains(mouse_position)){
                    MergeSortButton.setFillColor(sf::Color::Yellow);
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        currentWindow = Windows::sorting;
                        algoToRun = SortingAlgorithm::mergeSort;
                    } 
                }
                else{
                    MergeSortButton.setFillColor(sf::Color::White);
                }



                window.draw(insertionSortButton);
                window.draw(MergeSortButton);
                window.draw(insertionButtonText);
                window.draw(mergeButtonText);
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

