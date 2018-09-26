#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
 
#define MENU_COPY_FILE        1 
#define MENU_FILTER_FILE      2
#define MENU_MERGE_FILE       3
#define MENU_QUIT             4

typedef struct college { 
   
    // college id and name
    int id; 
    string name;

    // department id
    int departmentId;

    // department name
    string departmentName;

    // day / extension education
    string dayAndExtEdu;

    // Educational stage
    string stage;

    // number of students, teachers, graduates
    int students, teachers, graduates;
    
    // loaction
    string city;

    // type normal or general etc..
    string type;

} row;

void errorHandling(string message);

class database {
    int open(string);
    int save();

    // merge(file2Name)
    int merge(string);

    int query(int, int);
      
private:
    string fileName;
    vector<row> rows;
};

int main(int argc, char *argv[])
{
    // Menu mode and result for check successful
    int mode, result;

    while (1) {

        // print the menu
        cout << "              MENU              " << endl;
        cout << "* 1. COPY (Read & Save a file) *" << endl;
        cout << "* 2. FILTER (Reduce a file)    *" << endl;
        cout << "* 3. MERGE (Join two files)    *" << endl;
        cout << "* 4. Quit                      *" << endl;
        cout << "choice: ";

        // select menu
        cin >> mode;
         
        // execute selected action
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

        // check result of successful
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

    // print Error message
    cout << message << endl;
}
