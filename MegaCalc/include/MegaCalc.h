#ifndef MEGACALC_H
#define MEGACALC_H

#include "MegaInt.h"
// #include <string>

/*
	The calculator thats uses class MegaInt to provide general arithmetic 
	functions of an calculator to arbitrary large numbers
*/
class MegaCalc {

private:
	bool quit;
	bool error;


	void parse(std::string, MegaInt&);

	void factorial(MegaInt&);

	void hailstone(MegaInt&);

	std::string delWhiteSpaces(std::string &str);


public:
	MegaCalc();

	void run();

};

#endif // MEGACALC_H
