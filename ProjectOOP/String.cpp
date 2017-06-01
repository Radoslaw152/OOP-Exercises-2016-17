#include "String.h"
#include <iostream>

String::String()
{
	m_string = new char[1];
	m_string[0] = '\0';
	m_length = 0;
}
String::String(const char* string)
{
	m_length = StrLength(string);
	m_string = new char[m_length + 1];
	StrCopy(m_string, string);
}
String::String(const String& rhs)
{
	m_length = rhs.m_length;
	m_string = new char[m_length + 1];
	StrCopy(m_string, rhs.m_string);
}
void String::Append(const String& rhs)
{
	char* buffer = nullptr;
	buffer = new char[m_length + rhs.m_length + 1];
	if (m_string && m_string[0] != '\0')
	{
		StrCopy(buffer, m_string);
		delete[] m_string;
	}
	if (rhs.m_string)
	{
		StrCopy(buffer + m_length, rhs.m_string);
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
	delete[] m_string;
	m_string = new char[rhs.m_length + 1];
	StrCopy(m_string, rhs.m_string);
	m_length = rhs.m_length;
	return *this;

}
String String::operator+(const String& rhs) const
{
	String NewString = (*this).Concatenate(rhs);
	return NewString;
}
String& String::operator+= (const String& rhs)
{
	return *this = *this + rhs;
}
String::~String()
{
	delete[] m_string;
	m_string = nullptr;
}
void String::Print()
{
	std::cout << m_string << " " << m_length << std::endl;
}
std::ostream& operator<< (std::ostream& lhs, const String& rhs)
{
	return lhs << rhs.GetString();
}
std::istream& operator >> (std::istream& lhs, String& rhs)
{
	const int MaxLength = 1000;
	char buffer[MaxLength];
	lhs >> buffer;
	rhs = buffer;
	return lhs;
}
char& String::operator[](int i) const
{
	if (i > m_length)
	{
		std::cerr << m_string << "is trying to give char N" << i << std::endl;
		char ch = '0';
		return ch;
	}
	return m_string[i];
}
String& String::operator=(const char* str)
{
	String temp(str);
	return *this = temp;
}
int StrLength(const char* str)
{
	if (str == nullptr)
	{
		return 0;
	}
	int length = 0;
	for (int i = 0; str[i] != '\0'; ++i)
	{
		length++;
	}
	return length;
}
void StrCopy(char* str1, const char* str2)
{
	if (str2[0] == '\0')
	{
		str1[0] = '\0';
	}
	else
	{
		for (int i = 0; str2[i] != '\0'; ++i)
		{
			str1[i] = str2[i];
			if (str2[i + 1] == '\0')
				str1[i + 1] = '\0';
		}
	}
}
int StrCompr(const char* str1, const char* str2)
{
	for (int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++)
	{
		if (str1[i] > str2[i])
		{
			return 1;
		}
		else if (str1[i] < str2[i])
		{
			return -1;
		}
	}
	return 0;
}
bool String::operator==(const char* str2) const
{
	if (StrCompr((*this).GetString(), str2) == 0)
		return 1;
	else
		return 0;
}
bool String::operator==(const String& rhs) const
{
	return *this == rhs.GetString();
}
void String::Clear()
{
	String temp;
	*this = temp;
}
std::istream& getline(std::istream& is, String& str)
{
	char temp;
	str.Clear();
	while (is.get(temp) && temp != '\n')
		str.PushBack(temp);
	return is;
}
bool String::operator<(const char* rhs) const
{
	return (StrCompr(m_string, rhs) == -1) ? 1 : 0;
}
bool String::operator<(const String& rhs) const
{
	return (StrCompr(m_string, rhs.GetString()) == -1) ? 1 : 0;
}
bool String::operator>(const char* rhs) const
{
	return (StrCompr(m_string, rhs) == 1) ? 1 : 0;
}
bool String::operator>(const String& rhs) const
{
	return (StrCompr(m_string, rhs.GetString()) == 1) ? 1 : 0;
}
bool String::operator>=(const String& rhs) const
{
	return (StrCompr(m_string, rhs.GetString()) > -1) ? 1 : 0;
}
bool String::operator>=(const char* rhs) const
{
	return (StrCompr(m_string, rhs) > -1) ? 1 : 0;
}
bool String::operator<=(const char* rhs) const
{
	return (StrCompr(m_string, rhs) < 1) ? 1 : 0;
}
bool String::operator<=(const String& rhs) const
{
	return (StrCompr(m_string, rhs.GetString()) < 1) ? 1 : 0;
}
void String::PushBack(char ch)
{
	char temp[] = { ch,'\0' };
	*this += temp;
}
String& String::operator+=(const char* rhs)
{
	String temp = rhs;
	return *this += temp;
}
String String::operator+(const char* rhs) const
{
	String temp = rhs;
	String newString = *this + temp;
	return newString;
}
std::istream& getWord(std::istream& is, String& str)
{
	char temp;
	str.Clear();
	while (is.get(temp) && temp != ' ' && temp != '\n')
		str.PushBack(temp);
	return is;
}
String String::SubString(int a, int b) const
{
	int lengthOfNewString = b - a + 1;
	char* temp = new char[lengthOfNewString + 1];
	for (int i = 0; i < lengthOfNewString; ++i)
		temp[i] = (*this)[a + i];
	temp[lengthOfNewString] = '\0';
	String newString = temp;
	return newString;
}
template <typename T>
T PowFunction(T a, int n)
{
	if (n == 0)
	{
		return 1;
	}
	else if (n < 0)
	{
		n *= -1;
		T newNumber = a;
		for (int i = 1; i < n; ++i)
		{
			newNumber *= a;
		}
		return 1 / newNumber;
	}
	else
	{
		T newNumber = a;
		for (int i = 1; i < n; ++i)
		{
			newNumber *= a;
		}
		return newNumber;
	}
}
int String::FromStringToInt() const
{
	int ourNumber = 0;
	int positiveOrNegative = (m_string[0] == '-') ? -1 : 1;
	bool isThereASign = m_string[0] == '-' || m_string[0] == '+';
	for (int i = (isThereASign) ? 1 : 0; i < m_length; ++i)
	{
		int a = (m_string[i] - '0') * PowFunction<int>(10, m_length - i - 1);
		ourNumber +=  a;
	}
	return ourNumber * positiveOrNegative;
}
double String::FromStringToDouble() const
{
	double ourNumber = 0;
	int positiveOrNegative = (m_string[0] == '-') ? -1 : 1;
	bool isThereASign = m_string[0] == '-' || m_string[0] == '+';
	int indexOfComma = 0;
	while (m_string[indexOfComma] != '.')
		indexOfComma++;
	for (int i = (isThereASign) ? 1 : 0; i < indexOfComma; ++i)
	{
		ourNumber += (m_string[i] - '0') * PowFunction<int>(10, indexOfComma - i - 1);
	}
	for (int i = indexOfComma + 1; i < m_length; ++i)
	{
		ourNumber += (m_string[i] - '0') * PowFunction<double>(0.1, i - indexOfComma);
	}
	return ourNumber * positiveOrNegative;
}
String FromIntToString(int a)
{
	int lengthOfTheInt = 0;
	for (int i = 1; a / i > 0; i *= 10)
		lengthOfTheInt++;
	String newString;
	for (int i = 0; i < lengthOfTheInt; ++i)
	{
		char ch = a / PowFunction(10, lengthOfTheInt - i - 1) + '0';
		a %= PowFunction(10, lengthOfTheInt - i - 1);
		newString.PushBack(ch);
	}
	return newString;
}
void String::RemoveChar(int index)
{
	String beforeIndex;
	if(index - 1 >= 0)
		beforeIndex = (*this).SubString(0, index - 1);
	String afterIndex;
	if (index + 1 <= m_length - 1)
		afterIndex = (*this).SubString(index + 1, m_length - 1);
	*this = beforeIndex + afterIndex;
	int n = 0;
}
bool String::isThereAChar(char ch) const
{
	for (int i = 0; i < m_length; ++i)
	{
		if (m_string[i] == ch)
			return true;
	}
	return false;
}
void String::RemoveAllIntervalsInString()
{
	for (int i = 0; i < (*this).getLength(); ++i)
	{
		if ((*this)[i] == ' ')
		{
			(*this).RemoveChar(i);
			i--;
		}
	}
}
String FromNumberToString(double a)
{
	String number;
	if (a < 0)
	{
		number.PushBack('-');
		a *= -1;
	}
	int digitsBeforePoint = 1;
	int temp = (int)a;
	for (int i = 10; temp / i != 0; i *= 10)
	{
		digitsBeforePoint++;
	}
	for (int i = PowFunction(10, digitsBeforePoint - 1); i != 0; i /= 10)
	{
		number.PushBack((char)((temp / i) % 10 + '0'));
	}
	if (temp != a)
	{
		number.PushBack('.');
		int digitsAfterPoint = 0;
		for (int i = 1; a * i != (int)(a * i); i *= 10)
		{
			digitsAfterPoint++;
		}
		int numberAfterPoint = ((int)(a * PowFunction(10, digitsBeforePoint)) % PowFunction(10, digitsBeforePoint));
		for (int i = PowFunction(10, digitsAfterPoint - 1); i != 0; i /= 10)
		{
			number.PushBack((char)((numberAfterPoint / i) % 10 + '0'));
		}
	}
	return number;
}
