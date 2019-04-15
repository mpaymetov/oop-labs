#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

std::string ProtocolToString(const Protocol& protocol)
{
	return (protocol == Protocol::HTTP) ? "http" : "https";
}

void PrintUrlParseResult(const CHttpUrl& url, std::ostream& output)
{
	output << "url: " << url.GetURL() << "\n";
	output << "domain: " << url.GetDomain() << "\n";
	output << "document: " << url.GetDocument() << "\n";
	output << "port: " << url.GetPort() << "\n";
	output << "protocol: " << ProtocolToString(url.GetProtocol()) << "\n";
}

void ParseUrl(std::istream& input, std::ostream& output)
{
	std::string str;
	while (std::getline(input, str))
	{
		try
		{
			CHttpUrl url(str);
			PrintUrlParseResult(url, output);
		}
		catch (const CUrlParsingError& error)
		{
			output << error.what() << "\n";
		}		
	}
}

int main()
{
	ParseUrl(std::cin, std::cout);
	return 0;
}