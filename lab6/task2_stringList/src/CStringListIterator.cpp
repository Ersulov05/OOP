#include "./CStringListIterator.h"
#include "./Exception/IndexOutOfRangeException.h"

CStringListIterator::CStringListIterator(const std::shared_ptr<Node>& node, bool reverse)
	: m_node(node)
	, m_reverse(reverse)
{
}

CStringListIterator::~CStringListIterator() {}

std::string& CStringListIterator::operator*() const
{
	if (!m_node)
	{
		throw std::runtime_error("Dereferencing null iterator");
	}
	return m_node->data;
}

std::string* CStringListIterator::operator->() const
{
	if (!m_node)
	{
		throw std::runtime_error("Accessing null iterator");
	}
	return &(m_node->data);
}

CStringListIterator& CStringListIterator::operator++()
{
	m_node = m_reverse ? m_node->prev : m_node->next;
	if (!m_node)
	{
		throw IndexOutOfRangeException();
	}
	return *this;
}

CStringListIterator CStringListIterator::operator++(int)
{
	CStringListIterator copyStringListIterator = *this;
	++*this;
	return copyStringListIterator;
}

CStringListIterator& CStringListIterator::operator--()
{
	m_node = m_reverse ? m_node->next : m_node->prev;
	if (!m_node)
	{
		throw IndexOutOfRangeException();
	}
	return *this;
}

CStringListIterator CStringListIterator::operator--(int)
{
	CStringListIterator copyStringListIterator = *this;
	--*this;
	return copyStringListIterator;
}

CStringListIterator CStringListIterator::operator+(size_t index) const
{
	CStringListIterator copy = *this;
	for (size_t i = 0; i < index; ++i)
	{
		++copy;
	}
	return copy;
}

CStringListIterator CStringListIterator::operator-(size_t index) const
{
	CStringListIterator copy = *this;
	for (size_t i = 0; i < index; ++i)
	{
		--copy;
	}
	return copy;
}

bool CStringListIterator::operator==(const CStringListIterator& other) const
{
	return m_node == other.m_node;
}

bool CStringListIterator::operator!=(const CStringListIterator& other) const
{
	return !(*this == other);
}

std::shared_ptr<Node> CStringListIterator::GetNode() const
{
	return m_node;
}
