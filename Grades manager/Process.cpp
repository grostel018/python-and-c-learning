#include <iostream>
#include "src/sqlite3.h"
#include "Process.h"
#include "UI.h"
#include "Input.h"
#include "database.h"
#include <string>
#include "Menu.h"







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
    return true;
}




bool signUp(sqlite3* db, Student& loggedIn){
    taskDelimeter();
   
    std::cout << "Enter your Full name\n";
    loggedIn.name = takeString();

    taskDelimeter();

    

    bool valid = false;

    while (!valid)  {

        std::cout << "Enter an username\n";
        loggedIn.username = takeUsername();

    Student check = getStudentByUsername(db, loggedIn.username);

    if (check.id == -1) 
    { 
    std::cout << "Database error.\n"; 
    return false;
    }

    if (check.id != 0) 
    { 
    std::cout << "Username already taken\n"; 
    taskDelimeter();
    }

    else {
        std::cout << "Good, that's a Valid username\n";
        valid = true;
    }
    
    }


    taskDelimeter();

    bool equal = false;

    std::string password1 {};

    std::string password2 {};


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
    
    if (!insertStudent(db, loggedIn)) {
        std::cout << "Database error.\n";
        return false;
    }

    std::cout << "Registered succesfully. Welcome " << loggedIn.name << "!\n";
    



return true;
}

















void addCourse()
{}












void deleteCourse()
{}













void deleteUser()
{}












void logOut() {

    std::cout << "Logged out\n";
}





void runApp(sqlite3* db)
{
    Student currentUser{};

    while (true)
    {
        if (currentUser.id == 0)
            mainMenu(db, currentUser);
        else
            studentMenu(db, currentUser);
    }
}