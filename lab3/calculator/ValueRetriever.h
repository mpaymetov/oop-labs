#pragma once
#include "stdafx.h"

class IValueRetriever
{
public:
	virtual ~IValueRetriever() = default;
	virtual double GetValue() const = 0;
};
