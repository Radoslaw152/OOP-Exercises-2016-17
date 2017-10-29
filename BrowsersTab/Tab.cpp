#include "Tab.h"
#include <iostream>
#include <time.h>
void Tab::Initialize()
{
	m_Name = "about::blank";
	m_Time = time(NULL);
}
Tab::Tab()
{
	Initialize();
}
Tab::Tab(const String& name, long long _time) : m_Name(name), m_Time(_time)
{

}
void Tab::Print(std::ostream& os) const
{
	os << m_Name << " " << m_Time;
}
std::ostream& operator<<(std::ostream& os, const Tab& rhs)
{
	rhs.Print(os);
	return os;
}
void Tab::SetTab(const String& name) 
{
	m_Name = name;
	m_Time = time(NULL);
}