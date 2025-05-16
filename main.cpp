#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <thread>

#include "headers/sorting.hpp"
#include "headers/draw.hpp"
#include "initialize.hpp"

int main()
{

    //click logic
    bool wasLeftPressed = false;
    bool wasRightPressed = false;

    int arrSize = 35;

    std::vector<int> arr(arrSize);
    std::vector<sf::RectangleShape> rectangleList(arrSize);
    std::vector<std::vector<int>> steps;
    std::vector<int> currentStep;

    initialize(arr, arrSize);

    //create window, get size (size should probably be taken in main every frame)
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");

    insertionSort(arr, arrSize, steps);
    //mergeSort(arr, 0, arrSize - 1, steps);

    long long unsigned step = 0;
    steps.push_back(arr);
    currentStep = steps.at(step);

    //loop to keep open
    while(window.isOpen()){

        while (const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        //fill display with black
        window.clear(sf::Color(0,0,0));
        
        drawRectangles(rectangleList, currentStep, window);

        //display what is set up
        window.display();

        bool isLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if(isLeftPressed && !wasLeftPressed){
            if(step < steps.size() - 1){
                step++;
            }

        }
        wasLeftPressed = isLeftPressed;

        bool isRightPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
        if(isRightPressed && !wasRightPressed){
            if(step >= 1){
                step--;
            }

        }
        wasRightPressed = isRightPressed;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            if(step < steps.size() - 1){
                step++;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            if(step >= 1){
                step--;
            }
        }
                

        currentStep = steps.at(step);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }
}