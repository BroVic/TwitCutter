// TwitCutter
//
// CmdMain.cpp
// Main source file for command-line access to the application

// A document file is passed as an argument at the command line
// twtcut.exe [file]
// TwitCutter's main function is all about the initial preparation of the file
// such that it checks the file whether it is in a format that can be treated 
// and, if so, culminates in passing the path of the file to a generic
// processor object of class 'GenericProc' for appropriate handling. An attempt
// has been made at making this an interactive experience for the user.

#include <string>
#include <iostream>
#include <cstdio>

#include "genericproc.h"
#include "cmdctrl.h"

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

	// Use the file
	int tag;
	try
	{
		tag = check_extension(exte);
	}
	catch (const char* excep)
	{
		std::cerr << "A exception was caught." << excep << std::endl;
	}
	
	switch (tag)
	{
	case NOFILE:
		std::cerr << "Unrecognized file format.\nExiting the program." << std::endl;
		return WRONG_FILE;
	case DOC:
	{
		GenericProc docjob;
		docjob.globalProcess(path);
		break;
	}
	/*case TXT:
	{
		TxtProc txtjob;
		break;
	}*/

	}

	std::cout << "\nOPERATION COMPLETED." << std::endl;
	
	return SUCCESS;
}