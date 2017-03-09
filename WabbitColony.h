#pragma once
#include <vector>
#include "Wabbit.h"
class WabbitColony
{
private:
	std::vector<Wabbit> m_Wabbits;
	void MassExtinction();
	void Breed();
public:
	void AgeWorld();
};