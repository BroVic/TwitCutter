#ifndef TXTPROC_H_INCLUDED
#define TXTPROC_H_INCLUDED

#include <string>
#include <fstream>
#include <cassert>

class TextProc
{
	std::string _textString;

public:
	TextProc();
	~TextProc();

	void read_textfile(std::ifstream&);
	std::string getString();
};
#endif // !TXTPROC_H_INCLUDED

