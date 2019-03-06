#include "stdafx.h"
#include "htmlDecode.h"

HtmlEntitiesMap GenerateHtmlEntitiesMap()
{
	HtmlEntitiesMap htmlEntities;
	htmlEntities["&quot;"] = "\"";
	htmlEntities["&apos;"] = "'";
	htmlEntities["&lt;"] = "<";
	htmlEntities["&gt;"] = ">";
	htmlEntities["&amp;"] = "&";
	return htmlEntities;
}

std::string Replace(const std::string& subject, const std::string& searchString, const std::string& replacementString)
{
	if (searchString == "")
	{
		return subject;
	}

	size_t pos = 0;
	std::string result;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(searchString, pos);
		result.append(subject, pos, foundPos - pos);
		if (foundPos != std::string::npos)
		{
			result.append(replacementString);
			pos = foundPos + searchString.length();
		}
		else
		{
			break;
		}
	}
	return result;
}

std::string HtmlDecode(const std::string& html)
{
	std::string outString = html;
	const HtmlEntitiesMap htmlEntities = GenerateHtmlEntitiesMap();

	for (auto& htmlEntity : htmlEntities)
	{
		outString = Replace(outString, htmlEntity.first, htmlEntity.second);
	}

	return outString;
}

