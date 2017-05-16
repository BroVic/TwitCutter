// TwitCutter
//
// CmdMain.cpp
// Main source file for command-line access to the application

#include "GenericProc.h"

int main()
{
	/*if (argc != 2)
	{
		std::cerr << "Error: Invalid/No arguments" << std::endl;
		return -1;
	}
	std::string filename = argv[1];*/
	std::string filename = "test2.doc";

	GenericProc job;
	job.globalProcess(filename);

	return 0;
}