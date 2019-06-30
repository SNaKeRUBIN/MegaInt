#include <iostream>
#include "MegaInt.h"

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
MegaInt::MegaInt(char const new_sign, std::deque<char> new_magnitude)
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
	insert(num);
	this->normalize();
}

/*
	Inserts the number as string into a MegaInt number

	@param new_number the number as a string to be added to a MegaInt number
*/
void MegaInt::insert(std::string const &new_number)
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
void MegaInt::clear()
{
	m_sign = '+';
	m_magnitude.clear();

	m_magnitude.push_back('0');
}

/*
	Removes the leading zeroes from a MegaInt so that leftmost digit is a
	non-zero digit
*/
void MegaInt::normalize()
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
	Removes the leading zeroes from a deque so that the leftmost digit is a
	non-zero digit

	@param A the deque that has to be normalized

	@return the normalized deque
*/
std::deque<char> MegaInt::normalize1(std::deque<char> A) const
{
	if (A.size() > 1)
	{
		for (std::deque<char>::iterator iter = A.begin(); iter != A.end() - 1;)
		{
			if (*iter == '0')
			{
				iter = A.erase(iter);
			}
			else
			{
				break;
			}
		}
	}

	return A;
}

/*
	Inverts the sign of a MegaInt
*/
void MegaInt::negate()
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
	Function to get the int form of a character

	@param c the character to be converted to a int

	@return returns the int form of a character
*/
int MegaInt::get_int(char const c) const
{
	char c0 = '0';
	// TODO
	// use static_cast
	int const integerForm = c - static_cast<int>(c0);

	return integerForm;
}

/*
	Function to get the char form of an integer

	@param i the int to be converted to a char

	@return returns the char form of an integer
*/
char MegaInt::get_char(int const i) const
{
	char c0 = '0';
	char const charForm = static_cast<char>(i + c0);

	return charForm;
}

/*
	Function to add two MegaInt numbers

	@param B the MegaInt to be added

	@return The MegaInt that is the sum of the two numbers
*/
MegaInt MegaInt::add(MegaInt B) const
{
	char sign_A = m_sign;
	char sign_B = B.getSign();
	char sign_C;

	std::deque<char> mag_A = m_magnitude;
	std::deque<char> mag_B = B.getMagnitude();
	std::deque<char> mag_C;

	if (sign_A == sign_B)
	{
		sign_C = sign_A;
		mag_C = plus(mag_A, mag_B);
	}
	else
	{
		if (greaterThan(mag_A, mag_B))
		{
			sign_C = sign_A;
			mag_C = minus(mag_A, mag_B);
		}
		else if (lesserThan(mag_A, mag_B))
		{
			if (sign_A == '+')
			{
				sign_C = '-';
			}
			else
			{
				sign_C = '+';
			}
			mag_C = minus(mag_B, mag_A);
		}
		else
		{
			sign_C = '+';
			mag_C.push_front('0');
		}
	}

	MegaInt C{sign_C, mag_C};
	C.normalize();
	return C;
}

/*
	Function to add the numbers of two deques

	@param A The number to be added
	@param B The number to be added

	@return a deque containing the sum if two numbers
*/
std::deque<char> MegaInt::plus(std::deque<char> A, std::deque<char> B) const
{
	size_t const m = A.size();
	size_t const n = B.size();

	int p;
	if (m < n)
	{
		p = n + 1;
	}
	else
	{
		p = m + 1;
	}

	std::deque<char> result;

	int carry = 0;
	int i = p - 1;
	int j = m - 1;
	int k = n - 1;

	int temp = 0;
	while (j >= 0 && k >= 0)
	{
		temp = get_int(A[j]) + get_int(B[k]) + carry;

		result.push_front(get_char(temp % 10));
		carry = temp / 10;
		i--;
		j--;
		k--;
	}

	while (j >= 0)
	{
		temp = get_int(A[j]) + carry;

		result.push_front(get_char(temp % 10));
		carry = temp / 10;
		i--;
		j--;
	}

	while (k >= 0)
	{
		temp = get_int(B[k]) + carry;

		result.push_front(get_char(temp % 10));
		carry = temp / 10;
		i--;
		k--;
	}

	result.push_front(get_char(carry));
	return result;
}

