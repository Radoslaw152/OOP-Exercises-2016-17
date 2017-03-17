#include <iostream>
#include <vector>
#include <ctime>
#include "WabbitColony.h"
int main()
{
	srand(time(NULL));
	WabbitColony myColony;
	int numberOfWabbits;
	int numberOfYears;
	std::cin >> numberOfWabbits;
	std::cin >> numberOfYears;
	myColony.ReadColony(numberOfWabbits);
	for (int i = 0; i < numberOfYears; ++i)
	{
		std::cout << "Year: " << i << "\n";
		myColony.PrintStatistic();
		myColony.AgeWorld();
	}
	return 0;
}