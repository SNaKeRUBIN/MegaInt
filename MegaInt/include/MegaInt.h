#ifndef MEGAINT_H
#define MEGAINT_H

#include <deque>
#include <string>

namespace
{
struct DivisionResult;
}

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

	char &operator[](const int index);

	MegaInt &operator+=(const MegaInt &n);

	MegaInt &operator-=(const MegaInt &n);

	MegaInt &operator*=(const MegaInt &n);

	MegaInt &operator/=(const MegaInt &n);

	MegaInt &operator%=(const MegaInt &n);

	MegaInt &operator++();

	MegaInt &operator++(int);

	MegaInt &operator--();

	MegaInt &operator--(int);

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

	// TODO
	// why are deque based functions part of class def
	std::deque<char> Plus(std::deque<char> A, std::deque<char> B) const;

	MegaInt Subtract(MegaInt B) const;

	std::deque<char> Minus(std::deque<char> A, std::deque<char> B) const;

	MegaInt Multiply(MegaInt B) const;

	std::deque<char> Product(std::deque<char> A, std::deque<char> B) const;

	std::deque<char> Product2(std::deque<char> A, std::deque<char> B) const;

	MegaInt Division(MegaInt B) const;

	DivisionResult Quotient(std::deque<char> A, std::deque<char> B) const;

	DivisionResult Quotient2(std::deque<char> A, std::deque<char> B) const;

	MegaInt Modulus(MegaInt B) const;

	bool GreaterThan(const std::deque<char> &A, const std::deque<char> &B) const;

	bool LesserThan(const std::deque<char> &A, const std::deque<char> &B) const;

	bool EqualTo(const std::deque<char> &A, const std::deque<char> &B) const;

	char m_sign;
	std::deque<char> m_magnitude;
};

#endif // MEGAINT_H
