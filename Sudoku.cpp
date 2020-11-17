#include<vector>
#include <algorithm>
#include <cmath>
#include<iostream>
#include "Utils.h"
#include"Sudoku.h"



class IntPair {
public:
    int x, y;
    IntPair(int x, int y) : x(x), y(y) {}
};
IntPair pointWhereNumCouldGo(Board& board, int square, int num);
void checkAlmostRows(Board& board);
void checkSquares(Board& board);



Board::Board(std::vector<std::vector<int>> clues, std::vector<std::vector<int>> solved) 
    : numberRows(solved.size()), numberClues(0), rowsPerSquare((int)std::sqrt(numberRows)) {
	this->clues = clues;
	for (auto row : clues) {
		for (auto num : row) {
			if (num >= 0)
				numberClues++;
		}
	}
	this->board = solved;
}
Board::Board(std::vector<std::vector<int>> clues) 
    : clues(clues), numberRows(clues.size()), numberClues(0), rowsPerSquare((int)std::sqrt(numberRows)) {
    for (auto row : clues) {
        for (auto num : row) {
            if (num >= 0)
                numberClues++;
        }
    }
}
int const Board::getNumberClues() {
    return numberClues;
}
int const Board::getClue(int rowIndex, int colIndex){
    checkIndicies(rowIndex, colIndex);
    return clues[rowIndex][colIndex];
}
bool Board::setSpace(int rowIndex, int columnIndex, int value){
    if (!checkIndicies(rowIndex, columnIndex)) {
        std::cout << "attempted to set space at illegal indices";
        return false;
     }
    //verifies that clue you're trying to set isn't already set
    if (clues[rowIndex][columnIndex] != -1) {
        std::cout << "tried to set where there is already a number, " << clues[rowIndex][columnIndex] << " " << value << "\n";
        return false;
    }
    else {
        //verifies using the solved board, if it exists
        if (board.size() > 0) {
            if (board[rowIndex][columnIndex] == value) {
                clues[rowIndex][columnIndex] = value;
                numberClues++;
                return true;
            }
            else {
                std::cout << "tried to set where the answers shows is invalid\n";
                return false;
            }
        }
        //sets value if no solved board exists
        else {
            clues[rowIndex][columnIndex] = value;
            numberClues++;
            return true;
        }
    }
}

bool const Board::checkIndicies(int row, int col) {
    if (row < 0 || row >= numberRows) {
        return false;
    }
    else if (col < 0 || col >= numberRows) {
        return false;
    }
    return true;
}

void Board::solve() {
    int previousNumberClues;
    int i = 0;
    do {
        previousNumberClues = numberClues;
        checkAlmostRows(*this);
        checkSquares(*this);
        i++;
    } while (numberClues > previousNumberClues);
    std::cout << "number its:" << i << "\n";
}

bool const Board::rowContains(int index, int value) {
    checkIndicies(index, 0);
    for (int i = 0; i < numberRows; i++) {
        if (clues[index][i] == value)
            return true;
    }
    return false;
}

bool const Board::colContains(int index, int value) {
    checkIndicies(0, index);
    for (int i = 0; i < numberRows; i++) {
        if (clues[i][index] == value)
            return true;
    }
    return false;
}





void checkAlmostRows(Board& board) {
    //check for rows missing only one number

    for (int row = 0; row < board.numberRows; row++) {
        int emptyCol = -1;
        std::vector<int> numbersInRow;
        //iterate over the numbers in the row, putting numbers in it in numbersInRow
        //and keeping track of the last space that was empty
        for (int col = 0; col < board.numberRows; col++) {
            if (board.getClue(row, col) != -1) {
                numbersInRow.push_back(board.getClue(row, col));
            }
            else {
                emptyCol = col;
            }
        }
        if (numbersInRow.size() == board.numberRows - 1) {//check if there are exactly 1 numbers missing in the row
            //find the number that is not in the list and set it
            int absentNum = absentIn(numbersInRow, 1, board.numberRows)[0];
            board.setSpace(row, emptyCol, absentNum);
        }
    }
}

