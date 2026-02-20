#include "Input.h"
#include <iostream>
#include <cctype>




double takeNumber()
{
    std::cout << "\nNumbers only : " << std::endl;
    double number{ 0.0 };
    while (true)
    {
        if (std::cin >> number)
        {
            std::cin.ignore(10000, '\n');

            std::cout << "\nInput registered successfully" << std::endl;

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

    std::cout << "\nLetters and spaces only: " << std::endl;

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
            std::cout << "\nInput registered successfully" << std::endl;
            return text;
        }
        else {
            std::cout << "Invalid input! Use only letters and spaces.\n";
        }
    }
}