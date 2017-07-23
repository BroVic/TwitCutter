// TwitCutter
//
// CmdMain.cpp
// Main source file for command-line access to the application

// A document file is passed as an argument at the command line
// twtcut.exe [file]
// TwitCutter's main function is all about the initial preparation of the file
// such that it checks the file whether it is in a format that can be treated 
// and, if so, culminates in passing the path of the file to an generic
// processor object of class 'GenericProc' for appropriate handling. An attempt
// has been made at making this an interactive experience for the user.

#include <string>
#include <iostream>
#include <cstdio>
#include "GenericProc.h"

enum ErrorCodes
{
	SUCCESS			= 0,
	TOO_MANY_ARGS,
	WRONG_FILE,
	PATH_TOO_LONG
};

enum FileExtensions	
{
	NOFILE,
	DOC,
	TXT
	// PDF,
	// DOCX,
	// RTF,
	// etc.
};

// Checks file extension
int check_extension(std::string &str)
{
	int len = str.length() + 1;
	char *tempstr = new (std::nothrow) char[len];
	if (tempstr == nullptr)
	{
		std::cerr << "Unable to allocate memory." << std::endl;
		delete[] tempstr;
		return -1;
	}

	// Ensure all are lower-case
	for (int i = 0; i < len; ++i)
	{
		tempstr[i] = tolower(str[i]);
	}
	tempstr[len] = '\0';

	str.assign(tempstr);

	if (str == ".doc")
	{
		return DOC;
	}
	else if (str == ".txt")
	{
		return TXT;
	}
	return 0;
}

int main(int argc, char** argv)
{
	std::cout << "** Welcome to TwitCutter! **" << std::endl;

	std::string path;
	if (argc < 2)
	{
		std::cout << "Enter the path of the file you want to parse: ";
		std::cin >> path;
	}
	else if (argc > 2)
	{
		std::cerr << "Invalid entry. Accepts no more than 2 args" << std::endl;
		return TOO_MANY_ARGS;
	}
	else
	{
		path = argv[1];
	}
	
	if (path.length() > FILENAME_MAX)
	{
		std::cerr << "Path is too long for this application." << std::endl;
		return PATH_TOO_LONG;
	}

	// Ascertain file extension
	std::string::size_type dot = path.rfind('.');
	std::string exte = path.substr(dot);

	int tag = check_extension(exte);			// TODO: Use for switching
	if (tag == NOFILE)
	{
		std::cerr << "Application currently handles '.DOC' files, only."
			<< std::endl;
		std::cerr << "Exiting the program." << std::endl;
		return WRONG_FILE;
	}

	// Process file contents
	GenericProc docjob;
	docjob.globalProcess(path);

	std::cout << "\nOPERATION COMPLETED." << std::endl;
	
	return SUCCESS;
}