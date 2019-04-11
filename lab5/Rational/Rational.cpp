#include "stdafx.h"
#include "Rational.h"

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

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	int number1 = m_numerator / m_denominator;
	CRational number2(m_numerator - number1 * m_denominator, m_denominator);
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
	m_numerator = m_numerator * number.GetDenominator() + number.GetNumerator() * m_denominator;
	m_denominator = m_denominator * number.GetDenominator();
	
	int divisor = std::gcd(m_numerator, m_denominator);
	m_numerator /= divisor;
	m_denominator /= divisor;
	
	return *this;
}

CRational& CRational::operator-=(CRational const& number)
{
	m_numerator = m_numerator * number.GetDenominator() - number.GetNumerator() * m_denominator;
	m_denominator = m_denominator * number.GetDenominator();

	int divisor = std::gcd(m_numerator, m_denominator);
	m_numerator /= divisor;
	m_denominator /= divisor;

	return *this;
}

CRational& CRational::operator*=(CRational const& number)
{
	m_numerator = m_numerator * number.GetNumerator();
	m_denominator = m_denominator * number.GetDenominator();

	int divisor = std::gcd(m_numerator, m_denominator);
	m_numerator /= divisor;
	m_denominator /= divisor;

	return *this;
}

CRational& CRational::operator/=(CRational const& number)
{
	m_numerator = m_numerator * number.GetDenominator();
	m_denominator = m_denominator * number.GetNumerator();

	int divisor = std::gcd(m_numerator, m_denominator);
	m_numerator /= divisor;
	m_denominator /= divisor;

	return *this;
}

CRational const operator+(CRational const& number1, CRational const& number2)
{
	int numerator = number1.GetNumerator() * number2.GetDenominator() + number2.GetNumerator() * number1.GetDenominator();
	int denominator = number1.GetDenominator() * number2.GetDenominator();
	CRational result(numerator, denominator);
	return result;
}

CRational const operator-(CRational const& number1, CRational const& number2)
{
	int numerator = number1.GetNumerator() * number2.GetDenominator() - number2.GetNumerator() * number1.GetDenominator();
	int denominator = number1.GetDenominator() * number2.GetDenominator();
	CRational result(numerator, denominator);
	return result;
}

CRational const operator*(CRational const& number1, CRational const& number2)
{
	int numerator = number1.GetNumerator() * number2.GetNumerator();
	int denominator = number1.GetDenominator() * number2.GetDenominator();
	CRational result(numerator, denominator);
	return result;
}

CRational const operator/(CRational const& number1, CRational const& number2)
{
	int numerator = number1.GetNumerator() * number2.GetDenominator();
	int denominator = number1.GetDenominator() * number2.GetNumerator();
	CRational result(numerator, denominator);
	return result;
}

bool const operator==(CRational const& number1, CRational const& number2)
{
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