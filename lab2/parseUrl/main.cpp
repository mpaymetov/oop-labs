#include "stdafx.h"
#include "parseUrl.h"

void ParseUrl(std::istream &input, std::ostream &output)
{
	std::string url;

	while (std::getline(input, url))
	{
		Protocol protocol;
		int port = 0;
		std::string host, document;

		if (ParseURL(url, protocol, port, host, document))
		{
			output << "HOST: " << host << std::endl;
			output << "PORT: " << port << std::endl;
			output << "DOC : " << document << std::endl;
		}
		else
		{
			output << "parse url error" << std::endl;
		}
	}
}

int main()
{
	ParseUrl(std::cin, std::cout);
	return 0;
}
