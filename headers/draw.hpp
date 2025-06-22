#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "./stepStruct.hpp"
#include "./types.hpp"

void drawRectangles(stepStruct currentStepStruct, sf::RenderWindow& window);

void drawGraphBuilder(sf::RenderWindow& window, const sf::RectangleShape& graphWindow, EdgeList& edges, NodeList& nodeList, ButtonList& buttonList, sf::Text text);