#include "stdafx.h"
#include "..\parseUrl\parseUrl.h"

std::string url;
Protocol protocol;
int port;
std::string host;
std::string document;

TEST_CASE("ParseURL test")
{
	url = R"(http://www.mysite.com/docs/document1.html?page=30&lang=en#title)";
	CHECK(ParseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::HTTP);
	CHECK(port == 80);
	CHECK(host == "www.mysite.com");
	CHECK(document == R"(docs/document1.html?page=30&lang=en#title)");
}

TEST_CASE("ParseURL test: other port")
{
	url = R"(http://www.mysite.com:8080/docs/document1.html?page=30&lang=en#title)";
	CHECK(ParseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::HTTP);
	CHECK(port == 8080);
	CHECK(host == "www.mysite.com");
	CHECK(document == R"(docs/document1.html?page=30&lang=en#title)");
}

TEST_CASE("ParseURL test: protocol incorrect")
{
	url = R"(httpf://www.mysite.com:8080/docs/document1.html?page=30&lang=en#title)";
	CHECK(ParseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("ParseURL test: empty host")
{
	url = R"(http:///docs/document1.html?page=30&lang=en#title)";
	CHECK(ParseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("ParseURL test: empty document")
{
	url = R"(https://yandex.ru)";
	CHECK(ParseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::HTTPS);
	CHECK(port == 443);
	CHECK(host == "yandex.ru");
	CHECK(document == "");
}

TEST_CASE("ParseURL test: empty document with slash")
{
	url = R"(ftp://mail.ru/)";
	CHECK(ParseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::FTP);
	CHECK(port == 21);
	CHECK(host == "mail.ru");
	CHECK(document == "");
}

TEST_CASE("ParseURL test empty protocol")
{
	url = R"(://mail.ru)";
	CHECK(ParseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("ParseURL test incorrect delimetr")
{
	url = R"(https//google.ru)";
	CHECK(ParseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("ParseURL test empty port after colon")
{
	url = R"(https://google.ru:/)";
	CHECK(ParseURL(url, protocol, port, host, document) == true);
	CHECK(protocol == Protocol::HTTPS);
	CHECK(port == 443);
	CHECK(host == "google.ru");
	CHECK(document == "");
}

TEST_CASE("ParseURL test: port out of range")
{
	url = R"(https://rambler.ru:555555)";
	CHECK(ParseURL(url, protocol, port, host, document) == false);
}

TEST_CASE("ParseURL test: port striing type")
{
	url = R"(https://rambler.ru:str)";
	CHECK(ParseURL(url, protocol, port, host, document) == false);
}
