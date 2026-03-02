#pragma once
#include "Models.h"  // defines Student
#include "src/sqlite3.h"     // forward declaration for the sqlite3 opaque type

void runApp(sqlite3* db);

bool logIN(sqlite3* db, Student& loggedIn);
bool signUp(sqlite3* db, Student& loggedIn);

void addCourse();
void deleteCourse();
void deleteUser();
void logOut();


