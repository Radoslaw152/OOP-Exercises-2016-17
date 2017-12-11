#pragma once
constexpr int DefaultCapacity = 16;

template<typename T>
class Vector
{
private:
	int m_Size;
	int m_Capacity;
	T* m_Array;
	void Copy(const Vector&);
	void Delete();
	void Resize();
public:
	bool Erase(int);
	bool Insert(int, const T&);
	bool Pop_Back();
	bool Push_Back(const T&);
	const int& Size() const { return m_Size; }
	const int& Max_Size() const { return m_Capacity; }
	T& operator[](int);

	Vector();
	Vector(const Vector&);
	Vector<T>& operator=(const Vector&);
	~Vector();

	class Iterator
	{
	private:
		T* m_Start;
		T* m_Current;
		T* m_End;
	public:
		Iterator() : m_Start(nullptr), m_Current(nullptr), m_End(nullptr) {}
		Vector<T>::Iterator& operator++();
		Vector<T>::Iterator& operator++(int);
		T& operator*();
		Vector<T>::Iterator Next() const;
		Vector<T>::Iterator Prev() const;
		Vector<T>::Iterator operator+(int) const;
		bool operator==(const Vector<T>::Iterator&) const;
		bool operator!=(const Vector<T>::Iterator&) const;
	};
	Vector<T>::Iterator& Begin();
	Vector<T>::Iterator& End();
};
template<typename T>
void Vector<T>::Copy(const Vector& rhs)
{
	m_Array = new T[rhs.m_Capacity];
	for (int i = 0; i < rhs.m_Size; ++i)
	{
		m_Array[i] = rhs.m_Array[i];
	}
	m_Size = rhs.m_Size;
	m_Capacity = rhs.m_Capacity;
}
template<typename T>
void Vector<T>::Delete()
{
	delete[] m_Array;
}
template<typename T>
void Vector<T>::Resize()
{
	T* tempBuffer = m_Array;
	m_Capacity *= 2;
	m_Array = new T[m_Capacity];
	for (int i = 0; i < m_Size; ++i)
		m_Array[i] = tempBuffer[i];
	delete[] tempBuffer;
}

template<typename T>
bool Vector<T>::Erase(int index)
{
	if (index >= m_Size || index < 0)
	{
		std::cerr << "You have entered a invalid index. Range is from 0 to " << m_Size - 1 << std::endl;
		return false;
	}
	for (int i = index; i < m_Size - 1; ++i)
	{
		m_Array[i] = m_Array[i + 1];
	}
	--m_Size;
	return true;
}

template<typename T>
bool Vector<T>::Insert(int index, const T& key)
{
	if (index > m_Size || index < 0)
	{
		std::cerr << "You have entered a invalid index. Range is from 0 to " << size - 1 << std::endl;
		return false;
	}
	if (m_Size == m_Capacity)
		Resize();
	for (int i = m_Size; i > index; --i)
	{
		m_Array[i] = m_Array[i - 1];
		m_Array[index] = key;
	}
	++m_Size;
	return true;
}

template<typename T>
bool Vector<T>::Pop_Back()
{
	if (size == 0)
		return false;
	--size;
	return true;
}

template<typename T>
bool Vector<T>::Push_Back(const T& key)
{
	if (m_Size == m_Capacity)
		Resize();
	m_Array[m_Size++] = key;
	return true;
}

template<typename T>
T& Vector<T>::operator[](int index)
{
	if (index >= m_Size || index < 0)
	{
		std::cerr << "Error! There isn't a " << index
			<< " in the array. Maximum available index: "
			<< m_Size - 1 << std::endl;
		std::cout << "Returing the last available" << std::endl;
		return m_Array[m_Size - 1];
	}
	return m_Array[index];
}

template<typename T>
Vector<T>::Vector() : m_Size(0), m_Capacity(DefaultCapacity)
{
	m_Array = new T[DefaultCapacity];
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> rhs) : m_Size(0), m_Capacity(DefaultCapacity)
{
	while (m_Capacity < rhs.size())
		m_Capacity *= 2;
	m_Array = new T[m_Capacity];
	for (int i = 0; i < rhs.size(); ++i)
	{
		Push_Back(*(rhs.begin() + i));
	}
}

template<typename T>
Vector<T>::Vector(const Vector& rhs)
{
	Copy(rhs);
}

template<typename T>
Vector<T>::~Vector()
{
	Delete();
}