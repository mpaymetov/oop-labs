#include "stdafx.h"
#include "htmlDecode.h"

void DecodeHtmlEntities(std::istream &input, std::ostream &output)
{
	std::string html;

	while (std::getline(input, html))
	{
		output << HtmlDecode(html) << std::endl;
	}
}

int main()
{
	DecodeHtmlEntities(std::cin, std::cout);
	return 0;
}

