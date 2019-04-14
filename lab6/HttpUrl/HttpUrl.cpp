#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

// выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
// выбрасыват исключение CUrlParsingError, содержащее текстовое описание ошибки
CHttpUrl::CHttpUrl(std::string const& url)
{
	std::regex regex("(http|https)://([^/ :]+):?([^/ ]*)?([^ ]*)");
	std::cmatch result;
	if (regex_match(url.c_str(), result, regex))
	{
		std::string protocolStr = std::string(result[1].first, result[1].second);
		std::string host = std::string(result[2].first, result[2].second);
		std::string portStr = std::string(result[3].first, result[3].second);
		std::string document = std::string(result[4].first, result[4].second);

		m_protocol = (protocolStr == "http") ? Protocol::HTTP : Protocol::HTTPS;
		if (portStr.empty())
		{
			m_port = (m_protocol == Protocol::HTTP) ? 80 : 443;
		}
		else
		{
			int port;
			try
			{
				port = std::stoi(portStr);
			}
			catch (const std::exception& err)
			{
				throw CUrlParsingError(err.what());
			}
			if ((port < 1) || (port > 65535))
			{
				throw CUrlParsingError("port out of range");
			}
			m_port = port;
		}
		m_url = url;
		m_domain = host;
		if (document.empty())
		{
			m_document = "/";
		}
		else
		m_document = document;
	}
	else
		throw CUrlParsingError("cant parse url");
}

	/* инициализирует URL на основе переданных параметров.
		ѕри недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
}

	/* инициализирует URL на основе переданных параметров.
		ѕри недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
	*/
CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
}

	// возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
	// выбранного протокола (80 дл€ http и 443 дл€ https) в эту строку
	// не должен включатьс€
std::string CHttpUrl::GetURL() const
{
	return m_url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

	/* 
		¬озвращает им€ документа. ѕримеры: 
			/
			/index.html
			/images/photo.jpg
	*/
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