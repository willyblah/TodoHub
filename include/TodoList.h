#ifndef TODOLIST_H
#define TODOLIST_H

#include <string>
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
        MOVE,
        HELP,
        QUIT,
        UNKNOWN
    };

    void DisplayTasks();

    void AddTask(const Task& task);
    void RemoveTask(const int index);

    void MarkCompleted(const int index);
    void MarkNotCompleted(const int index);

    void SetDescription(const int index);

    void MoveTask(const int oldIndex, const int newIndex);

    void ViewHelp();

    TodoList::Commands StrToCommand(const std::string& str);

    void LoadTasks(const std::string& filename);
    void SaveTasks(const std::string& filename);

    static void ClearTerminal();

private:
    std::vector<Task> tasks;
};

#endif  // TODOLIST_H
