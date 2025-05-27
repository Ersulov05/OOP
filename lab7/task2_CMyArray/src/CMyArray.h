#pragma once
#include "./Exception/IndexOutOfRangeException.h"
#include <cassert>
#include <iterator>

template <typename T>
class CMyArray
{
public:
	CMyArray()
		: m_data(new T[1])
		, m_size(0)
		, m_capacity(1)
	{
	}

	CMyArray(const CMyArray& other)
	{
		m_size = other.m_size;
		m_capacity = other.m_size + 1;
		m_data = new T[m_capacity];

		for (size_t i = 0; i < other.m_size; ++i)
		{
			m_data[i] = other.m_data[i];
		}
	}

	CMyArray(CMyArray&& other)
		: CMyArray()
	{
		std::swap(m_data, other.m_data);
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
	}

	~CMyArray()
	{
		delete[] m_data;
	}

	void Resize(size_t size)
	{
		if (m_size >= size)
		{
			m_size = size;
			return;
		}

		m_capacity = size + 1;
		T* newData = new T[m_capacity];
		for (size_t i = 0; i < m_size; ++i)
		{
			newData[i] = m_data[i];
		}
		delete[] m_data;
		m_size = size;
		m_data = newData;
	}

	void Add(const T& value)
	{
		if (m_capacity <= m_size + 1)
		{
			m_capacity = m_capacity * 2;
			T* newData = new T[m_capacity];
			for (size_t i = 0; i < m_size; ++i)
			{
				newData[i] = m_data[i];
			}
			delete[] m_data;
			m_data = newData;
		}
		m_data[m_size] = value;
		++m_size;
	}

	void Clear()
	{
		delete[] m_data;
		m_data = new T[1];
		m_capacity = 1;
		m_size = 0;
	}

	size_t Size() const
	{
		return m_size;
	}

	size_t Capacity() const
	{
		return m_capacity;
	}

	const T& operator[](size_t index) const
	{
		if (index >= m_size)
		{
			throw IndexOutOfRangeException();
		}
		return m_data[index];
	}

	T& operator[](size_t index)
	{
		if (index >= m_size)
		{
			throw IndexOutOfRangeException();
		}
		return m_data[index];
	}

	CMyArray& operator=(CMyArray const& other)
	{
		CMyArray temp(other);
		std::swap(m_data, temp.m_data);
		std::swap(m_size, temp.m_size);
		std::swap(m_capacity, temp.m_capacity);
	}

	CMyArray& operator=(CMyArray&& other) noexcept
	{
		Clear();
		std::swap(m_data, other.m_data);
		std::swap(m_size, other.m_size);
		std::swap(m_capacity, other.m_capacity);
	}

	T* begin()
	{
		return m_data;
	}

	T* end()
	{
		return m_data + m_size;
	}

	std::reverse_iterator<T*> rbegin()
	{
		return std::reverse_iterator(end());
	}

	std::reverse_iterator<T*> rend()
	{
		return std::reverse_iterator(begin());
	}

	const T* begin() const
	{
		return m_data;
	}

	const T* end() const
	{
		return m_data + m_size;
	}

	const std::reverse_iterator<T*> rend() const
	{
		return std::reverse_iterator(begin());
	}

	const std::reverse_iterator<T*> rbegin() const
	{
		return std::reverse_iterator(end());
	}

private:
	T* m_data;
	size_t m_size;
	size_t m_capacity;
};
