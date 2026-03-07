#include <iostream>
#include <limits>   // for std::numeric_limits
#include "Random.h" // https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/

int getGuess(int count, int min, int max)
{
	while (true) // loop until user enters valid input
	{
		std::cout << "Guess #" << count << ": ";

		int guess {};
		std::cin >> guess;

		bool success { std::cin };
		std::cin.clear(); // put us back in 'normal' operation mode (if needed)
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove any extra input

		// If we didn't extract anything or the extracted guess is out of bounds, try again
		if (!success || guess < min || guess > max)
			continue;

		return guess;
	}
}

// returns true if the user won, false if they lost
bool playHiLo(int guesses, int min, int max)
{
	std::cout << "Let's play a game. I'm thinking of a number between " << min << " and " << max << ". You have " << guesses << " tries to guess what it is.\n";
	int number{ Random::get(min, max) }; // this is the number the user needs to guess

	// Loop through all of the guesses
	for (int count{ 1 }; count <= guesses; ++count)
	{
		int guess{ getGuess(count, min, max) };

		if (guess > number)
			std::cout << "Your guess is too high.\n";
		else if (guess < number)
			std::cout << "Your guess is too low.\n";
		else // guess == number, so the user won
		{
			std::cout << "Correct! You win!\n";
			return true;
		}
	}

	// The user lost
	std::cout << "Sorry, you lose. The correct number was " << number << '\n';
	return false; // if the user lost
}

bool playAgain()
{
	// Keep asking the user if they want to play again until they pick y or n.
	while (true)
	{
		char ch{};
		std::cout << "Would you like to play again (y/n)? ";
		std::cin >> ch;

		// clear out any extraneous input
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (ch)
		{
		case 'y': return true;
		case 'n': return false;
		}
	}
}

int main()
{
	constexpr int guesses { 7 }; // the user has this many guesses
	constexpr int min     { 1 };
	constexpr int max     { 100 };

	do
	{
		playHiLo(guesses, min, max);
	} while (playAgain());

	std::cout << "Thank you for playing.\n";

	return 0;
}
