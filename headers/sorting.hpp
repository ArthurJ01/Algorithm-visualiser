#pragma once
#include <vector>

void insertionSort(std::vector<int>& arr, int n, std::vector<std::vector<int>>& steps);
void merge(std::vector<int>& arr, int left, int mid, int right, std::vector<std::vector<int>>& steps);
void mergeSort(std::vector<int>& arr, int left, int right, std::vector<std::vector<int>>& steps);