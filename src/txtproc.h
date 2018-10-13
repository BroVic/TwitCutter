// txtproc.h

#ifndef TXTPROC_H_INCLUDED
#define TXTPROC_H_INCLUDED

#include <string>
#include <fstream>
#include <cassert>


class TextProcessor
{
	std::string _textString;

public:
	TextProcessor();
	~TextProcessor();

	void read_textfile(std::ifstream&);
	std::string getString();
};

#endif // !TXTPROC_H_INCLUDED