#pragma once
#include "stdafx.h"
#include "Operator.h"

class IValueRetriever
{
public:
	virtual ~IValueRetriever() = default;

	virtual double GetValue() const = 0;
	virtual bool HaveValue() const = 0;

	virtual std::string GetType() const = 0;
};