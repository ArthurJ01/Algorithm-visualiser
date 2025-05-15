#include <vector>
#include <SFML/Graphics.hpp>

#include "headers/draw.hpp"

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