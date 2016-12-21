#pragma once

enum Protocol
{
	HTTP = 80,
	HTTPS= 443
};

class CHttpUrl
{
public:
	// ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
	// ���������� ���������� CUrlParsingError, ���������� ��������� �������� ������
	CHttpUrl(std::string const& url);

	/* �������������� URL �� ������ ���������� ����������.
	��� �������������� ������� ���������� ����������� ����������
	std::invalid_argument
	���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP,
		unsigned short port = static_cast<unsigned short>(Protocol::HTTP)
	);

	// ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
	// ���������� ��������� (80 ��� http � 443 ��� https) � URL �� ������ ����������
	std::string GetURL()const;

	// ���������� �������� ���
	std::string GetDomain()const;

	/*
	���������� ��� ���������. �������:
	/
	/index.html
	/images/photo.jpg
	*/
	std::string GetDocument()const;

	// ���������� ��� ���������
	Protocol GetProtocol()const;

	// ���������� ����� �����
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

