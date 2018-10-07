#include <iostream>


#define MENU_QUIT       0
#define MENU_CHECK      1
#define MENU_TOPOSTFIX  2
#define MENU_SOLVE      3

using namespace std;

class LinkedList {

public:


};

class Stack {
    LinkedList list;
public:
    void pop()
    {
    }
    
    void top()
    {

    }
    
    void push()
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

