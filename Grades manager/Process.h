#pragma once
#include "Models.h"  // defines Student
struct sqlite3;      // forward declaration for the sqlite3 opaque type


bool logIN(sqlite3* db, Student& loggedIn);
void signIN();
void addCourse();
void deleteCourse();
void deleteUser();
void logOut();


