#include "UI.h"
#include <iostream>

void taskDelimeter() {
    std::cout << "\n********************************************************************************************\n";
}

void welcome()
{
    std::cout << "\t*Welcome to the GPA calculator*" << std::endl;
    std::cout << "\t*You can either compute your GPA or you CGPA*" << std::endl;
    taskDelimeter();
}

void printCommands()
{
    taskDelimeter();
    std::cout << "\t1- Add a lecture to the current semester\n";
    std::cout << "\t2- Compute a lecture's semester grade (And add it to the lecture)\n";
    std::cout << "\t3- Calculate the current GPA\n";
    std::cout << "\t4- Calculate the current CGPA\n";
    std::cout << "\t5- Delete a lecture\n";
    std::cout << "\t6- Delete an account\n";
    std::cout << "\t7- Log in\n";
    std::cout << "\t8- Register\n";
    std::cout << "\t3- Log out\n";
    taskDelimeter();

}