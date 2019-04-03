#include "stdafx.h"
#include "../shape/LineSegment.h"

TEST_CASE("LineSegment")
{
	CLineSegment lineSegment({ 3, 4 }, { 6, 8 }, 0x0000FF);
	CPoint startPoint = lineSegment.GetStartPoint();
	CHECK(startPoint.x == 3);
	CHECK(startPoint.y == 4);
	CPoint endPoint = lineSegment.GetEndPoint();
	CHECK(endPoint.x == 6);
	CHECK(endPoint.y == 8);
	CHECK(lineSegment.GetArea() == 0);
	CHECK(lineSegment.GetPerimeter() == 5);
	CHECK(lineSegment.GetOutlineColor() == 0x0000FF);
}