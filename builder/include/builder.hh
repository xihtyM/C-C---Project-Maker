#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include "utf8.h"
#include "null.h"


#define HELP_TEXT \
    "Commands:\n" \
    " -h: Prints all possible commands.\n" \
    " -c: Creates a C++ project.\n" \
    " [name]: Create a new project, [name] being the project name.\n" \
    "Syntax: *(-h|[name]) (-c)\n" \
    "\n"

#define BUILD_PY \
    "import os\n" \
    "\n" \
    "def build_project(name: str):\n" \
    "    command = COMPILER + \" -o %s.exe -O2 -s \" % name\n" \
    "\n" \
    "    for entry in os.scandir(\"impl\"):\n" \
    "        if not entry.is_file() or not entry.name.endswith((\".cc\", \".c\", \".cpp\")):\n" \
    "            continue\n" \
    "        \n" \
    "        command += \"\\\"%s\\\" \" % entry.path\n" \
    "    \n" \
    "    command += MAIN_FILE\n" \
    "    \n" \
    "    os.system(command)\n" \
    "\n" \
    "build_project(\""

#define MAIN_CODE \
    "\n" \
    "int main(int argc, char *argv[])\n" \
    "{\n" \
    "    \n" \
    "    return 0;\n" \
    "}\n"


typedef struct ARGS
{
    std::string project_name;
    bool is_cpp;
} ARGS;


std::unique_ptr<ARGS> parse_args(
    std::vector<std::string> args);


/// @brief Initialises project.
/// @param name string containing project name.
/// @param is_cpp false if `main.c` true if `main.cc`.
/// @return True on success, false on failure.
bool create_project(
    std::string name,
    bool is_cpp);
