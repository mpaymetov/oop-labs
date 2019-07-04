#pragma once
#include "stdafx.h"
#include "Canvas.h"

CCanvas::CCanvas(std::string const& outFileName)
{
	m_outStream.open(outFileName);
	if (m_outStream.is_open())
	{
		m_outStream << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
		m_outStream << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n";
		m_outStream << " \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
		m_outStream << "<svg version=\"1.1\" width=\"800\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">\n";
		m_outStream << "<title>Example</title>\n";
	}
}

CCanvas::~CCanvas()
{
	m_outStream << "</svg>";
	m_outStream.close();
}

void CCanvas::DrawLine(CPoint const& from, CPoint const& to, uint32_t const& lineColor)
{
	m_outStream << std::fixed << std::setprecision(0);
	m_outStream << "<line x1=\"" << from.x << "\" y1=\"" << from.y << "\"";
	m_outStream << " x2=\"" << to.x << "\" y2=\"" << to.y << "\"";
	m_outStream << " stroke=\"#" << std::hex << lineColor << "\" stroke-width=\"1\" />\n";
}

void CCanvas::FillCircle(CPoint const& center, double radius, uint32_t const& fillColor)
{
	m_outStream << std::fixed << std::setprecision(0);
	m_outStream << "<circle cx=\"" << center.x << "\" cy=\"" << center.y << "\"";
	m_outStream << " r=\"" << radius << "\" fill=\"#" << std::hex << fillColor << "\" />\n";
}

void CCanvas::DrawCircle(CPoint const& center, double radius, uint32_t const& lineColor)
{
	m_outStream << std::fixed << std::setprecision(0);
	m_outStream << "<circle cx=\"" << center.x << "\" cy=\"" << center.y << "\"";
	m_outStream << " r=\"" << radius << "\" fill=\"none\"";
	m_outStream << " stroke=\"#" << std::hex << lineColor << "\" stroke-width=\"1\" />\n";
}

void CCanvas::FillPolygon(std::vector<CPoint> const& points, uint32_t const& fillColor)
{
	m_outStream << std::fixed << std::setprecision(0) << "<polygon points=\"";
	for (auto [px, py] : points)
	{
		m_outStream << px << "," << py << " ";
	}
	m_outStream << "\" fill=\"#" << std::hex << fillColor << "\" />\n";
}

void CCanvas::DrawPolygon(std::vector<CPoint> const& points, uint32_t const& lineColor)
{
	m_outStream << std::fixed << std::setprecision(0) << "<polygon points=\"";
	for (auto [px, py] : points)
	{
		m_outStream << px << "," << py << " ";
	}
	m_outStream << "\" fill=\"none\" stroke=\"#";
	m_outStream << std::hex << lineColor << "\" stroke-width=\"1\" />\n";
}
