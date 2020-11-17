#include<vector>
#include<algorithm>

std::vector<int> absentIn(std::vector<int> present, int minValue, int maxValue) {
    std::vector<int> absent;
    if (present.size() == 0) {
        for (int i = minValue; i <= maxValue; i++)
            absent.push_back(i);
        return absent;
    }

    std::sort(present.begin(), present.end());
    if (present[0] > minValue) {
        for (int i = minValue; i < present[0]; i++)
            absent.push_back(i);
    }
    int previousValue = present[0];
    for (int i = 1; i < present.size(); i++) {
        if (present[i] - previousValue > 1) {
            for (int j = previousValue + 1; j < present[i]; j++) {
                absent.push_back(j);
            }
        }
        previousValue = present[i];
    }
    if (present[present.size() - 1] < maxValue) {
        for (int i = present[present.size() - 1] + 1; i <= maxValue; i++) {
            absent.push_back(i);
        }
    }
    return absent;
}