// must to use -std=c++11 or higher version
#include <algorithm>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// clang-format off
#define MENU_SELECT_BUBBLE      1
#define MENU_MERGE_QUICK        2
#define MENU_RADIX              3
#define MENU_QUIT               4

#define DATA_SIZE               11
#define DATA_ID                 0
#define DATA_NAME               1
#define DATA_DEPARTMENT_ID      2
#define DATA_DEPARTMENT_NAME    3
#define DATA_DAY_EXT_EDU        4
#define DATA_STAGE              5
#define DATA_STUDENTS           6
#define DATA_TEACHERS           7
#define DATA_GRADUATES          8
#define DATA_CITY               9
#define DATA_TYPE               10
// clang-format on

static bool inputSuccess;
void errorHandling(string message);

class Data {
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
        int count    = 0;
        inputSuccess = true;
        for (char c : input) {
            if (c != '\t')
                temp += c;
            else {
                data.column[count++] = temp;
                temp                 = "";
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

class HandleFile {
    fstream fin;
    fstream fout;

    // common function
    string getOnlyDigits(string str)
    {
        string tmp = "";
        for (char c : str)
            if (isdigit(c))
                tmp += c;

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

        fout.open(saveName, ios::out | ios::trunc);
        for (Data i : database)
            fout << i; // << overload

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
        while (true) {

            // input file name
            cout << message;
            cin >> fileName;

            // quit program if input "0"
            if (fileName == "0")
                return "";

            file.open(prefix + fileName + ".txt", ios::in);

            if (!file) {
                errorHandling("Error : there is no such file!");
                continue; // input again
            }

            dropHeader(file);

            return fileName;
        }
    }

    // use in task1
    bool task123_input(string &fileName, vector<Data> &database)
    {
        fileName = fileInput(fin, "Input (201, 202, ...[0]Quit): ", "input");

        // if fileName == "" then quit to menu
        if (fileName != "") {
            Data temp;
            while (fin >> temp) // >> overload
                if (inputSuccess)
                    database.push_back(temp);
        } else {
            cout << "switch to menu" << endl;
        }

        return fileName != ""; // {quit: 0, continue: 1}
    }

    int stringToInt(string str)
    {
        try {
            // "1,223,234,234,234"
            if (str[0] == '\"')
                str = getOnlyDigits(str);

            return stoi(str);
        } catch (exception e) {
            cout << "ERROR : stoi error!" << endl;
            cout << "Value : " << str << endl;
            return -1; // return error value
        }
    }

    typedef const function<void()> timerHandler;
    void timing(const string &display, timerHandler doing)
    {
        clock_t t = clock();
        doing();
        cout << display << (clock() - t) << " ms" << endl;
    }

    // sorts
    template <class T> void selection(void (*cmp)(T, T)) {}

    template <class T> void bubble(void (*cmp)(T, T)) {}

    template <class T> void merge(void (*cmp)(T, T)) {}

    template <class T> void quick(void (*cmp)(T, T)) {}

    template <class T> void redix(void (*cmp)(T, T)) {}

  public:
    bool task1()
    {
        vector<Data> database;
        string fileName;

        if (!task123_input(fileName, database))
            return 0;

        // sort and timer

        // save
        save("copy" + fileName + ".txt", database);

        return 0;
    }

    bool task2()
    {
        vector<Data> database;
        string fileName;

        if (!task123_input(fileName, database))
            return 0;

        // sort and timer

        // save
        save("copy" + fileName + ".txt", database);

        return 0;
    }

    bool task3()
    {
        vector<Data> database;
        string fileName;

        if (!task123_input(fileName, database))
            return 0;

        // sort and timer

        // save
        save("copy" + fileName + ".txt", database);

        return 0;
    }
};

int main(int argc, char *argv[])
{
    int mode;   // 選單選項
    int result; // 指令回傳檢查
    while (true) {

        // 輸出選單
        cout << "              MENU              " << endl;
        cout << "* 1. Selection  & Bubble Sort  *" << endl;
        cout << "* 2. Merge      & Quick Sort   *" << endl;
        cout << "* 3. Radix Sort                *" << endl;
        cout << "* 4. Quit                      *" << endl;
        cout << "choice: ";

        // 輸入選擇
        cin >> mode;

        HandleFile f;

        // 判斷選擇的內容
        switch (mode) {
        case MENU_QUIT:
            return 0; // 退出

        case MENU_SELECT_BUBBLE:
            result = f.task1();
            break;

        case MENU_MERGE_QUICK:
            result = f.task2();
            break;

        case MENU_RADIX:
            result = f.task3(); // 任務3
            break;

        default:
            errorHandling("Error: Command not found!");
            continue;
        }

        // 檢查回傳值是否為successful
        if (result)
            return 1;
        else
            cout << endl;
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
