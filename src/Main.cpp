// Main.cpp - the entry point and logic for Todo Hub

#include <cctype>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Colors.h"
#include "Task.h"
#include "TodoList.h"

int main() {
    using namespace std;

    TodoList todoList;
    todoList.LoadTasks("tasks.txt");

    while (true) {
        TodoList::ClearTerminal();
        cout << YELLOW;
        cout << "TODO HUB 1.0.0\n";
        cout << "--------------\n\n";
        cout << DEFAULT;
        todoList.DisplayTasks();

        bool actionDone = false;
        while (!actionDone) {
            cout << "\n> ";
            string commandStr;
            cin >> commandStr;
            TodoList::Commands command = todoList.StrToCommand(commandStr);

            switch (command) {
                case TodoList::Commands::ADD: {
                    string description;
                    cin.get();
                    getline(cin, description);
                    todoList.AddTask({description, false});
                    actionDone = true;
                    break;
                }
                case TodoList::Commands::REMOVE: {
                    string index;
                    cin >> index;
                    try {
                        stoi(index);
                    } catch (const invalid_argument& e) {
                        cerr << RED << "Parameter " << index << " is not an integer." << DEFAULT;
                        TodoList::Sleep(1000);
                        actionDone = true;
                        break;
                    }
                    todoList.RemoveTask(stoi(index));
                    actionDone = true;
                    break;
                }
                case TodoList::Commands::COMPLETE: {
                    string index;
                    cin >> index;
                    try {
                        stoi(index);
                    } catch (const invalid_argument& e) {
                        cerr << RED << "Parameter " << index << " is not an integer." << DEFAULT;
                        TodoList::Sleep(1000);
                        actionDone = true;
                        break;
                    }
                    todoList.MarkCompleted(stoi(index));
                    actionDone = true;
                    break;
                }
                case TodoList::Commands::UNCOMPLETE: {
                    string index;
                    cin >> index;
                    try {
                        stoi(index);
                    } catch (const invalid_argument& e) {
                        cerr << RED << "Parameter " << index << " is not an integer." << DEFAULT;
                        TodoList::Sleep(1000);
                        actionDone = true;
                        break;
                    }
                    todoList.MarkNotCompleted(stoi(index));
                    actionDone = true;
                    break;
                }
                case TodoList::Commands::RENAME: {
                    string index, newDescription;
                    cin >> index;
                    getline(cin, newDescription);
                    newDescription.erase(0, 1);  // Erase space in front of new description
                    try {
                        stoi(index);
                    } catch (const invalid_argument& e) {
                        cerr << RED << "Parameter " << index << " is not an integer." << DEFAULT;
                        TodoList::Sleep(1000);
                        actionDone = true;
                        break;
                    }
                    todoList.SetDescription(stoi(index), newDescription);
                    actionDone = true;
                    break;
                }
                case TodoList::Commands::MOVE: {
                    string oldIndex, newIndex;
                    cin >> oldIndex >> newIndex;
                    try {
                        stoi(oldIndex);
                    } catch (const invalid_argument& e) {
                        cerr << RED << "Parameter " << oldIndex << " is not an integer." << DEFAULT;
                        TodoList::Sleep(1000);
                        actionDone = true;
                        break;
                    }
                    try {
                        stoi(newIndex);
                    } catch (const invalid_argument& e) {
                        cerr << RED << "Parameter " << newIndex << " is not an integer." << DEFAULT;
                        TodoList::Sleep(1000);
                        actionDone = true;
                        break;
                    }
                    todoList.MoveTask(stoi(oldIndex), stoi(newIndex));
                    actionDone = true;
                    break;
                }
                case TodoList::Commands::SET_DUE_DATE: {
                    string index, dateStr;
                    cin >> index >> dateStr;
                    try {
                        stoi(index);
                    } catch (const invalid_argument& e) {
                        cerr << RED << "Parameter " << index << " is not an integer." << DEFAULT;
                        TodoList::Sleep(1000);
                        actionDone = true;
                        break;
                    }
                    tm date{};
                    istringstream ss(dateStr);
                    ss >> get_time(&date, "%Y/%m/%d");
                    if (ss.fail() || date.tm_year < 0 || date.tm_year > 1100) {
                        cerr << RED << "Failed to parse date. Date should be in YYYY/MM/DD format." << DEFAULT;
                        TodoList::Sleep(1000);
                        actionDone = true;
                        break;
                    }
                    todoList.SetDueDate(stoi(index), date);
                    actionDone = true;
                    break;
                }
                case TodoList::Commands::CLEAR_DUE_DATE: {
                    string index;
                    cin >> index;
                    try {
                        stoi(index);
                    } catch (const invalid_argument& e) {
                        cerr << RED << "Parameter " << index << " is not an integer." << DEFAULT;
                        TodoList::Sleep(1000);
                        actionDone = true;
                        break;
                    }
                    todoList.ClearDueDate(stoi(index));
                    actionDone = true;
                    break;
                }
                case TodoList::Commands::CLEAR: {
                    cout << "Are you sure you want to clear all tasks? Type Y to confirm: ";
                    char choice;
                    cin >> choice;
                    if (toupper(choice) == 'Y') {
                        todoList.ClearTodoList();
                    } else {
                        cout << "Canceled.";
                        TodoList::Sleep(1000);
                    }
                    actionDone = true;
                    break;
                }
                case TodoList::Commands::HELP:
                    todoList.ViewHelp();
                    actionDone = true;
                    break;
                case TodoList::Commands::QUIT:
                    todoList.SaveTasks("tasks.txt");
                    return 0;
                case TodoList::Commands::UNKNOWN:
                    cerr << RED << "Invalid command." << DEFAULT;
                    break;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
