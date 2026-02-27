#include <iostream>
#include "src/sqlite3.h"
#include "Process.h"
#include "UI.h"
#include "Input.h"
#include "database.h"
#include <string>







bool logIN(sqlite3* db, Student& loggedIn) {
    std::cout << "\tEnter your username\n";
    std::string username = takeString();

    std::cout << "\tEnter your password\n";
    std::string password = takeString();

    Student s = getStudentByUsername(db, username);

    // not found
    if (s.id == 0) {
        std::cout << "User not found.\n";
        return false;
    }

    // compare password (plain text)
    if (s.password != password) {
        std::cout << "Wrong password.\n";
        return false;
    }

    loggedIn = s;
    std::cout << "Login successful. Welcome " << loggedIn.name << "!\n";
    return true;
}















void signIN();












void addCourse();












void deleteCourse();













void deleteUser();












void logOut();