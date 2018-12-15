// 第11組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version
#include <climits>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// clang-format off

#define MENU_QUIT               0
#define MENU_LOAD_DATA          1
#define MENU_SHOW_RANGE         2
#define MENU_REMOVE_DATA        3

#define DATA_NUMERO             0
#define DATA_NAME               1
#define DATA_TYPE1              2
#define DATA_TYPE2              3
#define DATA_TOTAL              4
#define DATA_HP                 5
#define DATA_ATTACK             6
#define DATA_DEFENSE            7
#define DATA_SP_ATK             8
#define DATA_SP_DEF             9
#define DATA_SPEED              10
#define DATA_GENERATION         11
#define DATA_LEGENDARY          12

#define DATA_SIZE               13
// clang-format on

using namespace std;

static bool inputSuccess;
void errorHandling(string message);

static string getOnlyDigits(string str)
{
    string tmp = "";
    for (char c : str)
        if (isdigit(c))
            tmp += c;

    return tmp;
}

static int stringToInt(string str)
{
    try {
        // "1,223,234,234,234"
        if (str[0] == '\"')
            str = getOnlyDigits(str);

        return stoi(str);
    }
    catch (exception e) {
        cout << "ERROR : stoi error!" << endl;
        cout << "Value : " << str << endl;
        return -1; // return error value
    }
}

class Data {
    string column[DATA_SIZE];

public:
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

    string operator[](int i) const { return column[i]; }
    string &operator[](int i) { return column[i]; }

    friend ostream &operator<<(ostream &out, Data &data)
    {
        for (int i = 0; i < DATA_SIZE; i++)
            out << data.column[i] << (i < DATA_SIZE - 1 ? '\t' : '\n');

        return out;
    }

    void print(vector<int> &select)
    {
        for (auto i : select)
            cout << column[i] << '\t';
        cout << '\n';
    }

    void printAll(vector<int> &select)
    {
        for (auto i : select)
            cout << column[i] << '\t';
        cout << '\n';
    }

    int convertToInt(int num) { return stringToInt(column[num]); }
};

enum BSTException { NullTree, NotFound };

class BST {

    typedef struct Node {
        vector<Data *> datas;
        Node *left, *right;
    } Node;

    // select column datatype must be integer
    int select;

    Node *root;

    bool cmpMoreThen(Data &a, Data &b) { return a[select] > b[select]; }

    void insert(Node *root, Data data)
    {
        if (root == nullptr) {
            // is null
        }
        else {
            // not null
            // recurive or push back
            if (1) {
                // this node
            }
            else if (1) {
                // or left
            }
            else {
                // or right
            }
        }
    }
    void clear(Node *root) {}
    Node remove(Node *root) {}
    Node *find(Node *root) {}

public:
    BST() { root = nullptr; }
    void clear() { clear(root); }
    void insert(Data data) { insert(root, data); }
    void setOrder(int order = DATA_HP) { select = order; }

    Data remove(int key)
    {
        if (root == nullptr)
            throw BSTException::NullTree;
        // is null
        // not null
        // recurive
        // this node
        // or left
        // or right
    }

    Data find(int key)
    {
        if (root == nullptr)
            throw BSTException::NullTree;
        // is null
        // not null
        // recurive
        // this node
        // or left
        // or right
    }

    void range(vector<Data> &result, int min = INT_MIN, int max = INT_MAX)
    {
        if (root == nullptr)
            throw BSTException::NullTree;
    }

    int getMin()
    {
        Node *cur = root;
        if (cur == nullptr)
            throw BSTException::NullTree;

        // always left side
        while (cur->left != nullptr)
            cur = cur->left;

        return cur->datas.back()->convertToInt(select);
    }

    int getMax()
    {
        Node *cur = root;
        if (cur == nullptr)
            throw BSTException::NullTree;

        // always right side
        while (cur->right != nullptr)
            cur = cur->right;

        return cur->datas.back()->convertToInt(select);
    }
};

class HandleFile {
    fstream fin;
    fstream fout;

    BST bst;

    vector<Data> database;
    string cloumnName[DATA_SIZE] = {
        "#",     "Name",       "Type 1",   "Type 2", "Total",
        "HP",    "Attack",     "Defense",  "Sp.Atk", "Sp.Def",
        "Speed", "Generation", "Legendary"};

    // common function
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

    void dropHeader(fstream &file)
    {
        for (int i = 0; i < 1; ++i)
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

    void dataOutput(vector<int> &selectOrder)
    {
        for (auto i : selectOrder)
            cout << cloumnName[i] << '\t';
        cout << '\n';
        for (auto i : database)
            i.print(selectOrder);
        cout << '\n';
    }

    // use in task1 & set select order
    bool task1_input(string &fileName, vector<Data> &database)
    {
        fileName = fileInput(fin, "Input (601, 602, ...[0]Quit): ", "input");

        // if fileName == "" then quit to menu
        if (fileName != "") {
            Data temp;
            while (fin >> temp) // >> overload
                if (inputSuccess)
                    database.push_back(temp);
        }
        else {
            cout << "switch to menu" << endl;
        }

        return fileName != ""; // {quit: 0, continue: 1}
    }

public:
    ~HandleFile()
    {
        // clear tree
    }

    bool task1()
    {
        // load file
        string fileName;

        if (!task1_input(fileName, database))
            return 0;

        // qsort ID

        // display vector
        vector<int> selectOrder(6);
        selectOrder = {DATA_NUMERO, DATA_NAME,   DATA_TYPE1,
                       DATA_HP,     DATA_ATTACK, DATA_DEFENSE};
        dataOutput(selectOrder);

        // build tree HP

        // show tree hight

        return 0;
    }

    bool task2()
    {
        vector<Data> result;
        int min;
        // input range
        min = numberInput("Threshold (a positive integer):", "out of range!");

        // get range
        bst.range(result, min);

        // tree show range
        vector<int> selectOrder(7);
        selectOrder = {DATA_NUMERO, DATA_NAME,   DATA_TYPE1,  DATA_TOTAL,
                       DATA_HP,     DATA_ATTACK, DATA_DEFENSE};

        dataOutput(selectOrder);

        return 0;
    }

    bool task3()
    {
        // show max one data all field

        // delete max one data

        // show tree hight

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
        cout << "* 0. Quit                      *" << endl;
        cout << "* 1. Load Data                 *" << endl;
        cout << "* 2. Show Range                *" << endl;
        cout << "* 3. Remove Max                *" << endl;
        cout << "choice: ";

        // 輸入選擇
        cin >> mode;

        HandleFile f;

        // 判斷選擇的內容
        switch (mode) {
        case MENU_QUIT:
            return 0;

        case MENU_LOAD_DATA:
            result = f.task1();
            break;

        case MENU_SHOW_RANGE:
            result = f.task2();
            break;

        case MENU_REMOVE_DATA:
            result = f.task3();
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
