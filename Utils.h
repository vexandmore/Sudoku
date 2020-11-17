#pragma once
#include<vector>
#include<algorithm>

/**
* Takes a vector containing values from minValue to maxValue and return a vector
* containing only the values that the vector doesn't have. The returned vector
* does not have duplicate elements.
*/
std::vector<int> absentIn(std::vector<int> present, int minValue, int maxValue);