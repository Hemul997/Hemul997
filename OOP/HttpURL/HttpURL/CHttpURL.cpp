// CHttpURL.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "CHttpURL.h"
#include "CUrlParsingError.h"
#include "Errors.h"

static const int MAX_NUMBER_OF_PORT = 65535;
static const int MIN_NUMBER_OF_PORT = 1;
static const std::string PROTOCOL_DELIMITER = "://";

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::string strUrl(url);
	m_protocol = ParseProtocol(strUrl);
	m_domain = ParseDomain(strUrl);
	ValidateDomain(m_domain);
	m_port = ParsePort(strUrl);
	ValidateDocument(strUrl);
	m_document = (strUrl[0] == '/') ? strUrl : "/";
};

CHttpUrl::CHttpUrl(
	std::string const& domain,
	std::string const& document,
	Protocol protocol,
	unsigned short port
)
	:m_domain(domain)
	, m_document(document)
	, m_protocol(protocol)
	, m_port(port)
{
	ValidateDomain(domain);
	ValidateDocument(document);
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

std::string CHttpUrl::GetURL() const
{
	return ToStringProtocol() + "://" + m_domain + ToStringPort() + m_document;
}

std::string CHttpUrl::ToStringPort() const
{
	return ((m_port == static_cast<unsigned short>(Protocol::HTTP)) ||
		(m_port == static_cast<unsigned short>(Protocol::HTTPS))) ? "" : ":" + std::to_string(m_port);
}

std::string CHttpUrl::ToStringProtocol() const
{
	std::string result;
	if (m_protocol == Protocol::HTTP)
	{
		result = "http";
	}
	else if (m_protocol == Protocol::HTTPS)
	{
		result = "https";
	}
	return result;
}
Protocol CHttpUrl::ToProtocolType(std::string const& protocol) const
{
	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	if (protocol == "https")
	{
		return Protocol::HTTPS;
	}
	throw CUrlParsingError(INVALID_PROTOCOL);
}

Protocol CHttpUrl::ParseProtocol(std::string & urlRef) const
{
	auto position = urlRef.find(PROTOCOL_DELIMITER);
	if (position == std::string::npos)
	{
		throw CUrlParsingError(PROTOCOL_PARSING_ERROR);
	}
	auto protocol = urlRef.substr(0, position);
	boost::algorithm::to_lower(protocol);
	urlRef = urlRef.substr(position + PROTOCOL_DELIMITER.size());
	return ToProtocolType(protocol);
}

void CHttpUrl::ValidateDomain(std::string const& domain) const
{
	bool isContainsInvalidChar = (domain.find(" ") != std::string::npos) ||
		(domain.find("\'") != std::string::npos) ||
		(domain.find("\"") != std::string::npos);
	if (isContainsInvalidChar)
	{
		throw CUrlParsingError(INVALID_DOMAIN);
	}
}

std::string CHttpUrl::ParseDomain(std::string & urlRef) const
{
	auto position = urlRef.find(":");
	if (position == std::string::npos)
	{
		position = urlRef.find("/");
	}
	auto domain = urlRef.substr(0, position);
	if (domain.empty())
	{
		throw CUrlParsingError(DOMAIN_PARSING_ERROR);
	}
	urlRef = urlRef.substr(domain.size());
	boost::algorithm::to_lower(domain);
	return domain;
}

unsigned short CHttpUrl::ParsePort(std::string & urlRef) const
{
	int port;
	if (urlRef[0] == ':')
	{
		auto endPos = urlRef.find('/');
		auto portStr = urlRef.substr(1, endPos - 1);
		urlRef = urlRef.substr(portStr.size() + 1, urlRef.size() - 1);
		if (portStr.empty())
		{
			throw CUrlParsingError(PORT_PARSING_ERROR);
		}
		try
		{
			port = boost::lexical_cast<int>(portStr);
		}
		catch (boost::bad_lexical_cast const& error)
		{
			throw CUrlParsingError(error.what());
		}
		ValidatePort(port);
	}
	else
	{
		port = static_cast<unsigned short>(m_protocol);
	}
	return port;
}

void CHttpUrl::ValidateDocument(std::string const& document) const
{
	bool isValidDocument = document.find(" ") != std::string::npos;
	if (isValidDocument)
	{
		throw CUrlParsingError(INVALID_DOCUMENT);
	}
}
void CHttpUrl::ValidatePort(int port)const
{
	bool isValidPort(port < MIN_NUMBER_OF_PORT || port > MAX_NUMBER_OF_PORT);
	if (isValidPort)
	{
		throw CUrlParsingError(INVALID_PORT);
	}
}
