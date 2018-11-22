// print.h

//
// Print out of generated tweet-sized text
//

#ifndef _PRINT_H_INCLUDED_
#define _PRINT_H_INCLUDED_

#include <iostream>
#include <string>
#include <fstream>
#include "coredll.h"
#include "twfact.h"


class TWITCUTAPI TwitPrinter
	: public TwtProcessor
{        // To provide various options for displaying the tweets
private:
BEGIN_WARNINGS_ACTION
DISABLE_WARNING_4251
	std::ofstream printer;
END_WARNINGS_ACTION
	const char* lastMsg;
public:
	TwitPrinter();
	~TwitPrinter();
	void publish();
	const std::string get_lastMsg() const;


private:
	template <class T> void printALine(T&);
	template <class T> void printChain(T&);
	void displayInConsole();
	void writeToDisk();
};
#endif // ! _PRINT_H_INCLUDED_