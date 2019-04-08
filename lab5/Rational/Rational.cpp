#include "stdafx.h"
#include "Rational.h"

CRational::CRational()
	: m_numerator(0)
	, m_denominator(1)
{
}

CRational::CRational(int value)
	: m_numerator(value)
	, m_denominator(1)
{
}

CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (m_denominator == 0)
		throw std::invalid_argument("denominator can not be 0");

	if (m_denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}

	int divisor = std::gcd(m_numerator, m_denominator);
	m_numerator /= divisor;
	m_denominator /= divisor;
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

double CRational::ToDouble() const
{
	return (double)m_numerator / (double)m_denominator;
}

std::pair<int, CRational> CRational::GetMixedFraction() const
{
	int number1 = 2;
	CRational number2(3);
	std::pair<int, CRational> result = std::make_pair(number1, number2);
	return result;
}

CRational const CRational::operator-() const
{
	return CRational(-m_numerator, m_denominator);
}

CRational const CRational::operator+() const
{
	return *this;
}

CRational& CRational::operator+=(CRational const& number)
{
	return *this;
}

CRational& CRational::operator+=(int number)
{
	return *this;
}

CRational& CRational::operator-=(CRational const& number)
{
	return *this;
}

CRational& CRational::operator-=(int number)
{
	return *this;
}

CRational& CRational::operator*=(CRational const& number)
{
	return *this;
}

CRational& CRational::operator*=(int number)
{
	return *this;
}

CRational& CRational::operator/=(CRational const& number)
{
	return *this;
}

CRational& CRational::operator/=(int number)
{
	return *this;
}

CRational const operator+(CRational const& number1, CRational const& number2)
{
	int numerator = number1.GetNumerator() * number2.GetDenominator() + number2.GetNumerator() * number1.GetDenominator();
	int denominator = number1.GetDenominator() * number2.GetDenominator();
	CRational result(numerator, denominator);
	return result;
}

CRational const operator+(CRational const& number1, int intNumber2)
{
	CRational number2(intNumber2);
	CRational result = number1 + number2;
	return result;
}

CRational const operator+(int intNumber1, CRational const& number2)
{
	CRational result = number2 + intNumber1;
	return result;
}

CRational const operator-(CRational const& number1, CRational const& number2)
{
	int numerator = number1.GetNumerator() * number2.GetDenominator() - number2.GetNumerator() * number1.GetDenominator();
	int denominator = number1.GetDenominator() * number2.GetDenominator();
	CRational result(numerator, denominator);
	return result;
}

CRational const operator-(CRational const& number1, int intNumber2)
{
	CRational number2(intNumber2);
	return number1 - number2;
}

CRational const operator-(int intNumber1, CRational const& number2)
{
	CRational number1(intNumber1);
	return number1 - number2;
}

CRational const operator*(CRational const& number1, CRational const& number2)
{
	int numerator = number1.GetNumerator() * number2.GetNumerator();
	int denominator = number1.GetDenominator() * number2.GetDenominator();
	CRational result(numerator, denominator);
	return result;
}

CRational const operator*(CRational const& number1, int intNumber2)
{
	CRational number2(intNumber2);
	return number1 * number2;
}

CRational const operator*(int number1, CRational const& number2)
{
	return number2 * number1;
}

CRational const operator/(CRational const& number1, CRational const& number2)
{
	int numerator = number1.GetNumerator() * number2.GetDenominator();
	int denominator = number1.GetDenominator() * number2.GetNumerator();
	CRational result(numerator, denominator);
	return result;
}

CRational const operator/(CRational const& number1, int intNumber2)
{
	CRational number2(intNumber2);
	return number1 / number2;
}

CRational const operator/(int intNumber1, CRational const& number2)
{
	CRational number1(intNumber1);
	return number1 / number2;
}

bool const operator==(CRational const& number1, CRational const& number2)
{
	return number1.GetNumerator() * number2.GetDenominator() == number2.GetNumerator() * number1.GetDenominator();
}

bool const operator==(CRational const& number1, int intNumber2)
{
	CRational number2(intNumber2);
	return number1.GetNumerator() * number2.GetDenominator() == number2.GetNumerator() * number1.GetDenominator();
}

bool const operator==(int intNumber1, CRational const& number2)
{
	CRational number1(intNumber1);
	return number1.GetNumerator() * number2.GetDenominator() == number2.GetNumerator() * number1.GetDenominator();
}

bool const operator!=(CRational const& number1, CRational const& number2)
{
	return number1.GetNumerator() * number2.GetDenominator() != number2.GetNumerator() * number1.GetDenominator();
}

bool const operator<(CRational const& number1, CRational const& number2)
{
	return number1.GetNumerator() * number2.GetDenominator() < number2.GetNumerator() * number1.GetDenominator();
}

bool const operator>(CRational const& number1, CRational const& number2)
{
	return number1.GetNumerator() * number2.GetDenominator() > number2.GetNumerator() * number1.GetDenominator();
}

bool const operator<=(CRational const& number1, CRational const& number2)
{
	return number1.GetNumerator() * number2.GetDenominator() <= number2.GetNumerator() * number1.GetDenominator();
}

bool const operator>=(CRational const& number1, CRational const& number2)
{
	return number1.GetNumerator() * number2.GetDenominator() >= number2.GetNumerator() * number1.GetDenominator();
}

std::ostream& operator<<(std::ostream& strm, CRational const& number)
{
	strm << number.GetNumerator() << '/' << number.GetDenominator();
	return strm;
}

std::istream& operator>>(std::istream& strm, CRational& number)
{
	int numerator, denominator;
	if (strm >> numerator && strm.get() == '/' && strm >> denominator)
		number = CRational(numerator, denominator);
	return strm;
}