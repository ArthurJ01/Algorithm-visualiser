#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "./stepStruct.hpp"

void drawRectangles(std::vector<sf::RectangleShape> rectangleList, stepStruct currentStepStruct, sf::RenderWindow& window);