//Todo:
//1. 生成数独游戏存入文件
//2. -s 读取数独游戏，解答并存入文件
//3. -c 数独终盘数量
//4. -n 数独游戏数量
//5. -n -m 数独难度
//6. -n -r 挖空范围
//7. -n -u 唯一解

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Sudoku.h"
using namespace std;
const int K = 5;

void fillPartOfBoard(vector<vector<int>>& board1, vector<vector<int>>& board2, int row, int col) {
	//board1是9*9矩阵，board2是3*3矩阵
	//将board2填充到board1行列均从(row,col)开始的3*3区域
	for (int i = 0; i < board2.size(); i++) {
		for (int j = 0; j < board2.size(); j++) {
			board1[i + row][j + col] = board2[i][j];
		}
	}
}

int* select2Nums() {
	int groups[3][3] = {
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	};
	srand(time(0));
	// 随机选择一组
	int groupIndex = rand() % 3;

	// 从选择的组中选取两个数
	int* ret = new int[2];
	ret[0] = rand() % 3;
	ret[1] = rand() % 3; 
	return ret;
}

vector<vector<int>> SudokuBoard::getGrid() {
	return this->grid;
}

void SudokuBoard::fillCenter() {
	//先初始化为0
	this->grid.assign(GRID_SIZE, vector<int>(GRID_SIZE, 0));
	this->gridCenter.assign(SUBGRID_SIZE, vector<int>(SUBGRID_SIZE, 0));
	//初始化要填充的数字序列
	int count = 0;
	vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	random_shuffle(nums.begin(), nums.end());
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->gridCenter[i][j] = nums[count++];
		}
	}
	fillPartOfBoard(this->grid, this->gridCenter, 3, 3);
}

void SudokuBoard::swapRow(int m, int n, vector<vector<int>>& board) {
	int temp;
	for (int j = 0; j < board.size(); j++) {
		temp = board[m][j];
		board[m][j] = board[n][j];
		board[n][j] = temp;
	}
}

void SudokuBoard::swapCol(int m, int n, vector<vector<int>>& board) {
	int temp;
	for (int i = 0; i < board.size(); i++) {
		temp = board[i][m];
		board[i][m] = board[i][n];
		board[i][n] = temp;
	}
}

void SudokuBoard::generateFinal() {
	//将9*9看成9个3*3，标号分别是1~9号
	//中心格子（5号）的序列是(1,2,3)，两侧只能是(2,3,1)(3,1,2)或(3,1,2)(2,3,1)
	//0代表(2,3,1)，1代表(3,1,2)
	fillCenter();
	int num1;
	srand(time(0));
	
	//1.对5号行变换填4号，6号
	num1 = rand() % 2;
	vector<vector<int>> boardRow_231 = this->gridCenter;
	swapRow(0, 1, boardRow_231); //213
	swapRow(1, 2, boardRow_231); //231
	vector<vector<int>> boardRow_312 = this->gridCenter;
	swapRow(0, 2, boardRow_312); //321
	swapRow(1, 2, boardRow_312); //312
	if (num1 == 0) { // 4号231，6号312
		fillPartOfBoard(this->grid, boardRow_231, 3, 0);
		fillPartOfBoard(this->grid, boardRow_312, 3, 6);
	}
	else {
		fillPartOfBoard(this->grid, boardRow_312, 3, 0);
		fillPartOfBoard(this->grid, boardRow_231, 3, 6);
	}

	//2.对5号进行列变换填2号，8号
	num1 = rand() % 2;
	vector<vector<int>> boardCol_231 = this->gridCenter;
	swapCol(0, 1, boardCol_231); 
	swapCol(1, 2, boardCol_231); 
	vector<vector<int>> boardCol_312 = this->gridCenter;
	swapCol(0, 2, boardCol_312); 
	swapCol(1, 2, boardCol_312); 
	vector<vector<int>> board_2;
	vector<vector<int>> board_8;
	if (num1 == 0) { // 2号231，8号312
		fillPartOfBoard(this->grid, boardCol_231, 0, 3);
		fillPartOfBoard(this->grid, boardCol_312, 6, 3);
		board_2 = boardCol_231;
		board_8 = boardCol_312;
	}
	else {
		fillPartOfBoard(this->grid, boardCol_312, 0, 3);
		fillPartOfBoard(this->grid, boardCol_231, 6, 3);
		board_2 = boardCol_312;
		board_8 = boardCol_231;
	}

	//3.对2号进行行变换填1号，3号
	num1 = rand() % 2;
	vector<vector<int>> boardUp_231 = board_2;
	swapRow(0, 1, boardUp_231);
	swapRow(1, 2, boardUp_231);
	vector<vector<int>> boardUp_312 = board_2;
	swapRow(0, 2, boardUp_312); 
	swapRow(1, 2, boardUp_312); 
	if (num1 == 0) { //1号231，3号312
		fillPartOfBoard(this->grid, boardUp_231, 0, 0);
		fillPartOfBoard(this->grid, boardUp_312, 0, 6);
	}
	else {
		fillPartOfBoard(this->grid, boardUp_312, 0, 0);
		fillPartOfBoard(this->grid, boardUp_231, 0, 6);
	}

	//4.对8号进行行变换填7号，9号
	num1 = rand() % 2;
	vector<vector<int>> boardDown_231 = board_8;
	swapRow(0, 1, boardDown_231);
	swapRow(1, 2, boardDown_231);
	vector<vector<int>> boardDown_312 = board_8;
	swapRow(0, 2, boardDown_312);
	swapRow(1, 2, boardDown_312);
	if (num1 == 0) { //7号231，9号312
		fillPartOfBoard(this->grid, boardDown_231, 6, 0);
		fillPartOfBoard(this->grid, boardDown_312, 6, 6);
	}
	else {
		fillPartOfBoard(this->grid, boardDown_312, 6, 0);
		fillPartOfBoard(this->grid, boardDown_231, 6, 6);
	}

	//5.随机进行行列变换K次
	for (int i = 0; i < K; i++) {
		int* ret = new int[2];
		ret = select2Nums();
		swapRow(ret[0], ret[1], this->grid);
		ret = select2Nums();
		swapCol(ret[0], ret[1], this->grid);
	}


}

void SudokuBoard::generateGame(int num) {
	srand(time(0));
	while (num > 0) {
		int row = rand() % 9;
		int col = rand() % 9;
		if (this->grid[row][col] != 0) {
			this->grid[row][col] = 0;
			num--;
		}
	}
}
