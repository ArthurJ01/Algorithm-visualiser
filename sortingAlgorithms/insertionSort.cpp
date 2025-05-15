#include "../headers/sorting.hpp"
#include <vector>

void insertionSort(std::vector<int>& arr, int n, std::vector<std::vector<int>>& steps)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            steps.push_back(arr);
        }
        arr[j + 1] = key;
        steps.push_back(arr);
    }
}