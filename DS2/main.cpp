#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

#define MENU_COPY_FILE        1 
#define MENU_FILTER_FILE      2
#define MENU_MERGE_FILE       3
#define MENU_QUIT             4
#define SIZE                  11

static bool inputSuccess;
void errorHandling(string message);

class Data
{
public:
    string column[SIZE];

    friend istream &operator>>(istream &in, Data &data)
    {
        string input, temp;
        getline(in, input);
        input += '\t';
        if (in) {
            int count = 0;
            inputSuccess = true;
            for (int i = 0; i < input.length(); i++) {
                if (input[i] != '\t')
                    temp += input[i];
                else {
                    data.column[count++] = temp;
                    temp = "";
                }
            }
            if (count != SIZE) inputSuccess = false;
        }
        return in;
    }

    friend ostream &operator<<(ostream &out, Data &data)
    {
        for (int i = 0; i < SIZE; i++) 
            out << data.column[i] << (i < SIZE -1 ? '\t' : '\n');

        return out;
    }
};

class HandleFile
{
    vector<Data> database;

public:
    bool task1_input(fstream &fin, fstream &fout) 
    {
        string temp;
        string fin_str, fout_str;
        while (true) {
            cout << "Input ( 201, 202, ...[0]Quit):";
            cin >> temp;
            if (temp == "0") 
                return 0;
            else {
                fin_str = "input" + temp + ".txt";
                fout_str = "copy" + temp + ".txt";
            }

            fin.open(fin_str, ios::in);
            fout.open(fout_str, ios::out | ios::trunc);

            if (!fin) 
                errorHandling("Error : there is no such file!");
            else 
                return 1;
        }
    }

    bool task1() 
    {
        fstream fin;
        fstream fout;

        if (task1_input(fin, fout)) {
            // skip three line
            for (int i = 0; i < 3; ++i)
                fin.ignore(numeric_limits<streamsize>::max(), '\n');

            Data temp;
            while (fin >> temp)     // >> overload
                if (inputSuccess) database.push_back(temp);
            
            for (vector<Data>::iterator i = database.begin(); i != database.end(); i++) 
                fout << *i;         // << overload
            
            cout << database.size() << endl;
        }

        return 0;
    }

    bool task2()
    {
        return 0;
    }

    bool task3()
    {
        return 0;
    }
};

int main(int argc, char *argv[])
{
    int mode;                           // 選單選項
    int result;                         // 指令回傳檢查
    while (true) {

        // 輸出選單
        cout << "              MENU              " << endl;
        cout << "* 1. COPY (Read & Save a file) *" << endl;
        cout << "* 2. FILTER (Reduce a file)    *" << endl;
        cout << "* 3. MERGE (Join two files)    *" << endl;
        cout << "* 4. Quit                      *" << endl;
        cout << "choice: ";

        // 輸入選擇
        cin >> mode;

        HandleFile f;

        // 判斷選擇的內容
        switch (mode) {
        case MENU_QUIT:
            return 0;               // 退出
        case MENU_COPY_FILE:
            result = f.task1();       // 任務1
            break;
        case MENU_FILTER_FILE:
            // result = task2();       // 任務2
            break;
        case MENU_MERGE_FILE:
            // result = task3();       // 任務3
            break;
        default:
            errorHandling("Error: Command not found!");
            continue;
        }

        // 檢查回傳值是否為successful
        if (result)
            return 1;
    };
    return 0;
}

void errorHandling(string message)
{
    // 如果eof則強制結束程式
    if (cin.eof())
        exit(0);

    // 恢復cin的狀態 
    cin.clear();

    // 消滅最多2048個字元遇到\n 
    cin.ignore(2048, '\n');

    // 顯示錯誤訊息
    cout << message << endl;
}


