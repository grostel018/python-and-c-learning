#include <iostream>
#include "UI.h"
#include "Menu.h"
#include "sqlite3.h"

int main() {

    sqlite3* db;
    int exit = sqlite3_open("gpa.db", &db);

    if (exit)
        std::cout << "Error opening DB\n";
    else
        std::cout << "Database opened successfully!\n";

    sqlite3_close(db);

    welcome();
    printCommands();
    menu();
}