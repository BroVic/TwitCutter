#ifndef TXTPROC_H_INCLUDED
#define TXTPROC_H_INCLUDED

#include <string>
#include <fstream>

class TxtProc
{
	std::string _textString;

public:
	TxtProc();
	~TxtProc();

	void read_txtfile(std::ifstream&);
	std::string getString();
};
#endif // !TXTPROC_H_INCLUDED

