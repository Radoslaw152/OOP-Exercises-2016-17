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
const int g_MoreYearsForRMV = 3;
const int g_MaxWabbits = 100;
class Wabbit
{
private:
	unsigned m_AgeOfWabbit;
	TypeOfWabbit m_Type;
	ColorOfWabbit m_Color;
public:
	Wabbit();
	bool isSexuallyActive() const;
	void Print();
	void NextAge();
	int GetAge() const { return this->m_AgeOfWabbit; };
	Wabbit Breed(const Wabbit& Wabbit2) const;
	ColorOfWabbit GetColor() const { return this->m_Color; };
	TypeOfWabbit GetType() const { return this->m_Type; };
	
};