void checkSquares(Board& board) {
    int rowsPerSquare = board.rowsPerSquare;

    for (int square = 0; square < board.numberRows; square++) {
        std::vector<int> numsPresent;
        int startRow = (square / rowsPerSquare)*rowsPerSquare;
        int endRow = startRow + rowsPerSquare - 1;
        int startCol = square % rowsPerSquare * rowsPerSquare;
        int endCol = startCol + rowsPerSquare - 1;
        for (int row = startRow; row <= endRow; row++) {
            for (int col = startCol; col <= endCol; col++) {
                if (board.getClue(row, col) != -1)
                    numsPresent.push_back(board.getClue(row, col));
            }
        }
        std::vector<int> numsAbsent = absentIn(numsPresent, 1, board.numberRows);
        

        for (auto num : numsAbsent) {
            IntPair point = pointWhereNumCouldGo(board, square, num);
            if (point.x >= 0) {
                board.setSpace(point.x, point.y, num);
            }
        }
    }
}

IntPair pointWhereNumCouldGo(Board& board, int square, int num) {
    int rowsPerSquare = board.rowsPerSquare;
    int startRow = (square / rowsPerSquare) * rowsPerSquare;
    int endRow = startRow + rowsPerSquare - 1;
    int startCol = square % rowsPerSquare * rowsPerSquare;
    int endCol = startCol + rowsPerSquare - 1;

    std::vector<std::vector<bool>> possibleSpaces;
    int numberPossibilities = board.numberRows;
    //initialize vector representing the square in question
    for (int i = 0; i < rowsPerSquare; i++) {
        possibleSpaces.push_back(std::vector<bool>{});
        for (int j = 0; j < rowsPerSquare; j++) {
            possibleSpaces[i].push_back(board.getClue(startRow + i, startCol + j) == -1);
            if (possibleSpaces[i][j] == false)
                numberPossibilities--;
        }
    }
    if (numberPossibilities < 1)
        return IntPair(-1, -1);

    //check the rows and columns that this square intersects for instances of the num
    //and put numbers in the correspoinding row/column of this square2 to indicate
    //that the number can't go there
    for (int row = startRow; row <= endRow; row++) {
        if (board.rowContains(row, num)) {
            //fill row in square2 to indicate that num can't go there
            int relRow = row - startRow;
            for (int relCol = 0; relCol < rowsPerSquare; relCol++) {
                if (possibleSpaces[relRow][relCol] == true) {
                    possibleSpaces[relRow][relCol] = false;
                    numberPossibilities--;
                }
            }
        }
    }
    for (int col = startCol; col <= endCol; col++) {
        if (board.colContains(col, num)) {
            //fill row in square2 to indicate that num can't go there
            int relCol = col - startCol;
            for (int relRow = 0; relRow < rowsPerSquare; relRow++) {
                if (possibleSpaces[relRow][relCol] == true) {
                    possibleSpaces[relRow][relCol] = false;
                    numberPossibilities--;
                }
            }
        }
    }
    //if there are multiple possible spaces where the number could go
    if (numberPossibilities != 1) {
        return IntPair(-1, -1);
    }
    else {
        //find index of the one and only one available space
        for (int row = 0; row < possibleSpaces.size(); row++) {
            for (int col = 0; col < possibleSpaces[row].size(); col++) {
                if (possibleSpaces[row][col] == true)
                    return IntPair(row + startRow, col + startCol);
            }
        }
        //should never reach here
        return IntPair(-1, -1);
    }

}

std::ostream& operator<<(std::ostream& os, const Board& board)
{
    for (int i = 0; i < board.clues.size(); i++) {
        for (int j = 0; j < board.clues[i].size(); j++) {
            if (board.clues[i][j] == -1)
                std::cout << "~ ";
            else
                std::cout << board.clues[i][j] << " ";
            if (j % board.rowsPerSquare == board.rowsPerSquare - 1)
                std::cout << " ";
        }
        std::cout << "\n";
        if (i % board.rowsPerSquare == board.rowsPerSquare - 1)
            std::cout << "\n";
    }
    return os;
}
