// DdocProc.h: A Class for processing .DOC files

#ifndef DOCCPROC_H_INCLUDED
#define DOCCPROC_H_INCLUDED

#include <fstream>
#include <string>
#include <map>
#include "cfh.h"
#include "clx.h"
#include "dllclnt.h"
#include "fib.h"
#include "genproc.h"


// For decisions on encoding
constexpr int UNICODE  = 0;
constexpr int ANSI     = 1;

class DoccProcessor 
	: public IProcessorLib
{
private:
	CFHeader                    olehdr;
	Fib                         fib;
	DirEntry                    root;
	Clx                         clxobj;
	
	std::map<uint8_t, uint16_t> altANSI;
	std::string                 stringColl;
	std::wstring                wstringColl;
	wchar_t                     utfChar;
	unsigned char               ansiChar;
	
	std::u16string              strmName;
	uint16_t                    sectSz;
    unsigned long               wdocStart;
	unsigned long               tablStart;
    unsigned long               clxOffset;
	unsigned long               strmOffset;

public:
	DoccProcessor();
	~DoccProcessor();

	std::string getString() const;
	void process_file(std::ifstream&);
	void read_file_data(std::ifstream&);
	void collect_text(std::ifstream&);

private:
	inline std::wstring transferUTFString(std::ifstream&, int, int);
	inline std::string transferAnsiString(std::ifstream&, int, int);
	
	void setAnsiExceptions();
};
#endif // !DOCCPROC_H_INCLUDED
