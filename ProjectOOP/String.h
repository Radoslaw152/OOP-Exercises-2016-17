#pragma once
#include <iostream>
class String
{
private:
	char* m_string;
	int m_length;
public:
	String();
	String(const char*);
	String(const String&);
	int getLength() const { return m_length; };
	void Append(const String&);
	char* GetString() const { return m_string; };
	String Concatenate(const String&) const;
	String operator+ (const String&) const;
	String& operator=(const String&);
	String& operator=(const char*);
	String& operator+=(const String&);
	String& operator+=(const char*);
	String operator+(const char*) const;
	String SubString(int, int) const;
	int FromStringToInt() const;
	double FromStringToDouble() const;
	void Clear();
	bool operator==(const String&) const;
	bool operator==(const char*) const;
	bool operator<(const char*) const;
	bool operator<(const String&) const;
	bool operator>(const char*) const;
	bool operator>(const String&) const;
	bool operator>=(const String&) const;
	bool operator>=(const char*) const;
	bool operator<=(const char*) const;
	bool operator<=(const String&) const;
	char& operator[](int) const;
	bool isThereAChar(char) const;
	void RemoveAllIntervalsInString();
	void PushBack(char);
	void RemoveChar(int);
	~String();
	void Print();
};

void StrCopy(char*, const char*);
int StrLength(const char*);
int StrCompr(const char*, const char*);
std::ostream& operator<< (std::ostream&, const String&);
std::istream& operator>> (std::istream&, String&);
std::istream& getline(std::istream&, String&);
std::istream& getWord(std::istream&, String&);
String FromNumberToString(double);
template <typename T>
T PowFunction(T a, int n);