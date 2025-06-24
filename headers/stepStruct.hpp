#pragma once

#include <vector>

struct stepStruct{
    std::vector<int> step;
    int keyIndex;
    int comparatorIndex;

    stepStruct(std::vector<int> step, int keyIndex, int comparatorIndex)
        : step(std::move(step)), keyIndex(keyIndex), comparatorIndex(comparatorIndex) {}
};
