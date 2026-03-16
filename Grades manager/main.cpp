/**
 * @file main.cpp
 * @brief Entry point for the Grades Manager application.
 *
 * Responsibilities:
 *  - Open and initialize the SQLite database (via Database RAII class).
 *  - Display the welcome UI (via `welcome()`).
 *  - Run the main application loop (via `runApp(sqlite3*)`).
 *  - Close the SQLite database on exit (handled automatically by RAII).
 *
 * Usage:
 *  - The application reads/writes the database file named "gpa.db" in the current working directory.
 *
 * Dependencies:
 *  - `UI.h`       : declares `welcome()`
 *  - `Menu.h`     : menu-related declarations used by the app
 *  - `database.h` : declares `Database` RAII class and legacy functions
 *  - `Process.h`  : declares `runApp(sqlite3*)`
 *  - `sqlite3.h`  : SQLite C API
 *
 * Exit codes:
 *  - 0 : success
 *  - 1 : failed to initialize/open the database
 *
 * Notes:
 *  - Ensure SQLite is linked into the project.
 *  - The Database class uses RAII to automatically manage the SQLite connection.
 */

#pragma comment(linker, "/INCREMENTAL:NO")
#include <iostream>
#include "UI.h"
#include "Menu.h"
#include "sqlite3.h"
#include "Models.h"  // Fixed case: was "models.h"
#include "database.h"
#include "Process.h"

/// @brief Application entry point.
///
/// Sequence:
/// 1. Attempt to open and initialize the database using the Database RAII class.
/// 2. If initialization fails, report error to stderr and return exit code 1.
/// 3. Show the welcome screen and start the application loop (`runApp`).
/// 4. Database is automatically closed when the Database object goes out of scope.
///
/// @return int Process exit code (0 = success, 1 = failure to init DB).
int main()
{
    try {
        // Use RAII Database class - automatically closes on scope exit
        Database db(Constants::DATABASE_FILENAME);

        welcome();
        runApp(db.get());

        // Database automatically closed here via RAII
    } catch (const std::runtime_error& e) {
        std::cerr << "Database error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
