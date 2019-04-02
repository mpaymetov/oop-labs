#pragma once
#include "icanvas.h"

class ICanvasDrawable
{
public:
	virtual ~ICanvasDrawable() {};
	virtual void Draw(ICanvas & canvas) const = 0;
};
