#pragma once
#include "Models.h"  // defines Student, Course
#include "src/sqlite3.h"     // forward declaration for the sqlite3 opaque type

// Const correctness: runApp doesn't modify the database pointer
void runApp(sqlite3* db);

bool logIN(sqlite3* db, Student& loggedIn);
bool signUp(sqlite3* db, Student& loggedIn);

Course addCourse(sqlite3* db, const Student& loggedIn);

// UI / process functions — signatures must match implementations in Process.cpp
// Functions that take const Student& don't modify the student object
void deleteCourseFlow(sqlite3* db, const Student& loggedIn);
void deleteUser(sqlite3* db, Student& loggedIn);
void logOut(Student& loggedIn);
void courseAdder(double& grade, std::string& name, double& weight);
bool setStudentCourseGrade(sqlite3* db, const Student& loggedIn);

void updateStudentFlow(sqlite3* db, Student& currentUser);
