#include "String.h"
#include <string>
#include <iostream>
String::String()
{
	m_string = nullptr;
	m_length = 0;
}
String::String(const char* string)
{
	m_length = strlen(string);
	m_string = new char[m_length + 1];
	strcpy(m_string, string);
}
String::String(const String& rhs)
{
	m_length = rhs.m_length;
	m_string = new char[m_length + 1];
	strcpy(m_string, rhs.m_string);
}
void String::Append(const String& rhs)
{
	char* buffer = nullptr;
	buffer = new char[m_length + rhs.m_length + 1];
	if (m_string)
	{
		strcpy(buffer, m_string);
		delete[] m_string;
	}
	if (rhs.m_string)
	{
		strcpy(buffer + m_length, rhs.m_string);
	}
	m_length += rhs.m_length;
	m_string = buffer;
}
String String::Concatenate(const String& rhs) const
{
	String NewString(*this);
	NewString.Append(rhs);
	return NewString;
}
String& String::operator=(const String& rhs)
{
	m_length = 0;
	(*this).Append(rhs);
	return *this;

}
String String::operator+(const String& rhs) const
{
	String NewString = (*this).Concatenate(rhs);
	return NewString;
}
String& String::operator+= (const String& rhs)
{
	*this =  *this + rhs;
	return *this;
}
String::~String()
{
	delete[] m_string;
}
void String::Print()
{
	std::cout << m_string << " " << m_length << std::endl;
}