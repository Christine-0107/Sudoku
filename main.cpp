#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Sudoku.h"
#include <cstring>

void help();

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

void paramError(){
    cout << "参数输入非法，请输入正确的参数" << endl;
    help();
}

// 从文件读取数独问题
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
            cout << "非法的数独问题格式！" << endl;
            puzzle.clear();
            break;
        }
    }
    return puzzle;
}

bool levelConvert(int level,int&low,int &high){
    switch (level) {
        case 1:
            low=20;
            high=35;
            return true;
        case 2:
            low=36;
            high=45;
            return true;
        case 3:
            low=46;
            high=55;
            return true;
        default:
            return false;
    }
}

bool gerLowHigh(string arg, int &low,int&high){
    int size=arg.size();
    if(size==0){
        return false;
    }
    for(int i=0;i< size;i++){

    }
}

//-n相关指令的处理，生成指定的数独游戏。数独游戏难度等级1：20~35  等级2：36~45  等级3：46~55
void nInsProcess(int argc, char* argv[]){
    vector<vector<vector<int>>> puzzles;
    ifstream inFile("sudoku_final_set.txt");
    ofstream outFile("sudoku_game.txt");
    if(!inFile.is_open()){
        cout << "无法打开文件 sudoku_final_set.txt 以读取数独终局！" << endl;
        return;
    }
    if(!outFile.is_open()){
        cout << "无法打开文件 sudoku_game.txt 以写入生成的数独游戏！" << endl;
        return;
    }
    int num,low=36,high=45;
    bool unique = false;
    if(argc==3){        // -n num 默认为中等难度
        num = atoi(argv[2]);
    }else if(argc==4){          // -n num -u 默认为中等难度
        num = atoi(argv[2]);
        if (strcmp(argv[3], "-u")) {
            paramError();
            return;
        }
        unique = true;
    } else if(argc==5){      // -n num -m level 或 -n num -r low~high
        num= atoi(argv[2]);
        if(!strcmp(argv[3],"-m")){
            int level = atoi(argv[4]);
            if(!levelConvert(level,low,high)){
                paramError();
            }
        }else if(!strcmp(argv[3],"-r")){
            if(!gerLowHigh(argv[4],low,high)){
                paramError();
            }
        }else{
            paramError();
            return;
        }
    }else if(argc==6){      // -n num -u -m level 或 -n num -u -r low~high

    }
    int puzzleSeq=0;
    int failCount=0;
    for(int i=0;i<num;i++){
        vector<vector<int>> puzzle,game;
        if (!inFile.eof()){
            puzzle = readFromFile(inFile);
            puzzles.push_back(puzzle);
        }else{
            puzzle=puzzles[puzzleSeq];
            if(puzzleSeq=puzzles.size()-1){
                puzzleSeq=0;

            }
            puzzleSeq=puzzleSeq%puzzles.size();
        }
        if(failCount==3){
            SudokuBoard board_final;
            board_final.generateFinal();
            puzzle=board_final.getGrid();
            puzzles.push_back(puzzle);
            failCount=0;
        }
        SudokuBoard board_game(puzzle);
        int count=0,realBlankNum=-1;
        bool success= false;
        game=board_game.generateGame(unique,low,high,count,realBlankNum,success);
        if (!success){
            failCount++;
            i--;
        }else{
            outputToFile(game,outFile);
            cout<<"成功生成第"<<i+1<<"个游戏，空格数为"<<realBlankNum<<endl;
        }
    }
    outFile.close();
    inFile.close();
}

void help(){
    cout<<"参数用法："<<endl;
    cout<<"-c num ：生成num个数独终盘，默认输出到sudoku_final_set.txt中"<<endl;
    cout<<"-c num filePath ：生成num个数独终盘到filePath对应文件中"<<endl;
    cout<<"-s filePath ： 从filePath中读取若干个数独游戏，进行求解，并将求解结果输出到sudoku_solution.txt中"<<endl;
    cout<<"-n num ：生成num个数独游戏，并输出到sudoku_game.txt中（默认难度为中等）"<<endl;
    cout<<"-n num -m level ： 生成num个指定难度的数独游戏，并输出到sudoku_game.txt中。level从1到3表示从易到难"<<endl;
    //难度等级1：20~35  等级2：36~45  等级3：46~55
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
            paramError();
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
        if(argc!=3){
            paramError();
            return 0;
        }
        string filePath=argv[2];
        ifstream inFile(filePath);
        ofstream outFile("sudoku_solution.txt");
        if (inFile.is_open() && outFile.is_open()) {
            while (!inFile.eof()){
                cout<<"求解数独游戏："<<endl;
                vector<vector<int>> game = readFromFile(inFile);
                SudokuBoard board_gameSet(game);
                print(game);
                cout<<"数独解："<<endl;
                board_gameSet.solveGame(0, 0);
                vector<vector<int>> solution = board_gameSet.getGrid();
                print(solution);
                // 输出结果到文件
                outputToFile(solution, outFile);
                if(!inFile.eof()){
                    outFile<<endl;
                }
            }
            outFile.close();
            inFile.close();
        }else {
            cout << "打开文件 "<<filePath<<" 和 sudoku_solution.txt 失败！" << endl;
        }
    }else if(!strcmp(argv[1],"-n")){
        if(argc>6){
            paramError();
            return 0;
        }else{
            nInsProcess(argc,argv);
        }
    }else{
        paramError();
    }
    return 0;
}