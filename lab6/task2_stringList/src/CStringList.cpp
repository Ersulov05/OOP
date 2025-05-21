#include "./CStringList.h"
#include "./Exception/EraseEndIteratorException.h"
#include "./Exception/IndexOutOfRangeException.h"

CStringList::CStringList()
	: m_begin(std::make_shared<Node>())
	, m_end(std::make_shared<Node>())
{
	m_begin->next = m_end;
	m_end->prev = m_begin;
}

CStringList::~CStringList()
{
	Clear();
	// m_begin->next = nullptr;
	// m_end->prev = nullptr;
}

CStringList::CStringList(const CStringList& other)
	: CStringList()
{
	std::shared_ptr<Node> curr = other.m_begin->next;
	while (curr->next)
	{
		PushBack(curr->data);
		curr = curr->next;
	}
}

CStringList::CStringList(CStringList&& other)
	: CStringList()
{
	std::swap(m_begin, other.m_begin);
	std::swap(m_end, other.m_end);
	std::swap(m_size, other.m_size);
}

void CStringList::PushBack(const std::string& str)
{
	auto newPtr = std::make_shared<Node>(Node(str));

	newPtr->prev = m_end->prev;
	newPtr->next = m_end;
	m_end->prev = newPtr;
	newPtr->prev->next = newPtr;
	++m_size;
}

void CStringList::PushFront(const std::string& str)
{
	auto newPtr = std::make_shared<Node>(Node(str));

	newPtr->next = m_begin->next;
	newPtr->prev = m_begin;
	m_begin->next = newPtr;
	m_begin->next->prev = newPtr;
	++m_size;
}

size_t CStringList::Size() const noexcept
{
	return m_size;
}

bool CStringList::IsEmpty() const noexcept
{
	return m_size == 0;
}

void CStringList::Clear()
{
	auto curr = m_begin->next;
	while (curr->next)
	{
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		curr = curr->next;
	}
	m_size = 0;
}

void CStringList::Insert(CStringListIterator pos, const std::string& str)
{
	auto targetNode = pos.GetNode();
	auto newPtr = std::make_shared<Node>(Node(str));

	newPtr->prev = targetNode->prev;
	newPtr->next = targetNode;
	targetNode->prev = newPtr;
	newPtr->prev->next = newPtr;
	++m_size;
}

void CStringList::Erase(CStringListIterator pos)
{
	auto targetNode = pos.GetNode();
	if (targetNode == m_end || targetNode == m_begin)
	{
		throw EraseEndIteratorException();
	}
	targetNode->prev->next = targetNode->next;
	targetNode->next->prev = targetNode->prev;
	--m_size;
}

CStringListIterator CStringList::begin() noexcept
{
	return CStringListIterator(m_begin->next);
}

CStringListIterator CStringList::end() noexcept
{
	return CStringListIterator(m_end);
}

const CStringListIterator CStringList::begin() const noexcept
{
	return CStringListIterator(m_begin->next);
}

const CStringListIterator CStringList::end() const noexcept
{
	return CStringListIterator(m_end);
}

CStringListIterator CStringList::rbegin() noexcept
{
	return CStringListIterator(m_end->prev, true);
}

CStringListIterator CStringList::rend() noexcept
{
	return CStringListIterator(m_begin, true);
}

const CStringListIterator CStringList::rbegin() const noexcept
{
	return CStringListIterator(m_end->prev, true);
}

const CStringListIterator CStringList::rend() const noexcept
{
	return CStringListIterator(m_begin, true);
}

std::string CStringList::operator[](size_t index) const
{
	if (index >= m_size)
	{
		throw IndexOutOfRangeException();
	}
	return (begin() + index).GetNode()->data;
}

std::string& CStringList::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw IndexOutOfRangeException();
	}
	return (begin() + index).GetNode()->data;
}

CStringList& CStringList::operator=(CStringList const& other)
{
	if (this != &other)
	{
		CStringList temp(other);
		std::swap(m_size, temp.m_size);
		std::swap(m_begin, temp.m_begin);
		std::swap(m_end, temp.m_end);
	}

	return *this;
}
CStringList& CStringList::operator=(CStringList&& other)
{
	if (this != &other)
	{
		Clear();
		std::swap(m_size, other.m_size);
		std::swap(m_begin, other.m_begin);
		std::swap(m_end, other.m_end);
	}

	return *this;
}