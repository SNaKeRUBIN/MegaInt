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

	void run();

  private:
	void parse(std::string, MegaInt &);

	void factorial(MegaInt &);

	void hailstone(MegaInt &);

	std::string delWhiteSpaces(std::string &str);

	bool quit;
	bool error;
};

#endif // MEGACALC_H