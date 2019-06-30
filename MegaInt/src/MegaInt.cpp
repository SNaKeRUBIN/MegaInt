#include <iostream>
#include "MegaInt.h"
#include "DequeUtils.cpp"

MegaInt::MegaInt()
{
	m_sign = '+';
	m_magnitude.push_back('0');
}

/*
	Constructor

	@param new_sign the sign of the integer
	@param new_magnitude the magnitude of the integer
*/
MegaInt::MegaInt(char const new_sign, std::deque<char> &new_magnitude)
{
	m_sign = new_sign;
	m_magnitude = new_magnitude;
}

/*
	Constructor

	@param num the num to convert to MegaInt type
*/
MegaInt::MegaInt(std::string const &num)
{
	MegaInt();
	Insert(num);
	this->Normalize();
}

/*
	Inserts the number as string into a MegaInt number

	@param new_number the number as a string to be added to a MegaInt number
*/
void MegaInt::Insert(std::string const &new_number)
{
	int start = 0;
	m_magnitude.clear();

	if (new_number[0] == '+' || new_number[0] == '-')
	{
		m_sign = new_number[0];
		start = 1;
	}
	else
	{
		m_sign = '+';
	}

	for (size_t i = start; i < new_number.length(); i++)
	{
		m_magnitude.push_back(new_number[i]);
	}
}

/*
	Resets the magnitude and sign of a MegaInt to zero and positive sign
*/
void MegaInt::Clear()
{
	m_sign = '+';
	m_magnitude.clear();
	m_magnitude.push_back('0');
}

/*
	Removes the leading zeroes from a MegaInt so that leftmost digit is a
	non-zero digit
*/
void MegaInt::Normalize()
{
	if (m_magnitude.size() > 1)
	{
		for (std::deque<char>::iterator iter = m_magnitude.begin(); iter != m_magnitude.end() - 1;)
		{
			if (*iter == '0')
			{
				iter = m_magnitude.erase(iter);
			}
			else
			{
				break;
			}
		}
	}

	if (m_magnitude.size() == 1 && m_sign == '-')
	{
		if (m_magnitude[0] == '0')
		{
			m_sign = '+';
		}
	}
}

/*
	Inverts the sign of a MegaInt
*/
void MegaInt::Negate()
{
	if (m_sign == '+')
	{
		m_sign = '-';
	}
	else
	{
		m_sign = '+';
	}
}

/*
	Function to add two MegaInt numbers

	@param B the MegaInt to be added

	@return The MegaInt that is the sum of the two numbers
*/
MegaInt MegaInt::Add(MegaInt B) const
{
	char sign_A = m_sign;
	char sign_B = B.GetSign();
	char sign_C;

	std::deque<char> mag_A = m_magnitude;
	std::deque<char> mag_B = B.GetMagnitude();
	std::deque<char> mag_C;

	if (sign_A == sign_B)
	{
		sign_C = sign_A;
		mag_C = Plus(mag_A, mag_B);
	}
	else
	{
		if (GreaterThan(mag_A, mag_B))
		{
			sign_C = sign_A;
			mag_C = Minus(mag_A, mag_B);
		}
		else if (LesserThan(mag_A, mag_B))
		{
			if (sign_A == '+')
			{
				sign_C = '-';
			}
			else
			{
				sign_C = '+';
			}
			mag_C = Minus(mag_B, mag_A);
		}
		else
		{
			sign_C = '+';
			mag_C.push_front('0');
		}
	}

	MegaInt C{sign_C, mag_C};
	C.Normalize();
	return C;
}

/*
	Function to subtract two MegaInt numbers

	@param B the MegaInt that has to be subtracted

	@return The result of subtraction of two MegaInts
*/
MegaInt MegaInt::Subtract(MegaInt B) const
{
	char sign_A = m_sign;
	char sign_B = B.GetSign();
	char sign_C;

	std::deque<char> mag_A = m_magnitude;
	std::deque<char> mag_B = B.GetMagnitude();
	std::deque<char> mag_C;

	if (sign_A != sign_B)
	{
		sign_C = sign_A;
		mag_C = Plus(mag_A, mag_B);
	}
	else
	{
		if (GreaterThan(mag_A, mag_B))
		{
			sign_C = sign_A;
			mag_C = Minus(mag_A, mag_B);
		}
		else if (LesserThan(mag_A, mag_B))
		{
			if (sign_A == '+')
			{
				sign_C = '-';
			}
			else
			{
				sign_C = '+';
			}

			mag_C = Minus(mag_B, mag_A);
		}
		else
		{
			sign_C = '+';
			mag_C.push_front('0');
		}
	}

	MegaInt C{sign_C, mag_C};
	C.Normalize();
	return C;
}

