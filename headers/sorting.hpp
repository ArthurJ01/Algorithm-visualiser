#pragma once
#include <vector>
#include "./stepStruct.hpp"

void insertionSort(std::vector<int>& arr, int n, std::vector<stepStruct>& allSteps);
void merge(std::vector<int>& arr, int left, int mid, int right, std::vector<std::vector<int>>& steps);
void mergeSort(std::vector<int>& arr, int left, int right, std::vector<std::vector<int>>& steps);