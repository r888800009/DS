#include <iostream>
#include <algorithm>
#include <list>

#define MENU_QUIT       0
#define MENU_CHECK      1
#define MENU_TOPOSTFIX  2
#define MENU_SOLVE      3

#define ASCII_SIZE 256

using namespace std;

int priority[ASCII_SIZE];

class Stack {
    list<char> stackList;
public:
    void pop()
    {   
        stackList.pop_back();
    }
    
    char top()
    {
       return stackList.back(); 
    }
    
    void push(char c)
    {
        stackList.push_back(c);
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

int task1()
{
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
        if (result)
            return 1;
        else cout << endl;
    }

    return 0;
}

