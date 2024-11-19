#include <iostream>
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
            std::string commandStr;
            cin >> commandStr;
            TodoList::Commands command = todoList.StrToCommand(commandStr);
            switch (command) {
                case TodoList::Commands::ADD: {
                    std::string description;
                    cin.get();
                    getline(cin, description);
                    todoList.AddTask({description, false});
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
