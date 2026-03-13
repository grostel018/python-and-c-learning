/*
 * Menu.cpp
 *
 * Interactive menu handling for the Grades Manager application.
 *
 * This file contains the top-level console menus used by the application:
 *  - `mainMenu`  : entry menu for login / signup / exit
 *  - `studentMenu`: authenticated student menu for managing courses, grades, and account
 *
 * Dependencies:
 *  - UI helpers: `printCommands`, `printMenuCommands`, `displayStudentInfo`, etc.
 *  - Input helper: `takeIntInRange`
 *  - Database layer: sqlite3 handle and functions such as `getCoursesByStudentId`,
 *    `addCourse`, `setStudentCourseGrade`, `deleteCourseFlow`, `deleteUser`, `logIN`, `signUp`
 *  - GPA calculation: `computeGPA`
 *
 * Notes:
 *  - Menus use blocking console input and simple integer choices.
 *  - Functions mutate `currentUser` and may call DB-related flows which in turn
 *    update persistent state via `db`.
 */

    #include<iostream>
    #include "Menu.h"
    #include "UI.h"
    #include "Input.h"
    #include "Process.h"
    #include "src/sqlite3.h"
    #include "database.h"
    #include <string>
    #include "Calculs.h"


    /**
     * choose
     *
     * Small placeholder helper used during development/debugging.
     * Currently prints a short message to the console.
     *
     * TODO: remove or expand this function if it's not needed.
     */
    void choose()
    {
        std::cout << "\tYou choosed\n";
    }


    /**
     * mainMenu
     *
     * Presents the initial application menu to the user and handles the chosen action.
     *
     * Parameters:
     *  - db          : pointer to an open sqlite3 database connection used by downstream flows
     *  - currentUser : reference to the active `Student` struct. May be modified by `logIN`/`signUp`.
     *  - running     : reference to application run flag; set to false when the user chooses to exit.
     *
     * Behavior:
     *  - Displays a set of top-level commands via `printCommands`.
     *  - Reads an integer choice in the inclusive range [1,3] using `takeIntInRange`.
     *  - Choice mapping:
     *      1 -> `logIN(db, currentUser)` then return to caller (menu flow ends)
     *      2 -> `signUp(db, currentUser)` then return to caller
     *      3 -> set `running = false`, print exit message, and return
     *  - Invalid input is handled by `takeIntInRange` (bounds enforced) and the switch default prints a message.
     *
     * Side effects:
     *  - Calls into login/signup flows which may change `currentUser` and DB state.
     *  - May set `running` to false to signal application shutdown.
     */
    void mainMenu(sqlite3* db, Student& currentUser, bool& running)
    {
        while (true)
        {
            std::cout << "Choose your task and press Enter\n";
            printCommands();

            int choice = takeIntInRange(1, 3);

            switch (choice)
            {
            case 1:
                logIN(db, currentUser);
                return;

            case 2:
                signUp(db, currentUser);
                return;

            case 3:
                std::cout << "Exiting...\n";
                running = false;
                return;

            default:
                std::cout << "Invalid choice, please choose between (1-3)\n";
                break;
            }
        }
    }


    /**
     * studentMenu
     *
     * Presents the authenticated student menu and dispatches student-related actions.
     *
     * Parameters:
     *  - db          : pointer to an open sqlite3 database connection used by downstream flows
     *  - currentUser : reference to the logged-in `Student`. Must have a non-zero `id` to operate.
     *  - running     : reference to application run flag (not directly modified here except via flows).
     *
     * Preconditions:
     *  - `currentUser.id` must be non-zero. If it is zero, the function prints a message and returns.
     *
     * Behavior:
     *  - Refreshes `currentUser.courses` each loop using `getCoursesByStudentId`.
     *  - Displays menu choices via `printMenuCommands`.
     *  - Reads an integer choice in the inclusive range [1,8] using `takeIntInRange`.
     *  - Choice mapping:
     *      1 -> `addCourse(db, currentUser)`            : add a new course for the student
     *      2 -> `setStudentCourseGrade(db, currentUser)`: set or update a course grade
     *      3 -> `computeGPA(currentUser)`               : recompute GPA and notify
     *      4 -> `updateStudentFlow(db, currentUser)`    : update student profile/metadata
     *      5 -> `deleteCourseFlow(db, currentUser)`     : delete a course from the student's list
     *      6 -> `deleteUser(db, currentUser)`           : delete the student account; if deletion
     *                                                     clears `currentUser.id`, the menu returns
     *      7 -> recompute GPA and `displayStudentInfo(currentUser)` : show current student info
     *      8 -> `logOut(currentUser)` and return        : logs the user out of the session
     *
     * Side effects and notes:
     *  - Several flows call into the DB and may change persistent state.
     *  - `computeGPA` updates fields in `currentUser` (assumed) and is called before displaying info
     *    to ensure the most recent GPA is shown.
     *  - When `deleteUser` clears `currentUser.id`, this function exits to allow the caller to
     *    handle the logged-out / deleted state.
     */
    void studentMenu(sqlite3* db, Student& currentUser, bool& running)
    {

        if (currentUser.id == 0) {
            std::cout << "No user is currently logged in.\n";
            return;
        }

        while (true)
        {
            currentUser.courses = getCoursesByStudentId(db, currentUser.id);

            std::cout << "Choose your task and press Enter\n";
            printMenuCommands();
            int choice = takeIntInRange(1, 8);

            switch (choice)
            {
            case 1:
                addCourse(db, currentUser);
                break;

            case 2:
                setStudentCourseGrade(db, currentUser);
                break;

            case 3:
            
                computeGPA(currentUser);
                std::cout << "Current GPA calculated successfully.\n";
                break;

            case 4:
            
                updateStudentFlow(db, currentUser);
                break;

            case 5:
                deleteCourseFlow(db, currentUser);
                break;

            case 6:
                deleteUser(db, currentUser);
                if (currentUser.id == 0) return;
                break;

            case 7:
            
                computeGPA(currentUser);
                displayStudentInfo(currentUser);
                break;

            case 8:
            { logOut(currentUser); std::cout << "Logged out successfully.\n"; return; }

            default:
                std::cout << "Invalid choice, please choose between (1-8)\n";
                break;
            }
        }
    }