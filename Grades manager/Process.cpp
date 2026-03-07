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












Course addCourse(sqlite3* db, const Student& loggedIn) {
    Course c{};
    c.id = 0;
    c.studentId = loggedIn.id;

    taskDelimeter();
    std::cout << "Enter course name\n";
    c.name = takeString();

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











void deleteCourse(sqlite3* db, const Student& loggedIn)
{
    taskDelimeter();

    std::cout << "Enter the ID of the course to delete:\n";
    int id = takeIntInRange(1, 1000000);

    taskDelimeter();

    if (!deleteCourse(db, id, loggedIn.id)) {
        std::cout << "Could not delete course.\n";
        return;
    }

    std::cout << "Course deleted successfully.\n";
}











void deleteUser(sqlite3* db, Student& loggedIn)
{
    taskDelimeter();

    std::cout << "Are you sure you want to delete your account?\n";
    std::cout << "This will permanently delete all your data.\n";
    std::cout << "Type \"YES\"or \"Y\" to confirm: ";

    std::string confirm;
    std::getline(std::cin, confirm);

    if ((confirm != "YES") || (confirm != "yes") || (confirm != "y") || (confirm != "Y")) {
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


void displayStudentInfo(const Student& s)
{
    taskDelimeter();

    if (s.id == 0) {
        std::cout << "No user logged in.\n";
        taskDelimeter();
        return;
    }

    std::cout << "----- STUDENT PROFILE -----\n\n";

    std::cout << "Name      : " << s.name << "\n";
    std::cout << "Username  : " << s.username << "\n";
    std::cout << "Courses   : " << s.courses.size() << "\n";
    std::cout << "GPA       : " << std::fixed << std::setprecision(2) << s.gpa << "\n";
    std::cout << "CGPA      : " << std::fixed << std::setprecision(2) << s.cgpa << "\n";

    taskDelimeter();
}








void logOut(Student& loggedIn)
{
    taskDelimeter();

    loggedIn = {};   // reset the struct (id becomes 0, strings empty)

    std::cout << "You have been logged out successfully.\n";

    taskDelimeter();
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




bool setStudentCourseGrade(sqlite3* db, const Student& loggedIn)
{
    taskDelimeter();
    std::cout << "Enter the course ID to grade:\n";
    int courseId = takeNumber();

    taskDelimeter();
    std::cout << "Enter the final grade (0-100):\n";
    double grade = takeNumber();

    while (grade < 0.0 || grade > 100.0) {
        std::cout << "Invalid grade. Enter a value between 0 and 100:\n";
        grade = takeNumber();
    }

    const char* sql =
        "UPDATE courses "
        "SET final_grade = ? "
        "WHERE id = ? AND student_id = ?;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cout << "Database error: could not prepare grade update.\n";
        return false;
    }

    sqlite3_bind_double(stmt, 1, grade);
    sqlite3_bind_int(stmt, 2, courseId);
    sqlite3_bind_int(stmt, 3, loggedIn.id);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        std::cout << "Database error: could not save the grade.\n";
        return false;
    }

    if (sqlite3_changes(db) == 0) {
        std::cout << "No course was updated. Either the course does not exist or it does not belong to this student.\n";
        return false;
    }

    std::cout << "Grade updated successfully.\n";
    return true;
}