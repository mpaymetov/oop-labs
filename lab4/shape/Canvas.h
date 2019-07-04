#pragma once
#include <fstream>
#include "icanvas.h"

class CCanvas final : public ICanvas
{
public:
	CCanvas(std::string const& outFileName);
	~CCanvas();

	void DrawLine(CPoint const& from, CPoint const& to, uint32_t const& lineColor) override;

	void FillCircle(CPoint const& center, double radius, uint32_t const& fillColor) override;
	void DrawCircle(CPoint const& center, double radius, uint32_t const& lineColor) override;

	void FillPolygon(std::vector<CPoint> const& points, uint32_t const& fillColor) override;
	void DrawPolygon(std::vector<CPoint> const& points, uint32_t const& lineColor) override;

private:
	std::ofstream m_outStream;
};
