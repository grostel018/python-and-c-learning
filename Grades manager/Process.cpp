#include <iostream>
#include "src/sqlite3.h"
#include "Process.h"
#include "UI.h"
#include "Input.h"
#include "database.h"
#include <string>







void logIN() {
	
	
	taskDelimeter();
	std::cout << "\tEnter your username\n";
	std::string username = takeString();



	taskDelimeter();
	std::cout << "\tEnter your password\n";
	std::string password = takeString();







}















void signIN();












void addCourse();












void deleteCourse();













void deleteUser();












void logOut();