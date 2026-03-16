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
    std::cout << "\n" << UIDelimiter::DELIMITER << "\n";
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
 * @brief Format a grade value for display with 2 decimal places.
 *
 * @param grade The grade to format (0-100).
 * @return std::string Formatted grade string.
 */
[[nodiscard]] std::string formatGrade(double grade) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << grade;
    return oss.str();
}

/**
 * @brief Format a GPA value for display with 2 decimal places.
 *
 * @param gpa The GPA to format (0-4.0).
 * @return std::string Formatted GPA string.
 */
[[nodiscard]] std::string formatGPA(double gpa) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << gpa;
    return oss.str();
}


/**
 * @brief Display a student's profile and courses to the console.
 *
 * Prints identifying information (id, name, username), computed fields
 * (GPA, CGPA), and a formatted list of the student's courses.
 *
 * Behavior:
 * - If `s.getId() == 0` it is treated as "no user logged in" and the function returns.
 * - If the student has no courses, a message is shown and the function returns.
 * - The function determines the current semester by scanning the student's courses.
 *
 * @param s The student instance to display. Must expose at least:
 *          - `getId()` (numeric), `getName()` (string), `getUsername()` (string)
 *          - `getGPA()`, `getCGPA()` (floating point)
 *          - `getCourses()` (container of `Course` objects where each course has
 *            `getId()`, `getName()`, `getCredits()`, `getSemester()`, and `getFinalGrade()`).
 */
void displayStudentInfo(const Student& s)
{
    taskDelimeter();

    if (s.getId() == 0) {
        std::cout << "No user logged in.\n";
        taskDelimeter();
        return;
    }

    int currentSemester = 0;
    const auto& courses = s.getCourses();
    if (!courses.empty()) {
        currentSemester = courses[0].getSemester();
        for (const Course& c : courses) {
            if (c.getSemester() > currentSemester) {
                currentSemester = c.getSemester();
            }
        }
    }

    std::cout << "----- STUDENT PROFILE -----\n\n";
    std::cout << "ID        : " << s.getId() << "\n";
    std::cout << "Name      : " << s.getName() << "\n";
    std::cout << "Username  : " << s.getUsername() << "\n";
    std::cout << "Courses   : " << courses.size() << "\n";

    if (currentSemester > 0)
        std::cout << "Semester  : " << currentSemester << "\n";

    std::cout << "GPA       : " << formatGPA(s.getGPA()) << "\n";
    std::cout << "CGPA      : " << formatGPA(s.getCGPA()) << "\n";

    taskDelimeter();

    if (courses.empty()) {
        std::cout << "No courses found for this student.\n";
        taskDelimeter();
        return;
    }

    std::cout << "----- COURSES -----\n\n";

    for (const Course& c : courses) {
        std::cout << "Course ID    : " << c.getId() << "\n";
        std::cout << "Name         : " << c.getName() << "\n";
        std::cout << "Credits      : " << c.getCredits() << "\n";
        std::cout << "Semester     : " << c.getSemester() << "\n";
        std::cout << "Final Grade  : " << formatGrade(c.getFinalGrade()) << "\n";
        taskDelimeter();
    }
}
