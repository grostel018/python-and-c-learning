#include <iostream>


double getinput()
{
	double input {0.0};

	std::cout << "\nEnter an operand\n";

	std::cin >> input ;



	if (std::cin.fail())
	{
		std::cin.clear();  // Clear the error flag
		std::cin.ignore(1000, '\n');  // Ignore bad input
		std::cout << "\nEnter a valid input\n";
		return 0.0;  // Return default value
	}
		
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
	return { a / b };
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

		// Check if op IS valid (not if it's invalid)
		if (op == '+' || op == '-' || op == '*' || op == '/')
		{
			valid = 1;  // Now it's valid!
		}
		else
		{
			std::cout << "\nEnter a valid input\n";
		}
	}

	return op;
}



double calculate(double numb1, double numb2)
{

	char operand = getoperator();
	


	

	double result {0};

	std::cout << "\nThe result is :" <<result << "\n";


}






int main()
{	
	calculate(getinput(), getinput());


	return 0;
}
