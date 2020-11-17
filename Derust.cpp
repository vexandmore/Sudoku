#include <iostream>
#include <vector>
#include<stdlib.h>
#include<time.h>

using namespace std;
class Test {
    public:
    int a, b, c;
    Test(int a,int b,int c) {
        this->a = a;
        this->b = b*2;
        this->c = c*3;
    }
};

void qsortI (vector<int>& list,int start,int end) {
    if (end-start < 1)
        return;
    int pivot = list[start];
    int pivotIndex = start;
    for (int i = start+1; i <= end; i++) {
        if (list[i] < pivot) {
            swap(list[pivotIndex], list[i]);
            swap(list[++pivotIndex], list[i]);
        }
    }
    qsortI(list, start, pivotIndex-1);
    qsortI(list, pivotIndex+1, end);
}
void qsort(vector<int>& list) {
    qsortI(list, 0, list.size()-1);
}
void printVector(vector<int>& list) {
    for (auto val: list) {
        cout << val << " ";
    }
    cout << "\n";
}
/*int main() {
    vector<int> list;
    srand(time(NULL));
    for (int i = 0; i < 20; i++) {
        list.push_back(rand()%100);
    }
    printVector(list);
    qsort(list);
    printVector(list);
}*/
