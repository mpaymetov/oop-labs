#pragma once
#include "stdafx.h"
#include "calculator.h"

class CCalcControl
{
public:
	CCalcControl(CCalculator& calculator, std::istream& input, std::ostream& output);
	~CCalcControl() = default;
	bool ExecuteCommand();

private:
	bool Var(std::istream & args);
	bool Let(std::istream & args);
	bool Fn(std::istream & args);
	bool Print(std::istream & args);
	bool Printvars(std::istream & args);
	bool Printfns(std::istream & args);

private:
	using ActionMap = std::map<std::string, std::function<bool(std::istream & args)>>;
	CCalculator &m_calculator;
	std::istream &m_input;
	std::ostream &m_output;
	const ActionMap m_actionMap;
};
