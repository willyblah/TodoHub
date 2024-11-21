#include <iostream>
#include <stdexcept>
#include <string>

#include "Task.h"
#include "TodoList.h"

int main() {
    using namespace std;

    TodoList todoList;

    while (true) {
        TodoList::ClearTerminal();
        cout << "TODO HUB 1.0.0\n";
        cout << "--------------\n\n";

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
                        cerr << "Parameter " << index << " is not an integer.";
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
                        cerr << "Parameter " << index << " is not an integer.";
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
                        cerr << "Parameter " << index << " is not an integer.";
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
                    newDescription.erase(0, 1);
                    try {
                        stoi(index);
                    } catch (const invalid_argument& e) {
                        cerr << "Parameter " << index << " is not an integer.";
                        TodoList::Sleep(1000);
                        actionDone = true;
                        break;
                    }
                    todoList.SetDescription(stoi(index), newDescription);
                    actionDone = true;
                    break;
                }
                case TodoList::Commands::QUIT:
                    return 0;
                case TodoList::Commands::UNKNOWN:
                    cerr << "Invalid command.";
                    break;
            }
        }
    }
}