/*
	Function to subtract two MegaInt numbers

	@param B the MegaInt that has to be subtracted

	@return The result of subtraction of two MegaInts
*/
MegaInt MegaInt::subtract(MegaInt B) const
{
	char sign_A = m_sign;
	char sign_B = B.getSign();
	char sign_C;

	std::deque<char> mag_A = m_magnitude;
	std::deque<char> mag_B = B.getMagnitude();
	std::deque<char> mag_C;

	if (sign_A != sign_B)
	{
		sign_C = sign_A;
		mag_C = plus(mag_A, mag_B);
	}
	else
	{
		if (greaterThan(mag_A, mag_B))
		{
			sign_C = sign_A;
			mag_C = minus(mag_A, mag_B);
		}
		else if (lesserThan(mag_A, mag_B))
		{
			if (sign_A == '+')
			{
				sign_C = '-';
			}
			else
			{
				sign_C = '+';
			}

			mag_C = minus(mag_B, mag_A);
		}
		else
		{
			sign_C = '+';
			mag_C.push_front('0');
		}
	}

	MegaInt C{sign_C, mag_C};
	C.normalize();
	return C;
}

/*
	Function to subtract two numbers in form of deques

	@param A the minuend
	@param B the subtrahend

	@return the difference
*/
std::deque<char> MegaInt::minus(std::deque<char> A, std::deque<char> B) const
{
	// A-B
	size_t const m = A.size();
	size_t const n = B.size();

	int p;
	if (m < n)
	{
		p = n;
	}
	else
	{
		p = m;
	}

	std::deque<char> result;

	int borrow = 0;
	int i = p - 1;
	int j = m - 1;
	int k = n - 1;

	int temp = 0;
	while (j >= 0 && k >= 0)
	{
		temp = get_int(A[j]) - (get_int(B[k]) + borrow);

		borrow = 0;

		if (temp < 0)
		{
			borrow = 1;
			temp = 10 + temp;
		}
		result.push_front(get_char(temp));

		i--;
		j--;
		k--;
	}

	while (j >= 0)
	{
		temp = get_int(A[j]) - borrow;

		borrow = 0;

		if (temp < 0)
		{
			borrow = 1;
			temp = 10 + temp;
		}

		result.push_front(get_char(temp));
		i--;
		j--;
	}

	if (borrow == 1 || k >= 0)
	{
		std::cout << " X cannot be less than Y in (X-Y)" << std::endl;
	}

	return result;
}

