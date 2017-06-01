#include "StringElement.h"

StringElement::StringElement()
{
	Elements:: Elements();
}
StringElement::StringElement(const String& string) : Elements(string)
{
	
}
void StringElement::Print(std::ostream& o)
{
	for (int i = 0; i < m_String.getLength(); ++i)
	{
		bool removeQuoteMarks = (i > 0 && m_String[i - 1] != '\\' && m_String[i] == '\"')
			|| (i == 0 && m_String[i] == '\"');
		bool makeQuoteMarksReadable = i + 1 < m_String.getLength() && m_String[i] == '\\' && m_String[i + 1] == '\"';
		if (removeQuoteMarks)
		{
			continue;
		}
		else if (makeQuoteMarksReadable)
		{
			o << '\"';
			++i;
		}
		else
		{
			o << m_String[i];
		}
	}
}
int StringElement::GetLengthOfPrint()
{
	int tempLowerLength = 0;
	for (int i = 0; i < m_String.getLength(); ++i)
	{
		bool unreadableQuoteMarks = (i > 0 && m_String[i - 1] != '\\' && m_String[i] == '\"')
			|| (i == 0 && m_String[i] == '\"');
		bool ReadableQuoteMarks = i + 1 < m_String.getLength() && m_String[i] == '\\' && m_String[i + 1] == '\"';
		if (unreadableQuoteMarks)
		{
			tempLowerLength++;
		}
		else if (ReadableQuoteMarks)
		{
			tempLowerLength++;
		}
	}
	return m_String.getLength() - tempLowerLength;
}