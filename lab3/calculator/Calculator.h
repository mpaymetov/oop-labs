#pragma once
#include "stdafx.h"
#include "Variable.h"
#include "Function.h"
#include "Operator.h"

enum class Error
{
	NO_ERROR,
	VARIABLE_ALREADY_EXISTS,
	VARIABLE_NOT_EXIST,
	IDENTIFIER_NAME_INCORRECT,
	VALUE_INCORRECT
};

class CCalculator
{
public:
	CCalculator() = default;
	~CCalculator() = default; 
	
	bool SetVar(const std::string& identifier);
	bool SetValue(const std::string& identifier, const std::string& value);
	bool GetValue(const std::string& identifier, std::string& result);
	bool SetFn(const std::string& identifier, const std::string& firstOperand, const std::string& mathOperator, const std::string& secondOperand);
	std::string GetAllVarsVales();
	std::string GetAllFnsVales();
	Error GetError() const;

private:
	std::multimap<std::string, std::shared_ptr<IValueRetriever>> m_names;
	std::multimap<std::string, std::shared_ptr<CVariable>> m_vars;
	std::multimap<std::string, std::shared_ptr<CFunction>> m_fns;
	Error m_error = Error::NO_ERROR;

	COperator GetMathOperator(std::string str) const;
};
