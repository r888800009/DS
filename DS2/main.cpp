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

#define DATA_ID              0
#define DATA_NAME            1
#define DATA_DEPARTMENT__ID  2
#define DATA_DEPARTMENT_NAME 3
#define DATA_DAY_EXT_EDU     4
#define DATA_STAGE           5
#define DATA_STUDENTS        6
#define DATA_TEACHERS        7
#define DATA_GRADUATES       8
#define DATA_CITY            9
#define DATA_TYPE            10


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

int selectedColumn;

int stringToInt(string str)
{

    if (str[0] == '\"') {
        string tmp = "";
        for (int i = 0; i < str.length(); ++i)
            if (isdigit(str[i]))
                tmp += str[i];
        // cout << " OwO "; 
        return atoi(tmp.c_str());
    } else
        return atoi(str.c_str());
}

bool compare(Data a, Data b)
{
    int numA, numB;
    numA = stringToInt(a.column[selectedColumn]);
    numB = stringToInt(b.column[selectedColumn]);

    return (numA < numB) ;
}

class HandleFile
{
    vector<Data> database;
    fstream fin, fmerge;
    fstream fout;

public:
    void save() 
    {
        for (vector<Data>::iterator i = database.begin(); i != database.end(); i++) 
            fout << *i;         // << overload

        // closs all file
        if (fin.is_open())
            fin.close(); 
        if (fmerge.is_open())
            fmerge.close(); 
        if (fout.is_open())
            fout.close(); 

        cout << "Total number of records: " << database.size() << endl;
    }

    bool task1_input() 
    {
        string fileName;
        string fin_str, fout_str;
        while (true) {
            cout << "Input (201, 202, ...[0]Quit): ";
            cin >> fileName;
            if (fileName == "0")
                return 0;
            else {
                fin_str   = "input" + fileName + ".txt";
                fout_str  = "copy" + fileName + ".txt";
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
        if (task1_input()) {
            // skip three line
            for (int i = 0; i < 3; ++i)
                fin.ignore(numeric_limits<streamsize>::max(), '\n');

            Data temp;
            while (fin >> temp)     // >> overload
                if (inputSuccess) database.push_back(temp);
            
            save();

            return 0;
        }

        return 1;
    }

    bool task2_input(int &students, int &graduates) 
    {
        string fileName;
        string fin_str, fout_str;
        while (true) {
            cout << "Input (201, 202, ...[0]Quit): ";
            cin >> fileName;
            
            

            if (fileName == "0")
                return 0;
            else {
                fin_str   = "input" + fileName + ".txt";
                fout_str  = "copy" + fileName + ".txt";
            }

            fin.open(fin_str, ios::in);
            fout.open(fout_str, ios::out | ios::trunc);

            if (!fin) 
                errorHandling("Error : there is no such file!");
            else 
                break;
        }

        while (true) {
            cout << "Threshold on number of students: ";
            cin >> students;
            if (cin && students > -1)
                break;
            else 
                errorHandling("Error : number out of range!");

        }
        
        while (true) {
            cout << "Threshold on number of graduates: ";
            cin >> graduates;
            if (cin && graduates > -1)
                break;
            else 
                errorHandling("Error : number out of range!");
        }

        return 1;
    }

    bool task2()
    {
        int students, graduates;
        if (task2_input(students, graduates)) {
            // skip three line
            for (int i = 0; i < 3; ++i)
                fin.ignore(numeric_limits<streamsize>::max(), '\n');

            Data temp;
            while (fin >> temp)     // >> overload
                if (inputSuccess) database.push_back(temp);
            
            // query
            for (vector<Data>::iterator it = database.begin(); it != database.end(); )
                if (stringToInt(it->column[DATA_STUDENTS]) < students ||
                    stringToInt(it->column[DATA_GRADUATES]) < graduates) 
                {
                    it = database.erase(it);
                } else {
                    ++it;
                }
            
            save();

            return 0;
        }

        return 1;
    }

    bool task3_input() 
    {
        string fileName1, fileName2;
        string fin_str, fout_str, fmerge_str;
        while (true) {
            cout << "Input 1st(201, 202, ...[0]Quit): ";
            cin >> fileName1;

            cout << "Input 2nd(201, 202, ...[0]Quit): ";
            cin >> fileName2;

            if (fileName1  == "0")
                return 0;
            else {
                fin_str     = "input" + fileName1 + ".txt";
                fmerge_str  = "input" + fileName2 + ".txt";
                fout_str    = "output" + fileName1 + "_" + fileName2 + ".txt";
            }

            fin.open(fin_str, ios::in);
            fmerge.open(fmerge_str, ios::in);
            fout.open(fout_str, ios::out | ios::trunc);

            if (!fin || !fmerge) 
                errorHandling("Error : there is no such file!");
            else 
                return 1;
        }
    }

    // merge
    bool task3()
    {
        if (task3_input()) {
            // skip three line
            for (int i = 0; i < 3; ++i) {
                fin.ignore(numeric_limits<streamsize>::max(), '\n');
                fmerge.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            Data temp;
            while (fin >> temp)     // >> overload
                if (inputSuccess) database.push_back(temp);
            
            // merge
            while (fmerge >> temp)     // >> overload
                if (inputSuccess) database.push_back(temp);
            
            // sort department
            selectedColumn = DATA_DEPARTMENT__ID;
            stable_sort(database.begin(), database.end(), compare);

            // sort college
            selectedColumn = DATA_ID;
            stable_sort(database.begin(), database.end(), compare);

            save();

            return 0;
        }

        return 1;
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
            result = f.task2();       // 任務2
            break;
        case MENU_MERGE_FILE:
            result = f.task3();       // 任務3
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


