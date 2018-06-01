#pragma once

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "car.h"
#include "carControl.h"

std::string ConvertErrorToString(const Error &error)
{
	switch (error)
	{
	case Error::ENGINE_IS_ON:
		return "Engine is already on";
	case Error::ENGINE_IS_OFF:
		return "Engine is already off";
	case Error::ENGINE_CAN_NOT_BE_TURNED_OFF:
		return "Engine can not be turned off";
	case Error::NO_ZERO_SPEED:
		return "First you need to stop";
	case Error::SPEED_IS_NOT_CORRECT_FOR_GEAR:
		return "Speed is not correct for gear";
	case Error::ONLY_REDUCE_THE_SPEED:
		return "Speed can only be reduced";
	case Error::SPEED_IS_NOT_CORRECT_FOR_REVERSE_GEAR:
		return "the speed can be from 0 to 20";
	case Error::SPEED_IS_NOT_CORRECT_FOR_FIRST_GEAR:
		return "the speed can be from 0 to 30";
	case Error::SPEED_IS_NOT_CORRECT_FOR_SECOND_GEAR:
		return "the speed can be from 20 to 50";
	case Error::SPEED_IS_NOT_CORRECT_FOR_THIRD_GEAR:
		return "the speed can be from 30 to 60";
	case Error::SPEED_IS_NOT_CORRECT_FOR_FOURTH_GEAR:
		return "the speed can be from 40 to 90";
	case Error::SPEED_IS_NOT_CORRECT_FOR_FIFTH_GEAR:
		return "the speed can be from 50 to 150";
	}
	return "not error";
}

std::string ConvertGearToString(const Gear &gear)
{
	switch (gear)
	{
	case Gear::REVERSE:
		return "Reverse";
	case Gear::NEUTRAL:
		return "Neutral";
	case Gear::FIRST:
		return "First";
	case Gear::SECOND:
		return "Second";
	case Gear::THIRD:
		return "Third";
	case Gear::FOURTH:
		return "Fourth";
	}
	return "Fifth";
}

std::string ConvertDirectionToString(const Direction &direction)
{
	if (direction == Direction::BACK)
		return "back";
	else if (direction == Direction::STOP)
		return "stop";
	else
		return "forward";
}

CCarControl::CCarControl(CCar &car, std::istream & input, std::ostream & output)
	: m_car(car),
	m_input(input),
	m_output(output),
	m_actionMap({
		{ "EngineOn", std::bind(&CCarControl::EngineOn, this, std::placeholders::_1) },
		{ "EngineOff", std::bind(&CCarControl::EngineOff, this, std::placeholders::_1) },
		{ "Info", std::bind(&CCarControl::Info, this, std::placeholders::_1) },
		{ "SetGear", std::bind(&CCarControl::SetGear, this, std::placeholders::_1) },
		{ "SetSpeed", std::bind(&CCarControl::SetSpeed, this, std::placeholders::_1) }
		})
{
}

bool CCarControl::ExecuteCommand()
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

bool CCarControl::EngineOn(std::istream &)
{
	if (m_car.TurnOnEngine())
	{
		m_output << "Engine is turned on" << std::endl;
	}
	else
	{
		m_output << ConvertErrorToString(m_car.GetError()) << std::endl;
	}
	return true;
}

bool CCarControl::EngineOff(std::istream &)
{
	if (m_car.TurnOffEngine())
	{
		m_output << "Engine is turned off" << std::endl;
	}
	else
	{
		m_output << ConvertErrorToString(m_car.GetError()) << std::endl;
	}
	return true;
}

bool CCarControl::Info(std::istream &) const
{
	std::string infoEngine = (m_car.IsEngineOn()) ? ("Engine is turned on\n") : ("Engine is turned off\n");
	std::string infoSpeed = "Speed " + std::to_string(m_car.GetSpeed()) + "\n";
	std::string infoDirection = "Direction " + ConvertDirectionToString(m_car.GetDirection()) + "\n";
	std::string infoGear = "Gear " + ConvertGearToString(m_car.GetGear());

	m_output << (infoEngine + infoSpeed + infoDirection + infoGear) << "\n";
	return true;
}

bool isAvailable(const std::string &arg, int &gear)
{
	try
	{
		gear = std::stoi(arg);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}

bool CCarControl::SetGear(std::istream &args)
{
	int gear;
	std::string input;
	args >> input;

	if (isAvailable(input, gear))
	{
		if ((gear < -1) || (gear > 5))
		{
			m_output << "Use a gear between -1 and 5" << std::endl;
		}
		else if (m_car.SetGear(gear))
		{
			m_output << "Selected gear " << gear << std::endl;
		}
		else
		{
			m_output << "Gear did not change" << std::endl;
			m_output << ConvertErrorToString(m_car.GetError()) << std::endl;
		}
	}
	else
	{
		m_output << "Invalid gear" << std::endl;
	}

	return true;
}

bool CCarControl::SetSpeed(std::istream &args)
{
	int speed;
	std::string input;
	args >> input;

	if (isAvailable(input, speed))
	{
		if (speed < 0)
		{
			m_output << "Speed can not be negative" << std::endl;
		}
		else if (m_car.SetSpeed(speed))
		{
			m_output << "Selected speed " << speed << std::endl;
		}
		else
		{
			m_output << "Speed did not change" << std::endl;
			m_output << ConvertErrorToString(m_car.GetError()) << std::endl;
		}
	}
	else
	{
		m_output << "Invalid speed" << std::endl;
	}

	return true;
}

