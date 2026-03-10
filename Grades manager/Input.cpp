#include "Input.h"
#include <iostream>
#include <cctype>
#include "UI.h"
#include <limits>



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

            return number;  // No need for static_cast, number is already double
        }
        else
        {
            std::cout << "Enter a valid input (must be a number)" << std::endl;
            std::cin.clear();           // Clear the error flags
            std::cin.ignore(10000, '\n'); // Discard invalid input
        }


    }
    
}






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


// Small helper (so you don’t depend on unknown takeInt() implementations)
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

//make a better version of this : 

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