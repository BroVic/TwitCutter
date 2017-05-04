// DdocProc.h: A Class for processing .DOC files

#ifndef DDOCPROC_H_INCLUDED
#define DDOCPROC_H_INCLUDED

#include "CFHeader.h"
#include "FIB.h"
#include "CFDirEntry.h"
#include "Clx.h"
#include <fstream>
#include <string>

class DdocProc : 
	private CFHeader, Fib, DirEntry, Clx
{
	CFHeader  olehdr;
	Fib       fib;
	DirEntry  root;
	Clx       clxobj;
	
	std::u16string  _strmName;
	USHORT          _sectSz;
	USHORT          _wdocOffset;
	USHORT          _tdocOffset;
	USHORT          _clxOffset;
	USHORT          _capacity;

public:
	DdocProc();
	~DdocProc();

	VOID process_file(std::ifstream&);
	USHORT find_directory(std::ifstream&, std::u16string);
};

#endif // !DDOCPROC_H_INCLUDED


