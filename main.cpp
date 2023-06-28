#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Sudoku.h"
#include <cstring>

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

// ��������վֵ��ļ�
void outputToFile(const vector<vector<int>>& puzzle, ofstream& outfile) {
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
}

// ���ļ���ȡ��������
vector<vector<int>> readFromFile(ifstream& infile) {
    vector<vector<int>> puzzle;
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
            if(row.size() == 0 &&puzzle.size()==GRID_SIZE){
                return puzzle;
            }
            print(puzzle);
            cout << "�Ƿ������������ʽ��" << endl;
            puzzle.clear();
            break;
        }
    }
    return puzzle;
}

//��ָ���վ�finalPuzzle�����ڿ���ָ����low~high��������Ϸ��uniqueΪ�Ƿ���Ҫ����Ψһ��ı�־
vector<vector<int>> generateSpecifiedGame(vector<vector<int>> finalPuzzle ,int low, int high, bool unique){
    SudokuBoard board_finalSet(finalPuzzle);

}

void nInsProcess(int argc, char* argv[]){
    vector<vector<vector<int>>> puzzles;
    ifstream inFile("sudoku_final_set.txt");
    ofstream outFile("sudoku_game.txt");
    if(!inFile.is_open()){
        cout << "�޷����ļ� sudoku_final_set.txt �Զ�ȡ�����վ֣�" << endl;
        return;
    }
    if(!outFile.is_open()){
        cout << "�޷����ļ� sudoku_game.txt ��д�����ɵ�������Ϸ��" << endl;
        return;
    }
    if(argc==3){
        int num = atoi(argv[2]);
        for(int i=0;i<num;i++){
            if (!inFile.eof()){
                vector<vector<int>> puzzle = readFromFile(inFile);
                SudokuBoard board_gameSet(puzzle);
                board_gameSet.solveGame(0, 0);
                vector<vector<int>> solution = board_gameSet.getGrid();
                print(solution);
                // ���������ļ�
                outputToFile(solution, outFile);
                if(!inFile.eof()){
                    outFile<<endl;
                }
            }
        }
    } else if(argc==4){

    }else if(argc==5){

    }else if(argc==6){

    }
}

void help(){
    cout<<"�����÷���"<<endl;
    cout<<"-c num ������num���������̣�Ĭ�������sudoku_final_set.txt��"<<endl;
    cout<<"-c num filePath ������num���������̵�filePath��Ӧ�ļ���"<<endl;
    cout<<"-s filePath �� ��filePath�ж�ȡ���ɸ�������Ϸ��������⣬��������������sudoku_solution.txt��"<<endl;
    cout<<"-n num ������num��������Ϸ���������sudoku_game.txt�У�Ĭ���Ѷ�Ϊ�еȣ�"<<endl;
    cout<<"-n num -m level �� ����num��ָ���Ѷȵ�������Ϸ���������sudoku_game.txt�С�level��1��3��ʾ���׵���"<<endl;
    cout<<"-n num -r low~high �� ����num���ڿ�����low~high֮���������Ϸ���������sudoku_game.txt��"<<endl;
    cout<<"-n num -u �� ����num������Ψһ���������Ϸ���������sudoku_game.txt��"<<endl;
    cout<<"-n num -u -m level �� ����num������Ψһ���ָ���Ѷȵ�������Ϸ���������sudoku_game.txt�С�level��1��3��ʾ���׵���"<<endl;
    cout<<"-n num -u -r low~high �� ����num������Ψһ����ڿ�����low~high֮���������Ϸ���������sudoku_game.txt��"<<endl;
}

int main(int argc, char* argv[]) {

    srand(time(0));

    if(argc<3){
        cout<<"�����������㣬��������ȷ�Ĳ���"<<endl;
        help();
        return 0;
    }
    if(!strcmp(argv[1],"-c")){
        string filePath;
        if(argc==3){
            filePath="sudoku_final_set.txt";
        }else if(argc==4){
            filePath=argv[3];
        }else{
            cout<<"��������Ƿ�����������ȷ�Ĳ���"<<endl;
            help();
            return 0;
        }
        ofstream outFile(filePath);
        int num = atoi(argv[2]);
        if(outFile.is_open()){
            for(int i=0;i<num;i++) {
                SudokuBoard board_final;
                board_final.generateFinal();
                vector<vector<int>> finalSet = board_final.getGrid();
                //��������վֵ��ļ�
                outputToFile(finalSet, outFile);
                if(i!=num-1) {
                    outFile << endl;
                }
            }
            outFile.close();
            cout << "��д���ļ� " << filePath << endl;
        }else{
            cout << "�޷����ļ� " << filePath << " ��д��������" << endl;
        }
    }else if(!strcmp(argv[1],"-s")){
        if(argc!=3){
            cout<<"��������Ƿ�����������ȷ�Ĳ���"<<endl;
            help();
            return 0;
        }
        string filePath=argv[2];
        ifstream inFile(filePath);
        ofstream outFile("sudoku_solution.txt");
        if (inFile.is_open() && outFile.is_open()) {
            while (!inFile.eof()){
                cout<<"���������Ϸ��"<<endl;
                vector<vector<int>> game = readFromFile(inFile);
                SudokuBoard board_gameSet(game);
                print(game);
                cout<<"�����⣺"<<endl;
                board_gameSet.solveGame(0, 0);
                vector<vector<int>> solution = board_gameSet.getGrid();
                print(solution);
                // ���������ļ�
                outputToFile(solution, outFile);
                if(!inFile.eof()){
                    outFile<<endl;
                }
            }
        }else {
            cout << "���ļ� "<<filePath<<" �� sudoku_solution.txt ʧ�ܣ�" << endl;
        }
    }else if(!strcmp(argv[1],"-n")){
        if(argc>6){
            cout<<"��������Ƿ�����������ȷ�Ĳ���"<<endl;
            help();
            return 0;
        }else{
            nInsProcess(argc,argv);
        }
    }else{
        cout<<"��������Ƿ�����������ȷ�Ĳ���"<<endl;
        help();
    }
    return 0;
}