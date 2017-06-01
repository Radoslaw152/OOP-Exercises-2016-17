#pragma once
#include <iostream>
#include <fstream>
#include "String.h"
#include "Elements.h"
#include "Excel.h"
class ExcelMainMenu
{
private:
	int numberOfRows;
	String* myDocument;
	String operation;
	String fileDest;
	void Open();
	void Save(Excel&);
	void OperationsBeforeFile();
	void OperationsAfterFile(Excel&);
	void ClearConsole() const;
	void ShowOperations() const;
	String* EnterAOperation(int&);
public:
	ExcelMainMenu();
	~ExcelMainMenu();
	void StartTheProgram();
};
void PrintALine();