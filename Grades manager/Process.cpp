#include <iostream>
#include "src/sqlite3.h"
#include "Process.h"
#include "UI.h"
#include "Input.h"
#include "database.h"
#include <string>
#include "Menu.h"
#include "Models.h"
#include <iomanip>
#include "Calculs.h"
#include <algorithm>



void courseAdder(double& grade, std::string& name, double& weight) {
    std::cout << "\nEnter the lecture's name : ";

    name = takeString();

    taskDelimeter();

    std::cout << "\nEnter the lecture's grade : ";

    grade = takeNumber();

    taskDelimeter();

    std::cout << "\nEnter the lecture's weight : ";

    weight = takeNumber();

    taskDelimeter();
}








bool logIN(sqlite3* db, Student& loggedIn) {

    taskDelimeter();

    std::cout << "Enter your username\n";
    std::string username = takeUsername();
    taskDelimeter();

    std::cout << "Enter your password\n";
    std::string password = takePassword();

    taskDelimeter();

    Student s = getStudentByUsername(db, username);

    if (s.id == -1) {
        std::cout << "Database error.\n";
        return false;
    }

    // not found
    if (s.id == 0) {
        std::cout << "Invalid credentials\n";
        return false;
    }

    // compare password (plain text)
    if (s.password != password) {
        std::cout << "Wrong password.\n";
        return false;
    }

    loggedIn = s;
    std::cout << "Login successful. Welcome " << loggedIn.name << "!\n";
    loggedIn.courses = getCoursesByStudentId(db, loggedIn.id);
    computeGPA(loggedIn);
    return true;
}




bool signUp(sqlite3* db, Student& loggedIn)
{
    taskDelimeter();

    std::cout << "Enter your Full name\n";
    loggedIn.name = takeString();

    taskDelimeter();

    bool valid = false;

    while (!valid)
    {
        std::cout << "Enter a username\n";
        loggedIn.username = takeUsername();

        Student check = getStudentByUsername(db, loggedIn.username);

        if (check.id == -1) {
            std::cout << "Database error.\n";
            return false;
        }

        if (check.id != 0) {
            std::cout << "Username already taken\n";
            taskDelimeter();
        }
        else {
            std::cout << "Good, that's a valid username\n";
            valid = true;
        }
    }

    taskDelimeter();

    bool equal = false;
    std::string password1{};
    std::string password2{};

    while (!equal)
    {
        std::cout << "Enter a password\n";
        password1 = takePassword();

        std::cout << "Enter the same password\n";
        password2 = takePassword();

        if (password1 != password2) {
            std::cout << "Passwords don't match, try again\n";
            taskDelimeter();
        }
        else {
            equal = true;
        }
    }

    loggedIn.password = password1;

    int newId = insertStudent(db, loggedIn);
    if (newId == -1) {
        std::cout << "Database error.\n";
        return false;
    }

    loggedIn.courses.clear();
    loggedIn.gpa = 0.0;
    loggedIn.cgpa = 0.0;

    std::cout << "Registered successfully. Welcome " << loggedIn.name << "!\n";
    return true;
}












Course addCourse(sqlite3* db, const Student& loggedIn) {
    Course c{};
    c.id = 0;
    c.studentId = loggedIn.id;

    taskDelimeter();
    std::cout << "Enter course name\n";
    c.name = takeLineNonEmpty();

    taskDelimeter();
    std::cout << "Enter credits (1-30)\n";
    c.credits = takeIntInRange(1, 30);

    taskDelimeter();
    std::cout << "Enter semester (1-20)\n";
    c.semester = takeIntInRange(1, 20);

    c.finalGrade = 0.0;
    c.components.clear();

    taskDelimeter();

    int newId = insertCourse(db, c);
    if (newId == -1) { // ✅ correct check
        std::cout << "Database error: course was not saved.\n";
        c.id = -1;
        return c;
    }

    // c.id already set inside insertCourse, but keeping it explicit is fine:
    c.id = newId;

    std::cout << "Course added successfully (id=" << c.id << "): "
        << c.name << " | credits=" << c.credits
        << " | semester=" << c.semester << "\n";

    return c;
}











void deleteCourseFlow(sqlite3* db, const Student& loggedIn)
{

    if (loggedIn.id == 0) {
        std::cout << "No user is currently logged in.\n";
        return;
    }

    taskDelimeter();

    if (loggedIn.courses.empty()) {
        std::cout << "You have no courses to delete.\n";
        return;
    }


    std::cout << "----- COURSES -----\n\n";

    for (const Course& c : loggedIn.courses) {
        std::cout << "Course ID    : " << c.id << "\n";
        std::cout << "Name         : " << c.name << "\n";
        std::cout << "Credits      : " << c.credits << "\n";
        std::cout << "Semester     : " << c.semester << "\n";
        std::cout << "Final Grade  : " << std::fixed << std::setprecision(2) << c.finalGrade << "\n";
        taskDelimeter();
    }




    std::cout << "Enter the ID of the course to delete:\n";
    int id = takeIntInRange(1, 1000000);

    taskDelimeter();



    if (!deleteCourse(db, id, loggedIn.id)) {
        std::cout << "Could not delete course. Invalid ID or database error.\n";
        return;
    }

    std::cout << "Course deleted successfully.\n";
}











