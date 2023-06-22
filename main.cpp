#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Sudoku.h"



// 输出数独终局到文件
void outputToFile(const vector<vector<int>>& puzzle, const string& file) {
    ofstream outfile(file);
    if (outfile.is_open()) {
        for (const vector<int>& row : puzzle) {
            for (int num : row) {
                outfile << num << " ";
            }
            outfile << endl;
        }
        outfile.close();
        cout << "数独终局已写入文件 " << file << endl;
    }
    else {
        cout << "无法打开文件 " << file << " 以写入数独终局！" << endl;
    }
}

// 从文件读取数独问题
vector<vector<int>> readFromFile(const string& file) {
    vector<vector<int>> puzzle;
    ifstream infile(file);
    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            istringstream iss(line);
            vector<int> row;
            int num;
            while (iss >> num) {
                row.push_back(num);
            }
            if (row.size() == GRID_SIZE) {
                puzzle.push_back(row);
            }
            else {
                cout << "非法的数独问题格式！" << endl;
                puzzle.clear();
                break;
            }
        }
        infile.close();
    }
    else {
        cout << "无法打开文件 " << file << " 以读取数独问题！" << endl;
    }
    return puzzle;
}


// 检查数独终局的某个位置是否合法
bool isValid(const vector<vector<int>>& puzzle, int row, int col, int num) {
    // 检查行和列
    for (int i = 0; i < GRID_SIZE; ++i) {
        if (puzzle[row][i] == num || puzzle[i][col] == num) {
            return false;
        }
    }

    // 检查3x3子网格
    int subgridRow = SUBGRID_SIZE * (row / SUBGRID_SIZE);
    int subgridCol = SUBGRID_SIZE * (col / SUBGRID_SIZE);
    for (int i = 0; i < SUBGRID_SIZE; ++i) {
        for (int j = 0; j < SUBGRID_SIZE; ++j) {
            if (puzzle[subgridRow + i][subgridCol + j] == num) {
                return false;
            }
        }
    }

    return true;
}

// 使用回溯算法求解数独问题
bool solveSudoku(vector<vector<int>>& puzzle) {
    for (int row = 0; row < GRID_SIZE; ++row) {
        for (int col = 0; col < GRID_SIZE; ++col) {
            if (puzzle[row][col] == 0) {
                for (int num = 1; num <= GRID_SIZE; ++num) {
                    if (isValid(puzzle, row, col, num)) {
                        puzzle[row][col] = num;
                        if (solveSudoku(puzzle)) {
                            return true;
                        }
                        puzzle[row][col] = 0;  // 回溯
                    }
                }
                return false;
            }
        }
    }
    return true;
}


int main() {
    srand(time(0));

    // 生成数独终局
    SudokuBoard board;
    board.generateFinal();
    vector<vector<int>> puzzle = board.getGrid();
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
     
   // vector<vector<int>> puzzle(GRID_SIZE, vector<int>(GRID_SIZE, 0));
    //generateSudoku(puzzle);

    // 输出数独终局到文件
    /*string outputFile = "sudoku_terminus.txt";
    outputToFile(puzzle, outputFile);

    // 从文件读取数独问题
    string inputFile = "sudoku_problem.txt";
    vector<vector<int>> problem = readFromFile(inputFile);
    if (!problem.empty()) {
        // 求解数独问题
        solveSudoku(problem);

        // 输出结果到文件
        string outputSolution = "sudoku_solution.txt";
        outputToFile(problem, outputSolution);
    }*/

    return 0;
}