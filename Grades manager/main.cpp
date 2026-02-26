#pragma comment(linker, "/INCREMENTAL:NO")
#include <iostream>
#include "UI.h"
#include "Menu.h"
#include "sqlite3.h"
#include "models.h"
#include "database.h"
#include "Process.h"

int main() {

    openAndInitDatabase("gpa.db");

	
    welcome();
    printCommands();
    logIN();
    menu();
}