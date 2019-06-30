#include <string>
#include <iostream>
#include <algorithm>

#include "MegaCalc.h"

/*
	The class constructor
*/
MegaCalc::MegaCalc()
{
	m_quit = false;
}

/*
	Function to start the calculator
*/
void MegaCalc::Run()
{
	std::string command_line;
	MegaInt accumulator;

	std::cout << "Welcome to MegaCalculator" << std::endl;
	std::cout << "-------------------------" << std::endl;

	do
	{
		std::cout << std::endl;
		std::cout << "Accumulator: " << accumulator << std::endl;
		std::cout << "Enter input: ";

		std::getline(std::cin, command_line);
		Parse(command_line, accumulator);

		if (m_error)
		{
			std::cout << "Invalid Input" << std::endl;
		}
	} while (!m_quit);
}

/*
	Parses the input string, performs the requested function

	@param input the input string (the function to be performed)
	@param acc the accumulator value
*/
void MegaCalc::Parse(std::string &input, MegaInt &accumulator)
{
	std::string const inputNoWhiteSpace = DelWhiteSpaces(input);
	m_error = false;

	if (inputNoWhiteSpace.length() == 1)
	{
		char const command = inputNoWhiteSpace[0];
		switch (command)
		{
		case 'c':
			accumulator.Clear();
			break;
		case 'n':
			accumulator.Negate();
			break;
		case 'f':
			Factorial(accumulator);
			break;
		case 'h':
			Hailstone(accumulator);
			break;
		case 'q':
			m_quit = true;
			break;
		default:
			m_error = true;
		}
	}
	else if (inputNoWhiteSpace.length() > 1)
	{
		size_t const size5 = 41;
		char const set5[size5] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_', '!', '`', '~', '@', '#', '$', '^', '&', '(', ')', ',', '<', '.', '>'};
		size_t temp;

		for (char const tempChar : set5)
		{
			temp = inputNoWhiteSpace.find(tempChar);
			if (temp != std::string::npos)
			{
				m_error = true;
				return;
			}
		}

		auto const getStartValue = [&inputNoWhiteSpace] {
			if ((inputNoWhiteSpace[1] == '+') || (inputNoWhiteSpace[1] == '-'))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		};
		size_t const start = getStartValue();

		std::string const number = inputNoWhiteSpace.substr(1);
		size_t const size1 = 2;
		char const set1[size1] = {'+', '-'};

		for (char const tempChar : set1)
		{
			std::string const tempString = number.substr(start);
			temp = tempString.find(tempChar);
			if (temp != std::string::npos)
			{
				m_error = true;
				return;
			}
		}

		MegaInt num{number};
		MegaInt zero{"0"};

		char const command = inputNoWhiteSpace[0];

		switch (command)
		{
		case '=':
			accumulator = num;
			break;
		case '+':
			accumulator += num;
			break;
		case '-':
			accumulator -= num;
			break;
		case '*':
			accumulator *= num;
			break;
		case '/':
			if (num == zero)
			{
				m_error = true;
				break;
			}
			accumulator /= num;
			break;
		case '%':
			if (num == zero)
			{
				m_error = true;
				break;
			}
			accumulator %= num;
			break;
		default:
			m_error = true;
		}
	}
	else
	{
		m_error = true;
	}
}

/*
	Genrates and displays the factorial of a anumber

	@param num The number whose factorail has to be calculated
*/
void MegaCalc::Factorial(MegaInt &num)
{
	{
		MegaInt zero{"+0"};
		if (num == zero)
		{
			std::cout << "+1! = +1" << std::endl;
			return;
		}
		else if (num < zero)
		{
			m_error = true;
			return;
		}
	}

	MegaInt fact{"+1"};

	for (MegaInt i{"+1"}; i <= num; i++)
	{
		fact *= i;
		std::cout << i << "! = " << fact << std::endl;
	}
}

/*
	Generates and displays the hailstone sequence

	@param num the number from where hailstone sequence has to be calculated
*/
void MegaCalc::Hailstone(MegaInt &num)
{
	MegaInt zero{"+0"};

	if (num == zero)
	{
		std::cout << "+1! = +1" << std::endl;
		return;
	}
	else if (num < zero)
	{
		m_error = true;
		return;
	}

	MegaInt one{"+1"};
	MegaInt two{"+2"};
	MegaInt three{"+3"};
	MegaInt steps{"+1"};
	MegaInt temp{num};

	while (temp != one)
	{
		std::cout << "> " << temp << std::endl;

		if (temp % two == zero)
		{
			temp /= two;
		}
		else
		{
			temp = (three * temp) + one;
		}
		steps++;
	}
	std::cout << "> " << temp << std::endl;
	std::cout << "length of the hailstone (" << num << ") sequence: " << steps << std::endl;
}

/*
	Erases white spaces from a string

	@param str The string containing white spaces

	@return The string containing no white spaces
*/
std::string MegaCalc::DelWhiteSpaces(std::string &str) // source - https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
{
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	return str;
}
