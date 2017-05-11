// =============================================================================== //
// = GenericProc.h: Generic processing of strings retrieved from various sources = //
// =============================================================================== //

// Takes a stream containing text extracted from a document and does the following:
	// 1. Cut out out a string of a particular size
	// 2. Labels the strings with a number
	// 3. Builds a collection of these strings until all the document text has been accounted for.

#ifndef GENERICPROC_H_INCLUDED
#define	GENERICPROC_H_INCLUDED

#include <sstream>
#include <vector>
#include <string>
#include "TxtProc.h"
#include "DdocProc.h"

// For numbering text blocks
#define OPEN_TAG   (
#define DIVISOR    /
#define CLOSE_TAG  )

class GenericProc
{
	unsigned short _denom;
	unsigned short _counter;

public:
	std::stringstream intermediary;

public:
	GenericProc();
	~GenericProc();

    void collect_txt(DdocProc&);
};
#endif // !GENERICPROC_H_INCLUDED
