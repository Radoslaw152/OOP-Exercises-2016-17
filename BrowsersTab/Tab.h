#pragma once
#include "String.h"
#include <time.h>
class Tab
{
private:
	String m_Name;
	long long m_Time;
	void Initialize();
public:
	Tab();
	Tab(const String&, long long _time = time(NULL));
	void SetTab(const String& = "about::blank");
	String GetName() const { return m_Name; }
	long long GetTime() const { return m_Time; }
	void Print(std::ostream& os = std::cout) const;
};
std::ostream& operator<<(std::ostream&, const Tab&);