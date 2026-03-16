#pragma once
#include "Models.h"

// UI delimiter constants
namespace UIDelimiter {
    constexpr const char* DELIMITER = "********************************************************************************************";
    constexpr const char* SUB_DELIMITER = "----------------------------------------";
}

void taskDelimeter();
void welcome();
void printCommands();
void printMenu();
void printMenuCommands();

void displayStudentInfo(const Student& s);

// Const correctness: functions that only read should take const references
[[nodiscard]] std::string formatGrade(double grade);
[[nodiscard]] std::string formatGPA(double gpa);
