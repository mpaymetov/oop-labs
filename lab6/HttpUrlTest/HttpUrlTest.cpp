#include "stdafx.h"
#include "../HttpUrl/HttpUrl.h"
#include "../HttpUrl/UrlParsingError.h"

void CheckExpectedUrlParseResult(const CHttpUrl& url, const std::string& expectedUrl, const std::string& domain, 
	const std::string& document, const Protocol& protocol, unsigned short int port)
{
	CHECK(url.GetURL() == expectedUrl);
	CHECK(url.GetDomain() == domain);
	CHECK(url.GetDocument() == document);
	CHECK(url.GetProtocol() == protocol);
	CHECK(url.GetPort() == port);
}

TEST_CASE("test parse simple url")
{
	CheckExpectedUrlParseResult(CHttpUrl("http://www.google.com"), "http://www.google.com", "www.google.com", "/", Protocol::HTTP, 80);
}

TEST_CASE("test parse url with error")
{
	CHECK_THROWS_AS(CHttpUrl("ftp://www.google.com"), CUrlParsingError);
}

TEST_CASE("test parse url with port")
{
	CheckExpectedUrlParseResult(CHttpUrl("https://www.google.com:8080"), "https://www.google.com:8080", "www.google.com", "/", Protocol::HTTPS, 8080);
}

TEST_CASE("test port must be number in range 1..65535")
{
	CHECK_THROWS_AS(CHttpUrl("http://www.google.com:port"), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl("http://www.google.com:99999"), CUrlParsingError);
}

TEST_CASE("test parse document")
{
	CheckExpectedUrlParseResult(CHttpUrl("http://www.google.com/index.php"), "http://www.google.com/index.php", "www.google.com", "/index.php", Protocol::HTTP, 80);
}