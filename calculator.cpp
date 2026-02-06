#include <iostream>


double getinput()
{
	double input {0.0};

	std::cout << "\nEnter an operand :\n";

	int valid = 0;

	while (valid == 0) {
	std::cin >> input ;

	if (std::cin.fail())
	{
		std::cin.clear();  // Clear the error flag
		std::cin.ignore(1000, '\n');  // Ignore bad input
		valid = 0;
		std::cout << "\nEnter a valid number :\n";
		
	}
	else
	{
		valid = 1;  // <-- THIS IS WHAT YOU WERE MISSING!
	}
		
	}
	std::cin.ignore(1000, '\n');
	return input;

}




double addition(double a, double b)
{ 
	return { a + b };
}


double substraction(double a, double b)
{
	return { a - b };
}


double multiplication(double a, double b)
{
	return { a * b};
}

double division(double a, double b)
{
	// Add check for division by zero
	if (b == 0)
	{
		std::cout << "Error: Division by zero!\n";
		return 0.0;
	}
	return a / b;
}


char getoperator()
{
	char op = '+';
	int valid = 0;  // 0 means not valid yet

	std::cout << "\nEnter the operator\n";
	std::cout << "\nSelect between (+, -, * or /) \n";

	while (valid == 0)
	{
		std::cin >> op;
		std::cin.ignore(1000, '\n');

		// Check if op IS valid (not if it's invalid)
		if (op == '+' || op == '-' || op == '*' || op == '/')
		{
			valid = 1;  // Now it's valid!
		}
		else
		{
			std::cout << "\nEnter a valid operator :\n";
		}
	}

	return op;
}



double calculate(double numb1, double numb2)
{

	char operand = getoperator();

	std::cout << "=================\n";
	

	double result {0};

	switch (operand)
	{
		case '+' :
		result = addition (numb1, numb2);
		break;

		case '-' : 
		result = substraction (numb1, numb2);
		break;

		case '*' : 
		result = multiplication(numb1, numb2);
		break;

		case '/' : 
		result = division(numb1, numb2);
		break;


	}

	std::cout << "\nThe result of "<<numb1<<operand<<numb2<<" is : " <<result << "\n";

	return result ;


}
void newcalc()
{
	double numb1 = getinput();
	std::cout << "=================\n";
	double numb2 = getinput();
	std::cout << "=================\n";
	calculate(numb1, numb2);
}




int main()
{	
	std::cout << "\t-----welcome to the calculator app-----\t\n";
	std::cout << "\t           =================\n";

	char choice = 'y';

	while (choice == 'y' || choice == 'Y')
	{
		std::cout << "\nNew calculation:\n";
		newcalc();

		std::cout << "\nDo you wish to make Another calculation? (y/n): ";
		std::cin >> choice;
		std::cin.ignore(1000, '\n');

		std::cout << "\t           =================\n";


		
	}

	std::cout << "\nGoodbye!\n";
	return 0;
}
