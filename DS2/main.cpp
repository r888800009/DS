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
                errorHandling("Error: Command not found!"); #include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

#define MENU_COPY_FILE        1 
#define MENU_FILTER_FILE      2
#define MENU_MERGE_FILE       3
#define MENU_QUIT             4
static bool inputSuccess;

void errorHandling(string message);

class Data
{
public:
	int college_num;
	string college_name;
	int department_num;
	string department_name;
	string class_type;
	string class_rank;
	int student_num;
	int teacher_num;
	int graduate_num;
	string city;
	string system_type;

	friend istream &operator>>(istream & in, Data & data)
	{
		int count = 0;
		bool digit = true;
		inputSuccess = true;
		string input, temp;
		getline(in, input);
		input += '\t';
		if (in) {
			for (int i = 0; i < input.length(); i++) {
				if (input[i] != '\t') {
					temp += input[i];
					if (!('0' <= input[i] && input[i] <= '9')) digit = false;
				}
				else {
					switch (count)
					{
					case 0:
						if (digit) data.college_num = stoi(temp);
						else inputSuccess = false;
						break;
					case 1:
						data.college_name = temp;
						break;
					case 2:
						if (digit) data.department_num = stoi(temp);
						else inputSuccess = false;
						break;
					case 3:
						data.department_name = temp;
						break;
					case 4:
						data.class_type = temp;
						break;
					case 5:
						data.class_rank = temp;
						break;
					case 6:
						if (digit) data.student_num = stoi(temp);
						else inputSuccess = false;
						break;
					case 7:
						if (digit) data.teacher_num = stoi(temp);
						else inputSuccess = false;
						break;
					case 8:
						if (digit) data.graduate_num = stoi(temp);
						else inputSuccess = false;
						break;
					case 9:
						data.city = temp;
						break;
					case 10:
						data.system_type = temp;
						break;
					}
					temp = "";
					count++;
					digit = true;
				}
			}
			if (count != 11) inputSuccess = false;
		}
		return in;
	}
	friend ostream& operator<<(ostream & out, Data & data)
	{

		out << setw(4) << setfill('0') << data.college_num << '\t' << data.college_name << '\t'
			<< data.department_num << '\t' << data.department_name << '\t'
			<< data.class_type << '\t' << data.class_rank << '\t'
			<< data.student_num << '\t' << data.teacher_num << '\t'
			<< data.graduate_num << '\t' << data.city << '\t'
			<< data.system_type << endl;
		return out;
	}
};

class HandleFile
{
	vector<Data> database;
public:
	bool task1() {
		fstream fin;
		fstream fout;
		fin.open("D:/code/code_cpp/Project5/Debug/input204.txt", ios::in);
		fout.open("D:/code/code_cpp/Project5/Debug/input204_copy.txt", ios::out,ios::trunc);
		if (!fin) errorHandling("Error : there is no such file!");
		else {
			string str;
			getline(fin, str);
			getline(fin, str);
			getline(fin, str);
			// skip three line

			Data temp;
			while (fin >> temp) { // >> overload
				if (inputSuccess) database.push_back(temp);
			}
			for (vector<Data>::iterator i = database.begin(); i != database.end(); i++) {
				fout << *i; // << overload
			}
			cout << database.size() << endl;
		}
		return 0;
	}
};

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

		HandleFile f;

		// 判斷選擇的內容
		switch (mode) {
		case MENU_QUIT:
			return 0;               // 退出
		case MENU_COPY_FILE:
			result = f.task1();       // 任務1
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
