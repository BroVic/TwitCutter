// DdocProc.h: A Class for processing .DOC files

#ifndef DDOCPROC_H_INCLUDED
#define DDOCPROC_H_INCLUDED

#include <fstream>
#include <string>
#include <map>
#include "CFHeader.h"
#include "FIB.h"
#include "CFDirEntry.h"
#include "Clx.h"

// For decisions on encoding
constexpr int UNICODE  = 0;
constexpr int ANSI     = 1;

class DdocProc
{
private:
	CFHeader  olehdr;
	Fib       fib;
	DirEntry  root;
	Clx       clxobj;
	
	std::map<uint8_t, uint16_t> _altANSI;
	std::string                 _stringColl;
	std::wstring                _wstringColl;
	wchar_t                     _utfChar;
	unsigned char               _ansiChar;
	
	std::u16string  _strmName;
	uint16_t        _sectSz;
	USHORT          _wdocStart;
	USHORT          _tablStart;
	USHORT          _clxOffset;
	ULONG           _strmOffset;

public:
	DdocProc();
	~DdocProc();

	// Processes the entire .DOC file binary data
	void process_file(std::ifstream&);

	std::string getCollectedString() const;

private:
	// Reads data from the file stream unto objects
	void read_file_data(std::ifstream&);

	// Collects text from in-memory copy of stream
	void collect_text(std::ifstream&);

	// Move mapped UNICODE or ANSI values to string buffer
	inline std::wstring transferUTFString(std::ifstream&, int, int);
	inline std::string transferANSIString(std::ifstream&, int, int);
	
	// Sets exceptions to rule for the use of ANSI values
	void setANSIexceptions();
};
#endif // !DDOCPROC_H_INCLUDED


