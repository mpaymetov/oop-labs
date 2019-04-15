#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::regex regex("(http|https)://([^/ :]+):?([^/ ]*)?([^ ]*)");
	std::cmatch result;
	if (!regex_match(url.c_str(), result, regex))
	{
		throw CUrlParsingError("url parse error");
	}
	
	std::string protocolStr = std::string(result[1].first, result[1].second);
	std::string host = std::string(result[2].first, result[2].second);
	std::string portStr = std::string(result[3].first, result[3].second);
	std::string document = std::string(result[4].first, result[4].second);

	m_protocol = (protocolStr == "http") ? Protocol::HTTP : Protocol::HTTPS;

	if (portStr.empty())
	{
		UpdatePortFromProtocol();
	}
	else
	{
		UpdatePortFromString(portStr);
	}

	UpdateDomain(host);
	UpdateDocument(document);
	GreateUrl();
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
	m_protocol = protocol;
	UpdateDomain(domain);
	UpdatePortFromProtocol();
	UpdateDocument(document);
	GreateUrl();
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
	m_protocol = protocol;
	UpdateDomain(domain);
	m_port = port;
	UpdateDocument(document);
	GreateUrl();
}

std::string CHttpUrl::GetURL() const
{
	return m_url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

bool CHttpUrl::IsPortDefault()
{
	return ((m_protocol == Protocol::HTTP) && (m_port == HttpDefaultPort)) || ((m_protocol == Protocol::HTTPS) && (m_port == HttpsDefaultPort));
}

std::string CHttpUrl::ProtocolToString()
{
	return (m_protocol == Protocol::HTTP) ? "http" : "https";
}

void CHttpUrl::UpdateDomain(const std::string& domain)
{
	if (domain.empty())
	{
		throw CUrlParsingError("domain can not be empty");
	}
	m_domain = domain;
}

void CHttpUrl::UpdateDocument(const std::string& document)
{
	if (document.empty())
	{
		m_document = "/";
	}
	else if (document[0] != '/')
	{
		m_document = "/" + document;
	}
	else
	{
		m_document = document;
	}
}

void CHttpUrl::UpdatePortFromProtocol()
{
	m_port = (m_protocol == Protocol::HTTP) ? HttpDefaultPort : HttpsDefaultPort;
}

void CHttpUrl::UpdatePortFromString(std::string& portStr)
{
	int port;
	try
	{
		port = std::stoi(portStr);
	}
	catch (const std::exception& err)
	{
		std::string errorMsg = err.what();
		errorMsg += ": port must be a number";
		throw CUrlParsingError(errorMsg);
	}
	if ((port < MinPort) || (port > MaxPort))
	{
		throw CUrlParsingError("port out of range");
	}
	m_port = port;
}

void CHttpUrl::GreateUrl()
{
	m_url = ProtocolToString() + "://" + m_domain;
	if (!IsPortDefault())
	{
		m_url = m_url + ":" + std::to_string(m_port);
	}
	if (m_document != "/")
	{
		m_url += m_document;
	}
}