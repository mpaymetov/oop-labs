#pragma once
#include "stdafx.h"
#include "point.h"

class ICanvas
{
public:
	virtual ~ICanvas() {};

	virtual void DrawLine(CPoint const& from, CPoint const& to, uint32_t const& lineColor) = 0;

	virtual void FillCircle(CPoint const& center, double radius, uint32_t const& fillColor) = 0;
	virtual void DrawCircle(CPoint const& center, double radius, uint32_t const& lineColor) = 0;

	virtual void FillPolygon(std::vector<CPoint> const& points, uint32_t const& fillColor) = 0;
	virtual void DrawPolygon(std::vector<CPoint> const& points, uint32_t const& lineColor) = 0;
};
