#include "ExcelMainMenu.h"
#include "Elements.h"
#include "StringElement.h"
#include "FormulaElements.h"
#include "NumberElement.h"
#include "NumberElement.cpp"
#include "Excel.h"
#include <iostream>
int FindTheStartingIndexOfElement(const String& str, int a)
{
	int indexOfNextElement = a;
	while (indexOfNextElement  + 1< str.getLength() && str[indexOfNextElement] == ' ')
		indexOfNextElement++;
	if (str[indexOfNextElement] == ',')
		return a;
	return indexOfNextElement;
}
int FindTheLastIndexOfElement(const String& str, int a)
{
	bool aCommaInAString = false;
	int indexOfLastElement = a;
	for (int i = a; i < str.getLength(); ++i)
	{
		if (str[i] == ',' && aCommaInAString == false)
		{
			indexOfLastElement = i - 1;
			break;
		}
		if (str[i] == '\"')
			aCommaInAString = (aCommaInAString) ? false : true;
		if (str[i + 1] == '\0')
			indexOfLastElement = i;
	}
	return indexOfLastElement;
}
int numberOfLastIntervals(const String& str, int b)
{
	int index = 0;
	for (int i = b; i < str.getLength() && str[i] == ' '; --i)
	{
		index++;
	}
	return index;
}
Excel::Excel()
{
	m_Rows = 0;
	m_Columns = 0;
	m_Elements = nullptr;
}
void Excel::m_ColumnsCalculating(const String* str)
{
	m_Columns = 1;
	int sumColumns = 1;
	bool aCommaInString = false;
	for (int i = 0; i < m_Rows; ++i)
	{
		sumColumns = 1;
		for (int j = 0; j < str[i].getLength(); ++j)
		{
			if ((str[i].GetString())[j] == ',' && aCommaInString == false)
				sumColumns++;
			if ((str[i].GetString())[j] == '\"')
				aCommaInString = (aCommaInString) ? false : true;
		}
		if (sumColumns > m_Columns)
		{
			m_Columns = sumColumns;
		}
	}
}
Excel::Excel(const String* str, int numberOfRows)
{
	m_Rows = numberOfRows;
	m_ColumnsCalculating(str);
	m_Elements = new Elements**[m_Rows];
	for (int i = 0; i < m_Rows; ++i)
	{
		m_Elements[i] = new Elements*[m_Columns];
	}
	String** tempArrayOfStrings;
	tempArrayOfStrings = new String*[m_Rows];
	for (int i = 0; i < m_Rows; ++i)
	{
		tempArrayOfStrings[i] = new String[m_Columns];
	}
	for (int i = 0; i < m_Rows; ++i)
	{
		int tempFirstElement = 0;
		for (int j = 0; j < m_Columns && tempFirstElement + 1< str[i].getLength(); ++j)
		{
			int tempStart = FindTheStartingIndexOfElement(str[i], tempFirstElement);
			int tempFinal = FindTheLastIndexOfElement(str[i], tempFirstElement);
			if (tempStart == tempFinal)
			{
				tempArrayOfStrings[i][j] = "";
			}
			else
			{
				int tempNumberOfLastIntervals = numberOfLastIntervals(str[i], tempFinal);
				if(str[i].getLength() > tempStart && tempFinal - tempNumberOfLastIntervals < str[i].getLength())
					tempArrayOfStrings[i][j] = str[i].SubString(tempStart,tempFinal - tempNumberOfLastIntervals);
				else if (str[i].getLength() > tempStart)
				{
					tempArrayOfStrings[i][j] = str[i].SubString(tempStart, str[i].getLength() - 1);
				}
			}
			tempFirstElement = tempFinal + 2;
		}
	}
	for (int i = 0; i < m_Rows; ++i)
	{
		for (int j = 0; j < m_Columns; ++j)
		{
			if (TypeDeclaration(tempArrayOfStrings[i][j]) == STRING_TYPE)
			{
				m_Elements[i][j] = new StringElement(tempArrayOfStrings[i][j]);
			}
			else if (TypeDeclaration(tempArrayOfStrings[i][j]) == INT_TYPE)
			{
				m_Elements[i][j] = new NumberElement<int>(tempArrayOfStrings[i][j]);
			}
			else if (TypeDeclaration(tempArrayOfStrings[i][j]) == DOUBLE_TYPE)
			{
				m_Elements[i][j] = new NumberElement<double>(tempArrayOfStrings[i][j]);
			}
			else if (TypeDeclaration(tempArrayOfStrings[i][j]) == FORMULA_TYPE)
			{
				m_Elements[i][j] = new FormulaElements(tempArrayOfStrings[i][j],*this);
			}
			else
			{
				m_Elements[i][j] = new Elements(tempArrayOfStrings[i][j]);
			}
		}
	}
	for (int i = 0; i < m_Rows; ++i)
	{
		delete[] tempArrayOfStrings[i];
	}
	delete[] tempArrayOfStrings;
}
Excel::~Excel()
{
	for (int i = 0; i < m_Rows; ++i)
	{
		for (int j = 0; j < m_Columns; ++j)
		{
			delete m_Elements[i][j];
		}
		delete[] m_Elements[i];
	}
	delete[] m_Elements;
}
Elements* Excel::ReturnElement(int a, int b) const
{
	return m_Elements[a][b];
}
void Excel::PrintInvalidTypes() const
{
	bool areThereStillInvalidTypes = false;
	if (Elements::isThereAInvalidType == true)
	{
		for (int i = 0; i < m_Rows; ++i)
		{
			for (int j = 0; j < m_Columns; ++j)
			{
				if (m_Elements[i][j]->GetType() == INVALID_TYPE)
				{
					std::cerr << "Row: " << i + 1 << ", Column: " << j + 1 << 
						" is invalid type: " << m_Elements[i][j]->GetString() << std::endl;
					areThereStillInvalidTypes = true;
				}
			}
		}
		Elements::isThereAInvalidType = areThereStillInvalidTypes;
	}
	if (Elements::isThereAInvalidType)
		PrintALine();
}
void Excel::Print() const
{
	int* maxLengthColumn = new int[m_Columns];
	for (int j = 0; j < m_Columns; ++j)
	{
		maxLengthColumn[j] = m_Elements[0][j]->GetLengthOfPrint();
		for (int i = 0; i< m_Rows; ++i)
		{
			if (m_Elements[i][j]->GetLengthOfPrint() > maxLengthColumn[j])
			{
				maxLengthColumn[j] = m_Elements[i][j]->GetLengthOfPrint();
			}
		}
	}
	for (int i = 0; i < m_Rows; ++i)
	{
		std::cout << "| ";
		for (int j = 0; j < m_Columns; ++j)
		{
			for (int v = maxLengthColumn[j] - m_Elements[i][j]->GetLengthOfPrint(); v >= 0 && j != 0; --v)
			{
				std::cout << " ";
			}
			m_Elements[i][j]->Print(std::cout);
			for (int v = maxLengthColumn[j] - m_Elements[i][j]->GetLengthOfPrint(); v >= 0 && j == 0; --v)
			{
				std::cout << " ";
			}
			if(j + 1 != m_Columns)
				std::cout << " | ";
		}
		std::cout << " |";
		if(i + 1 != m_Rows)
			std::cout <<std::endl;
	}
	std::cout << std::endl;
	delete[] maxLengthColumn;
}
void Excel::EditElement(const String& string, int row, int column)
{
	delete m_Elements[row][column];
	if (TypeDeclaration(string) == STRING_TYPE)
	{
		m_Elements[row][column] = new StringElement(string);
	}
	else if (TypeDeclaration(string) == INT_TYPE)
	{
		m_Elements[row][column] = new NumberElement<int>(string);
	}
	else if (TypeDeclaration(string) == DOUBLE_TYPE)
	{
		m_Elements[row][column] = new NumberElement<double>(string);
	}
	else if (TypeDeclaration(string) == FORMULA_TYPE)
	{
		m_Elements[row][column] = new FormulaElements(string, *this);
	}
	else
	{
		m_Elements[row][column] = new Elements(string);
	}
}
Excel& Excel::operator=(const Excel& rhs)
{
	m_Rows = rhs.m_Rows;
	m_Columns = rhs.m_Columns;
	m_Elements = new Elements**[m_Rows];
	for (int i = 0; i < m_Rows; ++i)
	{
		m_Elements[i] = new Elements*[m_Columns];
	}
	for (int i = 0; i < m_Rows; ++i)
	{
		for (int j = 0; j < m_Columns; ++j)
		{
			if (TypeDeclaration(rhs.ReturnElement(i,j)->GetString()) == STRING_TYPE)
			{
				m_Elements[i][j] = new StringElement(rhs.ReturnElement(i, j)->GetString());
			}
			else if (TypeDeclaration(rhs.ReturnElement(i, j)->GetString()) == INT_TYPE)
			{
				m_Elements[i][j] = new NumberElement<int>(rhs.ReturnElement(i, j)->GetString());
			}
			else if (TypeDeclaration(rhs.ReturnElement(i, j)->GetString()) == DOUBLE_TYPE)
			{
				m_Elements[i][j] = new NumberElement<double>(rhs.ReturnElement(i, j)->GetString());
			}
			else if (TypeDeclaration(rhs.ReturnElement(i, j)->GetString()) == FORMULA_TYPE)
			{
				m_Elements[i][j] = new FormulaElements(rhs.ReturnElement(i, j)->GetString(), *this);
			}
			else
			{
				m_Elements[i][j] = new Elements(rhs.ReturnElement(i, j)->GetString());
			}
		}
	}
	return *this;
}

