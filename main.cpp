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
        cout << "已写入文件 " << file << endl;
    }
    else {
        cout << "无法打开文件 " << file << " 以写入数独！" << endl;
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

//打印
void print(vector<vector<int>>& puzzle) {
    for (int i = 0; i < puzzle.size(); i++) {
        for (int j = 0; j < puzzle.size(); j++) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));

    // 生成数独终局
    SudokuBoard board_final;
    board_final.generateFinal();
    vector<vector<int>> finalSet = board_final.getGrid();
    
    //输出数独终局到文件
    string outputFinal = "sudoku_final_set.txt";
    outputToFile(finalSet, outputFinal);

    //从文件中读取数独终局
    vector<vector<int>> puzzle = readFromFile(outputFinal);
    SudokuBoard board_finalSet(puzzle);
    cout << "数独终局" << endl;
    print(puzzle);

    //生成数独游戏
    int realBlank = 40;
    vector<vector<int>> gameSet = board_finalSet.generateGame(true, 40, realBlank);
    cout << "数独游戏" << endl;
    print(gameSet);
    cout << "空格数" << realBlank << endl;

    //输出数独游戏到文件
    string outputGame = "sudoku_game.txt";
    outputToFile(gameSet, outputGame);

    //从文件中读取数独游戏
    vector<vector<int>> game = readFromFile(outputGame);
    SudokuBoard board_gameSet(game);

    //求解数独游戏
    board_gameSet.solveGame(0, 0);
    vector<vector<int>> solution = board_gameSet.getGrid();
    cout << "数独解" << endl;
    print(solution);

    // 输出结果到文件
    string outputSolution = "sudoku_solution.txt";
    outputToFile(solution, outputSolution);

    return 0;
}