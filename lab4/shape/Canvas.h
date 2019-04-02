#pragma once
#include <fstream>
#include "icanvas.h"

class CCanvas final : public ICanvas
{
public:
	void DrawLine(CPoint const & from, CPoint const & to, std::string const & lineColor) override;

	void FillCircle(CPoint const & center, double radius, std::string const & fillColor) override;
	void DrawCircle(CPoint const & center, double radius, std::string const & lineColor) override;

	void FillPolygon(std::vector<CPoint> const & points, std::string const & fillColor) override;
	void DrawPolygon(std::vector<CPoint> const & points, std::string const & lineColor) override;
};
