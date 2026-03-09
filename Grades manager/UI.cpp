#include "UI.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


void taskDelimeter() {
    std::cout << "\n********************************************************************************************\n";
}

void welcome()
{
    taskDelimeter();
    std::cout << "\t*Welcome to the GPA calculator*" << std::endl;
    std::cout << "\t*You can compute your GPA or your CGPA*" << std::endl;
    
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
    std::cout << "\t1- To Add a course\n";
    std::cout << "\t2- To set a student's course grade\n";
    std::cout << "\t3- To Calculate the current GPA\n";
    std::cout << "\t4- To Calculate the current CGPA\n";
    std::cout << "\t5- To Delete a course\n";
    std::cout << "\t6- To Delete user\n";
    std::cout << "\t7- To display All the student's information\n";
    std::cout << "\t8- To log Out \n";


}



void printMenu() {



}



void displayStudentInfo(const Student& s)
{
    taskDelimeter();

    if (s.id == 0) {
        std::cout << "No user logged in.\n";
        taskDelimeter();
        return;
    }

    int currentSemester = 0;
    if (!s.courses.empty()) {
        currentSemester = s.courses[0].semester;
        for (const Course& c : s.courses) {
            if (c.semester > currentSemester) {
                currentSemester = c.semester;
            }
        }
    }

    std::cout << "----- STUDENT PROFILE -----\n\n";
    std::cout << "ID        : " << s.id << "\n";
    std::cout << "Name      : " << s.name << "\n";
    std::cout << "Username  : " << s.username << "\n";
    std::cout << "Courses   : " << s.courses.size() << "\n";

    if (currentSemester > 0)
        std::cout << "Semester  : " << currentSemester << "\n";



    std::cout << "GPA       : " << std::fixed << std::setprecision(2) << s.gpa << "\n";
    std::cout << "CGPA      : " << std::fixed << std::setprecision(2) << s.cgpa << "\n";

    taskDelimeter();

    if (s.courses.empty()) {
        std::cout << "No courses found for this student.\n";
        taskDelimeter();
        return;
    }

    std::cout << "----- COURSES -----\n\n";

    for (const Course& c : s.courses) {
        std::cout << "Course ID    : " << c.id << "\n";
        std::cout << "Name         : " << c.name << "\n";
        std::cout << "Credits      : " << c.credits << "\n";
        std::cout << "Semester     : " << c.semester << "\n";
        std::cout << "Final Grade  : " << std::fixed << std::setprecision(2) << c.finalGrade << "\n";
        taskDelimeter();
    }
}


