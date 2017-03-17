#include"WabbitColony.h"
#include<vector>
#include<iostream>

void WabbitColony::MassExtinction()
{
	int kill = m_Wabbits.size() / 2;
	for(int kill = m_Wabbits.size() / 2; kill > 0; kill--)
	{
		int i = rand() % m_Wabbits.size();
		this->m_Wabbits.erase(m_Wabbits.begin() + i);
	}
	if (m_Wabbits.size() > g_MaxWabbits)
	{
		MassExtinction();
	}
}
void WabbitColony::Breed()
{
	int currentAmountOfWabbits = m_Wabbits.size();
	for (int i = 0; i < currentAmountOfWabbits; ++i)
	{
		for (int j = 0; j < currentAmountOfWabbits; ++j)
		{
			bool canTheyMakeABaby = m_Wabbits[i].GetType() == Male 
				&& m_Wabbits[j].GetType() == Female
				&& m_Wabbits[i].isSexuallyActive()
				&& m_Wabbits[j].isSexuallyActive();
			if(canTheyMakeABaby)
				m_Wabbits.push_back(m_Wabbits[i].Breed(m_Wabbits[j]));
		}
	}
}
void WabbitColony::InfectionOfRMV()
{
	int numberOfInfectedRMV = 0;
	for (int i = 0; i < m_Wabbits.size(); ++i)
	{
		if (m_Wabbits[i].GetType() == RMV)
		{
			numberOfInfectedRMV++;
		}
	}
	int whereAmI = 0;
	for (int i = 0; whereAmI < numberOfInfectedRMV || i < m_Wabbits.size(); ++i)
	{
		if (m_Wabbits[i].GetType() != RMV)
		{
			m_Wabbits[i].GetType() == RMV;
			whereAmI++;
		}
	}
}
void WabbitColony::AgeWorld()
{
	if (m_Wabbits.size() > g_MaxWabbits)
		MassExtinction();
	for (int i = 0; i < m_Wabbits.size(); ++i)
	{
		m_Wabbits[i].NextAge();
	}
	areTheyOldAlready();
	Breed();
	InfectionOfRMV();
	if (m_Wabbits.size() > g_MaxWabbits)
		MassExtinction();
}
void WabbitColony::PrintColony()
{
	for (int i = 0; i < m_Wabbits.size(); ++i)
	{
		std::cout << i + 1 << ". Wabbit: ";
		m_Wabbits[i].Print();
		std::cout << "\n";
	}
}
void WabbitColony::ReadColony(int numberOfWabbits)
{
	for (int i = 0; i < numberOfWabbits; ++i)
	{
		m_Wabbits.push_back(Wabbit());
	}
}
void WabbitColony::PrintStatistic()
{
	int numberOfMale = 0;
	int numberOfFemale = 0;
	int numberOfRMV = 0;
	int numberOfGreen = 0;
	int numberOfRed = 0;
	int numberOfPink = 0;
	int numberOfBlue = 0;
	for (int i = 0; i < m_Wabbits.size(); ++i)
	{
		switch (m_Wabbits[i].GetType())
		{
		case Male: numberOfMale++; break;
		case Female: numberOfFemale++; break;
		case RMV: numberOfRMV++; break;
		}
		switch (m_Wabbits[i].GetColor())
		{
		case Green: numberOfGreen++; break;
		case Red: numberOfRed++; break;
		case Pink: numberOfPink++; break;
		case Blue: numberOfBlue++; break;
		}
	}
	std::cout << "Number of Male Wabbits: " << numberOfMale << "\n";
	std::cout << "Number of Female Wabbits: " << numberOfFemale << "\n";
	std::cout << "Number of RMV Wabbits: " << numberOfRMV << "\n";
	std::cout << "Number of Green Wabbits: " << numberOfGreen << "\n";
	std::cout << "Number of Red Wabbits: " << numberOfRed << "\n";
	std::cout << "Number of Pink Wabbits: " << numberOfPink << "\n";
	std::cout << "Number of Blue Wabbits: " << numberOfBlue << "\n";
}

void WabbitColony::areTheyOldAlready()
{
	for (int i = 0; i < m_Wabbits.size(); ++i)
	{
		if (m_Wabbits[i].GetType() != RMV && m_Wabbits[i].GetAge() > g_MaxAge)
		{
			m_Wabbits.erase(m_Wabbits.begin() + i);
		}
		else if (m_Wabbits[i].GetType() == RMV && m_Wabbits[i].GetAge() >
			g_MaxAge * g_MoreYearsForRMV)
		{
			m_Wabbits.erase(m_Wabbits.begin() + i);
		}
	}
}