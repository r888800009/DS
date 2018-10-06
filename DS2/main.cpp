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

        if (!in) 
            return in;
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

        if (count != DATA_SIZE)
            inputSuccess = false;

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
    fstream fin, fmerge;
    fstream fout;

    // common function
    string getOnlyDigits(string str)
    {
        string tmp = "";
        for (char c : str) 
            if (isdigit(c)) tmp += c;

        return tmp;
    }

    int numberInput(string message, string errorMsg)
    {
        int result;
        while (true) {
            cout << message;
            cin >> result;
            if (cin && result > -1)
                return result;
            else
                errorHandling("Error : " + errorMsg);
        }
    }

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
        while (true) {

            // input file number
            string errorMsg = "Must file number!";
            fileNum  = numberInput(message, errorMsg); 
            fileName = to_string(fileNum);

            // quit program if input "0"
            if (fileName == "0")
                return ""; 

            file.open(prefix + fileName + ".txt", ios::in);

            if (!file) {
                errorHandling("Error : there is no such file!");
                continue; // input again
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

        // if fileName == "" then quit to menu
        return fileName != "";  // {quit: 0, continue: 1}
    }

    int stringToInt(string str)
    {
        try {
            // "1,223,234,234,234"
            if (str[0] == '\"') 
                str = getOnlyDigits(str);

            return stoi(str);
        }
        catch (exception e) {
            cout << "ERROR : stoi error!" << endl;
            cout << "Value : " <<   str   << endl;
            return -1; // return error value
        }
    }

    bool task2_input(int &students, int &graduates, string &fileName)
    {
        string errorMsg = "number out of range!";
        fileName = fileInput(fin, "Input (201, 202, ...[0]Quit): ", "copy");
        if (fileName == "")
            return 0; // quit

        students  = numberInput("Threshold on number of students: ", errorMsg);
        graduates = numberInput("Threshold on number of graduates: ", errorMsg);

        return 1;
    }

    // use in task3
    int isLessThan(Data dataA, Data dataB, int selected)
    {
        string a = dataA.column[selected];
        string b = dataB.column[selected];
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

    bool equal(Data a, string str, int selected)
    {
        return a.column[selected] == str;
    }

    void addDebug(vector<Data> &database, string msg = "debug")
    {
        Data debug;
        for (string &d: debug.column)
            d = msg;
        database.push_back(debug);
    }

    void mergeDepartment(vector<Data> &database, Data &a, Data &b, vector<int> &selected, string id)
    {
        vector<Data> wait;
        while (fin && fmerge && equal(a, id, selected[0]) && equal(b, id, selected[0])) {
            // comp function return data priority
            int comp = isLessThan(a, b , selected[1]);
            if (comp == -1) {       // A > B
                wait.push_back(b);
                fmerge >> b;

            } else if (comp == 0) { // A == B
                string department = a.column[selected[1]];
                string department_name = a.column[DATA_DEPARTMENT_NAME];

                while (fin && equal(a, department, selected[1])) {
                    database.push_back(a);
                    fin >> a;
                }

                while (fmerge && equal(b, department, selected[1])) {
                    if (equal(b, department_name, DATA_DEPARTMENT_NAME)) {
                        database.push_back(b);
                        fmerge >> b;
                    } else {
                        wait.push_back(b);
                        fmerge >> b;
                    }
                }

            } else if (comp == 1) { // A < B
                database.push_back(a);
                fin >> a;
            }
        }

        // load not loaded
        while (fin && equal(a, id, selected[0])) {
            if (inputSuccess) database.push_back(a);
            fin >> a; // >> overload
        }
        
        addDebug(database, "debug");
        // merge loaded
        for (Data d : wait)
            database.push_back(d);

        // merge not loaded
        while (fmerge && equal(b, id, selected[0])) {
            if (inputSuccess) database.push_back(b);
            fmerge >> b; // >> overload
        }
    }

    void merge(vector<Data> &database, vector<int> &selected) {

        Data a, b;
        fin    >> a;
        fmerge >> b;
        vector<Data> wait;
        while (fin && fmerge) {
            // comp function return data priority
            int comp = isLessThan(a, b ,selected[0]);
            if (comp == -1) {       // A > B
                wait.push_back(b);
                fmerge >> b;

            } else if (comp == 0) { // A == B
                string id = a.column[selected[0]];
                mergeDepartment(database, a, b, selected, id);

            } else if (comp == 1) { // A < B
                database.push_back(a);
                fin >> a;
            }
        }

        // load not loaded
        while (fin) {
            if (inputSuccess) database.push_back(a);
            fin >> a; // >> overload
        }

        // merge loaded
        for (Data d : wait)
            database.push_back(d);

        // merge not loaded
        while (fmerge) {
            if (inputSuccess) database.push_back(b);
            fmerge >> b; // >> overload
        }
    }

    bool task3_input(string &fileName1, string &fileName2)
    {
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

        if (!task1_input(fileName)) {
            cout << "switch to menu" << endl;
            return 0;
        }

        Data temp;
        while (fin >> temp)     // >> overload
            if (inputSuccess) database.push_back(temp);

        save("copy" + fileName + ".txt", database);

        return 0;
    }

    bool task2()
    {
        vector<Data> database;
        int students, graduates;
        string fileName;

        if (!task2_input(students, graduates, fileName)) {
            cout << "switch to menu" << endl;
            return 0;
        }

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

    bool task3()
    {
        vector<Data> database;
        vector<int>  selected;
        string fileName1, fileName2;
        
        if (!task3_input(fileName1, fileName2)) {
            cout << "switch to menu" << endl;
            return 0;
        }

        // College priority than department
        selected.push_back(DATA_ID);
        selected.push_back(DATA_DEPARTMENT_ID);

        merge(database, selected);
        save("output" + fileName1 + "_" + fileName2 + ".txt", database);

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
