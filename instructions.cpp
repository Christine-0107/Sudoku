#include "instructions.h"

void help(){
    cout<<"�����÷���"<<endl;
    cout<<"-c num ������num���������̣�Ĭ�������sudoku_final_set.txt��"<<endl;
    cout<<"-c num filePath ������num���������̵�filePath��Ӧ�ļ���"<<endl;
    cout<<"-s filePath �� ��filePath�ж�ȡ���ɸ�������Ϸ��������⣬��������������sudoku_solution.txt��"<<endl;
    cout<<"-n num ������num��������Ϸ���������sudoku_game.txt�У�Ĭ���Ѷ�Ϊ�еȣ�"<<endl;
    cout<<"-n num -m level �� ����num��ָ���Ѷȵ�������Ϸ���������sudoku_game.txt�С�level��1��3��ʾ���׵���"<<endl;
    //�Ѷȵȼ�1��20~35  �ȼ�2��36~45  �ȼ�3��46~55
    cout<<"-n num -r low~high �� ����num���ڿ�����low~high֮���������Ϸ���������sudoku_game.txt��"<<endl;
    cout<<"-n num -u �� ����num������Ψһ���������Ϸ���������sudoku_game.txt��"<<endl;
    cout<<"-n num -u -m level �� ����num������Ψһ���ָ���Ѷȵ�������Ϸ���������sudoku_game.txt�С�level��1��3��ʾ���׵���"<<endl;
    cout<<"-n num -u -r low~high �� ����num������Ψһ����ڿ�����low~high֮���������Ϸ���������sudoku_game.txt��"<<endl;
}

bool processInstr(int argc, char* argv[]){
    #ifndef SRAND_TIME
    #define SRAND_TIME
    srand(time(0));
    #endif

    if(argc<3){
        cout<<"�����������㣬��������ȷ�Ĳ���"<<endl;
        help();
        return false;
    }
    if(!strcmp(argv[1],"-c")){
        string filePath;
        if(argc==3){
            filePath="sudoku_final_set.txt";
        }else if(argc==4){
            filePath=argv[3];
        }else{
            paramError();
            return false;
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
            return false;
        }
    }else if(!strcmp(argv[1],"-s")){
        if(argc!=3){
            paramError();
            return false;
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
            outFile.close();
            inFile.close();
        }else {
            cout << "���ļ� "<<filePath<<" �� sudoku_solution.txt ʧ�ܣ�" << endl;
            return false;
        }
    }else if(!strcmp(argv[1],"-n")){
        if(argc>6){
            paramError();
            return false;
        }else{
            if(!nInsProcess(argc,argv)){
                return false;
            }
        }
    }else{
        paramError();
        return false;
    }
    return true;
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

void paramError(){
    cout << "��������Ƿ�����������ȷ�Ĳ���" << endl;
    help();
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
            vector<vector<int>>().swap(puzzle);
            break;
        }
    }
    return puzzle;
}

// �����ѵȼ�ת��Ϊ��Ӧ���ڿշ�Χ
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

// �Ӳ���low~high�л�ȡlow��high
bool getLowHigh(string arg, int &low,int&high){
    int size=arg.size();
    int tempL=0,tempH=0;
    bool isLow= true;
    for(int i=0;i< size;i++){
        if(arg[i]=='~'&&i!=size-1){
            isLow= false;
            continue;
        }
        if(!isdigit(arg[i])){
            return false;
        }
        if(isLow){
            tempL =tempL*10+ (arg[i]-'0');
        }else{
            tempH = tempH*10 + (arg[i]-'0');
        }
    }
    if(isLow== false){
        low=tempL;
        high=tempH;
        return true;
    }else{
        return false;
    }
}

//-n���ָ��Ĵ�������ָ����������Ϸ��������Ϸ�Ѷȵȼ�1��20~35  �ȼ�2��36~45  �ȼ�3��46~55
bool nInsProcess(int argc, char* argv[]){
    vector<vector<vector<int>>> puzzles;
    ifstream inFile("sudoku_final_set.txt");
    ofstream outFile("sudoku_game.txt");
    if(!inFile.is_open()){
        cout << "�޷����ļ� sudoku_final_set.txt �Զ�ȡ�����վ֣�" << endl;
        return false;
    }
    if(!outFile.is_open()){
        cout << "�޷����ļ� sudoku_game.txt ��д�����ɵ�������Ϸ��" << endl;
        return false;
    }
    int num,low=36,high=45;
    bool unique = false;
    if(argc==3){        // -n num Ĭ��Ϊ�е��Ѷ�
        num = atoi(argv[2]);
    }else if(argc==4){          // -n num -u Ĭ��Ϊ�е��Ѷ�
        num = atoi(argv[2]);
        if (strcmp(argv[3], "-u")) {
            paramError();
            return false;
        }
        unique = true;
    } else if(argc==5){      // -n num -m level �� -n num -r low~high
        num= atoi(argv[2]);
        if(!strcmp(argv[3],"-m")){
            int level = atoi(argv[4]);
            if(!levelConvert(level,low,high)){
                paramError();
                return false;
            }
        }else if(!strcmp(argv[3],"-r")){
            if(!getLowHigh(argv[4],low,high)){
                paramError();
                return false;
            }
        }else{
            paramError();
            return false;
        }
    }else if(argc==6){      // -n num -u -m level �� -n num -u -r low~high
        num = atoi(argv[2]);
        if (strcmp(argv[3], "-u")) {
            paramError();
            return false;
        }
        unique = true;
        if(!strcmp(argv[4],"-m")){
            int level = atoi(argv[5]);
            if(!levelConvert(level,low,high)){
                paramError();
                return false;
            }
        }else if(!strcmp(argv[4],"-r")){
            if(!getLowHigh(argv[5],low,high)){
                paramError();
                return false;
            }
        }else{
            paramError();
            return false;
        }
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
            if(i!=num-1){
                outFile<<endl;
            }
            cout<<"�ɹ����ɵ�"<<i+1<<"����Ϸ���ո���Ϊ"<<realBlankNum<<endl;
        }
    }
    outFile.close();
    inFile.close();
    return true;
}


