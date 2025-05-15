#include "../headers/sorting.hpp"
#include <vector>


void merge(std::vector<int>& arr, int left, int mid, int right, std::vector<std::vector<int>>& steps)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    std::vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back 
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
            steps.push_back(arr);
        }
        else {
            arr[k] = R[j];
            j++;
            steps.push_back(arr);
        }
        k++;
    }

    // Copy the remaining elements of L[], 
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        steps.push_back(arr);
    }

    // Copy the remaining elements of R[], 
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        steps.push_back(arr);
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(std::vector<int>& arr, int left, int right, std::vector<std::vector<int>>& steps)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, steps);
    mergeSort(arr, mid + 1, right, steps);
    merge(arr, left, mid, right, steps);
}
