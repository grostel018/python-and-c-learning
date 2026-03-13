/**
 * Input.cpp
 *
 * Utility helpers for validated console input used by the application UI.
 *
 * Notes:
 *  - All functions read from std::cin and perform validation loops until valid input is provided.
 *  - These helpers perform simple validation and echo input to the console. They are NOT secure:
 *    do not use `takePassword()` for sensitive passwords in production (input is echoed and stored in memory).
 */

#include "Input.h"
#include <iostream>
#include <cctype>
#include "UI.h"
#include <limits>

/**
 * @brief Prompt the user for a floating-point number and validate input.
 *
 * Repeatedly reads from standard input until a valid floating-point value is entered.
 * Consumes the remainder of the line after successful extraction to avoid leftover characters
 * interfering with subsequent reads.
 *
 * Behaviour:
 *  - Prompts with: "Enter numbers : "
 *  - On success prints: "Input registered successfully"
 *  - On failure prompts user to enter a valid number and clears the error state.
 *
 * @return double The validated numeric value entered by the user.
 */
double takeNumber()
{
    std::cout << "Enter numbers : " ;
    double number{ 0.0 };
    while (true)
    {
        if (std::cin >> number)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Input registered successfully" << std::endl;

            return number;  // number is already double
        }
        else
        {
            std::cout << "Enter a valid input (must be a number)" << std::endl;
            std::cin.clear();                           // Clear the error flags
            std::cin.ignore(10000, '\n');               // Discard invalid input
        }
    }
}

/**
 * @brief Prompt the user for a non-empty string containing letters and spaces only.
 *
 * Reads a full line and validates that:
 *  - The line is not empty
 *  - Every character is either an alphabetic character or a space
 *
 * Prompts with: "Letters and spaces only: "
 * On success prints: "Input registered successfully"
 *
 * @return std::string The validated input string.
 */
std::string takeString()
{
    std::string text{ "" };

    std::cout << "Letters and spaces only: " ;

    while (true)
    {
        std::getline(std::cin >> std::ws, text);   // read input every loop

        bool valid = !text.empty();

        for (unsigned char c : text) {
            if (!std::isalpha(c) && c != ' ') {
                valid = false;
                break;
            }
        }

        if (valid) {
            std::cout << "Input registered successfully" << std::endl;
            return text;
        }
        else {
            std::cout << "Invalid input! Use only letters and spaces.\n";
        }
    }
}

/**
 * @brief Prompt the user for a password with simple validation rules.
 *
 * Validation rules:
 *  - Minimum length: 6 characters
 *  - No whitespace characters allowed
 *
 * Prompts with: "Password (min 6 chars, no spaces): "
 * On success prints: "Password registered successfully"
 *
 * Warning: This function reads and returns the password as a plain string and input is echoed.
 * For secure password input use platform-specific secure input (no echo) and avoid storing raw passwords.
 *
 * @return std::string The validated password string.
 */
std::string takePassword()
{
    std::string password{ "" };

    std::cout << "Password (min 6 chars, no spaces): ";

    while (true)
    {
        std::getline(std::cin >> std::ws, password);

        bool valid = true;

        // Rule 1: minimum length
        if (password.length() < 6)
            valid = false;

        // Rule 2: no spaces allowed
        for (unsigned char c : password) {
            if (std::isspace(c)) {
                valid = false;
                break;
            }
        }

        if (valid) {
            std::cout << "Password registered successfully\n";
            return password;
        }
        else {
            std::cout << "Invalid password! "
                "Minimum 6 characters, no spaces : \n";
        }
    }
}

/**
 * @brief Prompt the user for a username and validate against simple constraints.
 *
 * Validation rules:
 *  - Length between 3 and 20 characters (inclusive)
 *  - Must start with a letter
 *  - Allowed characters: letters, digits, underscore ('_')
 *
 * Prompts with:
 *  "Username (3-20 chars, letters/digits/_ , must start with letter): "
 *
 * On success prints: "Username Entered successfully"
 *
 * @return std::string The validated username.
 */
std::string takeUsername()
{
    std::string username{ "" };

    std::cout << "Username (3-20 chars, letters/digits/_ , must start with letter): ";

    while (true)
    {
        std::getline(std::cin >> std::ws, username);

        bool valid = true;

        // Rule 1: length check
        if (username.length() < 3 || username.length() > 20)
            valid = false;

        // Rule 2: must start with a letter
        if (!username.empty() && !std::isalpha(static_cast<unsigned char>(username[0])))
            valid = false;

        // Rule 3: allowed characters
        for (unsigned char c : username) {
            if (!std::isalnum(c) && c != '_') {
                valid = false;
                break;
            }
        }

        if (valid) {
            std::cout << "Username Entered successfully\n";
            return username;
        }
        else {
            std::cout << "Invalid username!\n";
            std::cout << "• 3-20 characters\n";
            std::cout << "• Must start with a letter\n";
            std::cout << "• Only letters, digits, and underscore allowed\n";
        }
    }
}

/**
 * @brief Read an integer value within an inclusive range [minV, maxV].
 *
 * Reads with operator>> and validates range. On successful read the remainder of the
 * line is consumed. If input is invalid or out of range, the user is prompted again.
 *
 * @param minV Minimum allowed value (inclusive)
 * @param maxV Maximum allowed value (inclusive)
 * @return int A validated integer in the requested range.
 */
int takeIntInRange(int minV, int maxV) {
    int x;

    while (true) {

        if (std::cin >> x && x >= minV && x <= maxV) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }

        std::cout << "Invalid number. Enter a value between "
            << minV << " and " << maxV << ": ";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

/**
 * @brief Read a non-empty line from input.
 *
 * Uses std::getline and trims leading whitespace by consuming std::ws.
 * Keeps prompting until the user enters a non-empty line.
 *
 * @return std::string A non-empty line entered by the user.
 */
std::string takeLineNonEmpty()
{
    std::string text;
    while (true)
    {
        std::getline(std::cin >> std::ws, text);
        if (!text.empty()) return text;
        std::cout << "Input cannot be empty.\n";
    }
}