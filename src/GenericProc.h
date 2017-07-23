
// GenericProc.h: Generic processing of strings retrieved from various sources

// Takes a string containing text extracted from a document and does the following:
	// 1. Cut out out a string of a particular size
	// 2. Labels the strings with a number
	// 3. Builds a collection of these strings until all the document text has been accounted for.

#ifndef GENERICPROC_H_INCLUDED
#define	GENERICPROC_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "TxtProc.h"
#include "DdocProc.h"

constexpr int ERR_NO_OPEN   = 1;
constexpr int ERR_NOT_GOOD  = 2;

constexpr int ZERO_OFFSET = 0;

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
	
	void spliceString();
	
	void makeChain();

	void printChain();

	void writeChainToDisk();

	void printLine();

	/*template <typename T>
	void iterate_and_stream(&T);*/

public:
	GenericProc();
	~GenericProc();
	
	int globalProcess(std::string filename);
};
#endif // !GENERICPROC_H_INCLUDED
