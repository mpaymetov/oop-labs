#include "stdafx.h"
#include "../HttpUrl/HttpUrl.h"
#include "../HttpUrl/UrlParsingError.h"

void CheckExpectedHttpUrlCreateResult(const CHttpUrl& url, const std::string& expectedUrl, const std::string& domain, 
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
	CheckExpectedHttpUrlCreateResult(CHttpUrl("http://www.google.com"), "http://www.google.com", "www.google.com", "/", Protocol::HTTP, 80);
	CheckExpectedHttpUrlCreateResult(CHttpUrl("http://www.google.com/"), "http://www.google.com", "www.google.com", "/", Protocol::HTTP, 80);
}

TEST_CASE("test parse url with error")
{
	CHECK_THROWS_AS(CHttpUrl("ftp://www.google.com"), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl("http//www.google.com"), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl("http:/www.google.com"), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl("http:///www.google.com"), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl("http://"), CUrlParsingError);
}

TEST_CASE("test parse url with port")
{
	CheckExpectedHttpUrlCreateResult(CHttpUrl("https://www.google.com:8080"), "https://www.google.com:8080", "www.google.com", "/", Protocol::HTTPS, 8080);
}

TEST_CASE("test port must be number in range 1..65535")
{
	CHECK_THROWS_AS(CHttpUrl("http://www.google.com:port"), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl("http://www.google.com:99999"), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl("http://www.google.com:0"), CUrlParsingError);
	CheckExpectedHttpUrlCreateResult(CHttpUrl("https://www.google.com:1"), "https://www.google.com:1", "www.google.com", "/", Protocol::HTTPS, 1);
	CheckExpectedHttpUrlCreateResult(CHttpUrl("https://www.google.com:65535"), "https://www.google.com:65535", "www.google.com", "/", Protocol::HTTPS, 65535);
	CHECK_THROWS_AS(CHttpUrl("http://www.google.com:65536"), CUrlParsingError);
}

TEST_CASE("test parse document")
{
	CheckExpectedHttpUrlCreateResult(CHttpUrl("http://www.google.com/index.php"), "http://www.google.com/index.php", "www.google.com", "/index.php", Protocol::HTTP, 80);
	CheckExpectedHttpUrlCreateResult(CHttpUrl("https://www.google.com/images/photo.jpg"), 
		"https://www.google.com/images/photo.jpg", "www.google.com", "/images/photo.jpg", Protocol::HTTPS, 443);
}

TEST_CASE("test exclude default port")
{
	CheckExpectedHttpUrlCreateResult(CHttpUrl("https://www.google.com:443/"), "https://www.google.com", "www.google.com", "/", Protocol::HTTPS, 443);
	CheckExpectedHttpUrlCreateResult(CHttpUrl("http://www.google.com:80/index.php"), "http://www.google.com/index.php", "www.google.com", "/index.php", Protocol::HTTP, 80);
}

TEST_CASE("test merge url")
{
	CheckExpectedHttpUrlCreateResult(CHttpUrl("www.google.com", ""), "http://www.google.com", "www.google.com", "/", Protocol::HTTP, 80);
	CheckExpectedHttpUrlCreateResult(CHttpUrl("www.google.com", "index.php", Protocol::HTTPS), 
		"https://www.google.com/index.php", "www.google.com", "/index.php", Protocol::HTTPS, 443);	
}

TEST_CASE("test domain can not be empty")
{
	CHECK_THROWS_AS(CHttpUrl("", "/index.php"), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl("", "/index.php", Protocol::HTTPS), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl("", "/index.php", Protocol::HTTP, 8081), CUrlParsingError);
}

TEST_CASE("test merge url with port")
{
	CheckExpectedHttpUrlCreateResult(CHttpUrl("www.google.com", "/index.php", Protocol::HTTP, 8080), 
		"http://www.google.com:8080/index.php", "www.google.com", "/index.php", Protocol::HTTP, 8080);
	CheckExpectedHttpUrlCreateResult(CHttpUrl("www.google.com", "", Protocol::HTTPS, 443),	"https://www.google.com", "www.google.com", "/", Protocol::HTTPS, 443);
}