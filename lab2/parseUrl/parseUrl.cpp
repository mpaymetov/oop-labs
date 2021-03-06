#include "stdafx.h"
#include "parseUrl.h"

Protocol GetProtocol(std::string& protocol)
{
	if (protocol == "http") return Protocol::HTTP;
	if (protocol == "https") return Protocol::HTTPS;
	return Protocol::FTP;
}

int GetPortFromProtocol(Protocol& protocol)
{
	if (protocol == Protocol::HTTP) return 80;
	if (protocol == Protocol::HTTPS) return 443;
	return 21;
}

bool ParseURL(const std::string& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex regex("(http|https|ftp)://([^/ :]+):?([^/ ]*)/?([^ ]*)");
	std::cmatch result;
	if (regex_match(url.c_str(), result, regex))
	{
		std::string protocolStr = std::string(result[1].first, result[1].second);
		host = std::string(result[2].first, result[2].second);
		std::string portStr = std::string(result[3].first, result[3].second);
		document = std::string(result[4].first, result[4].second);
		
		protocol = GetProtocol(protocolStr);
		if (portStr.empty())
		{
			port = GetPortFromProtocol(protocol);
		}
		else
		{
			try
			{
				port = std::stoi(portStr);
			}
			catch (const std::exception & err)
			{
				std::cout << err.what() << std::endl;
				return false;
			}
			if ((port < 1) || (port > 65535))
			{
				std::cout << "port number out of range" << std::endl;
				return false;
			}
		}
	}
	else 
	{
		return false;
	}

	return true;
}
