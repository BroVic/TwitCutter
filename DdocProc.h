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

// for decision on encoding
#define UNICODE  0
#define ANSI     1

class DdocProc : 
	private CFHeader, Fib, DirEntry, Clx
{
private:
	CFHeader  olehdr;
	Fib       fib;
	DirEntry  root;
	Clx       clxobj;
	
	std::stringstream stringColl;
	std::u16string  _strmName;
	wchar_t         _utfChar;
	unsigned char   _ansiChar;
	USHORT          _sectSz;
	USHORT          _wdocStart;
	USHORT          _tablStart;
	USHORT          _clxOffset;
	USHORT          _capacity;
	ULONG           _strmOffset;


public:
	DdocProc();
	~DdocProc();

	VOID process_file(std::ifstream&);

	// Locates and reads directory entry for specified string
	USHORT find_directory(std::ifstream&, std::u16string);

	VOID collect_text(std::ifstream&);

	inline VOID transferUTFStreams(std::ifstream&);
	

};

#endif // !DDOCPROC_H_INCLUDED


