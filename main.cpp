#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <thread>

#include "headers/sorting.hpp"
#include "headers/draw.hpp"
#include "initialize.hpp"

int main()
{
    int arrSize = 35;

    std::vector<int> arr(arrSize);
    std::vector<sf::RectangleShape> rectangleList(arrSize);
    std::vector<std::vector<int>> steps;
    std::vector<int> currentStep;

    initialize(arr, arrSize);

    //create window, get size (size should probably be taken in main every frame)
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");

    //insertionSort(arr, arrSize, steps);
    mergeSort(arr, 0, arrSize - 1, steps);

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
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            step++;
            if(step > steps.size() - 1){
                step = steps.size() - 1;
            }

        }

        currentStep = steps.at(step);

    }
}