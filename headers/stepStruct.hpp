#pragma once

#include <vector>

struct stepStruct{
    std::vector<int> step;
    int keyIndex;
    int comparatorIndex;

    stepStruct(std::vector<int> step, int keyIndex, int comparatorIndex)
        : step(std::move(step)), keyIndex(keyIndex), comparatorIndex(comparatorIndex) {}
};

/*
struct allStepsStruct{
    std::vector<stepStruct> steps;

    void addStep(std::vector<int> step, int keyIndex, int comparatorIndex){
        steps.emplace_back(step, keyIndex, comparatorIndex);
    };
};

*/