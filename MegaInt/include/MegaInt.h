#ifndef MEGAINT_H
#define MEGAINT_H

#include <deque>
#include <string>

/*
	MegaInt is a class used to describe a data type that models arbitrary large integers.
	Uses STL deque sequence container to store the digits of the numbers.

*/
class MegaInt
{

public:
	MegaInt();

	MegaInt(char const new_sign, std::deque<char> &new_magnitude);

	explicit MegaInt(std::string const &num);

	void Clear();

	void Negate();

	char GetSign() const;

	std::deque<char> GetMagnitude() const;

	char operator[](const int index);

	MegaInt &operator+=(const MegaInt &n);

	MegaInt &operator-=(const MegaInt &n);

	MegaInt &operator*=(const MegaInt &n);

	MegaInt &operator/=(const MegaInt &n);

	MegaInt &operator%=(const MegaInt &n);

	MegaInt &operator++();

	MegaInt operator++(int);

	MegaInt &operator--();

	MegaInt operator--(int);

	friend MegaInt operator+(const MegaInt &m, const MegaInt &n);

	friend MegaInt operator-(const MegaInt &m, const MegaInt &n);

	friend MegaInt operator*(const MegaInt &m, const MegaInt &n);

	friend MegaInt operator/(const MegaInt &m, const MegaInt &n);

	friend MegaInt operator%(const MegaInt &m, const MegaInt &n);

	friend bool operator>(const MegaInt &m, MegaInt &n);

	friend bool operator<(const MegaInt &m, MegaInt &n);

	friend bool operator==(const MegaInt &m, MegaInt &n);

	friend bool operator<=(const MegaInt &m, MegaInt &n);

	friend bool operator>=(const MegaInt &m, MegaInt &n);

	friend bool operator!=(const MegaInt &m, MegaInt &n);

	friend std::ostream &operator<<(std::ostream &out, const MegaInt &m);

private:
	void Insert(std::string const &new_number);

	void Normalize();

	MegaInt Add(MegaInt B) const;

	MegaInt Subtract(MegaInt B) const;

	MegaInt Multiply(MegaInt B) const;

	MegaInt Division(MegaInt B) const;

	MegaInt Modulus(MegaInt B) const;

	char m_sign;
	std::deque<char> m_magnitude;
};

#endif // MEGAINT_H
