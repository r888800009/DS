// 第11組 106127116 許逸翔 10612150 林詠翔 資訊二甲
// must to use -std=c++11 or higher version

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>
#include <ctime>
using namespace std;

#define MENU_QUIT             0
#define MENU_COPY_FILE        1
#define MENU_FILTER_FILE      2
#define MENU_MERGE_FILE       3

// sort column
#define DATA_SIZE             4
#define DATA_OID              0
#define DATA_ARRIVAL          1
#define DATA_DEURATION        2
#define DATA_TIMEOUT          3

// cancel & timeout cloumn
#define DATA_OID              0
#define DATA_CID              1
#define DATA_DELAY            2
#define DATA_ABORT_DEPARTURE  3

static bool inputSuccess;
void errorHandling(string message);

string getOnlyDigits(string str)
{
    string tmp = "";
    for (char c : str)
        if (isdigit(c)) tmp += c;

    return tmp;
}

int stringToInt(string str)
{
    try {
        // "1,223,234,234,234"
        if (str[0] == '\"')
            str = getOnlyDigits(str);

        return stoi(str);
    }
    catch (exception e) {
        string temp = "ERROR : stoi( " + str + " ) error!";
        errorHandling(temp);
        return -1; // return error value
    }
}

// sort & cancel & timeout DATA use
class Data {
public:
    int column[DATA_SIZE];

    Data() {}

    // used to creat cancel & timeout cloumn
    Data(int num1, int num2, int num3, int num4)
    {
        column[DATA_OID] = num1;
        column[DATA_CID] = num2;
        column[DATA_DELAY] = num3;
        column[DATA_ABORT_DEPARTURE] = num4;
    }

    friend bool operator<(const Data &i, const Data &j)
    {
        if (j.column[DATA_ARRIVAL] > i.column[DATA_ARRIVAL]) return true;
        else if (j.column[DATA_ARRIVAL] < i.column[DATA_ARRIVAL]) return false;
        else if (j.column[DATA_OID] > i.column[DATA_OID]) return true;
        else return false;
    }

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
                // change to int
                int num = stringToInt(temp);
                if (num == -1) inputSuccess = false;
                else data.column[count++] = num;
                temp = "";
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

class LinkedList {
private:

    typedef struct node {
        Data data;
        node *next, *prev;
    } node;

    node *firstNode, *endNode;

public:

    LinkedList()
    {
        firstNode = endNode = nullptr;
    }

    void pop()
    {
        // mark remove node
        node *rmNode = firstNode;

        if (rmNode == nullptr) {  // nothing
            throw "LinkedList empty!!";

        }
        else if (firstNode == endNode) {           // only one node
            endNode = firstNode = nullptr;

        }
        else {                             // not only one
         // replace end node with prev
            firstNode = firstNode->next;
            // unlink
            firstNode->prev = nullptr;
        }

        // free memory
        delete rmNode;
        rmNode = nullptr;
    }

    void pop_back()
    {
        // mark remove node
        node *rmNode = endNode;

        if (rmNode == nullptr) {  // nothing
            throw "LinkedList empty!!";

        }
        else if (firstNode == endNode) {           // only one node
            endNode = firstNode = nullptr;

        }
        else {                             // not only one
         // replace end node with prev
            endNode = rmNode->prev;
            // unlink
            endNode->next = nullptr;
        }

        // free memory
        delete rmNode;
        rmNode = nullptr;
    }

    void push_back(const Data d)
    {
        node *newNode = new node;
        newNode->data = d;
        newNode->next = nullptr;

        if (firstNode == nullptr) {  // no node
            firstNode = endNode = newNode;
            newNode->prev = nullptr;

        }
        else {              // have node
            // set new node prev
            newNode->prev = endNode;
            // set prev node link to newNode
            endNode->next = newNode;
            // ptr to new
            endNode = newNode;
        }
    }

    int size()
    {
        int count = 0;
        node *cur = firstNode;   // current

        while (cur != nullptr)
            cur = cur->next, count++;

        return count;
    }

    bool empty()
    {
        return firstNode == nullptr;
    }

    Data top()
    {
        return firstNode->data;
    }

    Data back()
    {
        return endNode->data;
    }

    void print()
    {
        // current
        node *cur = firstNode;

        while (cur != nullptr) {
            cout << cur->data;
            cout << (cur != endNode ? ',' : '\n');
            cur = cur->next;
        }

        cout.flush();
    }

    void clear()
    {
        node *cur = firstNode;   // current
        firstNode = nullptr;
        while (cur != nullptr) {
            if (cur->prev != nullptr)
                delete cur->prev;

            cur = cur->next;
        }
    }

    // range based for
    class iterator {
        node *current;

    public:
        iterator(node *node)
        {
            current = node;
        }

        Data operator*()
        {
            return current->data;
        }

        bool operator!=(const iterator &it2)
        {
            return current != it2.current;
        }

