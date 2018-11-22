// iproc.h

// Interface class to enable DLL export

// Abstract class to enable selective
// export/import of member function(s)

#ifndef _IPROC_H_INCLUDED_
#define _IPROC_H_INCLUDED_

#include <string>
#include <fstream>
#include "docapi.h"

class DOCAPI IProcessorLib
{
public:
	virtual ~IProcessorLib();
	virtual std::string getString() const = 0;
	virtual void process_file(std::ifstream&) = 0;
	virtual void read_file_data(std::ifstream&) = 0;
	virtual void collect_text(std::ifstream&) = 0;
};
#endif // !_IPROC_H_INCLUDED_