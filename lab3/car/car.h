#pragma once

enum class Direction { BACK, STOP, FORWARD };

enum class Gear { REVERSE = -1, NEUTRAL = 0, FIRST = 1, SECOND = 2, THIRD = 3, FOURTH = 4, FIFTH = 5 };

enum class Error
{
	NO_ERROR,
	ENGINE_IS_ON,
	ENGINE_IS_OFF,
	ENGINE_CAN_NOT_BE_TURNED_OFF,
	NO_ZERO_SPEED,
	SPEED_IS_NOT_CORRECT_FOR_GEAR,
	DIRECTION_NOT_CORRECT,
	ONLY_REDUCE_THE_SPEED,
	SPEED_IS_NOT_CORRECT_FOR_REVERSE_GEAR,
	SPEED_IS_NOT_CORRECT_FOR_FIRST_GEAR,
	SPEED_IS_NOT_CORRECT_FOR_SECOND_GEAR,
	SPEED_IS_NOT_CORRECT_FOR_THIRD_GEAR,
	SPEED_IS_NOT_CORRECT_FOR_FOURTH_GEAR,
	SPEED_IS_NOT_CORRECT_FOR_FIFTH_GEAR
};

class CCar
{
public:
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(unsigned int speed);

	bool IsEngineOn() const;
	Gear GetGear() const;
	unsigned int GetSpeed() const;
	Direction GetDirection() const;
	Error GetError() const;

private:
	bool m_isEngineOn = false;
	Gear m_gear = Gear::NEUTRAL;
	unsigned int m_speed = 0;
	Direction m_direction = Direction::STOP;
	Error m_error = Error::NO_ERROR;
};

