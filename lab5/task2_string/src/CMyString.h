#include <iostream>

class CMyString
{
public:
	CMyString();

	// конструктор, инициализирующий строку данными строки
	// с завершающим нулевым символом
	CMyString(const char* pString);

	// конструктор, инициализирующий строку данными из
	// символьного массива заданной длины
	CMyString(const char* pString, size_t length);

	// конструктор копирования
	CMyString(CMyString const& other);

	// перемещающий конструктор
	//  реализуется совместно с перемещающим оператором присваивания
	CMyString(CMyString&& other) noexcept;

	// конструктор, инициализирующий строку данными из
	// строки стандартной библиотеки C++
	CMyString(std::string const& stlString);

	// деструктор класса - освобождает память, занимаемую символами строки
	~CMyString();

	// возвращает длину строки (без учета завершающего нулевого символа)
	[[nodiscard]] size_t GetLength() const noexcept;

	// возвращает указатель на массив символов строки.
	// В конце массива обязательно должен быть завершающий нулевой символ
	// даже если строка пустая
	[[nodiscard]] const char* GetStringData() const noexcept;

	// возвращает подстроку с заданной позиции длиной не больше length символов
	[[nodiscard]] CMyString SubString(size_t start, size_t length = __SIZE_MAX__) const;

	// очистка строки (строка становится снова нулевой длины)
	void Clear();

	// Возвращает вместимость строки
	[[nodiscard]] size_t GetCapacity() const noexcept;

	CMyString& operator=(CMyString const& other);
	CMyString& operator=(CMyString&& other) noexcept;
	CMyString& operator+=(CMyString const& other);
	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	friend CMyString operator+(CMyString const& firstString, CMyString const& secondString);
	friend CMyString operator+(std::string const& firstString, CMyString const& secondString);
	friend CMyString operator+(CMyString const& firstString, std::string const& secondString);
	friend CMyString operator+(char const* firstString, CMyString const& secondString);
	friend CMyString operator+(CMyString const& firstString, char const* secondString);

	friend bool operator==(CMyString const& firstString, CMyString const& secondString) noexcept;
	friend bool operator!=(CMyString const& firstString, CMyString const& secondString) noexcept;
	friend bool operator>(CMyString const& firstString, CMyString const& secondString) noexcept;
	friend bool operator<(CMyString const& firstString, CMyString const& secondString) noexcept;
	friend bool operator>=(CMyString const& firstString, CMyString const& secondString) noexcept;
	friend bool operator<=(CMyString const& firstString, CMyString const& secondString) noexcept;
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
	static char EMPTY_STRING[1];
	size_t m_length;
	size_t m_capacity;
	char* m_string;
};