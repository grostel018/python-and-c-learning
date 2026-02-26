#include "UI.h"
#include <iostream>

void taskDelimeter() {
    std::cout << "\n********************************************************************************************\n";
}

void welcome()
{
    taskDelimeter();
    std::cout << "\t*Welcome to the GPA calculator*" << std::endl;
    std::cout << "\t*You can either compute your GPA or you CGPA*" << std::endl;
    taskDelimeter();
}

void printCommands()
{
    taskDelimeter();
    std::cout << "\t1- Log in\n";
    std::cout << "\t2- Sign in\n";
    std::cout << "\t3- Add a course to the current semester\n";
    std::cout << "\t4- Compute a course's semester grade (And add it to the course)\n";
    std::cout << "\t5- Calculate the current GPA\n";
    std::cout << "\t6- Calculate the current CGPA\n";
    std::cout << "\t7- Delete a course\n";
    std::cout << "\t8- Delete user\n";
    std::cout << "\t9- Log out\n";
    taskDelimeter();

}