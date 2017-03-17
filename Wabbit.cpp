#include "Wabbit.h"
#include <iostream>
#include <cassert>
#include <string>
Wabbit::Wabbit()
{
	m_Type = (TypeOfWabbit)(rand() % 3);
	m_Color = (ColorOfWabbit)(rand() % 4);
	m_AgeOfWabbit = 0;
}
bool Wabbit::isSexuallyActive() const
{
	return (m_Type != RMV && m_AgeOfWabbit >= 2);
	
}
Wabbit Wabbit::Breed(const Wabbit& Wabbit2) const
{
	Wabbit BabyWabbit;
	BabyWabbit.m_Type = (TypeOfWabbit)((rand() % 100 <= 20) ? RMV : rand() % 2);
	BabyWabbit.m_Color = Wabbit2.m_Color;
	BabyWabbit.m_AgeOfWabbit = 0;
	return BabyWabbit;
}
void Wabbit::Print()
{
	std::string colorTemp;
	std::string typeTemp;
	switch (m_Type)
	{
	case Male: typeTemp = "Male"; break;
	case Female: typeTemp = "Female"; break;
	case RMV: typeTemp = "RMV"; break;
	}
	switch (m_Color)
	{
	case Green: colorTemp = "Green"; break;
	case Red: colorTemp = "Red"; break;
	case Pink: colorTemp = "Pink"; break;
	case Blue: colorTemp = "Blue"; break;
	}
	std::cout << "Years: " << m_AgeOfWabbit
		<< ", Type: " << typeTemp << ", Color: " << colorTemp;
}
void Wabbit::NextAge()
{
	m_AgeOfWabbit++;
}
