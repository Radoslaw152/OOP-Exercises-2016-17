#include "ExcelMainMenu.h"
#include "Excel.h"
#include <iostream>
#include <fstream>
ExcelMainMenu::ExcelMainMenu()
{
	numberOfRows = 0;
	myDocument = nullptr;
}
void ExcelMainMenu::Open()
{
	std::ifstream myFile(fileDest.GetString());
	if (!myFile)
	{
		std::cout << "Invalid file " << fileDest << ", please try again!" << std::endl;
		PrintALine();
		OperationsBeforeFile();
	}
	else
	{
		while (!myFile.eof())
		{
			const int MAX = 1000;
			char buffer[MAX];
			myFile.getline(buffer, MAX);
			myFile.get();
			++numberOfRows;
		}
		myDocument = new String[numberOfRows];
		myFile.clear();
		myFile.seekg(0);
		for (int i = 0; i < numberOfRows; ++i)
		{
			getline(myFile, myDocument[i]);
		}
		myFile.close();
		std::cout << "Successfully opened " << fileDest << std::endl;
		Excel ExcelFMI(myDocument, numberOfRows);
		ShowOperations();
		PrintALine();
		OperationsAfterFile(ExcelFMI);
	}
}
void ExcelMainMenu::Save(Excel& ExcelFMI)
{
	std::ofstream myNewFile(fileDest.GetString());
	for (int i = 0; i < numberOfRows; ++i)
	{
		for (int j = 0; j < ExcelFMI.GetColumns(); ++j)
		{
			myNewFile << ExcelFMI.ReturnElement(i, j)->GetString();
			if (j + 1 != ExcelFMI.GetColumns())
			{
				myNewFile << ',';
			}
		}
		if(i + 1 < numberOfRows)
			myNewFile << std::endl;
	}
	myNewFile.close();
}
void ExcelMainMenu::OperationsBeforeFile()
{
	int intervals = 0;
	int indexOfFirstInterval = 0;
	String tempString;
	getline(std::cin, tempString);
	for (int& i = indexOfFirstInterval; i < tempString.getLength() && intervals < 1; ++i)
	{
		if (tempString[i] == ' ')
		{
			intervals++;
			indexOfFirstInterval--;
		}
	}
	operation = tempString.SubString(0, indexOfFirstInterval - 1);
	PrintALine();
	if (intervals > 0)
	{
		fileDest = tempString.SubString(indexOfFirstInterval + 1, tempString.getLength() - 1);
	}
	if (operation == "Open" || operation == "open" || operation == "OPEN")
	{
		Open();
	}
	else if (operation == "Exit" || operation == "EXIT" || operation == "exit")
	{
		std::cout << "Goodbye, have a nice day, and God please, let my developer has an Excellent grade!" << std::endl;
		std::cout << "Press any key to continue...";
		std::cin.get();
	}
	else
	{
		std::cout << "Ooops, invalid operation. Please, try again: \n";
		OperationsBeforeFile();
	}
}
void ExcelMainMenu::OperationsAfterFile(Excel& ExcelFMI)
{
	ExcelFMI.PrintInvalidTypes();
	std::cout << "Please, type your next command: " << std::endl;
	int intervals = 0;
	String* operations = EnterAOperation(intervals);
	PrintALine();
	operation = operations[0];
	if ((operation == "Edit" || operation == "edit" || operation == "EDIT") && intervals == 2)
	{
		int indexOfCharC = 1;
		while (operations[1][indexOfCharC] != 'C')
		{
			indexOfCharC++;
			if (indexOfCharC + 1 >= operations[1].getLength())
			{
				indexOfCharC = -1;
				break;
			}
		}
		if (operations[1][0] != 'R' || indexOfCharC < 2)
		{
			delete[] operations;
			std::cout << "You have entered invalid data for editting a cell. The correct format is:" << std::endl;
			std::cout << "Edit R<Row number>C<Column number> <TEXT>" << std::endl;
			std::cout << "Example: Edit R100C100 152. This edits Row 100 Column 100 with 152 in integer type cell." << std::endl;
			std::cout << "Returning back to Operations menu..." << std::endl;
			PrintALine();
			OperationsAfterFile(ExcelFMI);
		}
		else
		{
			int RowOfElement = (operations[1].SubString(1, indexOfCharC - 1)).FromStringToInt() - 1;
			int ColumnOfElement = (operations[1].SubString(indexOfCharC + 1, operations[1].getLength())).FromStringToInt() - 1;

			if (RowOfElement >= ExcelFMI.GetRows() || ColumnOfElement >= ExcelFMI.GetColumns())
			{
				ExcelFMI.ResizeTheExcel(RowOfElement + 1, ColumnOfElement + 1);
				numberOfRows = RowOfElement + 1;
			}
			if (TypeDeclaration(operations[2]) != INVALID_TYPE)
			{
				ExcelFMI.EditElement(operations[2], RowOfElement, ColumnOfElement);
				std::cout << "You successfully editted Cell R" << RowOfElement + 1 << 'C' << ColumnOfElement + 1 << std::endl;
			}
			else
			{
				std::cerr << "You have entered an invalid data for cell. " << operations[2] << " is invalid.\nNothing was changed. Please, try again!" << std::endl;
			}
			PrintALine();
			delete[] operations;
			OperationsAfterFile(ExcelFMI);
		}
	}
	else if (operation == "Close" || operation == "close" || operation == "CLOSE")
	{
		std::cout << "You successfully closed " << fileDest << std::endl;
		PrintALine();
		delete[] operations;
		numberOfRows = 0;
		myDocument = nullptr;
		StartTheProgram();
	}
	else if (operation == "Show" || operation == "SHOW" || operation == "show")
	{
		delete[] operations;
		ShowOperations();
		PrintALine();
		OperationsAfterFile(ExcelFMI);
	}
	else if (operation == "Exit" || operation == "exit" || operation == "EXIT")
	{
		std::cout << "Goodbye, have a nice day, and God please, let my developer has an Excellent grade!";
		std::cout << "Press any key to continue...";
		std::cin.get();
		delete[] operations;
	}
	else if (ExcelFMI.AreElementsInvalid() == true)
	{
		delete[] operations;
		std::cerr << "You cannot use this Excel, until there are invalid data type cells.\nPlease use other file or edit this Excel's invalid data types." << std::endl;
		OperationsAfterFile(ExcelFMI);
	}
	else
	{
		
		if (operation == "Print" || operation == "print" || operation == "Print")
		{
			ExcelFMI.Print();
			delete[] operations;
			PrintALine();
			OperationsAfterFile(ExcelFMI);
		}
		else if (operation == "Save" || operation == "save" || operation == "SAVE")
		{
			if (intervals > 0 && (operations[1] == "As" || operations[1] == "as" || operations[1] == "AS"))
			{
				fileDest = operations[2];
			}
			std::cout << "You successfully saved " << fileDest << std::endl;
			PrintALine();
			delete[] operations;
			Save(ExcelFMI);
			OperationsAfterFile(ExcelFMI);
		}
		else
		{
			delete[] operations;
			std::cout << "You've entered an invalid operation. Please Try again!" << std::endl;
			PrintALine();
			OperationsAfterFile(ExcelFMI);
		}
	}
}
void ExcelMainMenu::StartTheProgram()
{
	std::cout << "***Greetings, user! Welcome to the MITEV Excel 2017! How may I help you?***\n";
	std::cout << "1. Open <DESTINATION OF FILE>\n";
	std::cout << "2. Exit\n";
	PrintALine();
	std::cout << "Enter: ";
	OperationsBeforeFile();
}
void ExcelMainMenu::ClearConsole() const
{
	for (int i = 0; i < 1000; ++i)
		std::cout << std::endl;
}
ExcelMainMenu::~ExcelMainMenu()
{
	if(myDocument != nullptr)
		delete[] myDocument;
}
String* ExcelMainMenu::EnterAOperation(int& intervals)
{
	String tempString;
	getline(std::cin, tempString);
	for (int i = 0; i < tempString.getLength() && intervals < 2; ++i)
	{
		if (tempString[i] == ' ')
			intervals++;
	}
	String* operations = new String[intervals + 1];
	int indexOfFirstInterval = 0;
	int indexOfSecondInterval = 0;
	for (int i = 0; i < intervals + 1; ++i)
	{
		while (indexOfSecondInterval < tempString.getLength() && tempString[indexOfSecondInterval] != ' ')
		{
			if (i == 2)
			{
				indexOfSecondInterval = tempString.getLength();
			}
			else
			{
				indexOfSecondInterval++;
			}
		}
		operations[i] = tempString.SubString(indexOfFirstInterval, indexOfSecondInterval - 1);
		indexOfFirstInterval = ++indexOfSecondInterval;
	}
	return operations;
}
void ExcelMainMenu::ShowOperations() const
{
	std::cout << "1. Print (This prints your Excel table on the console)" << std::endl;
	std::cout << "2. Edit R<Row number>C<Column number> <TEXT>(This edits a cell in your Excel)" << std::endl;
	std::cout << "3. Save (This command saves your Excel table on the current file destination)" << std::endl;
	std::cout << "4. Save As <NEW FILE DESTINATION> (This command saves your Excel table on new file destination)" << std::endl;
	std::cout << "5. Close (This closes your Excel table WITHOUT saving it)" << std::endl;
	std::cout << "7. Show Menu (This command prints these operations above)" << std::endl;
	std::cout << "6. Exit (This exits the program)" << std::endl;
}
void PrintALine()
{
	for (int i = 0; i < 75; ++i)
		std::cout << '-';
	std::cout << std::endl;
}
