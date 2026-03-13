/**
 * @file UI.cpp
 * @brief Console-based user interface utilities for the GPA/CGPA application.
 *
 * This file contains simple printing helpers used by the application to present
 * menus and student/course information in a consistent, human-readable format.
 *
 * Notes:
 * - These functions write to std::cout and do not perform input handling.
 * - Types `Student` and `Course` are referenced from `UI.h` (or other project headers).
 */

#include "UI.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

/**
 * @brief Print a horizontal delimiter used to separate UI sections.
 *
 * The delimiter improves readability in the console by visually separating
 * different UI blocks (menus, profiles, course lists, etc.).
 */
void taskDelimeter() {
    std::cout << "\n********************************************************************************************\n";
}

/**
 * @brief Print the application welcome banner.
 *
 * Displays a short welcome message and a hint about the calculator's purpose.
 */
void welcome()
{
    taskDelimeter();
    std::cout << "\t*Welcome to the GPA calculator*" << std::endl;
    std::cout << "\t*You can compute your GPA or your CGPA*" << std::endl;
    
}

/**
 * @brief Print the top-level authentication commands.
 *
 * Lists available actions when the application first starts (login, sign up, exit).
 */
void printCommands()
{
    taskDelimeter();
    std::cout << "\t1- To Log in\n";
    std::cout << "\t2- To Sign in\n";
    std::cout << "\t3- Exit\n";
}

/**
 * @brief Print the main menu commands for a logged-in user.
 *
 * Lists operations related to course management and student account actions.
 */
void printMenuCommands()
{
    taskDelimeter();
    std::cout << "\t1- To Add a course\n";
    std::cout << "\t2- To set a student's course grade\n";
    std::cout << "\t3- To Calculate the current GPA\n";
    std::cout << "\t4- To update a student's info\n";
    std::cout << "\t5- To Delete a course\n";
    std::cout << "\t6- To Delete user\n";
    std::cout << "\t7- To display All the student's information\n";
    std::cout << "\t8- To log Out \n";
}

/**
 * @brief Placeholder for a more detailed menu printer.
 *
 * Currently empty. Keep as a separate function to allow future expansion
 * (for example: context-aware submenus or role-based menus).
 */
void printMenu() {



}

/**
 * @brief Display a student's profile and courses to the console.
 *
 * Prints identifying information (id, name, username), computed fields
 * (GPA, CGPA), and a formatted list of the student's courses.
 *
 * Behavior:
 * - If `s.id == 0` it is treated as "no user logged in" and the function returns.
 * - If the student has no courses, a message is shown and the function returns.
 * - The function determines the current semester by scanning the student's courses.
 *
 * @param s The student instance to display. Must expose at least:
 *          - `id` (numeric), `name` (string), `username` (string)
 *          - `gpa`, `cgpa` (floating point)
 *          - `courses` (container of `Course` objects where each course has
 *            `id`, `name`, `credits`, `semester`, and `finalGrade`).
 */
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


