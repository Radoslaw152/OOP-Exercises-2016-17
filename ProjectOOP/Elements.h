#pragma once
#include "String.h"
#include <iostream>
enum TypeOfElements
{
	NULL_TYPE, INT_TYPE, DOUBLE_TYPE, STRING_TYPE, FORMULA_TYPE, INVALID_TYPE
};
class Elements
{
private:
	bool NonFormulaRecursion;
protected:
	int m_LengthOfElement;
	String m_String;
	TypeOfElements m_Type;
public:
	Elements();
	Elements(const String&);
	static bool isThereAInvalidType; 
	virtual void Print(std::ostream&); 
	virtual bool& EndlessRecursion() { return NonFormulaRecursion; }
	virtual bool UsedInFormula() const { return false; }
	String GetString() const { return m_String; };
	virtual int GetLengthOfPrint() { return m_String.getLength(); }
	virtual double ValueForFormula() { return 0; };
	int GetLengthOfElement() const { return m_LengthOfElement; };
	TypeOfElements GetType() const { return m_Type; };
};
TypeOfElements TypeDeclaration(const String&);
std::istream& operator>> (std::istream&, const Elements&);
std::ostream& operator<< (std::ostream&, const Elements&);
std::ostream& operator<< (std::ostream&, Elements*);
