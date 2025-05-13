#include <map>
#include <regex>
#include <string>

enum class Protocol
{
	HTTP = 80,
	HTTPS = 443
};

class CHttpUrl
{
public:
	// выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
	// выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
	CHttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
		При недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		Если имя документа не начинается с символа /, то добавляет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	/* инициализирует URL на основе переданных параметров.
		При недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		Если имя документа не начинается с символа /, то добавляет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	// возвращает строковое представление URL-а. Порт, являющийся стандартным для
	// выбранного протокола (80 для http и 443 для https) в эту строку
	// не должен включаться
	std::string GetURL() const;

	// возвращает доменное имя
	std::string GetDomain() const;

	/*
		Возвращает имя документа. Примеры:
			/
			/index.html
			/images/photo.jpg
	*/
	std::string GetDocument() const;

	// возвращает тип протокола
	Protocol GetProtocol() const;

	// возвращает номер порта
	unsigned short GetPort() const;

	CHttpUrl& operator=(const CHttpUrl&);

private:
	const unsigned short MAX_PORT = 65535;
	const unsigned short MIN_PORT = 1;
	Protocol m_protocol;
	std::string m_domain;
	std::string m_document;
	unsigned short m_port;

	inline static const std::map<std::string, Protocol> STRING_TO_PROTOCOL_MAP = {
		{ "http", Protocol::HTTP },
		{ "https", Protocol::HTTPS }
	};

	inline static const std::map<Protocol, std::string> PROTOCOL_TO_STRING_MAP = {
		{ Protocol::HTTP, "http" },
		{ Protocol::HTTPS, "https" }
	};
	inline static const std::regex DOMAIN_REGEX = std::regex(R"(^(?:[a-z0-9](?:[a-z0-9-]{0,61}[a-z0-9])?\.)+[a-z0-9][a-z0-9-]{0,61}[a-z0-9]$)", std::regex_constants::icase);

	Protocol ConvertStringToProtocol(const std::string& string) const;
	std::string ConvertProtocolToString(const Protocol protocol) const;
	unsigned short ConvertStringToPort(const std::string& string) const;
	void CorrectDocumentPath();
	void AssertValidPort(unsigned long port) const;
	void AssertValidDomain(const std::string& domain) const;
};
