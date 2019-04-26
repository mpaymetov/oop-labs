#pragma once
#include "stdafx.h"

class IValueRetriever
{
public:
	virtual ~IValueRetriever() = default;

	virtual double GetValue() const = 0;
	virtual bool HaveValue() const = 0;
};