/*
	Function to multiply two MegaInt numbers

	@param B the factor

	@return The product as a MegaInt
*/
MegaInt MegaInt::Multiply(MegaInt B) const
{
	// product(multiplier, multiplicand)
	char const sign_A = m_sign;
	char const sign_B = B.GetSign();
	char sign_C;

	std::deque<char> mag_A = m_magnitude;
	std::deque<char> mag_B = B.GetMagnitude();
	std::deque<char> mag_C;

	if (GreaterThan(mag_A, mag_B))
	{
		mag_C = Product2(mag_B, mag_A);
	}
	else
	{
		mag_C = Product2(mag_A, mag_B);
	}

	if (sign_A == sign_B)
	{
		sign_C = '+';
	}
	else
	{
		sign_C = '-';
	}

	MegaInt C{sign_C, mag_C};
	C.Normalize();
	return C;
}

/*
	Function to divide two MegaInt numbers

	@param B The divisor

	@return the quotient as a MegaInt number
*/
MegaInt MegaInt::Division(MegaInt B) const
{
	// quotient(dividend, divisor)
	// quotient(A, B)
	char const sign_A = m_sign;
	char const sign_B = B.GetSign();
	char sign_C;

	std::deque<char> mag_A = m_magnitude;
	std::deque<char> mag_B = B.GetMagnitude();
	std::deque<char> mag_C;

	if (sign_A == sign_B)
	{
		sign_C = '+';
	}
	else
	{
		sign_C = '-';
	}

	DivisionResult result = Quotient2(mag_A, mag_B);
	mag_C = result.quotient;

	MegaInt C{sign_C, mag_C};
	C.Normalize();
	return C;
}

/*
	Function to return the remainder of a division of two MegaInt numbers

	@param B the divisor

	@return the remainder
*/
MegaInt MegaInt::Modulus(MegaInt B) const
{
	// quotient(dividend, divisor)
	// quotient(A, B)
	char const sign_A = m_sign;
	char const sign_B = B.GetSign();
	char sign_C;

	std::deque<char> mag_A = m_magnitude;
	std::deque<char> mag_B = B.GetMagnitude();
	std::deque<char> mag_C;

	if (sign_A == sign_B)
	{
		sign_C = '+';
	}
	else
	{
		sign_C = '-';
	}

	DivisionResult result = Quotient2(mag_A, mag_B);
	mag_C = result.remainder;

	MegaInt C{sign_C, mag_C};
	C.Normalize();
	return C;
}

/*
	Overloading operator +=

	@param n the MegaInt to be added

	@return the sum as a MegaInt
*/
MegaInt &MegaInt::operator+=(const MegaInt &n)
{
	*this = *this + n;
	return *this;
}

/*
	Overloading operator -=

	@param n the MegaInt to be subtracted

	@return the difference as a MegaInt
*/
MegaInt &MegaInt::operator-=(const MegaInt &n)
{
	*this = *this - n;
	return *this;
}

/*
	Overloading operator *=

	@param n the MegaInt to be multiplied

	@return the product as a MegaInt
*/
MegaInt &MegaInt::operator*=(const MegaInt &n)
{
	*this = (*this) * n;
	return *this;
}

/*
	Overloading operator /=

	@param n the divisor as a MegInt

	@return the quotient as a MegaInt
*/
MegaInt &MegaInt::operator/=(const MegaInt &n)
{
	*this = (*this) / n;
	return *this;
}

/*
	Overloading operator %=

	@param n the divisor as a MegaInt

	@return the remainder as a MegaInt
*/
MegaInt &MegaInt::operator%=(const MegaInt &n)
{
	*this = (*this) % n;
	return *this;
}

/*
	Overloading operator ++ as a prefix operator

	@return the sum of the MegaInt with one
*/
MegaInt &MegaInt::operator++()
{
	// prefix
	MegaInt one{"+1"};
	(*this) += one;
	return *this;
}

/*
	Overloading operator ++ as a postfix operator

	@return the sum of the MegaInt with one
*/
MegaInt MegaInt::operator++(int)
{
	// postfix
	MegaInt temp;
	temp = *this;
	++(*this);
	return temp;
}

/*
	Overloading operator -- as a prefix operator

	@return the difference of the MegaInt with one
*/
MegaInt &MegaInt::operator--()
{
	// prefix
	MegaInt one{"+1"};
	(*this) -= one;
	return *this;
}

/*
	Overloading operator -- as a postfix operator

	@return the difference of the MegaInt with one
*/
MegaInt MegaInt::operator--(int)
{
	// postfix
	MegaInt temp;
	temp = *this;
	--(*this);
	return temp;
}

/*
	Funciton to get the digit at a specified index of the magnitude

	@param index the index of the digit

	@return the digit at given index as a char
*/
char MegaInt::operator[](const int index)
{
	// chk if index is in right range
	if (index >= 0 && static_cast<size_t>(index) < m_magnitude.size())
	{
		return m_magnitude[index];
	}
	else
	{
		char temp{'0'};
		std::cout << "out of bound index entered" << std::endl;

		return temp;
	}
}

/*
	Returns the sign of the MegaInt

	@return the sign
*/
char MegaInt::GetSign() const
{
	return m_sign;
}

/*
	Return the magnitude of the MegaInt

	@return the magnitude
*/
std::deque<char> MegaInt::GetMagnitude() const
{
	return m_magnitude;
}

/*
	Overloading the operator +

	@param m the MegaInt to be added
	@param n the MegaInt to be added

	@return the sum of the two MegaInts
*/
MegaInt operator+(const MegaInt &m, const MegaInt &n)
{
	MegaInt temp;
	temp = m.Add(n);

	return temp;
}

