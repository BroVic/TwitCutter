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
#include <fstream>
#include <string>

// for decision on encoding
#define UNICODE  0
#define ANSI     1

class DdocProc : 
	private CFHeader, Fib, DirEntry, Clx
{
public:
	// friend void GenericProc::collect_txt(DdocProc&);

private:
	CFHeader  olehdr;
	Fib       fib;
	DirEntry  root;
	Clx       clxobj;
	
	std::u16string _strmName;
	USHORT    _sectSz;
	USHORT    _strmOffset;
	USHORT    _wdocOffset;
	USHORT    _tstrmOffset;
	USHORT    _clxOffset;
	USHORT    _capacity;

public:
	DdocProc();
	~DdocProc();

	VOID process_file(std::ifstream&);

	// Locates and reads directory entry for specified string
	USHORT find_directory(std::ifstream&, std::u16string);

	VOID collect_text(std::ifstream&);
	// Loop 1:
	// aCP[i] take the value as offset on new stream
	// collect value from
	
	// aPCD[i] use the structure as follows
		// fc.fc is offset on WordDocument stream
		// fc.fCompressed to determine whether to read UNICODE or ANSI
		
	    // Loop 2:
		// copy from file stream and onto string stream


};

#endif // !DDOCPROC_H_INCLUDED