void Excel::ResizeTheExcel(int rows, int columns)
{
	int maxRows = (rows > m_Rows) ? rows : m_Rows;
	int maxColumns = (columns > m_Columns) ? columns : m_Columns;
	Elements*** tempElements;
	tempElements = new Elements**[maxRows];
	for (int i = 0; i < rows; ++i)
	{
		tempElements[i] = new Elements*[maxColumns];
	}
	for (int i = 0; i < m_Rows; ++i)
	{
		for (int j = 0; j < m_Columns; ++j)
		{
			if (TypeDeclaration(m_Elements[i][j]->GetString()) == STRING_TYPE)
			{
				tempElements[i][j] = new StringElement(m_Elements[i][j]->GetString());
			}
			else if (TypeDeclaration(m_Elements[i][j]->GetString()) == INT_TYPE)
			{
				tempElements[i][j] = new NumberElement<int>(m_Elements[i][j]->GetString());
			}
			else if (TypeDeclaration(m_Elements[i][j]->GetString()) == DOUBLE_TYPE)
			{
				tempElements[i][j] = new NumberElement<double>(m_Elements[i][j]->GetString());
			}
			else if (TypeDeclaration(m_Elements[i][j]->GetString()) == FORMULA_TYPE)
			{
				tempElements[i][j] = new FormulaElements(m_Elements[i][j]->GetString(), *this);
			}
			else
			{
				tempElements[i][j] = new Elements(m_Elements[i][j]->GetString());
			}
		}
	}
	for (int i = m_Rows; i < maxRows; ++i)
	{
		bool shouldTheLoopContinue = false;
		for (int j = 0; j < maxColumns; ++j)
		{
			tempElements[i][j] = new Elements();
			shouldTheLoopContinue = true;
		}
		if (!shouldTheLoopContinue)
			break;
	}
	for (int i = 0; i < maxRows; ++i)
	{
		bool shouldTheLoopContinue = false;
		for (int j = m_Columns; j < maxColumns; ++j)
		{
			tempElements[i][j] = new Elements();
			shouldTheLoopContinue = true;
		}
		if (!shouldTheLoopContinue)
			break;
	}
	for (int i = m_Rows; i < maxRows; ++i)
	{
		bool shouldTheLoopContinue = false;
		for (int j = m_Columns; j < maxColumns; ++j)
		{
			tempElements[i][j] = new Elements();
			shouldTheLoopContinue = true;
		}
		if (!shouldTheLoopContinue)
			break;
	}
	(*this).~Excel();
	m_Rows = maxRows;
	m_Columns = maxColumns;
	m_Elements = tempElements;
}