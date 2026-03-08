#pragma once
#include "src/sqlite3.h"
#include "Models.h"

void mainMenu(sqlite3* db, Student& currentUser, bool& running);
void studentMenu(sqlite3* db, Student& currentUser, bool& running);
