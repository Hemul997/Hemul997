#pragma once

enum Protocol
{
	HTTP = 80,
	HTTPS= 443
};

class CHttpUrl
{
public:
	// выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
	// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
	CHttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
	ѕри недопустимости входных параметров выбрасывает исключение
	std::invalid_argument
	≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP,
		unsigned short port = static_cast<unsigned short>(Protocol::HTTP)
	);

	// возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
	// выбранного протокола (80 дл€ http и 443 дл€ https) в URL не должен включатьс€
	std::string GetURL()const;

	// возвращает доменное им€
	std::string GetDomain()const;

	/*
	¬озвращает им€ документа. ѕримеры:
	/
	/index.html
	/images/photo.jpg
	*/
	std::string GetDocument()const;

	// возвращает тип протокола
	Protocol GetProtocol()const;

	// возвращает номер порта
	unsigned short GetPort()const;

	std::string ToStringProtocol() const;

private:
	std::string m_document;
	std::string m_domain;
	Protocol m_protocol;
	unsigned short m_port;

	std::string ToStringPort() const;
	Protocol ToProtocolType(std::string const & protocol) const;
	Protocol ParseProtocol(std::string & urlRef) const;
	void ValidateDocument(std::string const & document) const;
	void ValidateDomain(std::string const & domain) const;
	std::string ParseDomain(std::string & urlRef) const;
	unsigned short ParsePort(std::string & urlRef) const;
};

