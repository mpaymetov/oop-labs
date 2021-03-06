#pragma once
#include "stdafx.h"
#include "ICanvasDrawable.h"

class IShape : public ICanvasDrawable
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual uint32_t GetOutlineColor() const = 0;
	virtual std::string GetType() const = 0;

private:
	virtual void AppendProperties(std::ostream& strm) const = 0;
};

