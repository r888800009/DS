

#include <iostream>
#include <algorithm>
#include <list>
#include <regex>

#define MENU_CHECK      1
#define MENU_TOPOSTFIX  2
#define MENU_SOLVE      3
#define MENU_QUIT       4

#define ASCII_SIZE 256


using namespace std;

enum Type {

    PARENTHESES_L,
    PARENTHESES_R,
    OPERATOR,
    NUMBER,
    SPACE

};

class Data {

public:
    union Value {
        char c;
        int i32;
    };

    Value value;
    Type type;
 
    Data(Type t, int v1) {
        value.i32 = v1;
        type = t;
    }

    Data(Type t, char v1) {
        value.c = v1;
        type = t;
    }

};

int priority[ASCII_SIZE];
vector<pair<regex, Type>> tokenDefine;

class Stack {
    list<Data> stackList;
public:
    void pop()
    {   
        stackList.pop_back();
    }
    
    Data top()
    {
       return stackList.back(); 
    }
    
    void push(Data c)
    {
        stackList.push_back(c);
    }
    
    void print() 
    {

    }

};

void errorHandling(string message)
{
    if (cin.eof())
        exit(0);

    // 恢復cin的狀態 
    cin.clear();

    // 消滅最多2048個字元遇到\n 
    cin.ignore(2048, '\n');

    // 顯示錯誤訊息
    cout << message << endl;
}

list<Data> getToken(string str)
{
    list<Data> ret;
    smatch m;
    bool status = true;
    while (status) {
        if (str.empty())
            break;

        for (pair<regex, Type> rgx : tokenDefine) {
            if ((status = regex_search(str, m, rgx.first))) {
                string get = m.str();
                
                if (rgx.second == NUMBER)
                    ret.push_back(Data(rgx.second, stoi(get)));
                else 
                    ret.push_back(Data(rgx.second, get[0]));

                str = m.suffix().str();
                goto next;
            }
        }

        cout << "\t"  << str << endl;
        cout << "\t^ is not a legitimate character." << endl;

        break;
    next:;
    }
    
    return ret;
}

void printList(list<Data> list1) {
    for (auto it = list1.begin(); it != list1.end();) { 
        if (it->type == NUMBER)
            cout << it->value.i32;
        else 
            cout << it->value.c;

        cout << (++it != list1.end() ? ',' : '\n');
    }
    
}

void syntaxCheck(list<Data>::iterator begin, list<Data>::iterator end) {
    // get priority 
    list<Data>::iterator priorityOpterate = begin, it = begin;
    
    while (it != end) {
        if (1) 
            priorityOpterate = it;
        it++;
    }

}

int task1()
{
    string expr;

    cin.ignore();
    getline(cin, expr);

    try {
        // getToken 
        list<Data> tokenize = getToken(expr);
        
        // check syntax
        syntaxCheck(tokenize.begin(), tokenize.end());
    } catch (exception e) {
        cout << e.what();
    }
    
    return 0;
}

int task2()
{
    return 0;
}

int task3()
{
    return 0;
}

void init()
{
    // disable priority
    fill(&priority[0], &priority[ASCII_SIZE], -1);
    
    priority['('] = 5;
    priority[')'] = 5;
    priority['*'] = 10;
    priority['/'] = 10;
    priority['+'] = 20;
    priority['-'] = 20;

    // num   
    // oper  [+\-*/]
    tokenDefine = vector<pair<regex, Type>> {
        { regex("^ +"), SPACE },
        { regex("^[0-9]+"), NUMBER },
        { regex("^[+\\-*/]"), OPERATOR },
        { regex("^\\)"), PARENTHESES_R },
        { regex("^\\("), PARENTHESES_L }
    };
}


int main(int argc, char *argv[])
{
    int mode;                           // 選單選項
    int result;                         // 指令回傳檢查
    init();
     
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

        // 判斷選擇的內容
        switch (mode) {
        case MENU_QUIT:
            return 0;               // 退出

        case MENU_CHECK:
            task1();
            break;

        case MENU_TOPOSTFIX:
            break;

        case MENU_SOLVE:
            break;

        default:
            errorHandling("Error: Command not found!");
            continue;
        }

        // 檢查回傳值是否為successful
        if (!result)
            return 1;
        else cout << endl;
    }

    return 0;
}

