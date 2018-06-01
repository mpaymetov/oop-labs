#include "stdafx.h"
#include "car.h"

bool IsSpeedCorrectForGear(int speed, int localSpeed, Gear gear)
{
	switch (gear)
	{
	case Gear::REVERSE:
		return (speed <= 20);
	case Gear::NEUTRAL:
		return (speed <= localSpeed);
	case Gear::FIRST:
		return (speed <= 30);
	case Gear::SECOND:
		return (speed >= 20 && speed <= 50);
	case Gear::THIRD:
		return (speed >= 30 && speed <= 60);
	case Gear::FOURTH:
		return (speed >= 40 && speed <= 90);
	case Gear::FIFTH:
		return (speed >= 50 && speed <= 150);
	}
	return true;
}

bool CCar::TurnOnEngine()
{
	if (!m_isEngineOn)
	{
		m_isEngineOn = true;
		m_error = Error::NO_ERROR;
		return true;
	}
	m_error = Error::ENGINE_IS_ON;
	return false;
}

bool CCar::IsEngineOn() const
{
	return m_isEngineOn;
}

bool CCar::TurnOffEngine()
{
	if (m_isEngineOn)
	{
		if (m_gear == Gear::NEUTRAL && m_speed == 0)
		{
			m_isEngineOn = false;
			m_error = Error::NO_ERROR;
			return true;
		}
		else
		{
			m_error = Error::ENGINE_CAN_NOT_BE_TURNED_OFF;
		}
	}
	else
	{
		m_error = Error::ENGINE_IS_OFF;
	}
	
	return false;
}

bool CCar::SetGear(int gear)
{
	Gear l_gear;
	switch (gear)
	{
	case -1:
		l_gear = Gear::REVERSE; 
		m_error = Error::SPEED_IS_NOT_CORRECT_FOR_REVERSE_GEAR;
		break;
	case 0:
		l_gear = Gear::NEUTRAL; 
		m_error = Error::ONLY_REDUCE_THE_SPEED;
		break;
	case 1:
		l_gear = Gear::FIRST; 
		m_error = Error::SPEED_IS_NOT_CORRECT_FOR_FIRST_GEAR;
		break;
	case 2:
		l_gear = Gear::SECOND; 
		m_error = Error::SPEED_IS_NOT_CORRECT_FOR_SECOND_GEAR;
		break;
	case 3:
		l_gear = Gear::THIRD; 
		m_error = Error::SPEED_IS_NOT_CORRECT_FOR_THIRD_GEAR;
		break;
	case 4:
		l_gear = Gear::FOURTH; 
		m_error = Error::SPEED_IS_NOT_CORRECT_FOR_FOURTH_GEAR;
		break;
	case 5:
		l_gear = Gear::FIFTH; 
		m_error = Error::SPEED_IS_NOT_CORRECT_FOR_FIFTH_GEAR;
		break;
	}

	if ((l_gear == Gear::FIRST) || (l_gear == Gear::REVERSE))
	{
		if (m_speed == 0)
		{
			m_gear = l_gear;
			m_error = Error::NO_ERROR;
			return true;
		}
	}
	else
	{
		if (IsSpeedCorrectForGear(m_speed, m_speed, l_gear))
		{
			m_gear = l_gear;
			m_error = Error::NO_ERROR;
			return true;
		}
	}
	return false;
}

bool CCar::SetSpeed(unsigned int speed)
{
	if (IsSpeedCorrectForGear(speed, m_speed, m_gear))
	{
		m_speed = speed;
		m_error = Error::NO_ERROR;
		if (speed > 0)
		{
			if (m_gear == Gear::REVERSE)
			{
				m_direction = Direction::BACK;
			}
			else
			{
				m_direction = Direction::FORWARD;
			}
		}
		else
		{
			m_direction = Direction::STOP;
		}
		return true;
	}
	m_error = Error::SPEED_IS_NOT_CORRECT_FOR_GEAR;
	return false;
}

Gear CCar::GetGear() const
{
	return m_gear;
}

unsigned int CCar::GetSpeed() const
{
	return m_speed;
}

Direction CCar::GetDirection() const
{
	return m_direction;
}

Error CCar::GetError() const
{
	return m_error;
}

