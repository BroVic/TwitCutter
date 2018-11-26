// starters.h

// Handling command line input

#ifndef _STARTERS_H_INCLUDED
#define _STARTERS_H_INCLUDED

#include <iostream>
#include <string>

class Parser
{
public:
	Parser();
	~Parser();

	std::string validate_args(int, const char*);
private:
	std::string path;
};
#endif // !_STARTERS_H_INCLUDED

