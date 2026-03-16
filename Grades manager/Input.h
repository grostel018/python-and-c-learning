#pragma once
#include <string>
#include <limits>

// Input helpers for validated console input
// All functions perform validation loops until valid input is provided

double takeNumber();
std::string takeString();
std::string takePassword();
std::string takeUsername();
int takeIntInRange(int minV, int maxV);
std::string takeLineNonEmpty();

// Constants for input validation (also defined in database.h, but kept here for convenience)
namespace InputConstants {
    constexpr int MIN_USERNAME_LENGTH = 3;
    constexpr int MAX_USERNAME_LENGTH = 20;
    constexpr int MIN_PASSWORD_LENGTH = 6;
    constexpr std::streamsize MAX_LINE_LENGTH = std::numeric_limits<std::streamsize>::max();
}
