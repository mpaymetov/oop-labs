#pragma once

class CRational
{
public:
	CRational(int numerator = 0, int denominator = 1);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const;

	CRational const operator-() const;
	CRational const operator+() const;
	CRational& operator+=(CRational const& number);
	CRational& operator-=(CRational const& number);
	CRational& operator*=(CRational const& number);
	CRational& operator/=(CRational const& number);

private:
	int m_numerator, m_denominator;
};

CRational const operator+(CRational const& number1, CRational const& number2);
CRational const operator-(CRational const& number1, CRational const& number2);
CRational const operator*(CRational const& number1, CRational const& number2);
CRational const operator/(CRational const& number1, CRational const& number2);

bool const operator==(CRational const& number1, CRational const& number2);
bool const operator!=(CRational const& number1, CRational const& number2);
bool const operator<(CRational const& number1, CRational const& number2);
bool const operator>(CRational const& number1, CRational const& number2);
bool const operator<=(CRational const& number1, CRational const& number2);
bool const operator>=(CRational const& number1, CRational const& number2);

std::ostream& operator<<(std::ostream& strm, CRational const& number);
std::istream& operator>>(std::istream& strm, CRational& number);