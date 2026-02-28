#pragma comment(linker, "/INCREMENTAL:NO")
#include <iostream>
#include "UI.h"
#include "Menu.h"
#include "sqlite3.h"
#include "models.h"
#include "database.h"
#include "Process.h"

int main() {
    
    sqlite3* db = openAndInitDatabase("gpa.db");
    Student currentUser{};
	
    welcome();
    printCommands();


    bool success = logIN(db, currentUser);
    if (success) {
        std::cout << "User ID: " << currentUser.id << "\n";
        std::cout << "Username: " << currentUser.username << "\n";

        // You can now call menu(currentUser) or dashboard(currentUser)
        menu();
    }
    else {
        std::cout << "Login failed.\n";
    }

    sqlite3_close(db);
    return 0;

}