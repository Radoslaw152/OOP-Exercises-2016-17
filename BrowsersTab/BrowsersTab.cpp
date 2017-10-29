#include "BrowsersTab.h"

BrowsersTab* BrowsersTab::Instance = nullptr;
BrowsersTab::BrowsersTab()
{
	m_List.Push_Back(Tab());
	m_CurrentTab = 0;
}
BrowsersTab* BrowsersTab::GetInstance()
{
	if (!BrowsersTab::Instance)
	{
		return BrowsersTab::Instance = new BrowsersTab();
	}
	return BrowsersTab::Instance;
}
void BrowsersTab::Go(const String& url)
{
	m_List[m_CurrentTab].SetTab(url);
}
void BrowsersTab::Insert(const String& rhs)
{
	m_List.Insert(Tab(rhs), ++m_CurrentTab);
}
void BrowsersTab::Back()
{
	if (m_CurrentTab)
		m_CurrentTab--;
}
void BrowsersTab::Forward()
{
	if (m_CurrentTab < m_List.Size() - 1)
		m_CurrentTab++;
}
void BrowsersTab::Remove()
{
	if (m_List.Size() > 1)
	{
		m_List.Remove(m_CurrentTab);
		if (m_CurrentTab == m_List.Size() - 1)
			m_CurrentTab--;
	}	
	else
	{
		m_List[m_CurrentTab].SetTab();
	}
}
void BrowsersTab::Print()
{
	for (int i = 0; i < m_List.Size(); ++i)
	{
		if (m_CurrentTab == i)
			std::cout << "> ";
		std::cout << m_List[i] << std::endl;
	}
}
void BrowsersTab::Sort(const String& sort)
{
	if (sort == "URL")
	{
		bool swapped = true;
		while (swapped)
		{
			swapped = false;
			for (int i = 0; i < m_List.Size() - 1; ++i)
			{
				if (m_List[i].GetName() > m_List[i + 1].GetName())
				{
					m_List.Swap(i, i + 1);
					swapped = true;
				}
				else if (m_List[i].GetName() == m_List[i + 1].GetName())
				{
					if (m_List[i].GetTime() > m_List[i + 1].GetTime())
					{
						m_List.Swap(i, i + 1);
						swapped = true;
					}
				}
			}
		}
	}
	else
	{
		bool swapped = true;
		while (swapped)
		{
			swapped = false;
			for (int i = 0; i < m_List.Size() - 1; ++i)
			{
				if (m_List[i].GetTime() > m_List[i + 1].GetTime())
				{
					m_List.Swap(i, i + 1);
					swapped = true;
				}
				else if (m_List[i].GetTime() == m_List[i + 1].GetTime())
				{
					if (m_List[i].GetName() > m_List[i + 1].GetName())
					{
						m_List.Swap(i, i + 1);
						swapped = true;
					}
				}
			}
		}
	}
}
void BrowsersTab::StartTheProgram()
{
	BrowsersTab* myProgram = BrowsersTab::GetInstance();
	String myCommand;
	std::cin >> myCommand;
	while (myCommand != "EXIT")
	{
		if (myCommand == "GO")
		{
			String url;
			std::cin >> url;
			myProgram->Go(url);
		}
		else if (myCommand == "INSERT")
		{
			String url;
			std::cin >> url;
			myProgram->Insert(url);
		}
		else if (myCommand == "BACK")
		{
			myProgram->Back();
		}
		else if (myCommand == "FORWARD")
		{
			myProgram->Forward();
		}
		else if (myCommand == "REMOVE")
		{
			myProgram->Remove();
		}
		else if (myCommand == "PRINT")
		{
			myProgram->Print();
		}
		else if (myCommand == "SORT")
		{
			String typeSort;
			std::cin >> typeSort;
			if (typeSort == "URL" || typeSort == "TIMESTAMP")
			{
				myProgram->Sort(typeSort);
				myProgram->m_CurrentTab = 0;
			}
			else
			{
				std::cerr << "WRONG COMMAND!" << std::endl;
			}
		}
		else
		{
			std::cerr << "WRONG COMMAND!" << std::endl;
		}
		std::cin >> myCommand;
	}
	delete myProgram;
}