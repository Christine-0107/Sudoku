# include <iostream>
# include <vector>
using namespace std;

const int GRID_SIZE = 9;
const int SUBGRID_SIZE = 3;

class SudokuBoard {
private:
	vector<vector<int>> grid; //9*9
	vector<vector<int>> gridCenter; //�м��3*3
	void fillCenter(); //�����ĵ�9����
	void swapRow(int m, int n, vector<vector<int>>& board);
	void swapCol(int m, int n, vector<vector<int>>& board);
	void selectBlank(int num);
public:
	SudokuBoard() : grid(GRID_SIZE, vector<int>(GRID_SIZE, 0)), gridCenter(SUBGRID_SIZE, vector<int>(SUBGRID_SIZE, 0)) {}
	vector<vector<int>> getGrid();
	void generateFinal();
	void generateGame(int num);
};