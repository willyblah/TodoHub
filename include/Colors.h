// Colors.h - defines escape sequences for printing colored text

#ifndef COLORS_H
#define COLORS_H

#include <string>

const std::string DEFAULT = "\033[0m";
const std::string BOLD = "\033[37;1m";
const std::string RED = "\033[1;31m";
const std::string GREEN = "\033[1;32m";
const std::string BLUE = "\033[1;34m";
const std::string YELLOW = "\033[1;33m";

#endif  // COLORS_H
