#include "CMyString.h"
#include "./Exception/IndexOutOfRangeException.h"
#include <cstring>

CMyString::CMyString(const char* pString, size_t length)
	: m_length(length)
	, m_capacity(length + 1)
{
	m_string = new char[m_capacity];
	if (pString)
	{
		for (size_t i = 0; i < length; ++i)
		{
			m_string[i] = pString[i];
		}
	}
	m_string[length] = END_OF_STRING;
}

CMyString::CMyString()
	: CMyString("", 0)
{
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, std::strlen(pString))
{
}

CMyString::CMyString(const CMyString& other)
	: CMyString(other.m_string, other.m_length)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: CMyString(other.m_string, other.m_length)
{
	other.Clear();
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::~CMyString()
{
	delete[] m_string;
}

size_t CMyString::GetLength() const noexcept
{
	return m_length;
}

const char* CMyString::GetStringData() const noexcept
{
	return m_string;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		return CMyString();
	}

	if ((start + length) > m_length)
	{
		length = m_length - start;
	}

	return CMyString(&m_string[start], length);
}

void CMyString::Clear()
{
	if (m_length > 0)
	{
		m_length = 0;
		m_capacity = 1;
		delete[] m_string;
		m_string = new char[m_capacity];
		m_string[0] = CMyString::END_OF_STRING;
	}
}

size_t CMyString::GetCapacity() const noexcept
{
	return m_capacity;
}

std::ostream& operator<<(std::ostream& os, const CMyString& string)
{
	os << string.m_string;
	return os;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		CMyString temp(other);
		std::swap(m_string, temp.m_string);
		std::swap(m_length, temp.m_length);
		std::swap(m_capacity, temp.m_capacity);
	}

	return *this;
}

CMyString& CMyString::operator=(CMyString&& other)
{
	if (this != &other)
	{
		Clear();
		std::swap(m_string, other.m_string);
		std::swap(m_length, other.m_length);
		std::swap(m_capacity, other.m_capacity);
	}

	return *this;
}

CMyString& CMyString::operator+=(CMyString const& other)
{
	if (other.m_length == 0)
		return *this;

	size_t newLength = m_length + other.m_length;
	if (newLength + 1 > m_capacity)
	{
		m_capacity = (newLength + 1) * 2;
		char* newString = new char[m_capacity];
		std::memcpy(newString, m_string, m_length);
		delete[] m_string;
		m_string = newString;
	}

	std::memcpy(m_string + m_length, other.m_string, other.m_length);
	m_length = newLength;
	m_string[m_length] = END_OF_STRING;

	return *this;
}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw IndexOutOfRangeException();
	}

	return m_string[index];
}

char& CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw IndexOutOfRangeException();
	}

	return m_string[index];
}

CMyString operator+(const CMyString& firstString, const CMyString& secondString)
{
	CMyString result;
	result += firstString;
	result += secondString;

	return result;
}

CMyString operator+(const std::string& firstString, const CMyString& secondString)
{
	return CMyString(firstString) + secondString;
}

CMyString operator+(const CMyString& firstString, const std::string& secondString)
{
	return firstString + CMyString(secondString);
}

CMyString operator+(const CMyString& firstString, const char* secondString)
{
	return firstString + CMyString(secondString);
}

CMyString operator+(const char* firstString, const CMyString& secondString)
{
	return CMyString(firstString) + secondString;
}

bool operator==(const CMyString& firstString, const CMyString& secondString) noexcept
{
	if (firstString.m_length != secondString.m_length)
		return false;

	return std::memcmp(firstString.m_string, secondString.m_string, firstString.m_length) == 0;
}

bool operator!=(const CMyString& firstString, const CMyString& secondString) noexcept
{
	return !(firstString == secondString);
}

bool operator<(const CMyString& firstString, const CMyString& secondString) noexcept
{
	size_t minLength = std::min(firstString.m_length, secondString.m_length);
	int comparison = std::memcmp(firstString.m_string, secondString.m_string, minLength);

	if (comparison == 0)
	{
		return firstString.m_length < secondString.m_length;
	}

	return comparison < 0;
}

bool operator>(const CMyString& firstString, const CMyString& secondString) noexcept
{
	size_t minLength = std::min(firstString.m_length, secondString.m_length);
	int comparison = std::memcmp(firstString.m_string, secondString.m_string, minLength);

	if (comparison == 0)
	{
		return firstString.m_length > secondString.m_length;
	}

	return comparison > 0;
}

bool operator>=(const CMyString& firstString, const CMyString& secondString) noexcept
{
	return !(firstString < secondString);
}

bool operator<=(const CMyString& firstString, const CMyString& secondString) noexcept
{
	return !(firstString > secondString);
}

std::istream& operator>>(std::istream& is, CMyString& string)
{
	string.Clear();
	is >> std::ws;

	char ch;
	while (is.get(ch) && !std::isspace(ch))
	{
		if (string.m_length + 1 >= string.m_capacity)
		{
			string.m_capacity *= 2;
			char* new_buffer = new char[string.m_capacity];
			std::memcpy(new_buffer, string.m_string, string.m_length);
			delete[] string.m_string;
			string.m_string = new_buffer;
		}
		string.m_string[string.m_length++] = ch;
	}

	if (string.m_capacity > 1)
	{
		string.m_string[string.m_length] = CMyString::END_OF_STRING;
	}

	return is;
}

char* CMyString::begin() noexcept
{
	return m_string;
}

const char* CMyString::begin() const noexcept
{
	return m_string;
}

char* CMyString::end() noexcept
{
	return m_string + m_length;
}

const char* CMyString::end() const noexcept
{
	return m_string + m_length;
}

const char* CMyString::cbegin() const noexcept
{
	return m_string;
}

const char* CMyString::cend() const noexcept
{
	return m_string + m_length;
}

std::reverse_iterator<char*> CMyString::rbegin()
{
	return std::reverse_iterator<char*>(end());
}

std::reverse_iterator<char*> CMyString::rend()
{
	return std::reverse_iterator<char*>(begin());
}

std::reverse_iterator<const char*> CMyString::rbegin() const
{
	return std::reverse_iterator<const char*>(end());
}

std::reverse_iterator<const char*> CMyString::rend() const
{
	return std::reverse_iterator<const char*>(begin());
}