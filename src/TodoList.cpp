// TodoList.cpp - implementation for TodoList class

#include "TodoList.h"

#include <direct.h>  // For _chdir()
#include <unistd.h>  // For chdir()

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "Colors.h"

void TodoList::DisplayTasks() {
    int i = 1;
    for (const Task& task : tasks) {
        std::cout << BOLD << i << ". " << task.description << DEFAULT;
        if (task.dueDate.tm_year >= 0 && task.dueDate.tm_mon >= 0 && task.dueDate.tm_mday > 0) {
            std::cout << BLUE << " (Due " << task.dueDate.tm_year + 1900 << "/"
                      << task.dueDate.tm_mon + 1 << "/" << task.dueDate.tm_mday << ")" << DEFAULT;
        }
        if (task.isCompleted) {
            std::cout << GREEN << " [COMPLETED]" << DEFAULT;
        }
        std::cout << "\n";
        i++;
    }
}

void TodoList::AddTask(const Task& task) { tasks.emplace_back(task); }

void TodoList::RemoveTask(const int index) {
    if (!IsIndexValid(index)) {
        return;
    }
    tasks.erase(tasks.begin() + index - 1);
}

void TodoList::MarkCompleted(const int index) {
    if (!IsIndexValid(index)) {
        return;
    }
    tasks[index - 1].isCompleted = true;
}

void TodoList::MarkNotCompleted(const int index) {
    if (!IsIndexValid(index)) {
        return;
    }
    tasks[index - 1].isCompleted = false;
}

void TodoList::SetDescription(const int index, const std::string& newDescription) {
    if (!IsIndexValid(index)) {
        return;
    }
    tasks[index - 1].description = newDescription;
}

void TodoList::SetDueDate(const int index, const std::tm& date) {
    if (!IsIndexValid(index)) {
        return;
    }
    tasks[index - 1].dueDate = date;
}

void TodoList::ViewHelp() {
    std::string originalWorkingDirectory = std::filesystem::current_path().string();

#ifdef _WIN32  // Change the working directory to docs/
    _chdir("..");
    _chdir("..\\docs");
    std::ifstream fin("help.txt");
#else
    chdir("..");
    chdir("../docs");
    std::ifstream fin("help.txt");
#endif

    ClearTerminal();

    if (!fin.is_open()) {
        std::cerr << RED << "Error opening file help.txt\n" << DEFAULT;
    }

    std::string line;
    while (std::getline(fin, line)) {
        std::cout << line << "\n";
    }
    fin.close();
    std::cout << "\nPress enter to continue...";
    std::cin.get();
    std::cin.get();

#ifdef _WIN32  // Change the working directory back to the program directory
    _chdir(originalWorkingDirectory.c_str());
#else
    chdir(originalWorkingDirectory.c_str());
#endif
}

void TodoList::LoadTasks(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        fin.close();
        return;
    }
    int size;
    fin >> size;
    for (int i = 0; i < size; i++) {
        std::string description;
        bool isCompleted;
        std::tm date;
        fin >> description >> isCompleted >> date.tm_year >> date.tm_mon >> date.tm_mday;
        std::replace(description.begin(), description.end(), '_', ' ');
        AddTask({description, isCompleted, date});
    }
    fin.close();
}

void TodoList::SaveTasks(const std::string& filename) {
    // Example:
    // 3
    // Do_homework 0 125 8 25
    // Shop_for_food 0
    // Edit_code 1

    std::ofstream fout(filename);
    int size = tasks.size();
    fout << size;
    for (const Task& task : tasks) {
        std::string description = task.description;
        // Convert spaces to underscores
        std::replace(description.begin(), description.end(), ' ', '_');
        fout << "\n"
             << description << " " << task.isCompleted << " " << task.dueDate.tm_year << " "
             << task.dueDate.tm_mon << " " << task.dueDate.tm_mday;
    }
    fout.close();
}

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
    } else if (str == "due") {
        return SET_DUE_DATE;
    } else if (str == "help") {
        return HELP;
    } else if (str == "q") {
        return QUIT;
    } else {
        return UNKNOWN;
    }
}

bool TodoList::IsIndexValid(const int index) {
    if (index < 1 || index > tasks.size()) {
        std::cerr << RED << "Invalid index." << DEFAULT;
        Sleep(1000);
        return false;
    } else {
        return true;
    }
}

void TodoList::ClearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
