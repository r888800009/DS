

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
    SPACE,
    UNDEFINE

};

class Data {

public:
    union Value {
        char c;
        int i32;
    };

    Value value;
    Type type;

    Data() 
    {
    }

    Data(Type t, int v1) 
    {
        value.i32 = v1;
        type = t;
    }

    Data(Type t, char v1) 
    {
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

class Tokenizer {
    string str;
    Data ret;

public:  
    Tokenizer(string strGet) 
    {
        str = strGet;
    }

    bool hasNext() 
    {
        return !str.empty();
    }

    bool hasDefine() 
    {
        return ret.type != UNDEFINE;
    }

    Data nextToken();

};

Data Tokenizer::nextToken()
{
    smatch m;
    
    for (auto rgx = tokenDefine.begin(); rgx != tokenDefine.end(); ++rgx) {
        if (regex_search(str, m, rgx->first)) {
            string get = m.str();
            str = m.suffix().str();

            // trim space
            if (rgx->second == SPACE)
                rgx = tokenDefine.begin();

            else if (rgx->second == NUMBER)
                return ret = Data(rgx->second, stoi(get));

            else 
                return ret = Data(rgx->second, get[0]);
        } 
    }   

    cout << "\t"  << str << endl;
    cout << "\t^ is not a legitimate character." << endl;

    return Data(UNDEFINE, ' ');
}

list<Data> getToken(string str)
{
    list<Data> ret;
    Tokenizer tokenizer(str);
    Data tmp;
    while (tokenizer.hasNext()) {
        tmp = tokenizer.nextToken();     
        if (tokenizer.hasDefine()) {
            ret.push_back(tmp);
        } else {
            break;
        }
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


void syntaxCheck(string str) {
    Stack stack;
    Tokenizer tokenizer(str);
    Data tmp;
    while (tokenizer.hasNext()) {
        tmp = tokenizer.nextToken();     
        if (tokenizer.hasDefine()) {

        } else {
            break;
        }
    }
}

int task1()
{
    string expr;

    // input
    cin.ignore();
    getline(cin, expr);

    try {
        // check syntax
        syntaxCheck(expr);

    } catch (invalid_argument &e) {
        cout << e.what();
    } catch (exception &e) {
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

