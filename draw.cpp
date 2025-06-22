#include <vector>
#include <SFML/Graphics.hpp>

#include "headers/draw.hpp"
#include "headers/stepStruct.hpp"
#include "headers/types.hpp"
#include "headers/node.hpp"
#include "headers/button.hpp"

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

void drawGraphBuilder(sf::RenderWindow& window, const sf::RectangleShape& graphWindow, EdgeList& edges, NodeList& nodeList, ButtonList& buttonList, sf::Text text){
    window.draw(graphWindow);
    window.draw(text);

    for (const auto& nodePair : edges){
        Node* node1 = nodePair.first;
        Node* node2 = nodePair.second;

        sf::VertexArray line (sf::PrimitiveType::Lines, 2);

        line[0].position = node1->getPosition();
        line[0].color = {200, 200, 200};

        line[1].position = node2->getPosition();
        line[1].color = {200, 200, 200};
        window.draw(line);
    }

    for(auto& nodeptr : nodeList){
        Node& node = *nodeptr;
        window.draw(node);
    }

    for(Button* buttonPtr : buttonList){
        window.draw(*buttonPtr);
    }


    window.display();
}