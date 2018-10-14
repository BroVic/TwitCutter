// DdocProc.h: A Class for processing .DOC files

#ifndef DOCCPROC_H_INCLUDED
#define DOCCPROC_H_INCLUDED

#include <fstream>
#include <string>
#include <map>
#include "cfh.h"
#include "fib.h"
#include "clx.h"
#include "genproc.h"

// For decisions on encoding
constexpr int UNICODE  = 0;
constexpr int ANSI     = 1;

class DoccProcessor
{
private:
	CFHeader                    _olehdr;
	Fib                         _fib;
	DirEntry                    _root;
	Clx                         _clxobj;
	
	std::map<uint8_t, uint16_t> _altANSI;
	std::string                 _stringColl;
	std::wstring                _wstringColl;
	wchar_t                     _utfChar;
	unsigned char               _ansiChar;
	
	std::u16string              _strmName;
	uint16_t                    _sectSz;
    unsigned long               _wdocStart;
	unsigned long               _tablStart;
    unsigned long               _clxOffset;
	unsigned long               _strmOffset;

public:
	DoccProcessor();
	~DoccProcessor();

	void process_file(std::ifstream&);
	std::string getString() const;

private:
	void read_file_data(std::ifstream&);

	void collect_text(std::ifstream&);

	inline std::wstring transferUTFString(std::ifstream&, int, int);
	inline std::string transferANSIString(std::ifstream&, int, int);
	
	void setANSIexceptions();
};
#endif // !DOCCPROC_H_INCLUDED


