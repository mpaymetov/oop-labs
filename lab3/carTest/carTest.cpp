#include "stdafx.h"
#include "../car/car.h"
#include "../car/carControl.h"

void ExpectOperationSuccess(CCar& car, const std::function<bool(CCar& car)>& op, bool engineIsOn, Gear gear, int speed, Direction direction)
{
	REQUIRE(op(car)); /* ожидаем, что операция вернет true (успех) */
					  /* Сравниваем состояние свойства объект с ожидаемым */
	CHECK(car.IsEngineOn() == engineIsOn);
	CHECK(car.GetGear() == gear);
	CHECK(car.GetSpeed() == speed);
	CHECK(car.GetDirection() == direction);
	return;
}

void ExpectOperationFailure(CCar const& car, const std::function<bool(CCar& car)>& op)
{
	auto clone(car); // сделали клон объекта
	REQUIRE(!op(clone)); // ожидаем, что операция завершится неуспешно (передаем клон)
						 // проверяем, что после выполнения операции состояние клона не отличается от оригинала 
						 // (операция в случае неудачи оставляет объект в состоянии, в котором он пребывал до операции)
	CHECK(clone.IsEngineOn() == car.IsEngineOn());
	CHECK(clone.GetGear() == car.GetGear());
	CHECK(clone.GetSpeed() == car.GetSpeed());
	CHECK(clone.GetDirection() == car.GetDirection());
	return;
}

TEST_CASE("can EngineOn")
{
	CCar car;
	CHECK(car.TurnOnEngine());
	CHECK(car.IsEngineOn());
	CHECK(!car.TurnOnEngine());
}

TEST_CASE("can not change gear if EngineOff")
{
	CCar car;
	CHECK(!car.IsEngineOn());
	CHECK(!car.SetGear(1));
}

TEST_CASE("can EngineOff")
{
	CCar car;
	CHECK(car.TurnOnEngine());
	CHECK(car.TurnOffEngine());
	CHECK(!car.TurnOffEngine());
}

TEST_CASE("can not change forward gear if move back")
{
	CCar car;
	CHECK(car.TurnOnEngine());
	CHECK(car.SetGear(-1));
	CHECK(car.GetGear() == Gear::REVERSE);
	CHECK(car.SetSpeed(20));
	CHECK(car.GetSpeed() == 20);
	CHECK(car.GetDirection() == Direction::BACK);
	CHECK(car.SetGear(0));
	CHECK(car.GetGear() == Gear::NEUTRAL);
	CHECK(car.GetDirection() == Direction::BACK);
	CHECK(!car.SetGear(1));
	CHECK(!car.SetGear(2));
}

TEST_CASE("can not EngineOff if speed not zero")
{
	CCar car;
	CHECK(car.TurnOnEngine());
	CHECK(car.SetGear(1));
	CHECK(car.GetGear() == Gear::FIRST);
	CHECK(!car.TurnOffEngine());
	CHECK(car.SetSpeed(10));
	CHECK(car.GetSpeed() == 10);
	CHECK(!car.TurnOffEngine());
	CHECK(car.SetGear(0));
	CHECK(!car.TurnOffEngine());
	CHECK(car.SetSpeed(0));
	CHECK(car.TurnOffEngine());
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

TEST_CASE("Can set engine on only when it is off")
{
	CCar car;// engine is off, gear = NEUTRAL, speed = 0, STOP
	ExpectOperationSuccess(car, [](auto&& car) {return car.TurnOnEngine(); }, true /*on*/, Gear::NEUTRAL /*gear*/, 0 /*speed*/, Direction::STOP);
	ExpectOperationFailure(car, [](auto&& car) {return car.TurnOnEngine(); });
	ExpectOperationSuccess(car, [](auto&& car) {return car.TurnOffEngine(); }, false /*on*/, Gear::NEUTRAL /*gear*/, 0 /*speed*/, Direction::STOP);
	ExpectOperationFailure(car, [](auto&& car) {return car.TurnOffEngine(); });
}

TEST_CASE("test Expect Operation all gear")
{
	CCar car;// engine is off, gear = NEUTRAL, speed = 0, STOP
	ExpectOperationSuccess(car, [](auto&& car) {return car.TurnOnEngine(); }, true /*on*/, Gear::NEUTRAL /*gear*/, 0 /*speed*/, Direction::STOP);

	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(1); }, true /*on*/, Gear::FIRST /*gear*/, 0 /*speed*/, Direction::STOP);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetSpeed(25); }, true /*on*/, Gear::FIRST /*gear*/, 25 /*speed*/, Direction::FORWARD);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(35); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(3); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(4); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(5); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(-1); });
	ExpectOperationFailure(car, [](auto&& car) {return car.TurnOffEngine(); });

	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(2); }, true /*on*/, Gear::SECOND /*gear*/, 25 /*speed*/, Direction::FORWARD);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetSpeed(45); }, true /*on*/, Gear::SECOND /*gear*/, 45 /*speed*/, Direction::FORWARD);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(15); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(55); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(1); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(5); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(-1); });

	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(3); }, true /*on*/, Gear::THIRD /*gear*/, 45 /*speed*/, Direction::FORWARD);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetSpeed(55); }, true /*on*/, Gear::THIRD /*gear*/, 55 /*speed*/, Direction::FORWARD);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(65); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(25); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(1); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(2); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(-1); });

	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(4); }, true /*on*/, Gear::FOURTH /*gear*/, 55 /*speed*/, Direction::FORWARD);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetSpeed(85); }, true /*on*/, Gear::FOURTH /*gear*/, 85 /*speed*/, Direction::FORWARD);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(95); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(35); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(1); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(2); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(3); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(-1); });
	
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(5); }, true /*on*/, Gear::FIFTH /*gear*/, 85 /*speed*/, Direction::FORWARD);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetSpeed(150); }, true /*on*/, Gear::FIFTH /*gear*/, 150 /*speed*/, Direction::FORWARD);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(155); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(45); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(1); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(2); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(3); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(4); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(-1); });

	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(0); }, true /*on*/, Gear::NEUTRAL /*gear*/, 150 /*speed*/, Direction::FORWARD);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetSpeed(40); }, true /*on*/, Gear::NEUTRAL /*gear*/, 40 /*speed*/, Direction::FORWARD);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetSpeed(90); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(1); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(5); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(-1); });
	ExpectOperationFailure(car, [](auto&& car) {return car.TurnOffEngine(); });
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(3); }, true /*on*/, Gear::THIRD /*gear*/, 40 /*speed*/, Direction::FORWARD);

	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(0); }, true /*on*/, Gear::NEUTRAL /*gear*/, 40 /*speed*/, Direction::FORWARD);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetSpeed(0); }, true /*on*/, Gear::NEUTRAL /*gear*/, 0 /*speed*/, Direction::STOP);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(-1); }, true /*on*/, Gear::REVERSE /*gear*/, 0 /*speed*/, Direction::STOP);
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetSpeed(20); }, true /*on*/, Gear::REVERSE /*gear*/, 20 /*speed*/, Direction::BACK);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(1); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(2); });
	ExpectOperationSuccess(car, [](auto&& car) {return car.SetGear(0); }, true /*on*/, Gear::NEUTRAL /*gear*/, 20 /*speed*/, Direction::BACK);
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(1); });
	ExpectOperationFailure(car, [](auto&& car) {return car.SetGear(2); });
	ExpectOperationFailure(car, [](auto&& car) {return car.TurnOffEngine(); });
}