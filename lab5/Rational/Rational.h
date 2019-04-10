#pragma once

class CRational
{
public:
	CRational();
	CRational(int value);
	CRational(int numerator, int denominator);

	int GetNumerator() const;
	int GetDenominator() const;
	double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const;

	CRational const operator-() const;
	CRational const operator+() const;
	CRational& operator+=(CRational const& number);
	CRational& operator+=(int number);
	CRational& operator-=(CRational const& number);
	CRational& operator-=(int number);
	CRational& operator*=(CRational const& number);
	CRational& operator*=(int number);
	CRational& operator/=(CRational const& number);
	CRational& operator/=(int number);

private:
	int m_numerator, m_denominator;
};

CRational const operator+(CRational const& number1, CRational const& number2);
CRational const operator+(CRational const& number1, int number2);
CRational const operator+(int number1, CRational const& number2);

CRational const operator-(CRational const& number1, CRational const& number2);
CRational const operator-(CRational const& number1, int number2);
CRational const operator-(int number1, CRational const& number2);

CRational const operator*(CRational const& number1, CRational const& number2);
CRational const operator*(CRational const& number1, int number2);
CRational const operator*(int number1, CRational const& number2);

CRational const operator/(CRational const& number1, CRational const& number2);
CRational const operator/(CRational const& number1, int number2);
CRational const operator/(int number1, CRational const& number2);

bool const operator==(CRational const& number1, CRational const& number2);
bool const operator==(CRational const& number1, int number2);
bool const operator==(int number1, CRational const& number2);

bool const operator!=(CRational const& number1, CRational const& number2);
bool const operator!=(CRational const& number1, int number2);
bool const operator!=(int number1, CRational const& number2);

bool const operator<(CRational const& number1, CRational const& number2);
bool const operator<(CRational const& number1, int number2);
bool const operator<(int number1, CRational const& number2);

bool const operator>(CRational const& number1, CRational const& number2);
bool const operator>(CRational const& number1, int number2);
bool const operator>(int number1, CRational const& number2);

bool const operator<=(CRational const& number1, CRational const& number2);
bool const operator<=(CRational const& number1, int number2);
bool const operator<=(int number1, CRational const& number2);

bool const operator>=(CRational const& number1, CRational const& number2);
bool const operator>=(CRational const& number1, int number2);
bool const operator>=(int number1, CRational const& number2);

std::ostream& operator<<(std::ostream& strm, CRational const& number);
std::istream& operator>>(std::istream& strm, CRational& number);