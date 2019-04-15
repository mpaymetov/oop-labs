#pragma once
#include "stdafx.h"

constexpr unsigned short HttpDefaultPort = 80;
constexpr unsigned short HttpsDefaultPort = 443;
constexpr unsigned short MinPort = 1;
constexpr unsigned short MaxPort = 65535;

enum Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:

	CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol = HTTP);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:

	std::string m_url;
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;

	bool IsPortDefault();
	std::string ProtocolToString();
	void UpdateDomain(const std::string& domain);
	void UpdateDocument(const std::string& document);
	void UpdatePortFromProtocol();
	void UpdatePortFromString(std::string& portStr);
	void GreateUrl();
};
