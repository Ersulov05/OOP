#include <memory>
#include <string>

struct Node
{
	std::string data;
	std::shared_ptr<Node> prev;
	std::shared_ptr<Node> next;
	explicit Node(std::string data)
		: data(data){};
	Node() = default;
};

class CStringListIterator
{
public:
	explicit CStringListIterator(const std::shared_ptr<Node>& node, bool reverse = false);
	~CStringListIterator();

	std::shared_ptr<Node> GetNode() const;

	std::string& operator*() const;
	std::string* operator->() const;

	CStringListIterator& operator++();
	CStringListIterator operator++(int);

	CStringListIterator& operator--();
	CStringListIterator operator--(int);
	CStringListIterator operator+(size_t index) const;
	CStringListIterator operator-(size_t index) const;

	bool operator==(const CStringListIterator& other) const;
	bool operator!=(const CStringListIterator& other) const;

private:
	std::shared_ptr<Node> m_node;
	bool m_reverse;
};
