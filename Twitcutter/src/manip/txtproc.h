// txtproc.h

#ifndef TXTPROC_H_INCLUDED
#define TXTPROC_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include "iproc.h"
#include "docapi.h"

class DOCAPI TextProcessor 
	: public IProcessorLib
{
BEGIN_WARNINGS_ACTION
DISABLE_WARNING_4251   // on non-exported STL objects https://bit.ly/2CHM88w
	std::string errBadStream;
	std::string txtString;
END_WARNINGS_ACTION
public:
	TextProcessor();
	~TextProcessor();		
	virtual void process_file(std::ifstream&);
	virtual void read_file_data(std::ifstream&) override final;
	virtual void collect_text(std::ifstream&) override final;
	virtual std::string getString() const override final;
};
#endif // !TXTPROC_H_INCLUDED