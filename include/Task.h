// Task.h - defines the Task struct

#ifndef TASK_H
#define TASK_H

#include <ctime>
#include <string>

struct Task {
    std::string description;
    bool isCompleted;
    std::tm dueDate = {};
};

#endif  // TASK_H
