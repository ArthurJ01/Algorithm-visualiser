#include "../headers/sorting.hpp"
#include "../headers/stepStruct.hpp"
#include <vector>

void insertionSort(std::vector<int>& arr, int n, std::vector<stepStruct>& allSteps)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            allSteps.emplace_back(arr, j, i);
            j = j - 1;
        }
        arr[j + 1] = key;
        allSteps.emplace_back(arr, j+1, i);
    }
}