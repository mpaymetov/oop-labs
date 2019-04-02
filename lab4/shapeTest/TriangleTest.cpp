#include "stdafx.h"
#include "../shape/Triangle.h"

TEST_CASE("Triangle")
{
	CTriangle triangle({ 0, 0 }, { 0, 3 }, { 4, 0 }, "0000FF", "00FF00");
	CHECK(triangle.GetArea() == 6);
	CHECK(triangle.GetPerimeter() == 12);
	CHECK(triangle.GetOutlineColor() == "0000FF");
	CHECK(triangle.GetFillColor() == "00FF00");
}