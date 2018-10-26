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

#ifndef _GENPROC_H_INCLUDED_
#define	_GENPROC_H_INCLUDED_

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "txtproc.h"
#include "dllclnt.h"
#include "doccproc.h"

///////////////////////////////////////////////////////////////////
///////////////         INPUT CLASSES         /////////////////////
///////////////////////////////////////////////////////////////////
enum FileExtension
{
	STATIC = -1,
	NOFILE,
	DOC,
	TXT
};

//
// Receiver: For processing of the original input file
// i.e. collecting its path, parsing the extension
class Receiver
{		
private:
	std::ifstream docstream;
	std::string   fName;
	std::string   exte;

	friend class MasterSelector;
public:
	Receiver();
	~Receiver();
	void startJob(const std::string&);
private:
	void activate_stream();
	void get_file_ext();
};

//
// Decides on format-specific processing
class MasterSelector
{
private:
	int fType;
public:
	MasterSelector();
	~MasterSelector();
	std::string enable_options(Receiver&);
private:
	int check_extension(Receiver&);
	int select_extension(Receiver&);
};

///////////////////////////////////////////////////////////////////
///////////////         OUTPUT CLASSES        /////////////////////
///////////////////////////////////////////////////////////////////
constexpr int ZERO_OFFSET = 0;

// For pagination
constexpr char OPEN_TAG   = '(';    // TODO: Make mutable; use struct.
constexpr char DIVISOR    = '/';
constexpr char CLOSE_TAG  = ')';
constexpr char SPACE      = ' ';

//
// Character limits for text blocs
constexpr unsigned int CHARACTER_MAX    = 140;
constexpr unsigned int CHARACTER_LIMIT  = 120;

//
// To process retrieved text and
// store the pieces in a chain.
class TwtProcessor
{        
	std::string            fullText;
	std::string            piece;
	std::string::iterator  it;

	void estimTwtNum();
	void spliceStr();
public:
	std::vector<std::string> chain;
	unsigned short         denom;
	unsigned short         twtNumb; // TODO: Possibly remove; deducible from vector length
	// TODO: Check if chain is empty (boolean)
	// TODO: Set maximum length of chain

	TwtProcessor();
	~TwtProcessor();
	void mkChain();
	void setFulltxt(std::string&);
};
#endif // !_GENERICPROC_H_INCLUDED_