/*
	Function to multiply two MegaInt numbers

	@param B the factor

	@return The product as a MegaInt
*/
MegaInt MegaInt::multiply(MegaInt B) const
{
	// product(multiplier, multiplicand)
	char const sign_A = m_sign;
	char const sign_B = B.getSign();
	char sign_C;

	std::deque<char> mag_A = m_magnitude;
	std::deque<char> mag_B = B.getMagnitude();
	std::deque<char> mag_C;

	if (greaterThan(mag_A, mag_B))
	{
		mag_C = product2(mag_B, mag_A);
	}
	else
	{
		mag_C = product2(mag_A, mag_B);
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
	C.normalize();
	return C;
}

/*
	Function to multiply two numbers as deques
	It employs the method of adding one factor to itself other factor times

	@param A the factor
	@param B the factor

	@return The product as a deque
*/
std::deque<char> MegaInt::product(std::deque<char> A, std::deque<char> B) const
{
	// product1(multiplier, multiplicand)
	std::deque<char> temp;
	temp.push_front('0');

	if (A.size() == 1 && A[0] == '0')
	{
		return temp;
	}

	std::deque<char> temp2;
	temp2.push_front('1');

	while (A.size() > 1 || A[A.size() - 1] != '0')
	{
		temp = plus(temp, B);

		A = minus(A, temp2);
		A = normalize1(A);
	}

	return temp;
}

/*
	Function to multiply two numbers as deques
	It employs the method of getting the product of a factor by each digit of other factor
	and then summing them all. It is also known as traditional paper and perncil algorithm.

	@param A the factor
	@param B the factor

	@return The product as a deque
*/
std::deque<char> MegaInt::product2(std::deque<char> A, std::deque<char> B) const
{
	// product2(multiplier, multiplicand)
	std::deque<std::deque<char>> list;

	std::deque<char> temp;
	std::deque<char> sum;

	size_t const count = A.size();

	for (size_t i = 0; i < count; i++)
	{
		char const c = A[count - i - 1];
		temp.clear();
		temp.push_front(c);

		temp = product(temp, B);
		temp = normalize1(temp);

		for (size_t j = count - i; j < count; j++)
		{
			temp.push_back('0');
		}

		list.push_back(temp);
	}

	sum = list[0];

	for (size_t i = 1; i < list.size(); i++)
	{
		sum = plus(sum, list[i]);
		sum = normalize1(sum);
	}

	return sum;
}

/*
	Function to divide two MegaInt numbers

	@param B The divisor

	@return the quotient as a MegaInt number
*/
MegaInt MegaInt::division(MegaInt B) const
{
	// quotient(dividend, divisor)
	// quotient(A, B)
	char const sign_A = m_sign;
	char const sign_B = B.getSign();
	char sign_C;

	std::deque<char> mag_A = m_magnitude;
	std::deque<char> mag_B = B.getMagnitude();
	std::deque<char> mag_C;

	std::deque<std::deque<char>> list;

	if (sign_A == sign_B)
	{
		sign_C = '+';
	}
	else
	{
		sign_C = '-';
	}

	list = quotient2(mag_A, mag_B);
	mag_C = list[0]; // list[0] = quotient, list[1] = remainder

	MegaInt C{sign_C, mag_C};
	C.normalize();
	return C;
}

/*
	Function to divide two numbers as deques.
	The function uses the method to subtract the dividend by the divisor and count the times
	we need to subtract before result is zero or less than divisors

	@param A the dividend
	@param B the divisor

	@return the quotient
*/
std::deque<std::deque<char>> MegaInt::quotient(std::deque<char> A, std::deque<char> B) const
{
	// quotient(dividend, divisor)
	// subsequent subtraction till we get remainder < divisor
	std::deque<char> dividend{A};
	std::deque<char> divisor{B};

	std::deque<char> quotient;
	quotient.push_front('0');

	std::deque<char> remainder;
	remainder = dividend;

	std::deque<char> increment;
	increment.push_front('1');

	std::deque<std::deque<char>> list;

	while (!(lesserThan(dividend, divisor)))
	{
		dividend = minus(dividend, divisor);
		dividend = normalize1(dividend);

		remainder = dividend;

		quotient = plus(quotient, increment);
		quotient = normalize1(quotient);
	}

	list.push_front(quotient);
	list.push_back(remainder);
	// list[0] = quotient, list[1] = remainder

	// TODO
	// Return a tuple/struct rather than list
	return list;
}

/*
	Function to divide two numbers as deques.
	This employs the method of dividing the least part of dividend greater than divisor by divisor
	and then subtracting the number by a multiple of divisor. It is also known as the traditional
	paper and pencil method.

	@param A the dividend
	@param B the divisor

	@return the quotient
*/
std::deque<std::deque<char>> MegaInt::quotient2(std::deque<char> A, std::deque<char> B) const
{
	// quotient(dividend, divisor)
	std::deque<char> current;
	std::deque<char> quotient_;
	std::deque<char> temp;
	std::deque<std::deque<char>> list;

	for (size_t i = 0; i < A.size(); i++)
	{
		current.push_back(A[i]);
		current = normalize1(current);

		if (greaterThan(B, current))
		{
			quotient_.push_back('0');
			continue;
		}

		list = quotient(current, B);

		quotient_.push_back(list[0][0]);
		quotient_ = normalize1(quotient_);
		current = list[1];
		current = normalize1(current);
	}

	list.clear();
	list.push_back(quotient_);
	list.push_back(current);

	// TODO
	// Return a tuple/struct
	return list;
}

/*
	Function to return the remainder of a division of two MegaInt numbers

	@param B the divisor

	@return the remainder
*/
MegaInt MegaInt::modulus(MegaInt B) const
{
	// quotient(dividend, divisor)
	// quotient(A, B)
	char const sign_A = m_sign;
	char const sign_B = B.getSign();
	char sign_C;

	std::deque<char> mag_A = m_magnitude;
	std::deque<char> mag_B = B.getMagnitude();
	std::deque<char> mag_C;

	std::deque<std::deque<char>> list;

	if (sign_A == sign_B)
	{
		sign_C = '+';
	}
	else
	{
		sign_C = '-';
	}

	list = quotient2(mag_A, mag_B);
	mag_C = list[1]; // list[0] = quotient, list[1] = remainder

	MegaInt C{sign_C, mag_C};
	C.normalize();
	return C;
}

/*
	Returns true if param A is greater than param B

	@param A a number as a deque
	@param B a number as a deque

	@return boolean value
*/
bool MegaInt::greaterThan(const std::deque<char> &A, const std::deque<char> &B) const
{
	if (A.size() > B.size())
	{
		return true;
	}
	else if (A.size() < B.size())
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < A.size(); i++)
		{
			if (A[i] > B[i])
			{
				return true;
			}
			else if (A[i] < B[i])
			{
				return false;
			}
		}
		return false;
	}
}

