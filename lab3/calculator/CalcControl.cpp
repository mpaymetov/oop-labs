#pragma once

#include "stdafx.h"
#include "calculator.h"
#include "calcControl.h"

std::string ConvertErrorToString(const Error &error)
{
	switch (error)
	{
	case Error::VARIABLE_ALREADY_EXISTS:
		return "Variable already exists";
	case Error::VARIABLE_NOT_EXIST:
		return "Variable not exists";
	case Error::IDENTIFIER_NAME_INCORRECT:
		return "identifier name incorrect";
	case Error::VALUE_INCORRECT:
		return "value incorrect";
	}
	return "not error";
}

CCalcControl::CCalcControl(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator),
	m_input(input),
	m_output(output),
	m_actionMap({
		{ "var", std::bind(&CCalcControl::Var, this, std::placeholders::_1) },
		{ "let", std::bind(&CCalcControl::Let, this, std::placeholders::_1) },
		{ "fn", std::bind(&CCalcControl::Fn, this, std::placeholders::_1) },
		{ "print", std::bind(&CCalcControl::Print, this, std::placeholders::_1) },
		{ "printvars", std::bind(&CCalcControl::Printvars, this, std::placeholders::_1) },
		{ "printfns", std::bind(&CCalcControl::Printfns, this, std::placeholders::_1) }
		})
{
}

bool CCalcControl::ExecuteCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CCalcControl::Var(std::istream & args)
{
	std::string input;
	args >> input;
	if (!m_calculator.SetVar(input))
	{
		m_output << ConvertErrorToString(m_calculator.GetError()) << std::endl;
	}
	return true;
}

bool CCalcControl::Let(std::istream & args)
{
	std::string identifier, assign, valueStr;
	args >> identifier >> assign >> valueStr;
	
	if (!m_calculator.SetValue(identifier, valueStr))
	{
		m_output << ConvertErrorToString(m_calculator.GetError()) << std::endl;
	}
	return true;
}

bool CCalcControl::Fn(std::istream & args)
{
	std::string identifier, assign, firstOperand, mathOperator, secondOperand;
	args >> identifier >> assign >> firstOperand >> mathOperator >> secondOperand;


	if (!m_calculator.SetFn(identifier, firstOperand, mathOperator, secondOperand))
	{
		m_output << ConvertErrorToString(m_calculator.GetError()) << std::endl;
	}
	return true;
}

bool CCalcControl::Print(std::istream & args)
{
	std::string input, result;
	args >> input;
	if (m_calculator.GetValue(input, result))
	{
		m_output << result << std::endl;
	}
	else
	{
		m_output << ConvertErrorToString(m_calculator.GetError()) << std::endl;
	}
	return true;
}

bool CCalcControl::Printvars(std::istream & args)
{
	m_output << m_calculator.GetAllVarsVales();
	return true;
}

bool CCalcControl::Printfns(std::istream & args)
{
	m_output << m_calculator.GetAllFnsVales();
	return true;
}

