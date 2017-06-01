#include "Elements.h"
#include "String.h"
#include <iostream>
bool Elements::isThereAInvalidType = false;
Elements::Elements()
{
	m_String = "";
	m_Type = NULL_TYPE;
	m_LengthOfElement = 0;
	NonFormulaRecursion = false;
}
Elements::Elements(const String& str)
{
	m_Type = TypeDeclaration(str);
	if(m_Type == INVALID_TYPE)
		Elements::isThereAInvalidType = true;
	m_LengthOfElement = str.getLength();
	m_String = str;
	NonFormulaRecursion = false;
}
TypeOfElements TypeDeclaration(const String& str) 
{
	if (str[0] == '\"')
		return STRING_TYPE;
	if (str[0] == '=')
		return FORMULA_TYPE;
	TypeOfElements tempType = NULL_TYPE;
	bool isThereMoreThanOnePoint = false;
	bool isThereASign = (str[0] == '+' || str[0] == '-');
	for (int i = (isThereASign) ? 1 : 0; i < str.getLength() && tempType != INVALID_TYPE; ++i)
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] == '.' && isThereMoreThanOnePoint == false)
			{
				tempType = DOUBLE_TYPE;
				isThereMoreThanOnePoint = true;
			}
			else
			{
				tempType = INVALID_TYPE;
			}
		}
		else if (tempType == NULL_TYPE)
		{
			tempType = INT_TYPE;
		}
	}
	return tempType;
}
std::istream& operator>> (std::istream& i, Elements& rhs)
{
	String tempString;
	i >> tempString;
	rhs = Elements(tempString);
	return i;
}
std::ostream& operator<< (std::ostream& i, const Elements& rhs)
{
	i << rhs.GetString();
	return i;
}
std::ostream& operator<< (std::ostream& o, Elements* rhs)
{
	rhs->Print(o);
	return o;
}
void Elements::Print(std::ostream& o)
{
	o << m_String;
}