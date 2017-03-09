#pragma once

enum TypeOfWabbit
{
	Male, Female, RMV
};
enum ColorOfWabbit
{
	Green, Red, Pink, Blue
};

const int g_MaxAge = 10;
const int g_MinBreedAge = 2;
const int g_RMVChance = 20;
class Wabbit
{
private:
	unsigned m_AgeOfWabbit;
	TypeOfWabbit m_Type;
	ColorOfWabbit m_Color;
public:
	bool isSexuallyActive() const;
	Wabbit Breed(const Wabbit&) const;
};