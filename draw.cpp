#include <vector>
#include <SFML/Graphics.hpp>

#include "headers/draw.hpp"
#include "headers/stepStruct.hpp"

//assumes maxValue is the size of array, should be fine for how it's used before
void drawRectangles(stepStruct currentStepStruct, sf::RenderWindow& window){
    
    std::vector<int> currentStep = currentStepStruct.step;
    int arrSize = currentStep.size();
    int maxValue = arrSize;
    
    for (int i = 0; i < arrSize; i++){
        float windowSizeY = window.getSize().y;
        float windowSizeX = window.getSize().x;
        float height = -(windowSizeY/maxValue) * currentStep.at(i);

        sf::RectangleShape rectangle;
        rectangle.setSize({10.f, height});


        if(i == currentStepStruct.keyIndex && i == currentStepStruct.comparatorIndex){
            rectangle.setFillColor(sf::Color::Yellow);
        }
        else if(i == currentStepStruct.keyIndex){
            rectangle.setFillColor(sf::Color::Red);
        } else if(i == currentStepStruct.comparatorIndex){
            rectangle.setFillColor(sf::Color::Green);
        }
        else{
            rectangle.setFillColor(sf::Color::White);
        }


        //this is useless after first call, but I don't feel like doing 2 functions
        float currentXPosition = (windowSizeX/arrSize) * i + 5.f;
        float yPosition = static_cast<float>(window.getSize().y);
        rectangle.setPosition({currentXPosition, yPosition});
        

        window.draw(rectangle);
    }
}