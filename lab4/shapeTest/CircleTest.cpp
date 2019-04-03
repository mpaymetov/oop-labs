#include "stdafx.h"
#include "../shape/Circle.h"

TEST_CASE("circle")
{
	CCircle circle({ 3, 4 }, 7, 0x0000FF, 0x00FF00);
	CPoint point = circle.GetCenter();
	CHECK(point.x == 3);
	CHECK(point.y == 4);
	CHECK(circle.GetRadius() == 7);
	circle.SetCenter({ 5, 6 });
	circle.SetRadius(3);
	point = circle.GetCenter();
	CHECK(point.x == 5);
	CHECK(point.y == 6);
	CHECK(circle.GetOutlineColor() == 0x0000FF);
	CHECK(circle.GetFillColor() == 0x00FF00);
	CHECK(circle.GetRadius() == 3);
	CHECK(abs(circle.GetPerimeter() - 18.84) < 0.01);
	CHECK(abs(circle.GetArea() - 28.27) < 0.01);
}