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
        cout << "��д���ļ� " << file << endl;
    }
    else {
        cout << "�޷����ļ� " << file << " ��д��������" << endl;
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

//��ӡ
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

    // ���������վ�
    SudokuBoard board_final;
    board_final.generateFinal();
    vector<vector<int>> finalSet = board_final.getGrid();
    
    //��������վֵ��ļ�
    string outputFinal = "sudoku_final_set.txt";
    outputToFile(finalSet, outputFinal);

    //���ļ��ж�ȡ�����վ�
    vector<vector<int>> puzzle = readFromFile(outputFinal);
    SudokuBoard board_finalSet(puzzle);
    cout << "�����վ�" << endl;
    print(puzzle);

    //����������Ϸ
    int realBlank = 40;
    vector<vector<int>> gameSet = board_finalSet.generateGame(true, 40, realBlank);
    cout << "������Ϸ" << endl;
    print(gameSet);
    cout << "�ո���" << realBlank << endl;

    //���������Ϸ���ļ�
    string outputGame = "sudoku_game.txt";
    outputToFile(gameSet, outputGame);

    //���ļ��ж�ȡ������Ϸ
    vector<vector<int>> game = readFromFile(outputGame);
    SudokuBoard board_gameSet(game);

    //���������Ϸ
    board_gameSet.solveGame(0, 0);
    vector<vector<int>> solution = board_gameSet.getGrid();
    cout << "������" << endl;
    print(solution);

    // ���������ļ�
    string outputSolution = "sudoku_solution.txt";
    outputToFile(solution, outputSolution);

    return 0;
}