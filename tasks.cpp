//  tasks.cpp - Simple task manager!
//  April 11, 2024
//  Kyriakos, kyke@otenet.gr

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#define FILENAME "tasks.txt"

void list_tasks(void);      // Displays a list of tasks
void add_new_task(void);    // User adds a task
void delete_task(void);     // User deletes a task

int main(void)
{
    int selection = 0;

    cout << "Welcome to task manager!" << endl;

    while (1) {
        cout << endl << "Select an option:" << endl << endl;
        cout << "\t1. List tasks" << endl;
        cout << "\t2. Add new task" << endl;
        cout << "\t3. Delete a task" << endl;
        cout << "\t4. Exit" << endl;

        cin >> selection;

        switch (selection) {
        case 1:
            list_tasks();
            break;
        case 2:
            add_new_task();
            break;
        case 3:
            delete_task();
            break;
        case 4:
            exit(0);
            // break;
        default:
            cout << "Invalid option!" << endl;
            break;
        }
    }

    return 0;
}

void list_tasks(void)
{
    fstream file;
    int tasksnum = 0;  // Number of tasks

    file.open(FILENAME, ios::in | ios::out | ios::app);

    if (!file.is_open()) {
        cout << "Text file could not be opened!" << endl;
        exit(1);
    }
    
    cout << endl;

    // Reads text file line by line and displays them. Each line contains a task
    for (string line; getline(file, line); ) {
        tasksnum++;
        if (tasksnum == 1) {
            cout << "Tasks" << endl;
            cout << "-----" << endl;
        }
        cout << tasksnum << ". " << line << endl;
    }

    if (!tasksnum) {
        cout << "File is empty. First add tasks!" << endl;
    }

    cout << endl << "Number of tasks: " << tasksnum << endl;

    file.close();
}

void add_new_task(void)
{
    fstream file;
    string task;

    file.open(FILENAME, ios::out | ios::app);
    
    if (!file.is_open()) {
        cout << "Text file could not be opened!" << endl;
        exit(1);
    }

    cout << "Enter new task:" << endl;

 
    cin.ignore();
    getline(cin, task);

    file << task << endl;

    file.close();
}

void delete_task(void)
{
    fstream file;
    vector<string> tasks;   // Our vector with the tasks
    int tasksnum = 0;
    int selection = 0;

    file.open(FILENAME, ios::in | ios::out | ios::app);

    if (!file.is_open()) {
        cout << "Text file could not be opened!" << endl;
        exit(1);
    }

    cout << endl;

    // Reads text file line by line and puts them to a vector
    for (string line; getline(file, line); ) {
        tasksnum++;
        cout << tasksnum << ". " << line << endl;
        tasks.push_back(line);
    }
    
    file.close();

    if (tasksnum) {
        cout << endl << "Enter number of task to be deleted:" << endl;

        cin.ignore();
        cin >> selection;

        // Checks for valid selection
        // Erases the given task number
        // Clears the text file
        // Saves the updated vector to the text file
        if (selection > 0 && selection <= tasksnum) {
            tasks.erase(tasks.begin() + selection - 1);
            file.open(FILENAME, ios::out | ios::trunc);
            for (string line : tasks) {
                file << line << endl;
            }
            file.close();
        }
        else {
            cout << "Invalid option!" << endl;
        }
    }
    else {
        cout << "File is empty. First add tasks!" << endl;
    }
}