#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <thread>
#include "headers/sorting.hpp"

void drawRectangles(std::vector<sf::RectangleShape> rectangleList, std::vector<int> currentStep, sf::RenderWindow& window);

int main()
{
    int arrSize = 35;
    std::vector<int> arr(arrSize);

    for (int i = 0; i < arrSize; i++){
        arr[i] = i + 1;
    }

    //shuffle array, first get seed, then shuffle
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(arr.begin(), arr.end(), std::default_random_engine(seed));

    //create window, get size (size should probably be taken in main every frame)
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");

    std::vector<sf::RectangleShape> rectangleList(arrSize);
    std::vector<std::vector<int>> steps;
    std::vector<int> currentStep;
    insertionSort(arr, arrSize, steps);
    //mergeSort(arr, 0, arr.size() - 1, steps);
    long long unsigned step = 0;
    steps.push_back(arr);
    currentStep = steps.at(step);

    drawRectangles(rectangleList, currentStep, window);

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
        step++;
        if(step > steps.size() - 1){
            step = steps.size() - 1;
        }
        currentStep = steps.at(step);
    }
}

//assumes maxValue is the size of array, should be fine for how it's used before
void drawRectangles(std::vector<sf::RectangleShape> rectangleList, std::vector<int> currentStep, sf::RenderWindow& window){
    
    int arrSize = currentStep.size();
    int maxValue = arrSize;
    
    for (int i = 0; i < arrSize; i++){
        float windowSizeY = window.getSize().y;
        float windowSizeX = window.getSize().x;
        float height = -(windowSizeY/maxValue) * currentStep.at(i);

        sf::RectangleShape rectangle = rectangleList[i];
        rectangle.setSize({10.f, height});

        //this is useless after first call, but I don't feel like doing 2 functions
        float currentXPosition = (windowSizeX/arrSize) * i + 5.f;
        rectangle.setPosition({currentXPosition, window.getSize().y});

        window.draw(rectangle);
    }
}