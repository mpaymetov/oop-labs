#include "stdafx.h"
#include "../shape/Rectangle.h"

TEST_CASE("Rectangle")
{
	CRectangle rectangle({ 3, 4 }, 7, 8, 0x0000FF, 0x00FF00);
	CPoint point = rectangle.GetLeftTop();
	
	CHECK(point.x == 3);
	CHECK(point.y == 4);
	
	CHECK(rectangle.GetWidth() == 7);
	CHECK(rectangle.GetHeight() == 8);
	
	CHECK(rectangle.GetOutlineColor() == 0x0000FF);
	CHECK(rectangle.GetFillColor() == 0x00FF00);
	
	CHECK(rectangle.GetArea() == 56);
	CHECK(rectangle.GetPerimeter() == 30);
}