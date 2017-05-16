
// GenericProc.h: Generic processing of strings retrieved from various sources

// Takes a string containing text extracted from a document and does the following:
	// 1. Cut out out a string of a particular size
	// 2. Labels the strings with a number
	// 3. Builds a collection of these strings until all the document text has been accounted for.

#ifndef GENERICPROC_H_INCLUDED
#define	GENERICPROC_H_INCLUDED

#include <vector>
#include <string>
#include <fstream>
#include "TxtProc.h"
#include "DdocProc.h"

#define ERR_NO_OPEN   1
#define ERR_NOT_GOOD  2
#define ZERO_OFFSET   0

// For numbering text blocks
constexpr char OPEN_TAG   = '(';
constexpr char DIVISOR    = '/';
constexpr char CLOSE_TAG  = ')';

constexpr unsigned int MAX_LIMIT  = 140;
constexpr unsigned int SET_LIMIT  = 120;

class GenericProc
{
	unsigned short         _denom;
	unsigned short         _twtNumb;
	std::ifstream          _docstream;
	std::string            _fullText;
	std::string            _piece;
	std::string::iterator  _it;
	
	DdocProc ddocProcessor;
	TxtProc  txtProcessor;

public:
	std::vector<std::string> chain;	

private:
	// Estimates the number of tweets in the string
	void estimateTweetNum();
	
	// Splits up the string
	void spliceString();
	
	// Creates a chain of tweets
	void makeChain();

public:
	GenericProc();
	~GenericProc();
	
	int globalProcess(std::string filename);
};
#endif // !GENERICPROC_H_INCLUDED
