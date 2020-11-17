#include <iostream>
#include <vector>
#include<algorithm>
#include"Sudoku.h"
using  namespace std;

int main() {
    vector<vector<int>> boardA = std::vector<std::vector<int>>{ {3, 4, 1, 2}, {1, 2, 3, 4}, {4, 3, 2, 1}, {2, 1, 4, 3} };
    vector<vector<int>> clues = std::vector<std::vector<int>>{ {3, 4, 1, -1}, {-1, 2, -1, -1}, {-1, -1, 2, -1}, {-1, 1, 4, 3} };
    Board board(clues, boardA);
    cout << board;
    board.solve();
    cout << board;

    vector<vector<int>> boardB = { {-1,-1,-1,-1,1,-1,7,2,-1},
        {-1,-1,3,2,7,8,-1,9,-1},
        {-1,5,7,-1,-1,-1,3,-1,8},
        {-1,-1,-1,9,6,-1,-1,7,1},
        {-1,-1,-1,-1,8,2,-1,6,3},
        {1,9,6,-1,-1,-1,-1,4,2},
        {3,-1,8,-1,2,9,-1,-1,4},
        {-1,-1,9,-1,5,1,-1,-1,-1},
        {-1,6,-1,7,-1,3,-1,8,9} };
    /*vector<vector<int>> solvedBoardB = { {9,8,4,3,1,5,7,2,6},
        {6,1,3,2,7,8,4,9,5},
        {2,5,7,4,9,6,3,1,8},
        {8,3,2,9,6,4,5,7,1},
        {7,4,5,1,8,2,9,6,3},
        {1,9,6,5,3,7,8,4,2},
        {3,7,8,6,2,9,1,5,4},
        {4,2,9,8,5,1,6,3,7},
        {5,6,1,7,4,3,2,8,9}
    };*/
    Board board2(boardB/*, solvedBoardB*/);
    cout << "clues: " << board2.getNumberClues() << "\n" <<  board2;
    board2.solve();
    cout << "clues: " << board2.getNumberClues() << "\n" << board2;

    vector<vector<int>> boardC = {
        {-1,-1,-1,-1,3,-1,-1,-1,-1},
        {-1,1,-1,-1,6,7,4,-1,-1},
        {6,-1,-1,8,-1,-1,7,-1,-1},
        {3,-1,6,-1,-1,-1,1,7,4},
        {-1,9,-1,-1,-1,-1,-1,2,-1},
        {5,7,1,-1,-1,-1,6,-1,9},
        {-1,-1,7,-1,-1,1,-1,-1,5},
        {-1,-1,5,9,4,-1,-1,1,-1},
        {-1,-1,-1,-1,5,-1,-1,-1,-1}
    };
    Board board3(boardC);

    cout << "clues: " << board3.getNumberClues() << "\n" << board3;
    board3.solve();
    cout << "clues: " << board3.getNumberClues() << "\n" << board3 << "This board was too complex for this to solve";

    cin.get();
}
