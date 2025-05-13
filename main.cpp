#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>
#include <thread>
#include "headers/sorting.hpp"

int main()
{

    float rectangleSizeX = 10.f;

    std::vector<int> arr(35);
    int arrSize = arr.size();

    for (int i = 0; i < arrSize; i++){
        arr[i] = i + 1;
    }

    //shuffle array, first get seed, then shuffle
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(arr.begin(), arr.end(), std::default_random_engine(seed));

    //create window, get size (size should probably be taken in main every frame)
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");
    float windowSizeX = window.getSize().x;

    std::vector<sf::RectangleShape> rectangleList(arrSize);

    for (int i = 0; i < arrSize; i++){

        float height = -10.f * arr[i];
        sf::RectangleShape rectangle({rectangleSizeX, height});
        float currentXPosition = (windowSizeX/arrSize) * i + 5.f;
        rectangle.setPosition({currentXPosition, 400.f});
        window.draw(rectangle);
        rectangleList[i] = rectangle;
    }

    std::vector<std::vector<int>> steps;
    std::vector<int> currentStep;
    insertionSort(arr, arrSize, steps);
    long long unsigned step = 0;
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
        
        for (int i = 0; i < arrSize; i++){

            float height = -10.f * currentStep.at(i);
            sf::RectangleShape rectangle = rectangleList[i];
            rectangle.setSize({rectangleSizeX, height});
            float currentXPosition = (windowSizeX/arrSize) * i + 5.f;
            rectangle.setPosition({currentXPosition, 400.f});
            window.draw(rectangle);
        }

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