#pragma once

#include "stdafx.h"
#include "UserInterface.h"
#include "calculator.h"
#include "operator.h"

COperator GetMathOperator(std::string str)
{
	if (str == "+")
		return COperator::Addition;
	if (str == "-")
		return COperator::Subtraction;
	if (str == "*")
		return COperator::Multiplication;
	if (str == "/")
		return COperator::Division;
	return COperator::Undefined;
}

CUserInterface::CUserInterface(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "var", std::bind(&CUserInterface::Var, this, std::placeholders::_1) },
		  { "let", std::bind(&CUserInterface::Let, this, std::placeholders::_1) },
		  { "fn", std::bind(&CUserInterface::Fn, this, std::placeholders::_1) },
		  { "print", std::bind(&CUserInterface::Print, this, std::placeholders::_1) },
		  { "printvars", std::bind(&CUserInterface::Printvars, this, std::placeholders::_1) },
		  { "printfns", std::bind(&CUserInterface::Printfns, this, std::placeholders::_1) } })
{
}

bool CUserInterface::ExecuteCommand()
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

bool CUserInterface::Var(std::istream& args)
{
	std::string identifier, errorMsg;
	args >> identifier;
	if (!m_calculator.SetVar(identifier, errorMsg))
	{
		m_output << errorMsg << std::endl;
	}
	return true;
}

bool CUserInterface::Let(std::istream& args)
{
	std::string identifier, valueStr, errorMsg;

	std::regex regex(R"((\w+)=([\w.]+))");
	std::string str;
	std::cmatch result;
	args >> str;
	if (regex_match(str.c_str(), result, regex))
	{
		identifier = std::string(result[1].first, result[1].second);
		valueStr = std::string(result[2].first, result[2].second);
	}
	else
	{
		m_output << "error in expression" << std::endl; 
		return true;
	}

	double value;
	try
	{
		value = std::stod(valueStr);
	}
	catch (const std::exception&)
	{
		if (!m_calculator.GetValue(valueStr, value, errorMsg))
		{
			m_output << errorMsg << std::endl;
			return true;
		}		
	}

	if (!m_calculator.SetValue(identifier, value, errorMsg))
	{
		m_output << errorMsg << std::endl;
	}
	return true;
}

bool CUserInterface::Fn(std::istream& args)
{
	std::string identifier, firstOperand, mathOperatorStr, secondOperand, errorMsg;

	std::regex regex(R"((\w+)=(\w+)([+-/*])?(\w*))");
	std::string str;
	std::cmatch result;
	args >> str;
	if (regex_match(str.c_str(), result, regex))
	{
		for (auto& res : result)
		{
			std::cout << "\"" << std::string(res.first, res.second) << "\"" << std::endl;
		}

		identifier = std::string(result[1].first, result[1].second);
		firstOperand = std::string(result[2].first, result[2].second);
		mathOperatorStr = std::string(result[3].first, result[3].second);
		secondOperand = std::string(result[4].first, result[4].second);
	}
	else
	{
		m_output << "error in expression" << std::endl;
		return true;
	}

	COperator mathOperator = GetMathOperator(mathOperatorStr);

	if (!m_calculator.SetFn(identifier, firstOperand, mathOperator, secondOperand, errorMsg))
	{
		m_output << errorMsg << std::endl;
	}

	return true;
}

bool CUserInterface::Print(std::istream& args)
{
	std::string identifier, errorMsg;
	double result;
	args >> identifier;
	if (m_calculator.GetValue(identifier, result, errorMsg))
	{
		m_output << result << std::endl;
	}
	else
	{
		m_output << errorMsg << std::endl;
	}
	return true;
}

bool CUserInterface::Printvars(std::istream& args)
{
	std::map<std::string, double> vars = m_calculator.GetAllVarsVales();
	for (const auto& [name, val] : vars)
	{
		m_output << name << ": " << std::setprecision(3) << val << std::endl;
	}
	return true;
}

bool CUserInterface::Printfns(std::istream& args)
{
	std::map<std::string, double> fns = m_calculator.GetAllFnsVales();
	for (const auto& [name, val] : fns)
	{
		m_output << name << ": " << std::setprecision(3) << val << std::endl;
	}
	return true;
}
