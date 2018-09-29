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

int selectedColumn1;
int selectedColumn2;

long long stringToLong(string str, int base = 10)
{
    try {
        if (str[0] == '\"') {
            string tmp = "";
            for (int i = 0; i < str.length(); ++i)
                if (isdigit(str[i])) tmp += str[i];

            return stol(tmp);
        }
        else
            return stol(str, nullptr, base);
    }
    catch (exception e) {
        cout << "ERROR : stoi error!" << endl;
        cout << "Value : " << str << endl;
        return -1;
    }
}

bool compare(Data a, Data b)
{
    // return 1 if numA first
    long long numA, numB;

    // first 
    numA = stringToLong(a.column[selectedColumn1], 64);
    numB = stringToLong(b.column[selectedColumn1], 64);
    if (numA > numB)
        return 0;
    else if (numA < numB)
        return 1;

    // second
    numA = stringToLong(a.column[selectedColumn2], 64);
    numB = stringToLong(b.column[selectedColumn2], 64);    
    if (numA > numB)
        return 0;
    else if (numA < numB)
        return 1;   

    return 1;
}

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

class HandleFile
{
    vector<Data> database;
    fstream fin, fmerge;
    fstream fout;

public:
    void save(string saveName) 
    {
        fout.open(saveName, ios::out | ios::trunc);

        for (vector<Data>::iterator i = database.begin(); i != database.end(); i++) 
            fout << *i;         // << overload

        // closs all file
        if (fin.is_open())
            fin.close(); 

        if (fmerge.is_open())
            fmerge.close(); 

        fout.close(); 

        cout << "Total number of records: " << database.size() << endl;
    }

    string fileInput(fstream &file, string message, bool loadToDatabase)
    {
        string fileName;
        string fin_str;
        while (true) {
            cout << message;
            cin >> fileName;
            if (fileName == "0")
                return "";
            
            file.open("input" + fileName + ".txt", ios::in);
            if (!file) 
                errorHandling("Error : there is no such file!");

             // skip three line
            for (int i = 0; i < 3; ++i)
                file.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if (!loadToDatabase)
                return fileName;

            // load file
            Data temp;
            while (file >> temp)     // >> overload
                if (inputSuccess) database.push_back(temp);

            return fileName;
        }
    }

    void merge(bool (*comp)(Data, Data)) {
        
        // comp function return which data have priority
        Data a, b;
        fin >> a;
        fmerge >> b;
        while (fin && fmerge) {
            if (comp(a, b)) {
                database.push_back(a);
                fin >> a;
            } else {
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

    bool task1_input(string &fileName) 
    {
        fileName = fileInput(fin, "Input (201, 202, ...[0]Quit): ", true); 
        if (fileName == "")
            return 0;
        else
            return 1;
    }

    bool task1() 
    {
        string fileName;
        if (task1_input(fileName)) {
            
            save("copy" + fileName + ".txt");

            return 0;
        }

        return 1;
    }

    bool task2_input(int &students, int &graduates, string &fileName) 
    {
        fileName = fileInput(fin, "Input (201, 202, ...[0]Quit): ", true); 
        if (fileName == "")
            return 0;

        students  = numberInput("Threshold on number of students: ");
        graduates = numberInput("Threshold on number of graduates: ");

        return 1;
    }

    bool task2()
    {
        int students, graduates;
        string fileName;
        if (task2_input(students, graduates, fileName)) {
            
            // query
            for (vector<Data>::iterator it = database.begin(); it != database.end(); )
                if (stringToLong(it->column[DATA_STUDENTS]) < students ||
                    stringToLong(it->column[DATA_GRADUATES]) < graduates) 
                {
                    it = database.erase(it);
                } else {
                    ++it;
                }
            
            save("copy" + fileName + ".txt");

            return 0;
        }

        return 1;
    }

    bool task3_input(string &fileName1, string &fileName2) 
    {
        string fin_str, fout_str, fmerge_str;
        fileName1 = fileInput(fin, "Input 1st(201, 202, ...[0]Quit): ", false); 
        if (fileName1 == "")
            return 0;

        fileName2 = fileInput(fmerge, "Input 2nd(201, 202, ...[0]Quit): ", false); 
        if (fileName2 == "")
            return 0;
        else
            return 1;
    }

    // merge
    bool task3()
    {
        string fileName1, fileName2;
        if (task3_input(fileName1, fileName2)) {
            // College priority than department
            selectedColumn1 = DATA_ID;
            selectedColumn2 = DATA_DEPARTMENT__ID;

            merge(compare);
            save("output" + fileName1 + "_" + fileName2 + ".txt");

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


