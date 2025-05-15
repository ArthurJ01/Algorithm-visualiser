#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#include "headers/initialize.hpp"

void initialize(std::vector<int>& arr, int arrSize){
    //initialise array
    for (int i = 0; i < arrSize; i++){
        arr[i] = i + 1;
    }

    //shuffle array, first get seed, then shuffle
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(arr.begin(), arr.end(), std::default_random_engine(seed));
}