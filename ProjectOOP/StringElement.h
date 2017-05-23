#pragma once
#include "Elements.h"
#include <iostream>
class StringElement : public Elements
{
public:
	StringElement();
	StringElement(const String&);
	void Print(std::ostream&);
	double ValueForFormula() { return 0; };
	virtual int GetLengthOfPrint() override;
};