#include <deque>
#include <cassert>
#include <iostream>

struct DivisionResult
{
    std::deque<char> quotient;
    std::deque<char> remainder;
};

/*
	Function to get the int form of a character

	@param c the character to be converted to a int

	@return returns the int form of a character
*/
int GetIntFromChar(char const c)
{
    char const c0 = '0';
    return static_cast<int>(c - c0);
}

/*
	Function to get the char form of an integer

	@param i the int to be converted to a char

	@return returns the char form of an integer
*/
char GetCharFromInt(int const i)
{
    assert(i >= 0 && i < 10);
    char c0 = '0';
    return static_cast<char>(i + c0);
}

/*
	Removes the leading zeroes from a deque so that the leftmost digit is a
	non-zero digit

	@param A the deque that has to be normalized

	@return the normalized deque
*/
static std::deque<char> NormalizeDeque(std::deque<char> A)
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
	Returns true if param A is greater than param B

	@param A a number as a deque
	@param B a number as a deque

	@return boolean value
*/
bool GreaterThan(const std::deque<char> &A, const std::deque<char> &B)
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
bool LesserThan(const std::deque<char> &A, const std::deque<char> &B)
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
bool EqualTo(const std::deque<char> &A, const std::deque<char> &B)
{
    if (A.size() != B.size())
    {
        return false;
    }
    for (size_t i = 0; i < A.size(); i++)
    {
        if (A[i] != B[i])
        {
            return false;
        }
    }
    return true;
}

/*
	Function to add the numbers of two deques

	@param A The number to be added
	@param B The number to be added

	@return a deque containing the sum if two numbers
*/
std::deque<char> Plus(std::deque<char> A, std::deque<char> B)
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
        temp = GetIntFromChar(A[j]) + GetIntFromChar(B[k]) + carry;

        result.push_front(GetCharFromInt(temp % 10));
        carry = temp / 10;
        i--;
        j--;
        k--;
    }

    while (j >= 0)
    {
        temp = GetIntFromChar(A[j]) + carry;

        result.push_front(GetCharFromInt(temp % 10));
        carry = temp / 10;
        i--;
        j--;
    }

    while (k >= 0)
    {
        temp = GetIntFromChar(B[k]) + carry;

        result.push_front(GetCharFromInt(temp % 10));
        carry = temp / 10;
        i--;
        k--;
    }

    result.push_front(GetCharFromInt(carry));
    return result;
}

/*
	Function to subtract two numbers in form of deques

	@param A the minuend
	@param B the subtrahend

	@return the difference
*/
std::deque<char> Minus(std::deque<char> A, std::deque<char> B)
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
        temp = GetIntFromChar(A[j]) - (GetIntFromChar(B[k]) + borrow);

        borrow = 0;

        if (temp < 0)
        {
            borrow = 1;
            temp = 10 + temp;
        }
        result.push_front(GetCharFromInt(temp));

        i--;
        j--;
        k--;
    }

    while (j >= 0)
    {
        temp = GetIntFromChar(A[j]) - borrow;

        borrow = 0;

        if (temp < 0)
        {
            borrow = 1;
            temp = 10 + temp;
        }

        result.push_front(GetCharFromInt(temp));
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
	Function to multiply two numbers as deques
	It employs the method of adding one factor to itself other factor times

	@param A the factor
	@param B the factor

	@return The product as a deque
*/
std::deque<char> Product(std::deque<char> A, std::deque<char> B)
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
        temp = Plus(temp, B);

        A = Minus(A, temp2);
        A = NormalizeDeque(A);
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
std::deque<char> Product2(std::deque<char> A, std::deque<char> B)
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

        temp = Product(temp, B);
        temp = NormalizeDeque(temp);

        for (size_t j = count - i; j < count; j++)
        {
            temp.push_back('0');
        }

        list.push_back(temp);
    }

    sum = list[0];

    for (size_t i = 1; i < list.size(); i++)
    {
        sum = Plus(sum, list[i]);
        sum = NormalizeDeque(sum);
    }

    return sum;
}

/*
	Function to divide two numbers as deques.
	The function uses the method to subtract the dividend by the divisor and count the times
	we need to subtract before result is zero or less than divisors

	@param A the dividend
	@param B the divisor

	@return Divison result
*/
DivisionResult Quotient(std::deque<char> A, std::deque<char> B)
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

    while (!(LesserThan(dividend, divisor)))
    {
        dividend = Minus(dividend, divisor);
        dividend = NormalizeDeque(dividend);

        remainder = dividend;

        quotient = Plus(quotient, increment);
        quotient = NormalizeDeque(quotient);
    }

    DivisionResult result;
    result.quotient = quotient;
    result.remainder = remainder;

    return result;
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
DivisionResult Quotient2(std::deque<char> A, std::deque<char> B)
{
    // quotient(dividend, divisor)
    std::deque<char> current;
    std::deque<char> quotient_;
    std::deque<char> temp;
    DivisionResult result;

    for (size_t i = 0; i < A.size(); i++)
    {
        current.push_back(A[i]);
        current = NormalizeDeque(current);

        if (GreaterThan(B, current))
        {
            quotient_.push_back('0');
            continue;
        }

        result = Quotient(current, B);

        quotient_.push_back(result.quotient[0]);
        quotient_ = NormalizeDeque(quotient_);
        current = NormalizeDeque(result.remainder);
    }

    result.quotient = quotient_;
    result.remainder = current;

    return result;
}
