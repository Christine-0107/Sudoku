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

    }else if(!strcmp(argv[1],"-n")){

    }else{
        cout<<"��������Ƿ�����������ȷ�Ĳ���"<<endl;
        help();
    }
    return 0;
}