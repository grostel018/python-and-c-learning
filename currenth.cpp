#include <iostream>




double getheight()
{

	double height{ 0.0 };

	std::cout << "\nEnter the height of the tower in meters: ";

	int valid = 0;

	while (valid == 0) {
		std::cin >> height;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			valid = 0;
			std::cout << "\nEnter a valid height :\n";

		}
		else
		{
			valid = 1;
		}

	}
	std::cin.ignore(1000, '\n');

	std::cout << "\n**************\n";

	return height;
}






double currentheight(double h, double t)  //h for height, t for time elapsed
{
	h = h - ((9.8 * t * t) / 2);
	return h;
}

void printheight(double h, double t)
{
	if (currentheight(h, t) >0 )
	std::cout << "\nAt " << t << " seconds, the ball is at height : " << currentheight(h, t) << " meters\n";
	else if (currentheight(h, t) < 0)
	std::cout <<"\nAt " << t << " seconds, the ball is on the ground.\n";

}



int main()
{


	double h{ getheight() };

	printheight(h, 0);
	printheight(h, 1);
	printheight(h, 2);
	printheight(h, 3);
	printheight(h, 4);
	printheight(h, 5);







	return 0;
}
