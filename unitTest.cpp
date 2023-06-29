//
// Created by Lenovo on 2023/6/29.
//
#include <iostream>
#include "gtest/gtest.h"
#include "instructions.h"

TEST(TestInstr,missing_parameter){
    char* argv[]={"Sudoku.exe","-c"};
    ASSERT_EQ(processInstr(2,argv), false);
}

TEST(TestInstr,wrong_parameter){
    char* argv[]={"Sudoku.exe","-x","10"};           // 非法参数
    ASSERT_EQ(processInstr(3,argv), false);
}

TEST(TestInstr,c_instr){
    char* argv1[]={"Sudoku.exe","-c","10000","create_large_num.txt"};       // -c num filePath. 同时测试生成大量终局
    ASSERT_EQ(processInstr(4,argv1), true);
    char* argv2[]={"Sudoku.exe","-c","3"};      // -c num
    ASSERT_EQ(processInstr(3,argv2), true);
    char* argv3[]={"Sudoku.exe","-c","3","wrong","wrong"};      // -c指令参数错误
    ASSERT_EQ(processInstr(5,argv3), false);
}

TEST(TestInstr,n_instr){
    char* argv1[]={"Sudoku.exe","-n","5"};       // -n num
    ASSERT_EQ(processInstr(3,argv1), true);
    char* argv2[]={"Sudoku.exe","-n","3","wrong","wrong","wrong","wrong"};      // -n指令参数错误
    ASSERT_EQ(processInstr(7,argv2), false);
}

TEST(TestInstr,n_m_instr){
    char* argv1[]={"Sudoku.exe","-n","5","-m","1"};      // -n num -m level1
    ASSERT_EQ(processInstr(5,argv1), true);
    argv1[4]="2";                                                           // -n num -m level2
    ASSERT_EQ(processInstr(5,argv1), true);
    argv1[4]="3";                                                           // -n num -m level3
    ASSERT_EQ(processInstr(5,argv1), true);
    argv1[4]="4";                                                          // 测试错误的level
    ASSERT_EQ(processInstr(5,argv1), false);
}

TEST(TestInstr,n_r_instr){
    char* argv1[]={"Sudoku.exe","-n","5","-r","28~43"};      // -n num -r low~high
    ASSERT_EQ(processInstr(5,argv1), true);
    argv1[4]="28";                                  // 错误的范围格式
    ASSERT_EQ(processInstr(5,argv1), false);
}

TEST(TestInstr,n_u_instr){
    char* argv1[]={"Sudoku.exe","-n","5","-u"};      // -n num -u
    ASSERT_EQ(processInstr(4,argv1), true);
    argv1[3]="wrong";      // 测试参数错误
    ASSERT_EQ(processInstr(4,argv1), false);
}

TEST(TestInstr,n_u_m_instr){
    char* argv1[]={"Sudoku.exe","-n","5","-u","-m","1"};      // -n num -u -m level1
    ASSERT_EQ(processInstr(6,argv1), true);
    argv1[5]="2";                                                           // -n num -u -m level2
    ASSERT_EQ(processInstr(6,argv1), true);
    argv1[5]="3";                                                           // -n num -u -m level3
    ASSERT_EQ(processInstr(6,argv1), true);
    argv1[5]="4";                                                           // 错误的level
    ASSERT_EQ(processInstr(6,argv1), false);
}

TEST(TestInstr,n_u_r_instr){
    char* argv1[]={"Sudoku.exe","-n","5","-u","-r","25~48"};      // -n num -u -r low~high
    ASSERT_EQ(processInstr(6,argv1), true);
    argv1[5]="28";                                  // 错误的范围格式
    ASSERT_EQ(processInstr(6,argv1), false);
}

TEST(TestInstr,s_instr){
    char* argv1[]={"Sudoku.exe","-s","sudoku_game.txt"};       // -s filePath
    ASSERT_EQ(processInstr(3,argv1), true);
    char* argv2[]={"Sudoku.exe","-s","fail.txt"};      // -s 不存在的filePath
    ASSERT_EQ(processInstr(3,argv2), false);
    char* argv3[]={"Sudoku.exe","-s","3","wrong"};      // -s指令参数错误
    ASSERT_EQ(processInstr(4,argv3), false);
}

TEST(TestReadFile,readFile){
    ifstream infile("wrong_readFile.txt");
    vector<vector<int>> puzzle;
    if(infile.is_open()){
        puzzle=readFromFile(infile);
    }
    ASSERT_EQ(puzzle.size(), 0);
}

TEST(TestGetLowHigh, right){                 // 测试getLowHigh()函数功能，正确
    int low,high;
    string argTrue="28~50";
    ASSERT_EQ(getLowHigh(argTrue,low,high), true);
    ASSERT_EQ(low,28);
    ASSERT_EQ(high,50);
}

TEST(TestGetLowHigh, wrong){                 // 测试getLowHigh()函数功能，错误
    int low,high;
    string arg1="28~",arg2="2x",arg3="234",argTrue="28~50";
    ASSERT_EQ(getLowHigh(arg1,low,high), false);
    ASSERT_EQ(getLowHigh(arg2,low,high), false);
    ASSERT_EQ(getLowHigh(arg3,low,high), false);
    ASSERT_EQ(getLowHigh(argTrue,low,high), true);
    ASSERT_EQ(low,28);
    ASSERT_EQ(high,50);
}

int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}