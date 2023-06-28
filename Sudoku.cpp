//Todo:
//1. ����������Ϸ�����ļ�
//2. -s ��ȡ������Ϸ����𲢴����ļ�
//3. -c ������������
//4. -n ������Ϸ����
//5. -n -m �����Ѷ�
//6. -n -r �ڿշ�Χ
//7. -n -u Ψһ��

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
	// ����к����Ƿ����ظ�����
	for (int i = 0; i < GRID_SIZE; i++) {
		if (board[row][i] == num || board[i][col] == num)
			return false;
	}
	// ���3x3С�Ź����Ƿ����ظ�����
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
	//����0~80���������
	vector<int> numbers(81);
	for (int i = 0; i < 81; i++) {
		numbers[i] = i;
	}
	random_shuffle(numbers.begin(), numbers.end());

	//����ǰnum��
	vector<int> ret;
	for (int i = 0; i < num; i++) {
		ret.push_back(numbers[i]);
	}
	return ret;
}

bool SudokuBoard::solveGame(int row, int col) {
	// �ﵽ�������ӵ����һ��λ�ã����и����Ѿ�������
	if (row == GRID_SIZE - 1 && col == GRID_SIZE)
		return true;

	// ��ǰ�������ϣ�������һ�е���ʼλ��
	if (col == GRID_SIZE) {
		row++;
		col = 0;
	}

	// ��ǰ�����Ѿ������֣��������������һ������
	if (this->grid[row][col] != 0)
		return solveGame(row, col + 1);

	// ����1��9�������
	vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	random_shuffle(nums.begin(), nums.end());

	// ������䵱ǰ����
	for (int i = 0; i < nums.size(); i++) {
		if (isValid(this->grid, row, col, nums[i])) {
			this->grid[row][col] = nums[i];
			if (solveGame(row, col + 1))
				return true;
			// ���ݣ�������һ������
			this->grid[row][col] = 0;
		}
	}

	return false;
}

bool SudokuBoard::judgeUnique(vector<vector<int>>& gameTemp, int row, int col, int& solutions) {
	// �ﵽ�������ӵ����һ��λ�ã����и����Ѿ�������
	if (row == GRID_SIZE - 1 && col == GRID_SIZE) {
		solutions++;
		return solutions > 1;  // ������ڶ���⣬�򷵻�true
	}

	// ��ǰ�������ϣ�������һ�е���ʼλ��
	if (col == GRID_SIZE) {
		row++;
		col = 0;
	}

	// ��ǰ�����Ѿ������֣��������������һ������
	if (gameTemp[row][col] != 0)
		return judgeUnique(gameTemp, row, col + 1, solutions);

	// ����1��9�������
	vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	random_shuffle(nums.begin(), nums.end());

	// ������䵱ǰ����
	for (int num : nums) {
		if (isValid(gameTemp, row, col, num)) {
			gameTemp[row][col] = num;
			if (judgeUnique(gameTemp, row, col + 1, solutions))
				return true;
			// ���ݣ�������һ������
			gameTemp[row][col] = 0;
		}
	}

	return false;
}

int SudokuBoard::generateUnique(vector<int>& blanks, vector<vector<int>>& gameTemp) {
	int left = 0;
	int right = blanks.size() - 1;
	int pos = -1; //��һ�����ֶ����ڿ�λ�õ�blanks�±�

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

	//pos��ֵ�������մﵽΨһ��ʱ�ڿյĸ���
	return pos;
	
}

bool SudokuBoard::generateFinal() {
	return solveGame(0, 0);
}

vector<vector<int>> SudokuBoard::generateGame1(bool flag, int num, int& realBlank, int difficulty) {
	//1. �ڿ�
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
	cout << "��ʼ���ɵ���Ϸ" << endl;
	print1(gameTemp);
	//2. ��Ҫ��Ψһ�⣬���ʱ����Ψһ�⣬ ֱ�ӷ���
	int solutions = 0;
	judgeUnique(gameTemp, 0, 0, solutions);
	if (!flag || solutions == 1) {
		return gameTemp;
	}
	//3. ����Ψһ��
	int blankNum = generateUnique(blanks, gameTemp);
	realBlank = blankNum;
	return gameTemp;
}

vector<vector<int>> SudokuBoard::generateGame(bool unique, int low, int high, int &count, int& realBlankNum, bool& success){
    //1. �ڿ�
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
//    cout << "��ʼ���ɵ���Ϸ" << endl;
//    print1(gameTemp);
    //2. ��Ҫ��Ψһ�⣬���ʱ����Ψһ�⣬ ֱ�ӷ���
    int solutions = 0;
    judgeUnique(gameTemp, 0, 0, solutions);
    if (unique && solutions != 1) {
        //3. ����Ψһ��
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