#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>

#include "sorting.hpp"
#include "draw.hpp"
#include "initialize.hpp"
#include "stepStruct.hpp"


enum class SortingAlgorithm { insertionSort, mergeSort };

void runSortAlgo(sf::RenderWindow& window, const SortingAlgorithm algoToRun);