void deleteUser(sqlite3* db, Student& loggedIn)
{

    if (loggedIn.id == 0) {
        std::cout << "No user is currently logged in.\n";
        return;
    }

    taskDelimeter();

    std::cout << "Are you sure you want to delete your account?\n";
    std::cout << "This will permanently delete all your data.\n";
    std::cout << "Type \"YES\"or \"Y\" to confirm: ";

    std::string confirm;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, confirm);


    std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::toupper);

    if (confirm != "YES" && confirm != "Y") {
        std::cout << "Account deletion cancelled.\n";
        return;
    }

    taskDelimeter();

    if (!deleteStudent(db, loggedIn.id)) {
        std::cout << "Database error. Could not delete account.\n";
        return;
    }

    std::cout << "Account deleted successfully.\n";

    loggedIn = {};  // reset logged user
}










void logOut(Student& loggedIn)
{
    taskDelimeter();

    loggedIn = {};   // reset the struct (id becomes 0, strings empty)

    std::cout << "Closed successfully.\n";

    taskDelimeter();
}



void runApp(sqlite3* db)
{
    Student currentUser{};
    bool running = true;

    while (running)
    {
        if (currentUser.id == 0)
            mainMenu(db, currentUser, running);
        else
            studentMenu(db, currentUser, running);
    }
}



bool setStudentCourseGrade(sqlite3* db, const Student& loggedIn)
{
    if (loggedIn.id == 0) {
        std::cout << "No user is currently logged in.\n";
        return false;
    }

    if (loggedIn.courses.empty()) {
        std::cout << "You have no courses to grade.\n";
        return false;
    }

    taskDelimeter();
    std::cout << "----- YOUR COURSES -----\n\n";

    for (const Course& c : loggedIn.courses) {
        std::cout << "Course ID    : " << c.id << "\n";
        std::cout << "Name         : " << c.name << "\n";
        std::cout << "Credits      : " << c.credits << "\n";
        std::cout << "Semester     : " << c.semester << "\n";
        std::cout << "Final Grade  : " << std::fixed << std::setprecision(2) << c.finalGrade << "\n";
        taskDelimeter();
    }

    int courseId = 0;
    bool found = false;

    while (!found) {
        std::cout << "Enter the course ID to grade:\n";
        courseId = takeIntInRange(1, 1000000);

        for (const Course& c : loggedIn.courses) {
            if (c.id == courseId) {
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Invalid course ID. Please choose one of the displayed course IDs.\n";
            taskDelimeter();
        }
    }

    taskDelimeter();
    std::cout << "Enter the final grade (0-100):\n";
    double grade = takeNumber();

    while (grade < 0.0 || grade > 100.0) {
        std::cout << "Invalid grade. Enter a value between 0 and 100:\n";
        grade = takeNumber();
    }

    taskDelimeter();

    if (!updateCourseGradeForStudent(db, courseId, loggedIn.id, grade)) {
        std::cout << "Could not update grade due to a database error.\n";
        return false;
    }

    std::cout << "Grade updated successfully.\n";
    return true;
}




void updateStudentFlow(sqlite3* db, Student& currentUser)
{
    if (currentUser.id == 0) {
        std::cout << "No user is currently logged in.\n";
        return;
    }

    while (true) {
        taskDelimeter();
        std::cout << "----- UPDATE ACCOUNT -----\n";
        std::cout << "1. Update name\n";
        std::cout << "2. Update username\n";
        std::cout << "3. Update password\n";
        std::cout << "4. Update all fields\n";
        std::cout << "5. Back\n";

        int choice = takeIntInRange(1, 5);

        std::string newName = currentUser.name;
        std::string newUsername = currentUser.username;
        std::string newPassword = currentUser.password;

        taskDelimeter();

        switch (choice) {
        case 1:
            std::cout << "Current name: " << currentUser.name << "\n";
            std::cout << "Enter new name:\n";
            newName = takeString();

            if (!updateStudent(db, currentUser.id, newName, newUsername, newPassword)) {
                std::cout << "Could not update account.\n";
                return;
            }

            currentUser.name = newName;
            std::cout << "Name updated successfully.\n";
            break;

        case 2:
            std::cout << "Current username: " << currentUser.username << "\n";
            std::cout << "Enter new username:\n";
            newUsername = takeUsername();

            if (!updateStudent(db, currentUser.id, newName, newUsername, newPassword)) {
                std::cout << "Could not update account. Username may already exist.\n";
                return;
            }

            currentUser.username = newUsername;
            std::cout << "Username updated successfully.\n";
            break;

        case 3:
            std::cout << "Enter new password:\n";
            newPassword = takePassword();

            if (!updateStudent(db, currentUser.id, newName, newUsername, newPassword)) {
                std::cout << "Could not update account.\n";
                return;
            }

            currentUser.password = newPassword;
            std::cout << "Password updated successfully.\n";
            break;

        case 4:
            std::cout << "Current name: " << currentUser.name << "\n";
            std::cout << "Enter new name:\n";
            newName = takeString();
            taskDelimeter();

            std::cout << "Current username: " << currentUser.username << "\n";
            std::cout << "Enter new username:\n";
            newUsername = takeUsername();
            taskDelimeter();

            std::cout << "Enter new password:\n";
            newPassword = takePassword();

            if (!updateStudent(db, currentUser.id, newName, newUsername, newPassword)) {
                std::cout << "Could not update account. Username may already exist.\n";
                return;
            }

            currentUser.name = newName;
            currentUser.username = newUsername;
            currentUser.password = newPassword;

            std::cout << "Account updated successfully.\n";
            break;

        case 5:
            return;
        }
    }
}