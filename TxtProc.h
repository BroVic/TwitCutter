#ifndef TXTPROC_H_INCLUDED
#define TXTPROC_H_INCLUDED

#include <string>
#include <fstream>

class TxtProc
{
	std::string _textString;
	std::ifstream _textStream;

public:
	TxtProc();
	~TxtProc();

	std::string getCollectedString();
};
#endif // !TXTPROC_H_INCLUDED

