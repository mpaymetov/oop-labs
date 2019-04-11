#include "stdafx.h"
#include "../Rational/Rational.h"

TEST_CASE("test create Rational number with no Numerator and no Denominator")
{
	CRational number;
	CHECK(number.GetNumerator() == 0);
	CHECK(number.GetDenominator() == 1);
}

TEST_CASE("test create Rational number with Numerator and no Denominator")
{
	CRational number(3);
	CHECK(number.GetNumerator() == 3);
	CHECK(number.GetDenominator() == 1);
}

TEST_CASE("test create Rational number with Numerator and Denominator")
{
	CRational number(3, 2);
	CHECK(number.GetNumerator() == 3);
	CHECK(number.GetDenominator() == 2);
}

TEST_CASE("test Denominator must be a natural number")
{
	CHECK_THROWS_AS(CRational(3, 0), std::invalid_argument);
	CRational number(3, -2);
	CHECK(number.GetNumerator() == -3);
	CHECK(number.GetDenominator() == 2);
}

TEST_CASE("test converting rational number to double")
{
	CRational first(3);
	CHECK(first.ToDouble() == 3.0);

	CRational second(-3, 4);
	CHECK(second.ToDouble() == -0.75);
}

TEST_CASE("test creation Rational number with normalizing")
{
	CRational first(15, 10);
	CHECK(first.GetNumerator() == 3);
	CHECK(first.GetDenominator() == 2);

	CRational second(-20, 40);
	CHECK(second.GetNumerator() == -1);
	CHECK(second.GetDenominator() == 2);

	CRational third(12, -9);
	CHECK(third.GetNumerator() == -4);
	CHECK(third.GetDenominator() == 3);

	CRational fourth(-28, -12);
	CHECK(fourth.GetNumerator() == 7);
	CHECK(fourth.GetDenominator() == 3);
}

TEST_CASE("test unary plus")
{
	CRational number(4, 5);
	CRational result = +number;
	CHECK(number.GetNumerator() == 4);
	CHECK(number.GetDenominator() == 5);
}

TEST_CASE("test unary minus")
{
	CRational number(4, 7);
	CRational result = -number;
	CHECK(result.GetNumerator() == -4);
	CHECK(result.GetDenominator() == 7);
}

TEST_CASE("test operator += for Rational numbers")
{
	CRational first(4, 3);
	CRational second(5, 2);
	first += second;
	CHECK(first.GetNumerator() == 23);
	CHECK(first.GetDenominator() == 6);

	CRational third(4, 9);
	CRational fourth(5, 9);
	third += fourth;
	CHECK(third.GetNumerator() == 1);
	CHECK(third.GetDenominator() == 1);
}

TEST_CASE("test operator += for int numbers")
{
	CRational first(4, 7);
	int second = 1;
	first += second;
	CHECK(first.GetNumerator() == 11);
	CHECK(first.GetDenominator() == 7);
}

TEST_CASE("test operator -= for Rational numbers")
{
	CRational first(5, 2);
	CRational second(3, 4);
	first -= second;
	CHECK(first.GetNumerator() == 7);
	CHECK(first.GetDenominator() == 4);

	CRational third(5, 9);
	CRational fourth(4, 9);
	third -= fourth;
	CHECK(third.GetNumerator() == 1);
	CHECK(third.GetDenominator() == 9);
}

TEST_CASE("test operator -= for int numbers")
{
	CRational first(12, 7);
	int second = 1;
	first -= second;
	CHECK(first.GetNumerator() == 5);
	CHECK(first.GetDenominator() == 7);
}

TEST_CASE("test operator *= for Rational numbers")
{
	CRational first(2, 3);
	CRational second(4, 5);
	first *= second;
	CHECK(first.GetNumerator() == 8);
	CHECK(first.GetDenominator() == 15);

	CRational third(2, 9);
	CRational fourth(4, 2);
	third *= fourth;
	CHECK(third.GetNumerator() == 4);
	CHECK(third.GetDenominator() == 9);
}

TEST_CASE("test operator *= for int numbers")
{
	CRational first(3, 7);
	int second = 2;
	first *= second;
	CHECK(first.GetNumerator() == 6);
	CHECK(first.GetDenominator() == 7);
}

TEST_CASE("test operator /= for Rational numbers")
{
	CRational first(7, 3);
	CRational second(2, 1);
	first /= second;
	CHECK(first.GetNumerator() == 7);
	CHECK(first.GetDenominator() == 6);

	CRational third(2, 9);
	CRational fourth(4, 5);
	third /= fourth;
	CHECK(third.GetNumerator() == 5);
	CHECK(third.GetDenominator() == 18);
}

TEST_CASE("test operator /= for int numbers")
{
	CRational first(7, 2);
	int second = 2;
	first /= second;
	CHECK(first.GetNumerator() == 7);
	CHECK(first.GetDenominator() == 4);
}

TEST_CASE("test binary plus 2 Rational numbers")
{
	CRational first(1, 2);
	CRational second(1, 4);
	CRational result = first + second;
	CHECK(result.GetNumerator() == 3);
	CHECK(result.GetDenominator() == 4);
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
}
TEST_CASE("test binary minus Rational and int numbers")
{
	CRational first(4);
	int second = 2;
	CRational result = first - second;
	CHECK(result.GetNumerator() == 2);
	CHECK(result.GetDenominator() == 1);
}
TEST_CASE("test binary minus int and Rational numbers")
{
	int first = 3;
	CRational second(3, 4);
	CRational result = first - second;
	CHECK(result.GetNumerator() == 9);
	CHECK(result.GetDenominator() == 4);
}

