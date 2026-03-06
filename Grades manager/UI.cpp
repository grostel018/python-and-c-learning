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
    
}

void printCommands()
{
    taskDelimeter();
    std::cout << "\t1- To Log in\n";
    std::cout << "\t2- To Sign in\n";
    std::cout << "\t3- Exit\n";
    

}

void printMenuCommands()
{
    taskDelimeter();
    std::cout << "\t1- To Add a course to the current semester\n";
    std::cout << "\t2- To Compute a course's semester grade (And add it to the course)\n";
    std::cout << "\t3- To Calculate the current GPA\n";
    std::cout << "\t4- To Calculate the current CGPA\n";
    std::cout << "\t5- To Delete a course\n";
    std::cout << "\t6- To Delete user\n";
    std::cout << "\t7- To display the student's information\n";
    std::cout << "\t8- To log Out \n";


}



void printMenu() {



}