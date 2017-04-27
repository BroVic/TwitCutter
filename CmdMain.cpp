// TwitCutter
//
// CmdMain.cpp
// Main source file for command-line access to the application
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include <cassert>
#include <vector>
#include <bitset>
#include <cmath>
#include <cwchar>
#include "CFHeader.h"
#include "CFDirEntry.h"
#include "FIB.h"
#include "Clx.h"

#define ERR_NO_OPEN 1
#define ERR_NOT_GOOD 2
#define ZERO_OFFSET 0

int main()
{
	
	std::string filename;
	filename = "test.doc";
	std::ifstream stream;

	stream.open(filename, std::ios::binary);
	if (!stream.is_open())
	{
		std::cerr << "Could not open the file." << std::endl;
		return ERR_NO_OPEN;
	}
	if (!stream.good())
	{
		std::cerr << "The file is probably corrupted." << std::endl;
		return ERR_NOT_GOOD;
	}
	if (!stream.tellg() == ZERO_OFFSET)
		stream.seekg(ZERO_OFFSET, std::ios::beg);
	
	// Read OLE Compound File Header first
	CFHeader oleBlock;
	oleBlock.readCFHeader(stream);

	const WORD sectorSize = oleBlock.set_sector_size();
	DirEntry rootEntry;
	stream.seekg(oleBlock.DirSect1 * sectorSize, std::ios::cur);
	rootEntry.readDirEntry(stream);

	// Locate WordDocument stream and read File Information Block
	std::u16string srchName(u"WordDocument");
	int offset = rootEntry.find_directory(stream, srchName, sectorSize);
	stream.seekg(offset, std::ios::beg);
	offset = -1;
	
	Fib fileInfoBlock;
	fileInfoBlock.readFib(stream);
	
	// Locate Table Stream and read Clx
	if (fileInfoBlock.base.fWhichTblStm)
		srchName = u"1Table";
	else { srchName = u"0Table"; }
	
	offset = rootEntry.find_directory(stream, srchName, sectorSize);
	stream.seekg(offset, std::ios::beg);

	Clx charProc;
	offset = fileInfoBlock.fibRgFcLcbBlob.fibRgFcLcb97.fcClx;
	unsigned int cap = fileInfoBlock.fibRgFcLcbBlob.fibRgFcLcb97.lcbClx;
	stream.seekg(offset, std::ios::cur);
	charProc.readToClx(stream);

	stream.close();

	return 0;
}