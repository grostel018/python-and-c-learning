#include <iostream>

double getinput()
{
	double input{ 0.0 };

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
	return input;

}




int main()
{
	std::cout<<"\n\t\tWelcome to the grade average calculator\t\t\n";

	double midterms, midweight, finals, finalsweight, bonus, bonusweight ;

	std::cout<<"\n********************************************************************************************\n";


	while (true) 
	{
	
	std::cout<<"\n\tEnter the midterms grade : ";

	midterms = getinput();

	std::cout << "\n\tEnter the midterms weight in percentages (Example : 40) : ";

	midweight = getinput();

	std::cout << "\n********************************************************************************************\n";



	std::cout << "\n\tEnter the finals grade : ";

    finals = getinput();

	std::cout << "\n\tEnter the finals weight in percentages (Example : 50) : ";

	finalsweight = getinput();

	std::cout << "\n********************************************************************************************\n";



	std::cout << "\n\tEnter the bonus/quizz/projects grade : ";

    bonus = getinput();

	std::cout << "\n\tEnter the bonus/quizz/projects weight in percentages (Example : 10 ) : ";

	bonusweight = getinput();

	std::cout << "\n********************************************************************************************\n";


	if (((midweight + finalsweight + bonusweight) > 100 ) || ((midweight + finalsweight + bonusweight) < 0))
	{
		std::cout << "\n\tError, the values entered exceed the 100% weight limit, or is incorrect, try again";

		std::cout << "\n********************************************************************************************\n";
		
	}

	else break;
	

	}

	double totalgrade = ( (finals*finalsweight/100) + (midterms*midweight/100) + (bonus*bonusweight/100) );

	std::cout << "\nThe total grade is then : "<< totalgrade << "\n";



	std::cout << "\nThe operation is complete\n";

	std::cout << "\n********************************************************************************************\n";







return 0;
}
