// TwitCutter
//
// CmdMain.cpp
// Main source file for command-line access to the application
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cassert>
#include <bitset>
#include <cmath>
#include <cwchar>
#include "DdocProc.h"

#define ERR_NO_OPEN 1
#define ERR_NOT_GOOD 2
#define ZERO_OFFSET 0

int main()
{
	/*if (argc != 2)
	{
		std::cerr << "Error: Invalid/No arguments" << std::endl;
		return -1;
	}
	std::string filename = argv[1];*/
	std::string filename = "test.doc";
	std::ifstream docstream;

	docstream.open(filename, std::ios::binary);
	if (!docstream.is_open())
	{
		std::cerr << "Could not open the file." << std::endl;
		return ERR_NO_OPEN;
	}
	if (!docstream.good())
	{
		std::cerr << "The file is probably corrupted." << std::endl;
		return ERR_NOT_GOOD;
	}
	if (!docstream.tellg() == ZERO_OFFSET)
		docstream.seekg(ZERO_OFFSET, std::ios::beg);
		
	DdocProc processor;
	processor.process_file(docstream);

	docstream.close();

	return 0;
}