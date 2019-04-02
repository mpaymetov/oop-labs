#pragma once
#include "stdafx.h"
#include "point.h"

class ICanvas
{
public:
	virtual ~ICanvas() {};

	virtual void DrawLine(CPoint const & from, CPoint const & to, std::string const & lineColor) = 0;

	virtual void FillCircle(CPoint const & center, double radius, std::string const & fillColor) = 0;
	virtual void DrawCircle(CPoint const & center, double radius, std::string const & lineColor) = 0;

	virtual void FillPolygon(std::vector<CPoint> const & points, std::string const & fillColor) = 0;
	virtual void DrawPolygon(std::vector<CPoint> const & points, std::string const & lineColor) = 0;
};
