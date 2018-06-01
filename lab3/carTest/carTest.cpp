#include "stdafx.h"
#include "../car/car.h"

TEST_CASE("can EngineOn")
{
	CCar car;
	CHECK(car.TurnOnEngine());
	CHECK(car.IsEngineOn());
	CHECK(!car.TurnOnEngine());
}

TEST_CASE("can EngineOff")
{
	CCar car;
	CHECK(car.TurnOnEngine());
	CHECK(car.TurnOffEngine());
	CHECK(!car.TurnOffEngine());
}

TEST_CASE("can not EngineOff if speed not zero")
{
	CCar car;
	CHECK(car.TurnOnEngine());
	CHECK(car.SetGear(1));
	CHECK(car.GetGear() == Gear::FIRST);
	CHECK(car.SetSpeed(10));
	CHECK(car.GetSpeed() == 10);
	CHECK(!car.TurnOffEngine());
}

TEST_CASE("test all gear")
{
	CCar car;
	CHECK(car.TurnOnEngine());
	
	CHECK(car.GetDirection() == Direction::STOP);

	CHECK(car.SetGear(1));
	CHECK(car.GetGear() == Gear::FIRST);
	CHECK(car.SetSpeed(25));
	CHECK(car.GetSpeed() == 25);

	CHECK(car.GetDirection() == Direction::FORWARD);
	
	CHECK(car.SetGear(2));
	CHECK(!car.SetGear(3));
	CHECK(car.GetGear() == Gear::SECOND);
	CHECK(car.SetSpeed(40));
	CHECK(!car.SetSpeed(80));
	CHECK(car.GetSpeed() == 40);
	
	CHECK(car.SetGear(3));
	CHECK(car.GetGear() == Gear::THIRD);
	CHECK(car.SetSpeed(50));
	CHECK(car.GetSpeed() == 50);

	CHECK(car.SetGear(4));
	CHECK(car.GetGear() == Gear::FOURTH);
	CHECK(car.SetSpeed(80));
	CHECK(car.GetSpeed() == 80);

	CHECK(car.SetGear(5));
	CHECK(car.GetGear() == Gear::FIFTH);
	CHECK(car.SetSpeed(140));
	CHECK(car.GetSpeed() == 140);

	CHECK(car.SetGear(0));
	CHECK(car.GetGear() == Gear::NEUTRAL);
	
	CHECK(car.SetSpeed(20));
	CHECK(car.GetSpeed() == 20);

	CHECK(!car.SetSpeed(25));
	CHECK(car.GetSpeed() == 20);

	CHECK(!car.SetGear(-1));
	CHECK(car.GetGear() == Gear::NEUTRAL);

	CHECK(car.SetSpeed(0));
	CHECK(car.GetSpeed() == 0);
	CHECK(car.GetDirection() == Direction::STOP);

	CHECK(car.SetGear(-1));
	CHECK(car.GetGear() == Gear::REVERSE);
	CHECK(car.SetSpeed(10));
	CHECK(car.GetSpeed() == 10);
	CHECK(car.GetDirection() == Direction::BACK);

	CHECK(car.GetError() == Error::NO_ERROR);
}

