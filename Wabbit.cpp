#include "Wabbit.h"
#include <iostream>
#include <cassert>
bool Wabbit::isSexuallyActive() const
{
	if (m_Type == RMV || m_AgeOfWabbit < 2) 
	return false;
	else return true;
}

Wabbit Wabbit::Breed(const Wabbit& Wabbit2) const
{
	assert(m_Type != Wabbit2.m_Type &&
		Wabbit2.isSexuallyActive());

	Wabbit BabyWabbit;
	BabyWabbit.m_Type = (TypeOfWabbit)((rand() % 100 <= 20) ? RMV : rand() % 2);
	BabyWabbit.m_Color = Wabbit2.m_Color;
	BabyWabbit.m_AgeOfWabbit = 0;
	return BabyWabbit;
}