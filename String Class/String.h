#pragma once

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
	String Concatenate(const String&) const;
	String operator+ (const String&) const;
	String& operator=(const String&);
	String& operator+=(const String&);
	~String();
	void Print();
};