/*
	Returns true if param A is lesser than param B

	@param A a number as a deque
	@param B a number as a deque

	@return boolean value
*/
bool MegaInt::lesserThan(const std::deque<char> &A, const std::deque<char> &B) const
{
	if (A.size() < B.size())
	{
		return true;
	}
	else if (A.size() > B.size())
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < A.size(); i++)
		{
			if (A[i] < B[i])
			{
				return true;
			}
			else if (A[i] > B[i])
			{
				return false;
			}
		}
		return false;
	}
}

/*
	Returns true if param A is equal to param B

	@param A a number as a deque
	@param B a number as a deque

	@return boolean value
*/
bool MegaInt::equalTo(const std::deque<char> &A, const std::deque<char> &B) const
{
	if (A.size() == B.size())
	{

		for (size_t i = 0; i < A.size(); i++)
		{
			if (A[i] != B[i])
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}

	return true;
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
MegaInt &MegaInt::operator++(int)
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
MegaInt &MegaInt::operator--(int)
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
char &MegaInt::operator[](const int index)
{
	// chk if index is in right range
	if (index >=0 && static_cast<size_t>(index) < m_magnitude.size())
	{
		return m_magnitude[index];
	}
	else
	{
		char temp{'0'};
		// TODO
		// Implement some form of logging or atleast output to stderr
		std::cout << "out of bound index entered" << std::endl;

		return temp;
	}
}

/*
	Returns the sign of the MegaInt

	@return the sign
*/
char MegaInt::getSign() const
{
	return m_sign;
}

/*
	Return the magnitude of the MegaInt

	@return the magnitude
*/
std::deque<char> MegaInt::getMagnitude() const
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
	temp = m.add(n);

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
	temp = m.subtract(n);

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
	temp = m.multiply(n);

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
	temp = m.division(n);

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
	temp = m.modulus(n);

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
	const char copySign = m.getSign();
	std::deque<char> copyMagnitude = m.getMagnitude();

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
	if (m.getSign() == '+' && n.getSign() == '+')
	{
		return m.greaterThan(m.getMagnitude(), n.getMagnitude());
	}
	else if (m.getSign() == '+' && n.getSign() == '-')
	{
		return true;
	}
	else if (m.getSign() == '-' && n.getSign() == '+')
	{
		return false;
	}
	else if (m.getSign() == '-' && n.getSign() == '-')
	{
		return m.greaterThan(n.getMagnitude(), m.getMagnitude());
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
	if (m.getSign() == '+' && n.getSign() == '+')
	{
		return m.lesserThan(m.getMagnitude(), n.getMagnitude());
	}
	else if (m.getSign() == '+' && n.getSign() == '-')
	{
		return false;
	}
	else if (m.getSign() == '-' && n.getSign() == '+')
	{
		return true;
	}
	else if (m.getSign() == '-' && n.getSign() == '-')
	{
		return m.lesserThan(n.getMagnitude(), m.getMagnitude());
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
	if (m.getSign() == '+' && n.getSign() == '+')
	{
		return m.equalTo(m.getMagnitude(), n.getMagnitude());
	}
	else if (m.getSign() == '+' && n.getSign() == '-')
	{
		return false;
	}
	else if (m.getSign() == '-' && n.getSign() == '+')
	{
		return false;
	}
	else if (m.getSign() == '-' && n.getSign() == '-')
	{
		return m.equalTo(m.getMagnitude(), n.getMagnitude());
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
