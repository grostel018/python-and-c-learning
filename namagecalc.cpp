#include <iostream>
#include <string>


int getname()

{
	std::cout <<"\nEnter your full name: \n";

	std:: string name {};

	std::getline(std::cin >> std::ws, name);

	std::cout << "\n********************************************************************************************\n";


return static_cast<int>(name.length());
}



int getage ()
{
	int input{ 0 };

	std::cout << "\nEnter your age: \n";

	int valid = 0;

	while (valid == 0) {
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();  // Clear the error flag
			std::cin.ignore(1000, '\n');  // Ignore bad input
			valid = 0;
			std::cout << "\nEnter a valid number :\n";

		}
		else
		{
			valid = 1;
		}

	}
	std::cin.ignore(1000, '\n');

	std::cout << "\n********************************************************************************************\n";


	return input;
}





int main()
{

std::cout << "\n********************************************************************************************\n";


int total = getname() + getage();

std::cout << "Your age + lenght of name is : "<<total ;

std::cout << "\n********************************************************************************************\n";






return 0;
}
