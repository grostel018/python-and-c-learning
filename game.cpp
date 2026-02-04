#include <iostream>
#include <string>  // For strings
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()  

int getinput()
{
	int input {0};

	std:: cout << "Please enter an input : \n";

	std::cin >> input;

	return input;
}


int randnumb(int min , int max)
{
	return min + (rand() % (max - min + 1));

}


int validinput() 
{
	
	while (true)
	{
	std::cout << "Choose between 1- for paper, 2- for scisors, 3- for rock \n";
	int input = getinput();
	if (input > 0 && input< 4) return input;

	else std::cout << "Error, try again\n";

	}



}

bool wannaplay()
{
	std::cout << "Do you wanna keep playing ? (press 1 for yes, 2 for no) \n ";

	if (getinput() == 1) return true;
	else return false;
}



void print(const std::string& sentence )
{
	std::cout << sentence;
}

std::string choiceToString(int choice)
{
	switch (choice)
	{
	case 1: return "paper";
	case 2: return "scissors";
	case 3: return "rock";
	default: return "invalid";
	}
}


int main()
{
	srand(time(nullptr));

	

	
	
	

	
	
	
	do
	{	
		int choix = validinput();
		srand(time(nullptr));
		int ai = randnumb(1, 3);

		std::cout << "You chose: " << choiceToString(choix) << "\n";
		std::cout << "AI chose: " << choiceToString(ai) << "\n\n";


		if (choix == 1 && ai == 2)
			print("scissors cut the paper, you lost\n") ;


		else if(choix == 2 && ai == 1)
			print("You won, scissors cut the paper\n");


		else if(choix == 3 && ai == 1)
			print("You lost, paper eat the rock\n");


		else if(choix == 1 && ai == 3)
			print("You won, paper eat the rock\n");

			
		else if (choix == 2 && ai == 3)
			print("You lost, rock break the scissors\n");

			
		else if (choix == 3 && ai == 2)
			print("You won, rock break the scissors\n");


		else
		print("It's a tie");

		std::cout << "\n";

	}
	while (wannaplay() == true);





	

	

	return 0;



}
