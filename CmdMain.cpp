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
#include <vector>
#include <bitset>
// #include <cmath>
#include "CFHeader.h"
#include "CFDirEntry.h"
#include "FIB.h"
#include "Clx.h"

#define ERR_NO_OPEN 1
#define ERR_NOT_GOOD 2
#define ZERO_OFFSET 0


void printFibBase(Fib::FibBase);
unsigned int fndDrctStrm(std::vector<DirEntry>, std::wstring);

int main()
{
	
	std::string filename;
	filename = "test.doc";
	std::ifstream strm;

	unsigned int location = 0;			// for testing purpuses only. REMOVE WHEN FINISHED!!!

	strm.open(filename, std::ios::binary);
	if (!strm.is_open())
	{
		std::cerr << "Could not open the file." << std::endl;
		return ERR_NO_OPEN;
	}
	if (!strm.good())
	{
		std::cerr << "The file is probably corrupted." << std::endl;
		return ERR_NOT_GOOD;
	}
	if (!strm.tellg() == ZERO_OFFSET)
		strm.seekg(ZERO_OFFSET, std::ios::beg);
	
	// Read OLE Compound File Header first
	OLESSHEADER oleBlock;
	strm.read(reinterpret_cast<char *>(&oleBlock), sizeof(oleBlock));

	static int sectorSize;
	if (oleBlock.VerDll == 3)
		sectorSize = 512;
	else if (oleBlock.VerDll == 4)
		sectorSize = 4096;
	else { assert(oleBlock.VerDll == 3 || oleBlock.VerDll == 4); }

	// offset of Word Document Stream
	std::vector<DirEntry> dirEntries;
	
	// Move to offset of First Directory
	strm.seekg(oleBlock.DirSect1 * sectorSize, std::ios::cur);
	
	// Read single directory entries into a vector
	DirEntry singleEntry;
	const int entrPerSctr = sectorSize / sizeof(DirEntry);
	do
	{
		strm.read(reinterpret_cast<char *>(&singleEntry), sizeof(singleEntry));
		location = strm.tellg();
		dirEntries.push_back(singleEntry);

	} while (singleEntry.rightSibID == NOSTREAM);
	
	location = fndDrctStrm(dirEntries, L"WordDocument");

	// Read the File Information Block
	strm.seekg(location, std::ios::beg);
	Fib fileInfoBlock;
	location = -1;
	fileInfoBlock.readFib(strm);
	
	// offset of Table Stream
	std::wstring table;
	if (fileInfoBlock.base.fWhichTblStm)
		table = L"1Table";
	else { table = L"0Table"; }
	
	location = fndDrctStrm(dirEntries, table);
	strm.seekg(location, std::ios::beg);
	
	// Find and read Clx
	Clx charProc;
	location = fileInfoBlock.fibRgFcLcbBlob.fibRgFcLcb97.fcClx;
	int szClx = fileInfoBlock.fibRgFcLcbBlob.fibRgFcLcb97.lcbClx;
	strm.seekg(location, std::ios::cur);
	strm.read(reinterpret_cast<char *>(&charProc), sizeof(charProc));

	// Testing...
	std::cout << std::showbase << std::internal;
	printFibBase(fileInfoBlock.base);
	std::cout << "The file pointer is now at offset " << strm.tellg() <<
		" and the size of the File Information Block is " << sizeof(fileInfoBlock) << std::endl << std::endl;

	strm.close();

	return 0;
}


