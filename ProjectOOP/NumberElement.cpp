#include "NumberElement.h"
#include "String.h"
template <typename T>
NumberElement<T>::NumberElement() : Elements()
{
	m_Number = 0;
}
template <typename T>
NumberElement<T>::NumberElement(const String& string) : Elements(string)
{
	if (typeid(T) == typeid(int))
		m_Number = string.FromStringToInt();
	else
		m_Number = string.FromStringToDouble();
}