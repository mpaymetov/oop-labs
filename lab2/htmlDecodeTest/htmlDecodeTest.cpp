#include "stdafx.h"
#include "..\htmlDecode\htmlDecode.h"

TEST_CASE("HtmlDecode test")
{
	CHECK(HtmlDecode("") == "");
	CHECK(HtmlDecode("A") == "A");
	CHECK(HtmlDecode("Hel&apos;lo") == "Hel'lo");
	CHECK(HtmlDecode("&lt;Hello&gt;") == "<Hello>");
	CHECK(HtmlDecode("&amp;") == "&");
	CHECK(HtmlDecode("Hello&quot;") == "Hello\"");
	CHECK(HtmlDecode("&amp;quot;") == "&quot;");
}
