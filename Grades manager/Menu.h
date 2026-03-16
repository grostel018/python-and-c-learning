#pragma once
#include "src/sqlite3.h"
#include "Models.h"

// Const correctness: Database pointer is const since menu functions don't own it
void mainMenu(sqlite3* db, Student& currentUser, bool& running);
void studentMenu(sqlite3* db, Student& currentUser, bool& running);
