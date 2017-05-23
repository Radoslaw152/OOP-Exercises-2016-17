#include "FormulaElements.h"
#include "Excel.h"
#include "String.h"
#include <stack>
bool IsTheCurrentCharAnOperator(const String& string, int index)
{
	return string[index] == '+' || string[index] == '-' || string[index] == '*' || string[index] == '/' || string[index] == '^';
}
String getASinglePart(const String& string, int& index)
{
	String tempString;
	while (string[index] == ' ')
	{
		index++;
	}
	if (index > 0 && index + 1 < string.getLength() && ((IsTheCurrentCharAnOperator(string, index) || string[index] == '(' || string[index] == ')')
		&& (IsTheCurrentCharAnOperator(string, index - 1)) == false
		&& (IsTheCurrentCharAnOperator(string, index + 1)) == false)
		|| ((IsTheCurrentCharAnOperator(string, index) || string[index] == '(' || string[index] == ')') && (string[index + 1] == '+' || string[index + 1] == '-' || string[index] == '(' || string[index] == ')')))
	{
		tempString.PushBack(string[index++]);
	}
	else
	{
		bool didWeHaveANumberAlready = false;
		while ((index < string.getLength() && (string[index] == '(' || string[index] == ')') == false && IsTheCurrentCharAnOperator(string, index) == false)
				|| (index > 0 && IsTheCurrentCharAnOperator(string, index - 1) && (string[index] == '+' || string[index] == '-')
				&& IsTheCurrentCharAnOperator(string, index + 1) == false && didWeHaveANumberAlready == false))
		{
			if (string[index] >= '0' && string[index] <= '9')
				didWeHaveANumberAlready = true;
			if(string[index] != ' ')
				tempString.PushBack(string[index++]);
		}
	}
	return tempString;
}
void RemoveStartingAndLastIntervals(String& string)
{
	int indexOfANewString = 0;
	while (string[indexOfANewString] == ' ')
	{
		indexOfANewString++;
	}
	int endingOfTheNewString = string.getLength() - 1;
	while (string[endingOfTheNewString] == ' ')
	{
		endingOfTheNewString--;
	}
	string = string.SubString(indexOfANewString, endingOfTheNewString);
}
FormulaElements::FormulaElements() : Elements()
{
	m_MyExcel = nullptr;
	m_DivisionByZero = false;
	m_Parts = nullptr;
	m_NumbersAndOperations = 0;
	m_UsedInFormula = false;
	m_EndlessRecursion = false;
}
FormulaElements::FormulaElements(const String& string, Excel& myExcel) : Elements(string)
{
	m_UsedInFormula = false;
	m_MyExcel = &myExcel;
	m_DivisionByZero = false;
	m_EndlessRecursion = false;
	String m_NewString = m_String.SubString(1, m_String.getLength() - 1);
	m_NewString.RemoveAllIntervalsInString();
	if (!m_isTheFormulaCorrectlyWritten(m_NewString))
	{
		m_Type = INVALID_TYPE;
	}
	else
	{
		int numberOfNumbersAndOperators = 0;
		int numberOfBrackets = 0;
		for (int i = 0; i < m_NewString.getLength(); ++i)
		{
			if (i > 0 && IsTheCurrentCharAnOperator(m_NewString, i) && IsTheCurrentCharAnOperator(m_NewString, i - 1) == false )
				numberOfNumbersAndOperators++;
			if (m_NewString[i] == '(')
				numberOfBrackets++;
		}
		m_NumbersAndOperations = 2 * numberOfBrackets + 2 * numberOfNumbersAndOperators + 1;
		m_Parts = new String[m_NumbersAndOperations];
		int startingIndex = 0;
		for (int i = 0; i < m_NumbersAndOperations;++i)
		{
			m_Parts[i] = getASinglePart(m_NewString, startingIndex);
			if (FormulaTypeDeclaration(m_Parts[i]) == INVALID_FORMULA)
				m_Type = INVALID_TYPE;
		}
		m_Parts = m_ShuntingYardingParts(m_NumbersAndOperations, m_Parts, numberOfBrackets);
	}
}
void FormulaElements::Print(std::ostream& o)
{
	if (m_DivisionByZero)
	{
		o << "Division By Zero!";
	}
	else if (m_EndlessRecursion == true)
	{
		o << "Endless Recursion!";
	}
	else
	{
		o << ValueForFormula();
	}
}
double FormulaElements::ValueForFormula()
{
	return m_PostfixEvaluation();
}
bool FormulaElements::m_isTheFormulaCorrectlyWritten(const String& string) const
{
	int numberOfStartingBrackets = 0;
	for (int i = 0; i < string.getLength(); ++i)
	{
		bool a = i == 0 && (string[i] == '*' || string[i] == '/' || string[i] == '^');
		bool b = i == string.getLength() - 1 && IsTheCurrentCharAnOperator(string, i);
		bool c = (i + 1 < string.getLength() && IsTheCurrentCharAnOperator(string, i)
			&& (string[i + 1] == '*' || string[i + 1] == '/' || string[i + 1] == '^'));
		if (a || b || c)
		{
			return false;
		}
		if (string[i] == '(')
		{
			numberOfStartingBrackets++;
		}
		if (string[i] == ')')
			numberOfStartingBrackets--;
		if (numberOfStartingBrackets < 0)
			break;
	}

	return numberOfStartingBrackets == 0;
}
FormulaElements::~FormulaElements()
{
	delete[] m_Parts;
	m_Parts = nullptr;
}
double FormulaElements::m_FromFormulaInStringToNumber(const String& string) const
{
	if (TypeDeclaration(string) == INT_TYPE)
	{
		return string.FromStringToInt();
	}
	else if (TypeDeclaration(string) == DOUBLE_TYPE)
	{
		return string.FromStringToDouble();
	}
	else
	{
		int indexOfCharC = 1;
		while (string[indexOfCharC] != 'C')
			indexOfCharC++;
		int RowOfElement = (string.SubString(1, indexOfCharC - 1)).FromStringToInt() - 1;
		int ColumnOfElement = (string.SubString(indexOfCharC + 1, string.getLength())).FromStringToInt() - 1;
		if (RowOfElement < m_MyExcel[0].GetRows() && ColumnOfElement < m_MyExcel[0].GetColumns())
		{
			if (m_MyExcel[0].ReturnElement(RowOfElement, ColumnOfElement)->GetType() == FORMULA_TYPE && m_MyExcel[0].ReturnElement(RowOfElement, ColumnOfElement)->UsedInFormula())
			{
				m_MyExcel[0].ReturnElement(RowOfElement, ColumnOfElement)->EndlessRecursion() = true;
				return 0;
			}
			else
			{
				return (m_MyExcel[0].ReturnElement(RowOfElement, ColumnOfElement))->ValueForFormula();
			}
		}
		else
			return 0;
	}
}
String* m_ShuntingYardingParts(int& m_NumbersAndOperations, String* m_Parts, int m_NumberOfBrackets)
{
	std::stack<String> m_Stack;
	std::stack<String> OutputQueue;
	for (int i = 0; i < m_NumbersAndOperations; ++i)
	{
		if (FormulaTypeDeclaration(m_Parts[i]) == INT_FORMULA ||
			FormulaTypeDeclaration(m_Parts[i]) == DOUBLE_FORMULA ||
			FormulaTypeDeclaration(m_Parts[i]) == FORMULA_FORMULA)
		{
			m_Stack.push(m_Parts[i]);
		}
		else
		{
			if (m_Parts[i][0] == ')')
			{
				while (OutputQueue.top()[0] != '(')
				{
					m_Stack.push(OutputQueue.top());
					OutputQueue.pop();
				}
				OutputQueue.pop();
			}
			else
			{
				while ((OutputQueue.empty() == false &&
					(((m_Parts[i][0] == '*' || m_Parts[i][0] == '/')
						&& (OutputQueue.top()[0] == '*' || OutputQueue.top()[0] == '/'))
						|| ((m_Parts[i][0] == '+' || m_Parts[i][0] == '-')) ||
							(m_Parts[i][0] != '^' && OutputQueue.top()[0] == '^'))))
				{
					m_Stack.push(OutputQueue.top());
					OutputQueue.pop();
				}
					OutputQueue.push(m_Parts[i]);
			}
		}
	}
	while (!OutputQueue.empty())
	{
		m_Stack.push(OutputQueue.top());
		OutputQueue.pop();
	}
	m_NumbersAndOperations -= (2 * m_NumberOfBrackets);
	delete[] m_Parts;
	m_Parts = new String[m_NumbersAndOperations];
	for (int i = m_NumbersAndOperations - 1 ; i >= 0; --i)
	{
		m_Parts[i] = m_Stack.top();
		m_Stack.pop();
	}
	return m_Parts;
}
FormulaType FormulaTypeDeclaration(const String& string)
{
	if (TypeDeclaration(string) == INT_TYPE)
	{
		return INT_FORMULA;
	}
	if (TypeDeclaration(string) == DOUBLE_TYPE)
	{
		return DOUBLE_FORMULA;
	}
	if (IsTheCurrentCharAnOperator(string, 0) || string[0] == '(' || string[0] == ')')
	{
		return OPERATOR_FORMULA;
	}
	else
	{
		if (string[0] != 'R' || string.isThereAChar('C') == false || string[1] == 'C')
		{
			return INVALID_FORMULA;
		}
		int indexOfCharC = 1;
		while (string[indexOfCharC] != 'C')
			indexOfCharC++;
		if (indexOfCharC >= string.getLength() - 1)
		{
			return INVALID_FORMULA;
		}
		return FORMULA_FORMULA;
	}
}
double FormulaElements::m_PostfixEvaluation() 
{
	m_UsedInFormula = true;
	std::stack<double> Stack;
	for (int i = 0; i < m_NumbersAndOperations && m_DivisionByZero == false && m_EndlessRecursion == false; ++i)
	{
		if (FormulaTypeDeclaration(m_Parts[i]) == FORMULA_FORMULA)
		{
			int indexOfCharC = 1;
			while (m_Parts[i][indexOfCharC] != 'C')
				indexOfCharC++;
			int RowOfElement = (m_Parts[i].SubString(1, indexOfCharC - 1)).FromStringToInt() - 1;
			int ColumnOfElement = (m_Parts[i].SubString(indexOfCharC + 1, m_Parts[i].getLength())).FromStringToInt() - 1;
			if (RowOfElement < m_MyExcel[0].GetRows() && ColumnOfElement < m_MyExcel[0].GetColumns())
			{
				if (m_MyExcel[0].ReturnElement(RowOfElement, ColumnOfElement)->GetType() == FORMULA_TYPE && m_MyExcel[0].ReturnElement(RowOfElement, ColumnOfElement)->EndlessRecursion())
				{
					m_EndlessRecursion = true;
				}
			}
		}
		if (FormulaTypeDeclaration(m_Parts[i]) == INT_FORMULA || FormulaTypeDeclaration(m_Parts[i]) == DOUBLE_FORMULA || FormulaTypeDeclaration(m_Parts[i]) == FORMULA_FORMULA)
		{
			Stack.push(m_FromFormulaInStringToNumber(m_Parts[i]));
		}
		else
		{
			double a = 1;
			double b = 0;
			char operation = m_Parts[i][0];
			if (Stack.empty() == false)
			{
				a = Stack.top();
				Stack.pop();
			}
			if (Stack.empty() == false)
			{
				b = Stack.top();
				Stack.pop();
			}
			switch (operation)
			{
			case '+': Stack.push(b + a); break;
			case '-': Stack.push(b - a); break;
			case '*': Stack.push(b * a); break;
			case '/': (a == 0) ? m_DivisionByZero = true: Stack.push(b / a); break;
			case '^': Stack.push(PowFunction(b, a)); break;
			}
		}
	}
	if (m_EndlessRecursion == false)
	{
		m_UsedInFormula = false;
	}
	else
	{
		return 0;
	}
	if (m_DivisionByZero || Stack.top() == -0)
		return 0;
	return Stack.top();
}
int FormulaElements::GetLengthOfPrint()
{
	int tempLength = (FromNumberToString(m_PostfixEvaluation())).getLength();
	if (m_DivisionByZero)
	{
		String lengthOf = "Division By Zero!";
		return lengthOf.getLength();
	}
	if (m_UsedInFormula == true)
	{
		String lengthOf = "Endless Recursion!";
		return lengthOf.getLength();
	}
	return tempLength;
}