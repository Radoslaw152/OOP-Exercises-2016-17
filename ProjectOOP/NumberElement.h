#pragma once
#include "Elements.h"

template <typename T>
class NumberElement : public Elements
{
private:
	T m_Number;
public:
	NumberElement();
	NumberElement(const String&);
	virtual double ValueForFormula() override { return m_Number; };
};