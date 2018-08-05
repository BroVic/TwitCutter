// genproc.h
// Generic processing of strings retrieved from various sources


// There are two kinds of classes in this header:
// A. Input: Classes that process input from files, other sources.
// B. Output: Classes that process text retrieved from these sources.

// The Input section will take the path to a given file of a supported format and determine
// what further processing needs to be done. It will pass the data stream to an appropriate
// class that is equipped to handle the given file format.

// The Output section takes a string containing text extracted from a document and do the following:
	// 1. Cuts out a string of a given size.
	// 2. Labels the strings with a number i.e. pagination.
	// 3. Builds a collection of these strings until all the text in the document has been accounted for.

#ifndef GENPROC_H_INCLUDED
#define	GENPROC_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "doccproc.h"
#include "txtproc.h"

///////////////////////////////////////////////////////////////////
///////////////         INPUT CLASSES         /////////////////////
///////////////////////////////////////////////////////////////////

//constexpr int ERR_NO_OPEN = 1;
//constexpr int ERR_NOT_GOOD = 2;

enum FileExtension
{
	STATIC = -1,
	NOFILE,
	DOC,
	TXT
};

class Receiver
{		// Processor of the original input file
private:
	std::ifstream _docstream;
	std::string   _fName;
	std::string   _exte;

	friend class MasterSelector;

public:
	Receiver();
	~Receiver();

	void startJob(const std::string&);

private:
	void activate_stream();
	void get_file_ext();
};

class MasterSelector
{		// Decides on format-specific processing
private:
	int fType;

public:
	MasterSelector();
	~MasterSelector();

	void enable_options(Receiver&);

private:
	int check_extension(Receiver&);
	int select_extension(Receiver&);

};
                   //////////////////////////

///////////////////////////////////////////////////////////////////
///////////////         OUTPUT CLASSES        /////////////////////
///////////////////////////////////////////////////////////////////

constexpr int ZERO_OFFSET = 0;

// For pagination
constexpr char OPEN_TAG   = '(';
constexpr char DIVISOR    = '/';
constexpr char CLOSE_TAG  = ')';

// Character limits for text blocs
constexpr unsigned int CHARACTER_MAX  = 140;
constexpr unsigned int CHARACTER_LIMIT  = 120;


class TwtProcessor
{        // To process retrieved text and store the pieces in a chain.
	std::string            _fullText;
	std::string            _piece;
	std::string::iterator  _it;
	
	void estimTwtNum();
	void spliceStr();
	// void collectStr();

public:
	std::vector<std::string> chain;
	unsigned short         denom;
	unsigned short         twtNumb; // TODO: Possibly remove; deducible from vector length
	// TODO: Check if chain is empty (boolean)
	// TODO: Set maximum length of chain

	TwtProcessor();
	~TwtProcessor();
	void mkChain();
	void setFulltxt(std::string);
};
                   ////////////////////////
#endif // !GENERICPROC_H_INCLUDED
