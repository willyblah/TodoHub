#ifndef TODOLIST_H
#define TODOLIST_H

#include <chrono>
#include <string>
#include <thread>
#include <vector>

#include "Task.h"

class TodoList {
public:
    enum Commands {
        ADD,
        REMOVE,
        COMPLETE,
        UNCOMPLETE,
        RENAME,
        HELP,
        QUIT,
        UNKNOWN
    };

    void DisplayTasks();

    void AddTask(const Task& task);
    void RemoveTask(const int index);

    void MarkCompleted(const int index);
    void MarkNotCompleted(const int index);

    void SetDescription(const int index, const std::string& newDescription);

    void ViewHelp();

    TodoList::Commands StrToCommand(const std::string& str);

    void LoadTasks(const std::string& filename);
    void SaveTasks(const std::string& filename);

    static void ClearTerminal();
    inline static void Sleep(const int duration) {
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    }

private:
    std::vector<Task> tasks;
};

#endif  // TODOLIST_H
