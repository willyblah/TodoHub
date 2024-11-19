#include "TodoList.h"

#include <cstdlib>
#include <iostream>
#include <string>

void TodoList::DisplayTasks() {
    int i = 1;
    for (const Task& task : tasks) {
        std::cout << i << ". " << task.description;
        if (task.isCompleted) {
            std::cout << " [COMPLETED]";
        }
        std::cout << "\n";
        i++;
    }
}

void TodoList::AddTask(const Task& task) { tasks.emplace_back(task); }

TodoList::Commands TodoList::StrToCommand(const std::string& str) {
    if (str == "add") {
        return ADD;
    } else if (str == "rm") {
        return REMOVE;
    } else if (str == "do") {
        return COMPLETE;
    } else if (str == "undo") {
        return UNCOMPLETE;
    } else if (str == "rn") {
        return RENAME;
    } else if (str == "mv") {
        return MOVE;
    } else if (str == "help") {
        return HELP;
    } else if (str == "q") {
        return QUIT;
    } else {
        return UNKNOWN;
    }
}

void TodoList::ClearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif  // _WIN32
}
