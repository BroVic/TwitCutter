// starters.h

// Handling command line input

#ifndef _STARTERS_H_INCLUDED
#define _STARTERS_H_INCLUDED

#include <iostream>
#include <string>

class HelpModule
{
public:
	HelpModule();
	~HelpModule();

protected:

};

class Valet
	: public HelpModule
{
public:
	Valet();
	~Valet();

protected:
	std::string wlcm;

};

class Parser
	: public Valet
{
public:
	Parser();
	~Parser();

	std::string validate_args(int, const char*);

private:
	std::string path;
};
#endif // !_STARTERS_H_INCLUDED

