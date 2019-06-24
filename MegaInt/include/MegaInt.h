#ifndef MEGAINT_H
#define MEGAINT_H

#include <deque>
#include <string>


/*
	MegaInt is a class used to describe a data type that models arbitrary large integers.
	Uses STL deque sequence container to store the digits of the numbers.

*/
class MegaInt {

private:
	char sign;
	std::deque<char> magnitude;


	void insert(std::string new_number);

	void normalize();

	std::deque<char> normalize1(std::deque<char> A) const;

	int get_int(char c) const;

	char get_char(int i) const;
	
	MegaInt add(MegaInt B) const;

	std::deque<char> plus(std::deque<char>  A, std::deque<char> B) const;

	MegaInt subtract(MegaInt B) const;

	std::deque<char> minus(std::deque<char>  A, std::deque<char> B) const;

	MegaInt multiply(MegaInt B) const;

	std::deque<char> product(std::deque<char>  A, std::deque<char> B) const;

	std::deque<char> product2(std::deque<char>  A, std::deque<char> B) const;

	MegaInt division(MegaInt B) const;

	std::deque<std::deque<char>> quotient(std::deque<char>  A, std::deque<char> B) const;

	std::deque<std::deque<char>> quotient2(std::deque<char>  A, std::deque<char> B) const;

	MegaInt modulus(MegaInt B) const;

	bool greaterThan(const std::deque<char> &A, const std::deque<char> &B) const;

	bool lesserThan(const std::deque<char> &A, const std::deque<char> &B) const;

	bool equalTo(const std::deque<char> &A, const std::deque<char> &B) const;

	char getSign() const;

	std::deque<char> getMagnitude() const;


public:
	MegaInt();

	MegaInt(char new_sign, std::deque<char> new_magnitude);

	MegaInt(std::string);

	void clear();

	void negate();

	char& operator[](const int index);

	MegaInt& operator+=(const MegaInt &n);

	MegaInt& operator-=(const MegaInt &n);

	MegaInt& operator*=(const MegaInt &n);

	MegaInt& operator/=(const MegaInt &n);

	MegaInt& operator%=(const MegaInt &n);

	MegaInt& operator++();

	MegaInt& operator++(int);

	MegaInt& operator--();

	MegaInt& operator--(int);

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

	friend std::ostream& operator<<(std::ostream &out, const MegaInt &m);

};

#endif // MEGAINT_H