// Print output (for testing purposes only)
void printFibBase(Fib::FibBase obj)
{
	std::cout << "The value of \"wIdent\" is " << std::hex << std::uppercase << obj.wIdent << std::endl;
	std::cout << "The value of \"nFib\" is " << obj.nFib << std::endl;
	std::cout << "The value of \"unused\" is " << obj.unused << std::endl;
	std::cout << "The value of \"lid\" is " << obj.lid << std::endl;
	std::cout << "The value of \"pnNext is " << obj.pnNext << std::endl;
	std::cout << "The value of \"fDot\" is " << std::bitset<8>(obj.fDot) << std::endl;
	std::cout << "The value of \"fGlsy\" is " << std::bitset<8>(obj.fGlsy) << std::endl;
	std::cout << "The value of \"fComplex\" is " << std::bitset<8>(obj.fComplex) << std::endl;
	std::cout << "The value of \"fHasPic\" is " << std::bitset<8>(obj.fHasPic) << std::endl;
	std::cout << "The value of \"cQuickSaves\" is " << std::bitset<8>(obj.cQuickSaves) << std::endl;
	std::cout << "The value of \"fEncrypted\" is " << std::bitset<8>(obj.fEncrypted) << std::endl;
	std::cout << "The value of \"fWhichTblStm\" is " << std::bitset<8>(obj.fWhichTblStm) << std::endl;
	std::cout << "The value of \"fReadOnlyRecommended\" is " << std::bitset<8>(obj.fReadOnlyRecommended) << std::endl;
	std::cout << "The value of \"fWriteReservation\" is " << std::bitset<8>(obj.fWriteReservation) << std::endl;
	std::cout << "The value of \"fExtChar\" is " << std::bitset<8>(obj.fExtChar) << std::endl;
	std::cout << "The value of \"fLoadOverride\" is " << std::bitset<8>(obj.fLoadOverride) << std::endl;
	std::cout << "The value of \"fFarEast\" is " << std::bitset<8>(obj.fFarEast) << std::endl;
	std::cout << "The value of \"fObfuscated\" is " << std::bitset<8>(obj.fObfuscated) << std::endl;
	std::cout << "The value of \"nFibBack\" is " << obj.nFibBack << std::endl;
	std::cout << "The value of \"lkey\" is " << obj.lkey << std::endl;
	std::cout << "The value of \"envr\" is " << obj.envr << std::endl;
	std::cout << "The value of \"flags2\" is " << std::bitset<8>(obj.flags2) << std::endl;
	// std::cout << "The value of \"fMac\" is " << std::bitset<8>(obj.fMac) << std::endl;
	// std::cout << "The value of \"fHasPic\" is " << std::bitset<8>(obj.fHasPic) << std::endl;
	// std::cout << "The value of \"fEmptySpecial\" is " << std::bitset<8>(obj.fEmptySpecial) << std::endl;
	// std::cout << "The value of \"fLoadOverridePage\" is " << std::bitset<8>(obj.fLoadOverridePage) << std::endl;
	// std::cout << "The value of \"reserved1\" is " << std::bitset<8>(obj.reserved1) << std::endl;
	// std::cout << "The value of \"reserved2\" is " << std::bitset<8>(obj.reserved2) << std::endl;
	// std::cout << "The value of \"fSpare0\" is " << std::bitset<8>(obj.fSpare0) << std::endl;
	std::cout << "The value of \"reserved3\" is " << obj.reserved3 << std::endl;
	std::cout << "The value of \"reserved4\" is " << obj.reserved4 << std::endl;
	std::cout << "The value of \"reserved5\" is " << obj.reserved5 << std::endl;
	std::cout << "The value of \"reserved6\" is " << obj.reserved6 << std::endl;

	return;
}

unsigned int fndDrctStrm(std::vector<DirEntry> vec, std::wstring str)
{
	int index = vec[0].childID;
	unsigned int offset = -1;
	int actualLen = str.length();

	while (true)
	{
		if (actualLen > vec[index].nameLength)
			index = vec[index].rightSibID;
		else if (actualLen < vec[index].nameLength)
			index = vec[index].leftSibID;
		else
		{
			// implement UNICODE matching
			if (str.compare(vec[index].name) == 0)
			{
				offset = vec[index].startSectorLoc;
				break;
			}
			// else {}		//iterate through string & do the needful
		}
	}
	return offset;
}
