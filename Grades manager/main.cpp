/**
 * @file main.cpp
 * @brief Entry point for the Grades Manager application.
 *
 * Responsibilities:
 *  - Open and initialize the SQLite database (via `openAndInitDatabase`).
 *  - Display the welcome UI (via `welcome()`).
 *  - Run the main application loop (via `runApp(sqlite3*)`).
 *  - Close the SQLite database on exit.
 *
 * Usage:
 *  - The application reads/writes the database file named "gpa.db" in the current working directory.
 *
 * Dependencies:
 *  - `UI.h`       : declares `welcome()`
 *  - `Menu.h`     : menu-related declarations used by the app
 *  - `database.h` : declares `openAndInitDatabase()`
 *  - `Process.h`  : declares `runApp(sqlite3*)`
 *  - `sqlite3.h`  : SQLite C API
 *
 * Exit codes:
 *  - 0 : success
 *  - 1 : failed to initialize/open the database
 *
 * Notes:
 *  - Ensure SQLite is linked into the project.
 *  - Database initialization function should return a valid `sqlite3*` on success.
 */

#pragma comment(linker, "/INCREMENTAL:NO")
#include <iostream>
#include "UI.h"
#include "Menu.h"
#include "sqlite3.h"
#include "models.h"
#include "database.h"
#include "Process.h"

/// @brief Application entry point.
/// 
/// Sequence:
/// 1. Attempt to open and initialize the database with `openAndInitDatabase("gpa.db")`.
/// 2. If the database pointer is null, report error to stderr and return exit code 1.
/// 3. Show the welcome screen and start the application loop (`runApp`).
/// 4. Close the database connection and return 0 on success.
/// 
/// @return int Process exit code (0 = success, 1 = failure to init DB).
int main()
{
    sqlite3* db = openAndInitDatabase("gpa.db");
    if (!db) {
        std::cerr << "Failed to initialize database.\n";
        return 1;
    }

    welcome();
    runApp(db);

    sqlite3_close(db);
    return 0;
}