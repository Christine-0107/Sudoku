# include <iostream>
# include <vector>
using namespace std;

const int GRID_SIZE = 9;
const int SUBGRID_SIZE = 3;

class SudokuBoard {
private:
	vector<vector<int>> grid; //9*9
	void swapRow(int m, int n, vector<vector<int>>& board);
	void swapCol(int m, int n, vector<vector<int>>& board);
	bool isValid(int row, int col, int num);
	vector<int> selectBlank(int num);
	int generateUnique(vector<int>& blanks, vector<vector<int>>& gameTemp);
public:
	SudokuBoard() : grid(GRID_SIZE, vector<int>(GRID_SIZE, 0)){}
	SudokuBoard(vector<vector<int>>& board) { this->grid = board; }
	vector<vector<int>> getGrid();
	bool generateFinal(int row, int col);
	vector<vector<int>> generateGame(bool flag, int num, int& realBlank);
	bool solveGame(vector<vector<int>>& game);
};