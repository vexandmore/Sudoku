#include <iostream>
#include<vector>
#pragma once
class Board {
    private:
        int numberClues;
        std::vector<std::vector<int>> board;
        std::vector<std::vector<int>> clues;
    public:
        const int numberRows;
        const int rowsPerSquare;

        Board(std::vector<std::vector<int>> clues, std::vector<std::vector<int>> solved);
        Board(std::vector<std::vector<int>> clues);

        int const getClue(int rowIndex, int columnIndex);
        bool const rowContains(int index, int value);
        bool const colContains(int index, int value);
        int const getNumberClues();
        bool const checkIndicies(int row, int col);
        friend std::ostream& operator<< (std::ostream& os, const Board& board);

        void solve();
        bool setSpace(int rowIndex, int columnIndex, int value);
};