        iterator &operator++()
        {
            current = current->next;
            return *this;
        }
    };

    iterator begin()
    {
        return iterator(firstNode);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

};

class Queue {
    LinkedList queueList;
public:

    int size()
    {
        return queueList.size();
    }

    bool empty()
    {
        return queueList.empty();
    }

    Data top()
    {
        return queueList.top();
    }

    void pop()
    {
        queueList.pop();
    }

    void push(Data c)
    {
        queueList.push_back(c);
    }

    void print()
    {
        queueList.print();
    }

    void clear()
    {
        queueList.clear();
    }

};

class Chef: public Queue{
    int order;
    int idleTime;
public:
    Chef() : idleTime(0), order(0){}

    int getOrder()
    {
        return order;
    }

    void setOrder(int o)
    {
        order = o;
    }

    int getIdleTime()
    {
        return idleTime;
    }

    void setIdleTime(int time)
    {
        idleTime = time;
    }
};

class Manager {
    Chef* chef_arr;
    int size; // chef_arr.size
    vector<Data> cancel;
    vector<Data> timeout;

    void handleOrder(Chef &chef, const Data &data)
    {
        if (chef.getIdleTime() < data.column[DATA_ARRIVAL])
            chef.setIdleTime(data.column[DATA_ARRIVAL]); // time jump

        int final_time = chef.getIdleTime() + data.column[DATA_DEURATION];
        int cancel_delay_time = chef.getIdleTime() - data.column[DATA_ARRIVAL];

        if (data.column[DATA_TIMEOUT] <= chef.getIdleTime())
            cancelOrder(chef, data, cancel_delay_time);
        else if (data.column[DATA_TIMEOUT] < final_time)
            timeoutOrder(chef, data, final_time);
        else
            chef.setIdleTime(final_time);
    }

    void cancelOrder(Chef &chef, const Data &data, int cancel_delay_time)
    {
        if(cancel_delay_time == 0) {
            cancel.push_back(Data(
                        data.column[DATA_OID],
                        chef.getOrder(),
                        cancel_delay_time,
                        data.column[DATA_ARRIVAL]));
        } else {
            cancel.push_back(Data(
                        data.column[DATA_OID],
                        chef.getOrder(),
                        cancel_delay_time,
                        chef.getIdleTime()));
        }
    }

    void timeoutOrder(Chef &chef, const Data &data, int final_time) {
        timeout.push_back(Data(
                    data.column[DATA_OID],
                    chef.getOrder(),
                    chef.getIdleTime() - data.column[DATA_ARRIVAL],
                    final_time));

        chef.setIdleTime(final_time);
    }

public:
    Manager(int num): size(num)
    {
        chef_arr = new Chef[num];
        for(int i = 0; i < num; i++)
            chef_arr[i].setOrder(i+1);
    }

    void handleQueue(const Data *data = nullptr)
    {
        int min;
        while (true) {
            min = -1;
            for (int i = 0; i < size; i++) {
                if (!chef_arr[i].empty() &
                   // check data only data is not NULL when
                   (data == nullptr || chef_arr[i].getIdleTime() <= data->column[DATA_ARRIVAL])) {

                    if (min == -1)
                        min = i;
                    else if (chef_arr[i].getIdleTime() < chef_arr[min].getIdleTime())
                        min = i;
                    else if (chef_arr[i].getIdleTime() == chef_arr[min].getIdleTime() &&
                            chef_arr[i].top().column[DATA_ARRIVAL] < chef_arr[min].getIdleTime())
                        min = i;
                }
            }

            if (min == -1)
                break;
            handleOrder(chef_arr[min], chef_arr[min].top());
            chef_arr[min].pop();
        }
    }

    void action(const Data &data)
    {
        handleQueue(&data);

        // handle order immediately
        for (int i = 0; i < size; i++) {
            if (chef_arr[i].empty() && chef_arr[i].getIdleTime() <= data.column[DATA_ARRIVAL]) {
                handleOrder(chef_arr[i], data);
                return;
            }
        }

        // push to queue
        int min = 0;
        for (int i = 0; i < size; i++) {
            if (chef_arr[i].size() < chef_arr[min].size()) min = i;
        }

        if (chef_arr[min].size() < 3) {
            chef_arr[min].push(data);
            return;
        }

        // cancel order
        Chef* temp = new Chef();
        cancelOrder(*temp, data, 0);

    }

    vector<Data> &getCancel()
    {
        return cancel;
    }
    vector<Data> &getTimeout()
    {
        return timeout;
    }
};

class HandleFile {
    fstream fin;
    fstream fout;
    int total_delay;
    int fail_order;

