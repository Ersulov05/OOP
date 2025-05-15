#include <iostream>

class CMyString
{
public:
	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(std::string const& stlString);
	CMyString(CMyString const& other);
	CMyString(CMyString&& other) noexcept;
	~CMyString();
	[[nodiscard]] size_t GetLength() const noexcept;
	[[nodiscard]] const char* GetStringData() const noexcept;
	[[nodiscard]] CMyString SubString(size_t start, size_t length = __SIZE_MAX__) const;
	[[nodiscard]] size_t GetCapacity() const noexcept;
	void Clear();

	CMyString& operator=(CMyString const& other);
	CMyString& operator=(CMyString&& other);
	CMyString& operator+=(CMyString const& other);
	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	friend CMyString operator+(const CMyString& firstString, const CMyString& secondString);
	friend CMyString operator+(const std::string& firstString, const CMyString& secondString);
	friend CMyString operator+(const CMyString& firstString, const std::string& secondString);
	friend CMyString operator+(const char* firstString, const CMyString& secondString);
	friend CMyString operator+(const CMyString& firstString, const char* secondString);

	friend bool operator==(const CMyString& firstString, const CMyString& secondString) noexcept;
	friend bool operator!=(const CMyString& firstString, const CMyString& secondString) noexcept;
	friend bool operator>(const CMyString& firstString, const CMyString& secondString) noexcept;
	friend bool operator<(const CMyString& firstString, const CMyString& secondString) noexcept;
	friend bool operator>=(const CMyString& firstString, const CMyString& secondString) noexcept;
	friend bool operator<=(const CMyString& firstString, const CMyString& secondString) noexcept;
	// TODO: Разобраться со <=>
	friend std::ostream& operator<<(std::ostream& os, const CMyString& string);
	friend std::istream& operator>>(std::istream& is, CMyString& string);

	char* begin() noexcept;
	const char* begin() const noexcept;
	char* end() noexcept;
	const char* end() const noexcept;
	const char* cbegin() const noexcept;
	const char* cend() const noexcept;
	std::reverse_iterator<char*> rbegin();
	std::reverse_iterator<char*> rend();
	std::reverse_iterator<const char*> rbegin() const;
	std::reverse_iterator<const char*> rend() const;

private:
	const static char END_OF_STRING = '\0';
	// static char EMPTY_STRING[1]; // TODO избавиться
	size_t m_length;
	size_t m_capacity;
	char* m_string;
};