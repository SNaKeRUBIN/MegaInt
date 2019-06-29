#include <string>
#include <iostream>
#include <algorithm>

#include "MegaCalc.h"

/*
	The class constructor
*/
MegaCalc::MegaCalc()
{
	quit = false;
}

/*
	Function to start the calculator
*/
void MegaCalc::run()
{
	std::string command_line;
	MegaInt acc;

	std::cout << "Welcome to MegaCalculator" << std::endl;
	std::cout << "-------------------------" << std::endl;

	do
	{
		std::cout << std::endl;
		std::cout << "Accumulator: " << acc << std::endl;
		std::cout << "Enter input: ";

		std::getline(std::cin, command_line);
		parse(command_line, acc);

		if (error)
		{
			std::cout << "Invalid Input" << std::endl;
		}
	} while (!quit);
}

/*
	Parses the input string, performs the requested function

	@param input the input string (the function to be performed)
	@param acc the accumulator value
*/
void MegaCalc::parse(std::string input, MegaInt &acc)
{
	error = false;
	input = delWhiteSpaces(input);

	if (input.length() == 1)
	{

		char command = input[0];

		switch (command)
		{
		case 'c':
			acc.clear();
			break;

		case 'n':
			acc.negate();
			break;

		case 'f':
			factorial(acc);
			break;

		case 'h':
			hailstone(acc);
			break;

		case 'q':
			quit = true;
			break;

		default:
			error = true;
		}
	}
	else if (input.length() > 1)
	{
		int start{0};

		const int size5 = 41;
		char set5[size5] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_', '!', '`', '~', '@', '#', '$', '^', '&', '(', ')', ',', '<', '.', '>'};
		int temp;

		for (int i = 0; i < size5; i++)
		{
			temp = input.find(set5[i]);
			if (temp != std::string::npos)
			{
				error = true;
				return;
			}
		}

		if ((input[1] == '+') || (input[1] == '-'))
		{
			start = 1;
		}

		std::string number = input.substr(1);
		const int size1 = 2;
		char set1[size1] = {'+', '-'};
		for (int i = start; i < size1; i++)
		{
			std::string tempString;
			tempString = number.substr(start);
			temp = tempString.find(set1[i]);
			if (temp != std::string::npos)
			{
				error = true;
				return;
			}
		}

		MegaInt num{number};
		MegaInt zero{"0"};

		char command = input[0];

		switch (command)
		{
		case '=':
			acc = num;
			break;

		case '+':
			acc += num;
			break;

		case '-':
			acc -= num;
			break;

		case '*':
			acc *= num;
			break;

		case '/':
			if (num == zero)
			{
				error = true;
				break;
			}
			acc /= num;
			break;

		case '%':
			acc %= num;
			break;

		default:
			error = true;
		}
	}
	else
	{
		error = true;
	}
}

/*
	Genrates and displays the factorial of a anumber

	@param num The number whose factorail has to be calculated
*/
void MegaCalc::factorial(MegaInt &num)
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
			error = true;
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
void MegaCalc::hailstone(MegaInt &num)
{
	MegaInt zero{"+0"};

	if (num == zero)
	{
		std::cout << "+1! = +1" << std::endl;
		return;
	}
	else if (num < zero)
	{
		error = true;
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
std::string MegaCalc::delWhiteSpaces(std::string &str) // source - https://stackoverflow.com/questions/83439/remove-spaces-from-stdstring-in-c
{
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	return str;
}