#pragma comment(linker, "/INCREMENTAL:NO")
#include <iostream>
#include "UI.h"
#include "Menu.h"
#include "sqlite3.h"
#include "models.h"
#include "database.h"
#include "Process.h"

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