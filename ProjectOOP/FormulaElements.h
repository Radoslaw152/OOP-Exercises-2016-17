#pragma once
#include "Elements.h"
#include "Excel.h"
#include "String.h"
#include <iostream>
#include <stack>
enum FormulaType
{
	INT_FORMULA, DOUBLE_FORMULA, FORMULA_FORMULA, OPERATOR_FORMULA, INVALID_FORMULA
};
class FormulaElements : public Elements
{
private:
	String* m_Parts;
	Excel* m_MyExcel;
	int m_NumbersAndOperations;
	bool m_UsedInFormula;
	bool m_EndlessRecursion;
	bool m_DivisionByZero;
	bool m_isTheFormulaCorrectlyWritten(const String&) const;
	double m_FromFormulaInStringToNumber(const String&) const;
	double m_PostfixEvaluation();
public:
	FormulaElements();
	FormulaElements(const String&, Excel&);
	~FormulaElements();
	virtual bool& EndlessRecursion() override { return m_EndlessRecursion; }
	virtual bool UsedInFormula() const override { return m_UsedInFormula; }
	virtual void Print(std::ostream&); //const
	virtual double ValueForFormula() override;
	virtual int GetLengthOfPrint() override;
};
String* m_ShuntingYardingParts(int& m_NumbersAndOperations, String* m_Parts, int m_NumberOfBrackets);
FormulaType FormulaTypeDeclaration(const String&);