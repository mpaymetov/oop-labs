#include "stdafx.h"
#include "../car/car.h"
#include "../car/carControl.h"
#include <functional>

void VerifyCommandHandling(CCar &car, const std::string &command, const std::string &expectedOutput)
{
	std::stringstream output, input;
	output = std::stringstream();
	input = std::stringstream();
	CCarControl carControl(car, input, output);

	CHECK(input << command);
	CHECK(carControl.ExecuteCommand());
	CHECK(input.eof());
	CHECK(output.str() == expectedOutput);
}

TEST_CASE("can handle EngineOn command")
{
	CCar car;
	VerifyCommandHandling(car, "EngineOn", "Engine is turned on\n");
	VerifyCommandHandling(car, "EngineOn", "Engine is already on\n");
	VerifyCommandHandling(car, "EngineOff", "Engine is turned off\n");
	VerifyCommandHandling(car, "EngineOff", "Engine is already off\n");
};

TEST_CASE("can handle Gear, Speed and info command")
{
	CCar car;
	VerifyCommandHandling(car, "EngineOn", "Engine is turned on\n");
	VerifyCommandHandling(car, "SetGear 1", "Selected gear 1\n");
	VerifyCommandHandling(car, "SetSpeed 20", "Selected speed 20\n");
	VerifyCommandHandling(car, "SetGear 2", "Selected gear 2\n");
	VerifyCommandHandling(car, "Info", "Engine is turned on\nSpeed 20\nDirection forward\nGear Second\n");
};

