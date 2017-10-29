#pragma once
#include "Tab.h"
#include "DoublyLinkedList.h"

class BrowsersTab
{
private:
	DoublyLinkedList<Tab> m_List;
	size_t m_CurrentTab;
	static BrowsersTab* Instance;
	BrowsersTab();
	void Go(const String&);
	void Insert(const String&);
	void Back();
	void Forward();
	void Remove();
	void Print();
	void Sort(const String&);
	static BrowsersTab* GetInstance();
public:
	static void StartTheProgram();
};