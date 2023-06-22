#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Sudoku.h"



// ��������վֵ��ļ�
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
        cout << "�����վ���д���ļ� " << file << endl;
    }
    else {
        cout << "�޷����ļ� " << file << " ��д�������վ֣�" << endl;
    }
}

// ���ļ���ȡ��������
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
                cout << "�Ƿ������������ʽ��" << endl;
                puzzle.clear();
                break;
            }
        }
        infile.close();
    }
    else {
        cout << "�޷����ļ� " << file << " �Զ�ȡ�������⣡" << endl;
    }
    return puzzle;
}


// ��������վֵ�ĳ��λ���Ƿ�Ϸ�
bool isValid(const vector<vector<int>>& puzzle, int row, int col, int num) {
    // ����к���
    for (int i = 0; i < GRID_SIZE; ++i) {
        if (puzzle[row][i] == num || puzzle[i][col] == num) {
            return false;
        }
    }

    // ���3x3������
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

// ʹ�û����㷨�����������
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
                        puzzle[row][col] = 0;  // ����
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

    // ���������վ�
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

    // ��������վֵ��ļ�
    /*string outputFile = "sudoku_terminus.txt";
    outputToFile(puzzle, outputFile);

    // ���ļ���ȡ��������
    string inputFile = "sudoku_problem.txt";
    vector<vector<int>> problem = readFromFile(inputFile);
    if (!problem.empty()) {
        // �����������
        solveSudoku(problem);

        // ���������ļ�
        string outputSolution = "sudoku_solution.txt";
        outputToFile(problem, outputSolution);
    }*/

    return 0;
}