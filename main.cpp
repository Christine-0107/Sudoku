#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Sudoku.h"
#include <cstring>


// ��������վֵ��ļ�
void outputToFile(const vector<vector<int>>& puzzle, const string& file) {
    ofstream outfile(file);
    if (outfile.is_open()) {
        for (const vector<int>& row : puzzle) {
            for (int num : row) {
                if(num==0){
                    outfile<<'$'<<" ";
                }else {
                    outfile << num << " ";
                }
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
            char c;
            int num;
            while (iss >> c) {
                if(c=='$'){
                    num=0;
                }else{
                    num=c-'0';
                }
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
            if(puzzle[i][j]==0){
                cout<<'$'<<" ";
            }else{
                cout << puzzle[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void help(){
    cout<<"�����÷���"<<endl;
    cout<<"-c num ������num����������"<<endl;
    cout<<"-c num filePath ������num���������̵�filePath��Ӧ�ļ���"<<endl;
    cout<<"-s filePath �� ��filePath�ж�ȡ���ɸ�������Ϸ��������⣬��������������sudoku_solution.txt��"<<endl;
    cout<<"-n num ������num��������Ϸ���������sudoku_game.txt�У�Ĭ���Ѷ�Ϊ�еȣ�"<<endl;
    cout<<"-n num -m level �� ����num��ָ���Ѷȵ�������Ϸ���������sudoku_game.txt�С�level��1��3��ʾ���׵���"<<endl;
    cout<<"-n num -r low~high �� ����num���ڿ�����low~high֮���������Ϸ���������sudoku_game.txt��"<<endl;
    cout<<"-n num -u �� ����num������Ψһ���������Ϸ���������sudoku_game.txt��"<<endl;
}

int main(int argc, char* argv[]) {

    srand(time(0));

    if(argc<3){
        cout<<"�����������㣬��������ȷ�Ĳ���"<<endl;
        help();
        return 0;
    }
    if(!strcmp(argv[1],"-c")){

    }else if(!strcmp(argv[1],"-s")){

    }else if(!strcmp(argv[1],"-n")){

    }else{
        cout<<"��������Ƿ�����������ȷ�Ĳ���"<<endl;
        help();
    }

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
    int realBlank = 45; //����û�û��Ҫ��Ĭ�ϴ�45���տ�ʼ
    int difficulty = 2;  //�Ѷȵȼ�1��20~35  �ȼ�2��36~45  �ȼ�3��46~55
    vector<vector<int>> gameSet = board_finalSet.generateGame(true, 40, realBlank, difficulty);
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