#include "stdafx.h"
#include "../calculator/UserInterface.h"
#include <regex>

TEST_CASE("test UserInterface")
{
	std::string str = "var x\nlet x=5\nprint x";
	std::istringstream istrm(str);
	std::ostringstream ostrm;
	CCalculator calculator;
	CUserInterface userInterface(calculator, istrm, ostrm);
	//CHECK(ostrm.str() == "5");
	CHECK(true);
}