    void dropHeader(fstream &file, int num)
    {
        for (int i = 0; i < num; ++i)
            file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void save(string saveName, vector<Data> &database, string column[])
    {
        // closs all file
        if (fin.is_open())
            fin.close();

        fout.open(saveName, ios::out | ios::trunc);

        for (int i = 0; i < DATA_SIZE; i++)
            fout << column[i] << (i < DATA_SIZE - 1 ? '\t' : '\n');

        for (int i = 0; i < database.size(); i++)
            fout << database[i];         // << overload

        fout.close();

        // cout << "Total number of records: " << database.size() << endl;
    }

    void save(string saveName, vector<Data> &database, string title, string column[])
    {
        // closs all file
        if (fin.is_open())
            fin.close();

        fout.open(saveName, ios::out | ios::app);

        fout << "\t[" << title << "]\n" << '\t';
        for (int i = 0; i <= column->size(); i++)
            fout << column[i] << (i < column->size() ? '\t' : '\n');

        for (int i = 0; i < database.size(); i++) {
            fout << '[' << i + 1 << "]\t" << database[i];         // << overload
            total_delay += database[i].column[DATA_DELAY];
            fail_order++;
        }

        fout.close();

        cout << "Total number of records: " << database.size() << endl;
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

            // if (prefix == "input" && prefix == "sort")
            dropHeader(file, 1);

            return fileName;
        }
    }

    // use in task1
    bool task1_input(string &fileName)
    {
        fileName = fileInput(fin, "Input (401, 402, ...[0]Quit): ", "input");

        // if fileName == "" then quit to menu
        return fileName != "";  // {quit: 0, continue: 1}
    }

    void shell_sort(vector<Data> &arr)
    {
        int len = arr.size();
        for (int d = len / 2; d >= 1; d /= 2) {
            for (int i = d; i < len; i++) {
                Data temp = arr[i];
                int j = i - d;
                for (; j >= 0 && temp < arr[j]; j -= d) {
                    arr[j + d] = arr[j];
                }
                arr[j + d] = temp;
            }
        }
    }

    // use in task2_3
    bool task2_3_input(string &fileName)
    {

        fileName = fileInput(fin, "Input (401, 402, ...[0]Quit): ", "sort");

        // if fileName == "" then quit to menu
        return fileName != "";  // {quit: 0, continue: 1}
    }

    void summary(string saveName, int total)
    {
        if (fin.is_open())
            fin.close();

        fout.open(saveName, ios::out | ios::app);

        fout << "[Total Delay]" << endl;
        fout << total_delay << " min." << endl;
        fout << "[Failure Percentage]" << endl;
        fout << fixed << setprecision(2) << fail_order/float(total)*100 << " %" << endl;
    }

public:

    bool task1()
    {
        vector<Data> database;
        string fileName;

        // is quit task1?
        if (!task1_input(fileName)) {
            cout << "switch to menu" << endl;
            return 0;
        }

        Data temp;
        clock_t t = clock();
        while (fin >> temp)     // >> overload
            if (inputSuccess) database.push_back(temp);

        cout << "Read File: " << (clock() - t)  << " ms"<< endl;

        t = clock();
        shell_sort(database);
        cout << "Sort File: " << (clock() - t) << " ms" << endl;

        string column[4] = {
            "OID", "Arrival", "Duration", "TimeOut"
        };

        t = clock();
        save("sort" + fileName + ".txt", database, column);
        cout << "Save File: " << (clock() - t) << " ms" << endl;

        return 0;
    }

    bool task2_3(int num, string prefix)
    {
        Manager manager(num);
        string fileName;

        if (!task2_3_input(fileName)) {
            cout << "switch to menu" << endl;
            return 0;
        }

        int total = 0;
        Data temp;
        while (fin >> temp) {     // >> overload
            if (inputSuccess)
                total++, manager.action(temp);
        }

        manager.handleQueue();

        string saveName = prefix + fileName + ".txt";
        total_delay = fail_order = 0;
        fout.open(saveName, ios::out | ios::trunc);
        fout.close();

        // one queue also print "CID"
        string column[4] = {
            "OID", "CID", "Delay", "Abort"
        };

        // cancel
        save(saveName, manager.getCancel(), "Abort List", column);

        // timeout
        column[3] = "Departure";
        save(saveName, manager.getTimeout(), "Timeout List", column);

        summary(saveName, total);

        return 0;
    }

};

int main(int argc, char *argv[])
{
    int mode;                           // 選單選項
    int result;                         // 指令回傳檢查
    while (true) {

        // 輸出選單
        cout << "              MENU              " << endl;
        cout << "* 0. Quit                      *" << endl;
        cout << "* 1. SHELL_SORT                *" << endl;
        cout << "* 2. Simulate one queue        *" << endl;
        cout << "* 3. Simulate two queues       *" << endl;
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
            result = f.task2_3(1, "one");       // 任務2
            break;

        case MENU_MERGE_FILE:
            result = f.task2_3(2, "two");       // 任務3
            break;

        default:
            errorHandling("Error: Command not found!");
            continue;
        }

        // 檢查回傳值是否為successful
        if (result)
            return 1;
        else cout << endl;
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
