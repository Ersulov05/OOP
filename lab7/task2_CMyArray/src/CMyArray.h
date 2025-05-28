#pragma once
#include "./Exception/IndexOutOfRangeException.h"
#include <cassert>
#include <iterator>

template <typename T>
class CMyArray
{
public:
	CMyArray();
	CMyArray(const CMyArray<T>& other);
	CMyArray(CMyArray<T>&& other);
	~CMyArray();

	void Resize(size_t size);
	void Add(const T& value);
	void Clear();

	size_t Size() const;
	size_t Capacity() const;

	const T& operator[](size_t index) const;
	T& operator[](size_t index);
	CMyArray<T>& operator=(CMyArray<T> const& other);
	CMyArray<T>& operator=(CMyArray<T>&& other) noexcept;

	T* begin();
	T* end();
	std::reverse_iterator<T*> rbegin();
	std::reverse_iterator<T*> rend();
	const T* begin() const;
	const T* end() const;
	const std::reverse_iterator<T*> rend() const;
	const std::reverse_iterator<T*> rbegin() const;

private:
	T* Allocate(size_t size);
	void Swap(CMyArray<T>& firstArr, CMyArray<T>& secondArr);
	T* m_data = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;
};

// Realisation

template <typename T>
CMyArray<T>::CMyArray() {}

template <typename T>
CMyArray<T>::CMyArray(const CMyArray<T>& other)
	: m_size(other.m_size)
	, m_capacity(other.m_size)
{
	if (m_size == 0)
	{
		m_data = nullptr;
		return;
	}

	m_data = Allocate(m_capacity);
	std::copy_n(other.m_data, m_size, m_data);
}

template <typename T>
CMyArray<T>::CMyArray(CMyArray<T>&& other)
	: CMyArray()
{
	Swap(*this, other);
}

template <typename T>
CMyArray<T>::~CMyArray()
{
	Clear();
}

template <typename T>
void CMyArray<T>::Resize(size_t size)
{
	if (m_size >= size)
	{
		m_size = size;
		return;
	}

	m_capacity = size;
	T* newData = Allocate(m_capacity);
	std::copy_n(m_data, m_size, newData);
	delete[] m_data;
	m_size = size;
	m_data = newData;
}

template <typename T>
void CMyArray<T>::Add(const T& value)
{
	if (m_capacity == m_size)
	{
		m_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
		T* newData = Allocate(m_capacity);
		std::copy_n(m_data, m_size, newData);
		delete[] m_data;
		m_data = newData;
	}
	m_data[m_size] = value;
	++m_size;
}

template <typename T>
void CMyArray<T>::Clear()
{
	delete[] m_data;
	m_data = nullptr;
	m_capacity = 0;
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
	if (index >= m_size)
	{
		throw IndexOutOfRangeException();
	}
	return m_data[index];
}

template <typename T>
T& CMyArray<T>::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw IndexOutOfRangeException();
	}
	return m_data[index];
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator=(CMyArray<T> const& other)
{
	CMyArray temp(other);
	Swap(*this, temp);
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator=(CMyArray<T>&& other) noexcept
{
	Clear();
	Swap(*this, other);
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

template <typename T>
T* CMyArray<T>::Allocate(size_t size)
{
	T* newData = nullptr;
	try
	{
		newData = new T[size]();
		return newData;
	}
	catch (...)
	{
		delete[] newData;
		throw;
	}
}

template <typename T>
void CMyArray<T>::Swap(CMyArray<T>& firstArr, CMyArray<T>& secondArr)
{
	std::swap(firstArr.m_data, secondArr.m_data);
	std::swap(firstArr.m_size, secondArr.m_size);
	std::swap(firstArr.m_capacity, secondArr.m_capacity);
}