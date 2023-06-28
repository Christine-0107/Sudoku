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

void print1(vector<vector<int>>& puzzle) {
	for (int i = 0; i < puzzle.size(); i++) {
		for (int j = 0; j < puzzle.size(); j++) {
            if(puzzle[i][j]==0){
                cout<<'$'<<" ";
            }else {
                cout << puzzle[i][j] << " ";
            }
		}
		cout << endl;
	}
}

vector<vector<int>> SudokuBoard::getGrid() {
	return this->grid;
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

bool SudokuBoard::isValid(vector<vector<int>>& board, int row, int col, int num) {
	// 检查行和列是否有重复数字
	for (int i = 0; i < GRID_SIZE; i++) {
		if (board[row][i] == num || board[i][col] == num)
			return false;
	}
	// 检查3x3小九宫格是否有重复数字
	int startRow = (row / SUBGRID_SIZE) * SUBGRID_SIZE;
	int startCol = (col / SUBGRID_SIZE) * SUBGRID_SIZE;
	for (int i = 0; i < SUBGRID_SIZE; i++) {
		for (int j = 0; j < SUBGRID_SIZE; j++) {
			if (board[startRow + i][startCol + j] == num)
				return false;
		}
	}
	return true;
}

vector<int> SudokuBoard::selectBlank(int num) {
	//生成0~80的随机排列
	vector<int> numbers(81);
	for (int i = 0; i < 81; i++) {
		numbers[i] = i;
	}
	random_shuffle(numbers.begin(), numbers.end());

	//返回前num个
	vector<int> ret;
	for (int i = 0; i < num; i++) {
		ret.push_back(numbers[i]);
	}
	return ret;
}

bool SudokuBoard::solveGame(int row, int col) {
	// 达到数独格子的最后一个位置，所有格子已经填充完毕
	if (row == GRID_SIZE - 1 && col == GRID_SIZE)
		return true;

	// 当前行填充完毕，进入下一行的起始位置
	if (col == GRID_SIZE) {
		row++;
		col = 0;
	}

	// 当前格子已经有数字，跳过继续填充下一个格子
	if (this->grid[row][col] != 0)
		return solveGame(row, col + 1);

	// 数字1到9随机排序
	vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	random_shuffle(nums.begin(), nums.end());

	// 尝试填充当前格子
	for (int i = 0; i < nums.size(); i++) {
		if (isValid(this->grid, row, col, nums[i])) {
			this->grid[row][col] = nums[i];
			if (solveGame(row, col + 1))
				return true;
			// 回溯，尝试下一个数字
			this->grid[row][col] = 0;
		}
	}

	return false;
}

bool SudokuBoard::judgeUnique(vector<vector<int>>& gameTemp, int row, int col, int& solutions) {
	// 达到数独格子的最后一个位置，所有格子已经填充完毕
	if (row == GRID_SIZE - 1 && col == GRID_SIZE) {
		solutions++;
		return solutions > 1;  // 如果存在多个解，则返回true
	}

	// 当前行填充完毕，进入下一行的起始位置
	if (col == GRID_SIZE) {
		row++;
		col = 0;
	}

	// 当前格子已经有数字，跳过继续填充下一个格子
	if (gameTemp[row][col] != 0)
		return judgeUnique(gameTemp, row, col + 1, solutions);

	// 数字1到9随机排序
	vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	random_shuffle(nums.begin(), nums.end());

	// 尝试填充当前格子
	for (int num : nums) {
		if (isValid(gameTemp, row, col, num)) {
			gameTemp[row][col] = num;
			if (judgeUnique(gameTemp, row, col + 1, solutions))
				return true;
			// 回溯，尝试下一个数字
			gameTemp[row][col] = 0;
		}
	}

	return false;
}

int SudokuBoard::generateUnique(vector<int>& blanks, vector<vector<int>>& gameTemp) {
	int left = 0;
	int right = blanks.size() - 1;
	int pos = -1; //第一个出现多解的挖空位置的blanks下标

	while (left <= right) {
		int mid = left + (right - left) / 2;
		for (int i = left; i <= mid; i++) {
			int row = blanks[i] / GRID_SIZE;
			int col = blanks[i] % GRID_SIZE;
			gameTemp[row][col] = 0;
		}
		for (int i = mid + 1; i < blanks.size(); i++) {
			int row = blanks[i] / GRID_SIZE;
			int col = blanks[i] % GRID_SIZE;
			gameTemp[row][col] = this->grid[row][col];
		}
		int solutions = 0;
		judgeUnique(gameTemp, 0, 0, solutions);
		if (solutions == 1) {
			left = mid + 1;
		}
		else {
			pos = mid;
			right = mid - 1;
		}
	}

	for (int i = 0; i < pos; i++) {
		int row = blanks[i] / GRID_SIZE;
		int col = blanks[i] % GRID_SIZE;
		gameTemp[row][col] = 0;
	}
	for (int i = pos; i < blanks.size(); i++) {
		int row = blanks[i] / GRID_SIZE;
		int col = blanks[i] % GRID_SIZE;
		gameTemp[row][col] = this->grid[row][col];
	}

	//pos的值就是最终达到唯一解时挖空的个数
	return pos;
	
}

bool SudokuBoard::generateFinal() {
	return solveGame(0, 0);
}

vector<vector<int>> SudokuBoard::generateGame1(bool flag, int num, int& realBlank, int difficulty) {
	//1. 挖空
	vector<vector<int>> gameTemp = this->grid;
	switch (difficulty) {
	case 1:
		num = 35;
		break;
	case 2:
		num = 45;
		break;
	case 3:
		num = 55;
		break;
    default:
        num=45;
	}
	vector<int> blanks = selectBlank(num);
	for (int i = 0; i < blanks.size(); i++) {
		int row = blanks[i] / GRID_SIZE;
		int col = blanks[i] % GRID_SIZE;
		gameTemp[row][col] = 0;
	}
	cout << "初始生成的游戏" << endl;
	print1(gameTemp);
	//2. 不要求唯一解，或此时就是唯一解， 直接返回
	int solutions = 0;
	judgeUnique(gameTemp, 0, 0, solutions);
	if (!flag || solutions == 1) {
		return gameTemp;
	}
	//3. 生成唯一解
	int blankNum = generateUnique(blanks, gameTemp);
	realBlank = blankNum;
	return gameTemp;
}

vector<vector<int>> SudokuBoard::generateGame(bool unique, int low, int high, int &count, int& realBlankNum, bool& success){
    //1. 挖空
    vector<vector<int>> gameTemp = this->grid;
    if(count>=5){
        success= false;
        return gameTemp;
    }
    vector<int> blanks = selectBlank(high);
    for (int i = 0; i < blanks.size(); i++) {
        int row = blanks[i] / GRID_SIZE;
        int col = blanks[i] % GRID_SIZE;
        gameTemp[row][col] = 0;
    }
//    cout << "初始生成的游戏" << endl;
//    print1(gameTemp);
    //2. 不要求唯一解，或此时就是唯一解， 直接返回
    int solutions = 0;
    judgeUnique(gameTemp, 0, 0, solutions);
    if (unique && solutions != 1) {
        //3. 生成唯一解
        int blankNum = generateUnique(blanks, gameTemp);
        if(blankNum<low){
            count++;
            gameTemp = generateGame(true,low,high,count,success);
        }else{
            realBlankNum = blankNum;
            success = true;
        }
    }else{
        realBlankNum=high;
    }
    return gameTemp;
}