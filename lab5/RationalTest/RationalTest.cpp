#include "stdafx.h"
#include "../Rational/Rational.h"

TEST_CASE("test create Rational number with no Numerator and no Denominator")
{
	CRational number;
	CHECK(number.GetNumerator() == 0);
	CHECK(number.GetDenominator() == 1);
	CHECK(number.ToDouble() == 0);
}

TEST_CASE("test create Rational number with Numerator and no Denominator")
{
	CRational number(3);
	CHECK(number.GetNumerator() == 3);
	CHECK(number.GetDenominator() == 1);
	CHECK(number.ToDouble() == 3);
}

TEST_CASE("test create Rational number with Numerator and Denominator")
{
	CRational number(3, 2);
	CHECK(number.GetNumerator() == 3);
	CHECK(number.GetDenominator() == 2);
	CHECK(number.ToDouble() == 1.5);
}

TEST_CASE("test create Rational number with Denominator 0")
{
	CHECK_THROWS_AS(CRational(3, 0), std::invalid_argument);
}

TEST_CASE("test create Rational number if Denominator < 0")
{
	CRational number(3, -2);
	CHECK(number.GetNumerator() == -3);
	CHECK(number.GetDenominator() == 2);
	CHECK(number.ToDouble() == -1.5);
}

TEST_CASE("test create Rational number with Normalize")
{
	CRational number(15, 10);
	CHECK(number.GetNumerator() == 3);
	CHECK(number.GetDenominator() == 2);
}

TEST_CASE("test unary plus")
{
	CRational number(4, 5);
	CRational result = +number;
	CHECK(number.GetNumerator() == 4);
	CHECK(number.GetDenominator() == 5);
	CHECK(number.ToDouble() == 0.8);
}

TEST_CASE("test unary minus")
{
	CRational number(4, 7);
	CRational result = -number;
	//CHECK(number.GetNumerator() == -4);
	CHECK(number.GetDenominator() == 7);
}

TEST_CASE("test binary plus 2 Rational numbers")
{
	CRational first(1, 2);
	CRational second(1, 4);
	CRational result = first + second;
	CHECK(result.GetNumerator() == 3);
	CHECK(result.GetDenominator() == 4);
	CHECK(result.ToDouble() == 0.75);
}

TEST_CASE("test binary plus Rational and int numbers")
{
	CRational first(1, 2);
	int second = 1;
	CRational result = first + second;
	CHECK(result.GetNumerator() == 3);
	CHECK(result.GetDenominator() == 2);
}

TEST_CASE("test binary plus int and Rational numbers")
{
	int first = 2;
	CRational second(1, 4);
	CRational result = first + second;
	CHECK(result.GetNumerator() == 9);
	CHECK(result.GetDenominator() == 4);
}

TEST_CASE("test binary minus 2 Rational numbers")
{
	CRational first(1, 2);
	CRational second(1, 4);
	CRational result = first - second;
	CHECK(result.GetNumerator() == 1);
	CHECK(result.GetDenominator() == 4);
	CHECK(result.ToDouble() == 0.25);
}
TEST_CASE("test binary minus Rational and int numbers")
{
	CRational first(4);
	int second = 2;
	CRational result = first - second;
	CHECK(result.GetNumerator() == 2);
	CHECK(result.GetDenominator() == 1);
	CHECK(result.ToDouble() == 2.0);
}
TEST_CASE("test binary minus int and Rational numbers")
{
	int first = 3;
	CRational second(3, 4);
	CRational result = first - second;
	CHECK(result.GetNumerator() == 9);
	CHECK(result.GetDenominator() == 4);
	CHECK(result.ToDouble() == 2.25);
}

TEST_CASE("test binary multiplication 2 Rational numbers")
{
	CRational first(1, 2);
	CRational second(3, 4);
	CRational result = first * second;
	CHECK(result.GetNumerator() == 3);
	CHECK(result.GetDenominator() == 8);
	CHECK(result.ToDouble() == 0.375);
}

TEST_CASE("test binary multiplication Rational and int numbers")
{
	CRational first(1, 2);
	int second = 3;
	CRational result = first * second;
	CHECK(result.GetNumerator() == 3);
	CHECK(result.GetDenominator() == 2);
	CHECK(result.ToDouble() == 1.5);
}

TEST_CASE("test binary multiplication int and Rational numbers")
{
	int first = 3;
	CRational second(3, 4);
	CRational result = first * second;
	CHECK(result.GetNumerator() == 9);
	CHECK(result.GetDenominator() == 4);
	CHECK(result.ToDouble() == 2.25);
}

TEST_CASE("test binary division 2 Rational numbers")
{
	CRational first(3, 4);
	CRational second(2, 1);
	CRational result = first / second;
	CHECK(result.GetNumerator() == 3);
	CHECK(result.GetDenominator() == 8);
	CHECK(result.ToDouble() == 0.375);
}

TEST_CASE("test binary division Rational and int numbers")
{
	CRational first(3, 4);
	int second = 2;
	CRational result = first / second;
	CHECK(result.GetNumerator() == 3);
	CHECK(result.GetDenominator() == 8);
	CHECK(result.ToDouble() == 0.375);
}

TEST_CASE("test binary division int and Rational numbers")
{
	int first = 5;
	CRational second(2, 1);
	CRational result = first / second;
	CHECK(result.GetNumerator() == 5);
	CHECK(result.GetDenominator() == 2);
	CHECK(result.ToDouble() == 2.5);
}

TEST_CASE("test operator == 2 Rational numbers")
{
	CRational first(1, 2);
	CRational second(2, 4);
	CRational third(3, 4);
	CHECK(first == second);
	CHECK(!(first == third));
}

TEST_CASE("test operator == Rational and int numbers")
{
	CRational first(4, 2);
	int second = 2;
	int third = 3;
	CHECK(first == second);
	CHECK(!(first == third));
}

TEST_CASE("test operator == int and Rational numbers")
{
	int first = 3;
	CRational second(6, 2);
	CRational third(3, 4);
	CHECK(first == second);
	CHECK(!(first == third));
}

TEST_CASE("test operator !=")
{
	CRational first(1, 2);
	CRational second(2, 4);
	CRational third(3, 4);
	CHECK(!(first != second));
	CHECK(first != third);
}

TEST_CASE("test operator <")
{
	CRational first(1, 2);
	CRational second(2, 4);
	CRational third(3, 4);
	CHECK(first < third);
	CHECK(!(third < first));
	CHECK(!(first < second));
}

TEST_CASE("test operator >")
{
	CRational first(1, 2);
	CRational second(2, 4);
	CRational third(3, 4);
	CHECK(third > first);
	CHECK(!(first > third));
	CHECK(!(first > second));
}

TEST_CASE("test operator <=")
{
	CRational first(1, 2);
	CRational second(2, 4);
	CRational third(3, 4);
	CHECK(first <= third);
	CHECK(!(third <= first));
	CHECK(first <= second);
}

TEST_CASE("test operator >=")
{
	CRational first(1, 2);
	CRational second(2, 4);
	CRational third(3, 4);
	CHECK(third >= first);
	CHECK(!(first >= third));
	CHECK(first >= second);
}