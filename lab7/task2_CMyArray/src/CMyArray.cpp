#include "./CMyArray.h"
#include <cassert>

template <typename T>
CMyArray<T>::CMyArray()
	: m_data(nullptr)
	, m_size(0)
	, m_capacity(0)
{
}

template <typename T>
CMyArray<T>::~CMyArray()
{
	delete[] m_data;
}

template <typename T>
CMyArray<T>::CMyArray(const CMyArray& other)
{
	m_size = other.m_size;
	m_capacity = other.m_size + 1;
	m_data = new T[m_capacity];

	for (size_t i = 0; i < other.m_size; ++i)
	{
		m_data[i] = other.m_data[i];
	}
}

template <typename T>
CMyArray<T>::CMyArray(CMyArray&& other)
	: CMyArray()
{
	std::swap(m_data, other.m_data);
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
}

template <typename T>
void CMyArray<T>::Resize(size_t size)
{
	if (m_size >= size)
	{
		m_size = size;
		return;
	}

	m_size = size;
	m_capacity = size + 1;
	T* newData = new T[m_capacity];
	for (size_t i = 0; i < m_size; ++i)
	{
		newData[i] = m_data[i];
	}
	delete[] m_data;
	m_data = newData;
}

template <typename T>
void CMyArray<T>::Add(const T& value)
{
	if (m_capacity <= m_size + 1)
	{
		m_capacity = m_capacity == 0
			? 1
			: m_capacity * 2;
		T* newData = new T[m_capacity];
		for (size_t i = 0; i < m_size; ++i)
		{
			newData[i] = m_data[i];
		}
		delete[] m_data;
		m_data = newData;
	}
	++m_size;
	m_data[m_size] = value;
}

template <typename T>
void CMyArray<T>::Clear()
{
	delete[] m_data;
	m_data = nullptr;
	m_capacity = 1;
	m_size = 0;
}

template <typename T>
size_t CMyArray<T>::Size() const
{
	return m_size;
}

template <typename T>
size_t CMyArray<T>::Capacity() const
{
	return m_capacity;
}

template <typename T>
const T& CMyArray<T>::operator[](size_t index) const
{
	assert(index < m_size);
	return m_data[index];
}

template <typename T>
T& CMyArray<T>::operator[](size_t index)
{
	assert(index < m_size);
	return m_data[index];
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator=(CMyArray const& other)
{
	CMyArray temp(other);
	std::swap(m_data, temp.m_data);
	std::swap(m_size, temp.m_size);
	std::swap(m_capacity, temp.m_capacity);
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator=(CMyArray&& other) noexcept
{
	Clear();
	std::swap(m_data, other.m_data);
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
}

template <typename T>
T* CMyArray<T>::begin()
{
	return m_data;
}

template <typename T>
T* CMyArray<T>::end()
{
	return m_data + m_size;
}

template <typename T>
std::reverse_iterator<T*> CMyArray<T>::rbegin()
{
	return std::reverse_iterator(end());
}

template <typename T>
std::reverse_iterator<T*> CMyArray<T>::rend()
{
	return std::reverse_iterator(begin());
}

template <typename T>
const T* CMyArray<T>::begin() const
{
	return m_data;
}

template <typename T>
const T* CMyArray<T>::end() const
{
	return m_data + m_size;
}

template <typename T>
const std::reverse_iterator<T*> CMyArray<T>::rend() const
{
	return std::reverse_iterator(begin());
}

template <typename T>
const std::reverse_iterator<T*> CMyArray<T>::rbegin() const
{
	return std::reverse_iterator(end());
}