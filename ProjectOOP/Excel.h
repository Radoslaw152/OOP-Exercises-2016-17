#pragma once
#include "Elements.h"
class Excel
{
private:
	int m_Rows;
	int m_Columns;
	Elements*** m_Elements;
	void m_ColumnsCalculating(const String*);
public:
	Excel();
	Excel(const String*, int);
	Excel& operator=(const Excel&);
	int GetRows() const { return m_Rows; }
	int GetColumns() const { return m_Columns; }
	void PrintInvalidTypes() const;
	void Print() const;
	bool AreElementsInvalid() const { return m_Elements[0][0]->isThereAInvalidType; }
	void ResizeTheExcel(int, int);
	void EditElement(const String&, int, int);
	Elements* ReturnElement(int, int) const;
	~Excel();
};
int FindTheStartingIndexOfElement(const String&, int);
int FindTheStartingIndexOfElement(const String&, int );
int FindTheLastIndexOfElement(const String&, int);
int numberOfLastIntervals(const String&, int);