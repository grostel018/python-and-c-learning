#include<iostream>
#include "Menu.h"
#include "UI.h"
#include "Input.h"
#include "Process.h"
#include "src/sqlite3.h"
#include "database.h"
#include <string>
#include "Calculs.h"



void choose()

{
    std::cout << "\tYou choosed\n";
}



void mainMenu(sqlite3* db, Student& currentUser, bool& running)
{
    while (true)
    {
        std::cout << "Choose your task and press Enter\n";
        printCommands();

        int choice = takeIntInRange(1, 3);

        switch (choice)
        {
        case 1:
            logIN(db, currentUser);
            return;

        case 2:
            signUp(db, currentUser);
            return;

        case 3:
            std::cout << "Exiting...\n";
            running = false;
            return;

        default:
            std::cout << "Invalid choice, please choose between (1-3)\n";
            break;
        }
    }
}



void studentMenu(sqlite3* db, Student& currentUser, bool& running)
{
    while (true)
    {
        currentUser.courses = getCoursesByStudentId(db, currentUser.id);

        std::cout << "Choose your task and press Enter\n";
        printMenuCommands();
        int choice = takeIntInRange(1, 8);

        switch (choice)
        {
        case 1:
            addCourse(db, currentUser);
            break;

        case 2:
            setStudentCourseGrade(db, currentUser);
            break;

        case 3:
            currentUser.courses = getCoursesByStudentId(db, currentUser.id);
            computeGPA(currentUser);
            std::cout << "Current GPA calculated successfully.\n";
            break;

        case 4:
            currentUser.courses = getCoursesByStudentId(db, currentUser.id);
            computeGPA(currentUser);
            std::cout << "Current CGPA calculated successfully.\n";
            break;

        case 5:
            deleteCourseFlow(db, currentUser);
            break;

        case 6:
            deleteUser(db, currentUser);
            if (currentUser.id == 0) return;
            break;

        case 7:
            currentUser.courses = getCoursesByStudentId(db, currentUser.id);
            computeGPA(currentUser);
            displayStudentInfo(currentUser);
            break;

        case 8:
        { logOut(currentUser); std::cout << "Logged out successfully.\n"; return; }

        default:
            std::cout << "Invalid choice, please choose between (1-8)\n";
            break;
        }
    }
}
        

        