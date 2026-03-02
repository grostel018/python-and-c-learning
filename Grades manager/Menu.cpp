#include<iostream>
#include "Menu.h"
#include "UI.h"
#include "Input.h"
#include "Process.h"
#include "src/sqlite3.h"
#include "database.h"
#include <string>



void choose()

{
    std::cout << "\tYou choosed\n";
}

void mainMenu(sqlite3* db, Student& currentUser) {


    int choice{ 0 };


    while (true)
    {

        std::cout << "Choose your task and press Enter \n";
        printCommands();
        choice = takeNumber();

        switch (choice) {

        case 1: //logIn(db, currentUser);
            break;

        case 2: //signUp(db, currentUser);
            break;

        case 3: //{logOut() ; std::cout << "Exiting...\n"; return;}
            break;
        default:std::cout << "invalid choice, please choose between (1-10)\n";
        



        }




    }


}




    void studentMenu(sqlite3* db, Student& currentUser) {


        int choice{ 0 };


        while (true)
        {

            std::cout << "Choose your task and press Enter \n";
            printCommands();
            choice = takeNumber();

            switch (choice) {

            case 1: //addCourse();
                break;

            case 2: //courseGradeCalculator();
                break;

            case 3: //std::cout << " current GPA calculated\n";
                break;

            case 4: //std::cout << " current CGPA calculated\n";
                break;

            case 5: //deleteCourse();
                break;

            case 6: //deleteUser();
                break;

            case 7: //display user's info, courses, grades and GPA;
                break;

            case 8: //{logOut() ; std::cout << "Exiting...\n"; return;}
                break;
            default:std::cout << "invalid choice, please choose between (1-10)\n";

            }




        }


        }

        

        