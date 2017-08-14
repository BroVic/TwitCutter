// TwitCutter
//
// CmdMain.cpp
// Main source file for command-line access to the application

// A document file is passed as an argument at the command line
// twtcut.exe [file]
// TwitCutter's main function is all about the initial preparation of the file
// such that it checks the file whether it is in a format that can be treated 
// and, if so, culminates in passing the path of the file to a generic
// processor object of class 'DocSelector' for appropriate handling. An attempt
// has been made at making this an interactive experience for the user.

#include <string>
#include <iostream>
#include <cstdio>

#include "genericproc.h"

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

	// Work proper
	Receiver jobIn;
	jobIn.startJob(path);

	DocSelectorStart rel;
	rel.chooseFormat(jobIn);

	TwtProcessor roundup;
	roundup.mkChain();

	TwtPrinter jobOut;
	jobOut.publish();

	std::cout << "OPERATION COMPLETED." << std::endl;
	
	return 0;
}