// TodoList.h - the TodoList class

#ifndef TODOLIST_H
#define TODOLIST_H

#include <chrono>
#include <ctime>
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
        MOVE,
        SET_DUE_DATE,
        HELP,
        QUIT,
        UNKNOWN
    };

    // Displays the to-do list.
    void DisplayTasks();

    // Adds a task to the end of the to-do list.
    void AddTask(const Task& task);

    // Removes the task at a specified index.
    void RemoveTask(const int index);

    // Marks a task as completed.
    void MarkCompleted(const int index);

    // Marks a task as incomplete.
    void MarkNotCompleted(const int index);

    // Sets the description of the task at a specified index.
    void SetDescription(const int index, const std::string& newDescription);

    // Moves the task at `oldIndex` to `newIndex`.
    void MoveTask(const int oldIndex, const int newIndex);

    // Sets the due date of the task at a specified intex.
    void SetDueDate(const int index, const std::tm& date);

    // Displays the help document (docs/help.txt).
    void ViewHelp();

    // Load tasks from file.
    void LoadTasks(const std::string& filename);

    // Save tasks to file.
    void SaveTasks(const std::string& filename);

    // Converts a Command type to the corresponding string.
    TodoList::Commands StrToCommand(const std::string& str);

    // Uses the clear or cls command to clear the terminal screen.
    static void ClearTerminal();

    // Makes the program pause for `duration` milliseconds.
    inline static void Sleep(const int duration) {
        std::this_thread::sleep_for(std::chrono::milliseconds(duration));
    }

private:
    std::vector<Task> tasks;

    // Checks if an index is valid and outputs an error message if invalid.
    bool IsIndexValid(const int index);
};

#endif  // TODOLIST_H
