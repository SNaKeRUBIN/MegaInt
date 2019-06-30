#ifndef MEGACALC_H
#define MEGACALC_H

#include "MegaInt.h"

/*
	The calculator thats uses class MegaInt to provide general arithmetic 
	functions of an calculator to arbitrary large numbers
*/
class MegaCalc
{
  public:
	MegaCalc();

	void Run();

  private:
	void Parse(std::string &input, MegaInt &accumulator);

	void Factorial(MegaInt &);

	void Hailstone(MegaInt &);

	std::string DelWhiteSpaces(std::string &str);

	bool m_quit;
	bool m_error;
};

#endif // MEGACALC_H
