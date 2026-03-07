#pragma once
#include "Models.h"  // defines Student, Course
#include "src/sqlite3.h"     // forward declaration for the sqlite3 opaque type

void runApp(sqlite3* db);

bool logIN(sqlite3* db, Student& loggedIn);
bool signUp(sqlite3* db, Student& loggedIn);

Course addCourse(sqlite3* db, const Student& loggedIn);

// UI / process functions — signatures must match implementations in Process.cpp
void deleteCourse(sqlite3* db, const Student& loggedIn);
void deleteUser(sqlite3* db, Student& loggedIn);
void logOut(Student& loggedIn);
void displayStudentInfo(const Student& s);
void courseAdder(double& grade, std::string& name, double& weight);
bool setStudentCourseGrade(sqlite3* db, const Student& loggedIn);


