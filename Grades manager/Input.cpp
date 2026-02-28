#include "Input.h"
#include <iostream>
#include <cctype>
#include "UI.h"




double takeNumber()
{
    
    std::cout << "Numbers only : " ;
    double number{ 0.0 };
    while (true)
    {
        if (std::cin >> number)
        {
            std::cin.ignore(10000, '\n');

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