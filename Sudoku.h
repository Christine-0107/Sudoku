#ifndef SUDOKU_H
#define SUDOKU_H

# include <iostream>
# include <vector>
using namespace std;

const int GRID_SIZE = 9;
const int SUBGRID_SIZE = 3;

void print(vector<vector<int>>& puzzle);

class SudokuBoard {
private:
	vector<vector<int>> grid; //9*9
	bool isValid(vector<vector<int>>& board, int row, int col, int num);
	vector<int> selectBlank(int num);
	int generateUnique(vector<int>& blanks, vector<vector<int>>& gameTemp);
public:
    bool judgeUnique(vector<vector<int>>& gameTemp, int row, int col, int& solutions);
	SudokuBoard() : grid(GRID_SIZE, vector<int>(GRID_SIZE, 0)){}
	SudokuBoard(vector<vector<int>>& board) { this->grid = board; }
	vector<vector<int>> getGrid();
	bool generateFinal();
    vector<vector<int>> generateGame(bool unique, int low, int high, int &count, int& realBlankNum, bool &success);
	bool solveGame(int row, int col);
};

#endif