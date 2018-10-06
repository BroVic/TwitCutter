// print.h

//
// Print out of generated tweet-sized text
//

#ifndef _PRINT_H_INCLUDED_
#define _PRINT_H_INCLUDED_

#include <iostream>
#include <string>
#include "genproc.h"


class TwitPrinter
	: public TwtProcessor
{        // To provide various options for displaying the tweets
private:
	std::ofstream _printer;

public:
	TwitPrinter();
	~TwitPrinter();

	void publish();

private:
	template <class T> void printALine(T&);
	template <class T> void printChain(T&);
	void displayInConsole();
	void writeToDisk();
};
#endif // ! _PRINT_H_INCLUDED_