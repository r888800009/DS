#include <iostream>
#include <cstring>
using namespace std;
 
#define MENU_COPY_FILE        1 
#define MENU_FILTER_FILE      2
#define MENU_MERGE_FILE       3
#define MENU_QUIT             4

void errorHandling(string message);

int main(int argc, char *argv[])
{
    int mode;                           // 選單選項
    int result;                         // 指令回傳檢查
    while (1) {

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
            case MENU_COPY_FILE:
                // result = task1();       // 任務1
                break;
            case MENU_FILTER_FILE:
                // result = task2();       // 任務2
                break;
            case MENU_MERGE_FILE:
                // result = task3();       // 任務3
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
