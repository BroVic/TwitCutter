// DdocProc.h: A Class for processing .DOC files

// check aCP[i]; set start
// check corresponding aPcd[i]
// check fc; set string offset
// move file pointer to offset on WordDocument stream
// start reading from the file stream to the string stream
// ... initiate from the value of aCP[i]
// ... read while aCP[i] is less than aCP[i+1]
// if fc.fCompressed == 0, 
// receiving variable is  16-bits
// else if it is == 1,
// receiving variable is 8-bit
// copy the value and append to string object


#ifndef DDOCPROC_H_INCLUDED
#define DDOCPROC_H_INCLUDED

#include "CFHeader.h"
#include "FIB.h"
#include "CFDirEntry.h"
#include "Clx.h"
#include <sstream>
#include <fstream>
#include <string>
#include <map>

// for decision on encoding
#define UNICODE  0
#define ANSI     1

class DdocProc : 
	private CFHeader, Fib, DirEntry, Clx  // is inheritance still necessary???
{
private:
	CFHeader  olehdr;
	Fib       fib;
	DirEntry  root;
	Clx       clxobj;
	
	std::map<uint8_t, uint16_t> _altANSI;
	std::stringstream           _stringColl;
	std::u16string              _strmName;
	wchar_t                     _utfChar;
	unsigned char               _ansiChar;
	USHORT                      _sectSz;
	USHORT                      _wdocStart;
	USHORT                      _tablStart;
	USHORT                      _clxOffset;
	USHORT                      _capacity;
	ULONG                       _strmOffset;


public:
	DdocProc();
	~DdocProc();

	// Processes .DOC file binary data
	void process_file(std::ifstream&);

	// Reads data from the file stream unto objects
	void read_file_data(std::ifstream&);

	// Collects text from in-memory copy of stream
	void collect_text(std::ifstream&);

	inline void transferUTFStreams(std::ifstream&);
	
	// Sets exceptions to rule for the use of ANSI values
	void setANSIexceptions();
};

#endif // !DDOCPROC_H_INCLUDED


