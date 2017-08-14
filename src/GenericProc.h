
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
#include "DoccProc.h"
// #include "txtproc.h"
// #include "docxproc.h"

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
	// TxtProc  txtProcessor;
	// DocxProc docxProcessor;
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
constexpr unsigned int MAX_LIMIT  = 140;
constexpr unsigned int SET_LIMIT  = 120;


class TwtProcessor
{        // To process retrieved text and store the pieces in a chain.
	unsigned short         _denom;
	unsigned short         _twtNumb;
	std::string            _fullText;
	std::string            _piece;
	std::string::iterator  _it;

public:
	std::vector<std::string> chain;	

private:
	void estimTwtNum();
	
	void spliceStr();
	
	// void collectStr();

public:
	TwtProcessor();
	~TwtProcessor();

	void mkChain();
	void setFulltxt(std::string);
	
};


class TwtPrinter
	: public TwtProcessor
{        // To provide various options for displaying the tweets
private:
	std::ofstream _printer;

public:
	TwtPrinter();
	~TwtPrinter();

	void publish();

private:
	template <class T>
	void printALine(T&);

	template <class T>
	void printChain(T&);

	void displayInConsole();

	void writeToDisk();
};

                   ////////////////////////           

#endif // !GENERICPROC_H_INCLUDED

