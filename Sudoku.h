# include <iostream>
# include <vector>
using namespace std;

const int GRID_SIZE = 9;
const int SUBGRID_SIZE = 3;

class SudokuBoard {
private:
	vector<vector<int>> grid; //9*9
	vector<vector<int>> gridCenter; //中间的3*3
	void fillCenter(); //填中心的9宫格
	void swapRow(int m, int n, vector<vector<int>>& board);
	void swapCol(int m, int n, vector<vector<int>>& board);
	vector<int> selectBlank(int num);
	int generateUnique(vector<int>& blanks, vector<vector<int>>& gameTemp);
public:
	SudokuBoard() : grid(GRID_SIZE, vector<int>(GRID_SIZE, 0)), gridCenter(SUBGRID_SIZE, vector<int>(SUBGRID_SIZE, 0)) {}
	SudokuBoard(vector<vector<int>>& board) { this->grid = board; }
	vector<vector<int>> getGrid();
	void generateFinal();
	vector<vector<int>> generateGame(bool flag, int num, int& realBlank);
	bool solveGame(vector<vector<int>>& game);
};