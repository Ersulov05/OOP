#include "./CStringListIterator.h"
#include <string>

class CStringList
{
public:
	CStringList();
	CStringList(const CStringList& other);
	CStringList(CStringList&& other);
	~CStringList();

	void PushBack(const std::string& str);
	void PushFront(const std::string& str);

	[[nodiscard]] size_t Size() const noexcept;
	[[nodiscard]] bool IsEmpty() const noexcept;
	void Clear();

	void Insert(CStringListIterator pos, const std::string& str);
	void Erase(CStringListIterator pos);

	CStringListIterator begin() noexcept;
	CStringListIterator end() noexcept;
	const CStringListIterator begin() const noexcept;
	const CStringListIterator end() const noexcept;
	CStringListIterator rbegin() noexcept;
	CStringListIterator rend() noexcept;
	const CStringListIterator rbegin() const noexcept;
	const CStringListIterator rend() const noexcept;

	std::string operator[](size_t index) const;
	std::string& operator[](size_t index);

	CStringList& operator=(CStringList const& other);
	CStringList& operator=(CStringList&& other);

private:
	size_t m_size = 0;
	std::shared_ptr<Node> m_begin;
	std::shared_ptr<Node> m_end;
};
