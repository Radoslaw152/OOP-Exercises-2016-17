#pragma once
#include <vector>
#include "Wabbit.h"
class WabbitColony
{
private:
	std::vector<Wabbit> m_Wabbits;
	void MassExtinction();
	void Breed();
	void InfectionOfRMV();
public:
	void AgeWorld();
	void PrintColony();
	void PrintStatistic();
	void ReadColony(int numberOfWabbits);
	void areTheyOldAlready();
};