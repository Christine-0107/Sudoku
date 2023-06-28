#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Sudoku.h"
#include <cstring>


// 输出数独终局到文件
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

// 从文件读取数独问题
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
    cout<<"参数用法："<<endl;
    cout<<"-c num ：生成num个数独终盘，默认输出到sudoku_final_set.txt中"<<endl;
    cout<<"-c num filePath ：生成num个数独终盘到filePath对应文件中"<<endl;
    cout<<"-s filePath ： 从filePath中读取若干个数独游戏，进行求解，并将求解结果输出到sudoku_solution.txt中"<<endl;
    cout<<"-n num ：生成num个数独游戏，并输出到sudoku_game.txt中（默认难度为中等）"<<endl;
    cout<<"-n num -m level ： 生成num个指定难度的数独游戏，并输出到sudoku_game.txt中。level从1到3表示从易到难"<<endl;
    cout<<"-n num -r low~high ： 生成num个挖空数在low~high之间的数独游戏，并输出到sudoku_game.txt中"<<endl;
    cout<<"-n num -u ： 生成num个具有唯一解的数独游戏，并输出到sudoku_game.txt中"<<endl;
    cout<<"-n num -u -m level ： 生成num个具有唯一解的指定难度的数独游戏，并输出到sudoku_game.txt中。level从1到3表示从易到难"<<endl;
    cout<<"-n num -u -r low~high ： 生成num个具有唯一解的挖空数在low~high之间的数独游戏，并输出到sudoku_game.txt中"<<endl;
}

int main(int argc, char* argv[]) {

    srand(time(0));

    if(argc<3){
        cout<<"参数个数不足，请输入正确的参数"<<endl;
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
            cout<<"参数输入非法，请输入正确的参数"<<endl;
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
                //输出数独终局到文件
                outputToFile(finalSet, outFile);
                if(i!=num-1) {
                    outFile << endl;
                }
            }
            outFile.close();
            cout << "已写入文件 " << filePath << endl;
        }else{
            cout << "无法打开文件 " << filePath << " 以写入数独！" << endl;
        }
    }else if(!strcmp(argv[1],"-s")){

    }else if(!strcmp(argv[1],"-n")){

    }else{
        cout<<"参数输入非法，请输入正确的参数"<<endl;
        help();
    }
    return 0;
}