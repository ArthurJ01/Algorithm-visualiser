#include <vector>
#include <SFML/Graphics.hpp>

#include "draw.hpp"
#include "stepStruct.hpp"
#include "types.hpp"
#include "node.hpp"
#include "button.hpp"

//assumes maxValue is the size of array, should be fine for how it's used before
void drawRectangles(stepStruct currentStepStruct, sf::RenderWindow& window){
    
    std::vector<int> currentStep = currentStepStruct.step;
    int arrSize = currentStep.size();
    int maxValue = arrSize;
    sf::RectangleShape drawWindow({600.f, 500.f}); 
    drawWindow.setFillColor({30, 30, 46});
    drawWindow.setPosition({15.f, 15.f});
    drawWindow.setOutlineThickness(5.f);
    drawWindow.setOutlineColor({100, 100, 100});

    window.draw(drawWindow); 

    float graphPosX = drawWindow.getPosition().x;
    float graphPosY = drawWindow.getPosition().y;
    float graphWidth = drawWindow.getSize().x;
    float graphHeight = drawWindow.getSize().y;

    float barWidth = graphWidth / static_cast<float>(arrSize);

    for (int i = 0; i < arrSize; i++) {
        float value = currentStep.at(i);
        float height = -(graphHeight / maxValue) * value; // negative to grow upward

        sf::RectangleShape rectangle;
        rectangle.setSize({barWidth - 2.f, height}); // slight spacing between bars

        // Color logic
        if (i == currentStepStruct.keyIndex && i == currentStepStruct.comparatorIndex) {
            rectangle.setFillColor(sf::Color::Yellow);
        } else if (i == currentStepStruct.keyIndex) {
            rectangle.setFillColor(sf::Color::Red);
        } else if (i == currentStepStruct.comparatorIndex) {
            rectangle.setFillColor(sf::Color::Green);
        } else {
            rectangle.setFillColor(sf::Color::White);
        }

        // Compute X and Y positions relative to graphWindow
        float x = graphPosX + barWidth * i + 1.f; // +1.f for left padding
        float y = graphPosY + graphHeight;        // start at bottom of graphWindow
        rectangle.setPosition({x, y});

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

    for(const auto& actionButtonPtr : buttonList){
        window.draw(actionButtonPtr->button);
    }


    window.display();
}