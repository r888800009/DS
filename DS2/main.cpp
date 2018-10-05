// must to use -std=c++11 or higher version

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

#define DATA_SIZE             11
#define DATA_ID               0
#define DATA_NAME             1
#define DATA_DEPARTMENT_ID    2
#define DATA_DEPARTMENT_NAME  3
#define DATA_DAY_EXT_EDU      4
#define DATA_STAGE            5
#define DATA_STUDENTS         6
#define DATA_TEACHERS         7
#define DATA_GRADUATES        8
#define DATA_CITY             9
#define DATA_TYPE             10


static bool inputSuccess;
void errorHandling(string message);

class Data
{
public:
    string column[DATA_SIZE];

    friend istream &operator>>(istream &in, Data &data)
    {
        string input, temp;
        getline(in, input);

        if (in) {
            // drop \r if the program running on unix
            // or unix like system, the string may be 
            // contained '\r'
            if (input.back() == '\r')
                input.pop_back();

            // put \t for split easily
            input += '\t';

            // splitting
            int count = 0;
            inputSuccess = true;
            for (char c : input) {
                if (c != '\t')
                    temp += c;
                else {
                    data.column[count++] = temp;
                    temp = "";
                }
            }
            if (count != DATA_SIZE) inputSuccess = false;
        }
        return in;
    }

    friend ostream &operator<<(ostream &out, Data &data)
    {
        for (int i = 0; i < DATA_SIZE; i++)
            out << data.column[i] << (i < DATA_SIZE - 1 ? '\t' : '\n');

        return out;
    }
};

class HandleFile
{
    vector<int>  selected;
    fstream fin, fmerge;
    fstream fout;

    void select(int column)
    {
        selected.push_back(column);
    }
    
    string getOnlyDigits(string str)
    {
        string tmp = "";
        for (char c : str) 
            if (isdigit(c)) tmp += c;

        return tmp;
    }

    int isLessThan(string a, string b)
    {
        // a < b return 1, a == b return 0, a > b return -1
        if (a.length() < b.length())
            return 1;
        else if (a.length() > b.length())
            return -1;

        for (int i = 0; i < a.length(); ++i) {
            if (a[i] < b[i])
                return 1;
            else if (a[i] > b[i])
                return -1;
        }

        return 0;
    }

    bool comp(Data a, Data b)
    {
        // comp return 1, return 1 push a
        // comp return -1, return 0 push b
        int comp;

        // comp all selected 
        for (int select1 : selected) {
            comp = isLessThan(a.column[select1], b.column[select1]);
            if (comp == 1)
                return 1;
            else if (comp == -1)
                return 0;
        }

        // same return 1 push a
        return 1;
    }

    // common function
    void save(string saveName, vector<Data> &database)
    {

        // closs all file
        if (fin.is_open())
            fin.close();

        if (fmerge.is_open())
            fmerge.close();

        fout.open(saveName, ios::out | ios::trunc);
        for (Data i : database)
            fout << i;         // << overload

        fout.close();

        cout << "Total number of records: " << database.size() << endl;
    }

    void dropHeader(fstream &file)
    {
        for (int i = 0; i < 3; ++i)
            file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string fileInput(fstream &file, string message, string prefix)
    {
        string fileName;
        int fileNum;
        string fin_str;
        while (true) {

            // input file number
            while (true) {
                cout << message;
                cin  >> fileNum;
                if (!cin)
                    errorHandling("Error: Must file number!");
                else
                    break;
            }

            fileName = to_string(fileNum);

            // quit program if input "0"
            if (fileName == "0")
                return ""; 

            file.open(prefix + fileName + ".txt", ios::in);

            if (!file) {
                errorHandling("Error : there is no such file!");
                continue;
            }
            
            if (prefix == "input")
                dropHeader(file);

            return fileName;
        }
    }

    // use in task1
    bool task1_input(string &fileName)
    {
        fileName = fileInput(fin, "Input (201, 202, ...[0]Quit): ", "input");
        if (fileName == "")
            return 0; // quit
        else
            return 1;
    }

    // use in task2
    int numberInput(string message)
    {
        int result;
        while (true) {
            cout << message;
            cin >> result;
            if (cin && result > -1)
                return result;
            else
                errorHandling("Error : number out of range!");
        }
    }

    int stringToInt(string str)
    {
        try {
            // "1,223,234,234,234"
            if (str[0] == '\"') 
                return stoi(getOnlyDigits(str));

            return stoi(str);
        }
        catch (exception e) {
            cout << "ERROR : stoi error!" << endl;
            cout << "Value : " <<   str   << endl;
            return -1;
        }
    }

    bool task2_input(int &students, int &graduates, string &fileName)
    {
        fileName = fileInput(fin, "Input (201, 202, ...[0]Quit): ", "copy");
        if (fileName == "")
            return 0; // quit

        students  = numberInput("Threshold on number of students: ");
        graduates = numberInput("Threshold on number of graduates: ");

        return 1;
    }

    // use in task3
    void merge(vector<Data> &database) {

        // comp function return data priority
        Data a, b;
        fin    >> a;
        fmerge >> b;
        while (fin && fmerge) {
            if (comp(a, b)) {
                database.push_back(a);
                fin >> a;
            }
            else {
                database.push_back(b);
                fmerge >> b;
            }
        }

        while (fin) {
            if (inputSuccess) database.push_back(a);
            fin >> a; // >> overload
        }

        while (fmerge) {
            if (inputSuccess) database.push_back(b);
            fmerge >> b; // >> overload
        }
    }

    bool task3_input(string &fileName1, string &fileName2)
    {
        string fin_str, fout_str, fmerge_str;
        fileName1 = fileInput(fin, "Input 1st(201, 202, ...[0]Quit): ", "copy");
        if (fileName1 == "")
            return 0; // quit

        fileName2 = fileInput(fmerge, "Input 2nd(201, 202, ...[0]Quit): ", "copy");
        if (fileName2 == "")
            return 0; // quit

        return 1;
    }

public:

    bool task1()
    {

        vector<Data> database;
        string fileName;
        if (task1_input(fileName)) {

            Data temp;
            while (fin >> temp)     // >> overload
                if (inputSuccess) database.push_back(temp);

            save("copy" + fileName + ".txt", database);

            return 0;
        }
        else {
            cout << "switch to menu" << endl;
            return 0;
        }
    }

    bool task2()
    {
        vector<Data> database;
        int students, graduates;
        string fileName;
        if (task2_input(students, graduates, fileName)) {

            Data temp;
            while (fin >> temp) {
                if (inputSuccess &&
                    stringToInt(temp.column[DATA_STUDENTS]) >= students &&
                    stringToInt(temp.column[DATA_GRADUATES]) >= graduates)
                {
                    database.push_back(temp);
                }
            }

            save("copy" + fileName + ".txt", database);

            return 0;
        }
        else {
            cout << "switch to menu" << endl;
            return 0;
        }
    }

    bool task3()
    {
        vector<Data> database;
        string fileName1, fileName2;
        if (task3_input(fileName1, fileName2)) {
            // College priority than department
            select(DATA_ID);
            select(DATA_DEPARTMENT_ID);

            merge(database);
            save("output" + fileName1 + "_" + fileName2 + ".txt", database);

            return 0;
        }
        else {
            cout << "switch to menu" << endl;
            return 0;
        }
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