TEST_CASE("test binary multiplication 2 Rational numbers")
{
	CRational first(1, 2);
	CRational second(3, 4);
	CRational result = first * second;
	CHECK(result.GetNumerator() == 3);
	CHECK(result.GetDenominator() == 8);
}

TEST_CASE("test binary multiplication Rational and int numbers")
{
	CRational first(1, 2);
	int second = 3;
	CRational result = first * second;
	CHECK(result.GetNumerator() == 3);
	CHECK(result.GetDenominator() == 2);
}

TEST_CASE("test binary multiplication int and Rational numbers")
{
	int first = 3;
	CRational second(3, 4);
	CRational result = first * second;
	CHECK(result.GetNumerator() == 9);
	CHECK(result.GetDenominator() == 4);
}

TEST_CASE("test binary division 2 Rational numbers")
{
	CRational first(3, 4);
	CRational second(2, 1);
	CRational result = first / second;
	CHECK(result.GetNumerator() == 3);
	CHECK(result.GetDenominator() == 8);
}

TEST_CASE("test binary division Rational and int numbers")
{
	CRational first(3, 4);
	int second = 2;
	CRational result = first / second;
	CHECK(result.GetNumerator() == 3);
	CHECK(result.GetDenominator() == 8);
}

TEST_CASE("test binary division int and Rational numbers")
{
	int first = 5;
	CRational second(2, 1);
	CRational result = first / second;
	CHECK(result.GetNumerator() == 5);
	CHECK(result.GetDenominator() == 2);
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

TEST_CASE("test operator != 2 Rational numbers")
{
	CRational first(1, 2);
	CRational second(2, 4);
	CRational third(3, 4);
	CHECK(!(first != second));
	CHECK(first != third);
}

TEST_CASE("test operator != Rational and int numbers")
{
	CRational first(4, 2);
	int second = 2;
	int third = 3;
	CHECK(!(first != second));
	CHECK(first != third);
}

TEST_CASE("test operator != int and Rational numbers")
{
	int first = 2;
	CRational second(4, 2);
	CRational third(3, 4);
	CHECK(!(first != second));
	CHECK(first != third);
}

TEST_CASE("test operator < 2 Rational numbers")
{
	CRational first(1, 2);
	CRational second(2, 4);
	CRational third(3, 4);
	CHECK(first < third);
	CHECK(!(third < first));
	CHECK(!(first < second));
}

TEST_CASE("test operator < Rational and int numbers")
{
	CRational first(5, 2);
	int second = 2;
	int third = 3;
	CHECK(first < third);
	CHECK(!(third < first));
	CHECK(!(first < second));
}

TEST_CASE("test operator < int and Rational numbers")
{
	int first = 1;
	CRational second(3, 4);
	CRational third(7, 4);
	CHECK(first < third);
	CHECK(!(third < first));
	CHECK(!(first < second));
}

TEST_CASE("test operator > 2 Rational numbers")
{
	CRational first(1, 2);
	CRational second(2, 4);
	CRational third(3, 4);
	CHECK(third > first);
	CHECK(!(first > third));
	CHECK(!(first > second));
}

TEST_CASE("test operator > Rational and int numbers")
{
	CRational first(5, 2);
	int second = 2;
	int third = 3;
	CHECK(first > second);
	CHECK(!(first > third));
}

TEST_CASE("test operator > int and Rational numbers")
{
	int first = 2;
	CRational second(2, 4);
	CRational third(9, 4);
	CHECK(first > second);
	CHECK(!(first > third));
}

TEST_CASE("test operator <= 2 Rational numbers")
{
	CRational first(1, 2);
	CRational second(2, 4);
	CRational third(3, 4);
	CHECK(first <= third);
	CHECK(!(third <= first));
	CHECK(first <= second);
}

TEST_CASE("test operator <= Rational and int numbers")
{
	CRational first(4, 2);
	int second = 1;
	int third = 2;
	int fourth = 3;
	CHECK(!(first <= second));
	CHECK(first <= third);
	CHECK(first <= fourth);
}

TEST_CASE("test operator <= int and Rational numbers")
{
	int first = 2;
	CRational second(2, 4);
	CRational third(8, 4);
	CRational fourth(11, 4);
	CHECK(!(first <= second));
	CHECK(first <= third);
	CHECK(first <= fourth);
}

TEST_CASE("test operator >= 2 Rational numbers")
{
	CRational first(1, 2);
	CRational second(2, 4);
	CRational third(3, 4);
	CHECK(third >= first);
	CHECK(!(first >= third));
	CHECK(first >= second);
}

TEST_CASE("test operator >= Rational and int numbers")
{
	CRational first(2);
	int second = 1;
	int third = 2;
	int fourth = 3;
	CHECK(first >= second);
	CHECK(first >= third);
	CHECK(!(first >= fourth));
}

TEST_CASE("test operator >= int and Rational numbers")
{
	int first = 2;
	CRational second(2, 4);
	CRational third(2);
	CRational fourth(7, 3);
	CHECK(first >= second);
	CHECK(first >= third);
	CHECK(!(first >= fourth));
}

TEST_CASE("test operator << and >>")
{
	CRational first(1, 2);
	CRational second;
	std::stringstream strm;
	strm << first;
	strm >> second;
	CHECK(first == second);
}

void CheckCompoundFraction(CRational const& number, int first, CRational const& second)
{
	auto result = number.ToCompoundFraction();
	CHECK(result.first == first);
	CHECK(result.second == second);
}

TEST_CASE("test ToCompoundFraction")
{
	CheckCompoundFraction(CRational(5, 2), 2, CRational(1, 2));
	CheckCompoundFraction(CRational(-5, 2), -2, CRational(-1, 2));
}