/*
	Overloading the operator -

	@param m the minuend MegaInt
	@param n the subtrahend MegaInt

	@return the difference of the two MegaInts
*/
MegaInt operator-(const MegaInt &m, const MegaInt &n)
{
	MegaInt temp;
	temp = m.Subtract(n);

	return temp;
}

/*
	Overloading the operator *

	@param m the MegaInt to be multiplied
	@param n the MegaInt to be multiplied

	@return the product of the two MegaInts
*/
MegaInt operator*(const MegaInt &m, const MegaInt &n)
{
	MegaInt temp;
	temp = m.Multiply(n);

	return temp;
}

/*
	Overloading the operator /

	@param m the dividend MegaInt
	@param n the divisor MegaInt

	@return the quotient of the two MegaInts
*/
MegaInt operator/(const MegaInt &m, const MegaInt &n)
{
	MegaInt temp;
	temp = m.Division(n);

	return temp;
}

/*
	Overloading the operator %

	@param m the dividend MegaInt
	@param n the divisor MegaInt

	@return the remainder of the two MegaInts
*/
MegaInt operator%(const MegaInt &m, const MegaInt &n)
{
	MegaInt temp;
	temp = m.Modulus(n);

	return temp;
}

/*
	Overloading the operator <<
	Returns the MegaInt as a output stream so that it could be easily read out

	@param out the output stream
	@param m the MagaInt to be printed

	@return the ouput stream containing the MegaInt
*/
std::ostream &operator<<(std::ostream &out, const MegaInt &m)
{
	const char copySign = m.GetSign();
	std::deque<char> copyMagnitude = m.GetMagnitude();

	out << copySign;

	for (auto iter = copyMagnitude.begin(); iter != copyMagnitude.end(); iter++)
	{
		out << *iter;
	}

	return out;
}

/*
	Overloading the operator >
	Returns true if param A is greater than param B

	@param m a number as a MegaInt
	@param n a number as a MegaInt

	@return boolean value
*/
bool operator>(const MegaInt &m, MegaInt &n)
{
	if (m.GetSign() == '+' && n.GetSign() == '+')
	{
		return GreaterThan(m.GetMagnitude(), n.GetMagnitude());
	}
	else if (m.GetSign() == '+' && n.GetSign() == '-')
	{
		return true;
	}
	else if (m.GetSign() == '-' && n.GetSign() == '+')
	{
		return false;
	}
	else if (m.GetSign() == '-' && n.GetSign() == '-')
	{
		return GreaterThan(n.GetMagnitude(), m.GetMagnitude());
	}
	else
	{
		return false;
	}
}

/*
	Overloading the operator <
	Returns true if param A is lesser than param B

	@param m a number as a MegaInt
	@param n a number as a MegaInt

	@return boolean value
*/
bool operator<(const MegaInt &m, MegaInt &n)
{
	if (m.GetSign() == '+' && n.GetSign() == '+')
	{
		return LesserThan(m.GetMagnitude(), n.GetMagnitude());
	}
	else if (m.GetSign() == '+' && n.GetSign() == '-')
	{
		return false;
	}
	else if (m.GetSign() == '-' && n.GetSign() == '+')
	{
		return true;
	}
	else if (m.GetSign() == '-' && n.GetSign() == '-')
	{
		return LesserThan(n.GetMagnitude(), m.GetMagnitude());
	}
	else
	{
		return false;
	}
}

/*
	Overloading the operator ==
	Returns true if param A is equal to param B

	@param m a number as a MegaInt
	@param n a number as a MegaInt

	@return boolean value
*/
bool operator==(const MegaInt &m, MegaInt &n)
{
	if (m.GetSign() == '+' && n.GetSign() == '+')
	{
		return EqualTo(m.GetMagnitude(), n.GetMagnitude());
	}
	else if (m.GetSign() == '+' && n.GetSign() == '-')
	{
		return false;
	}
	else if (m.GetSign() == '-' && n.GetSign() == '+')
	{
		return false;
	}
	else if (m.GetSign() == '-' && n.GetSign() == '-')
	{
		return EqualTo(m.GetMagnitude(), n.GetMagnitude());
	}
	else
	{
		return false;
	}
}

/*
	Overloading the operator <=
	Returns true if param A is lesser than or equal to param B

	@param m a number as a MegaInt
	@param n a number as a MegaInt

	@return boolean value
*/
bool operator<=(const MegaInt &m, MegaInt &n)
{
	return !(m > n);
}

/*
	Overloading the operator >=
	Returns true if param A is greater than or equal to param B

	@param m a number as a MegaInt
	@param n a number as a MegaInt

	@return boolean value
*/
bool operator>=(const MegaInt &m, MegaInt &n)
{
	return !(m < n);
}

/*
	Overloading the operator !=
	Returns true if param A is not equal to param B

	@param m a number as a MegaInt
	@param n a number as a MegaInt

	@return boolean value
*/
bool operator!=(const MegaInt &m, MegaInt &n)
{
	return !(m == n);
}
