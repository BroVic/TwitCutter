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


void printFibBase(Fib::FibBase);
int fndDrctStrm(std::vector<DirEntry>, int&, std::u16string, const int);

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
	OLESSHEADER oleBlock;
	oleBlock.readCFHeader(stream);

	DirEntry rootEntry;
	const int sectorSize = static_cast<int>(pow(2, oleBlock.SectorShift));
	stream.seekg(oleBlock.DirSect1 * sectorSize, std::ios::cur);
	rootEntry.readDirEntry(stream);
	stream.seekg(-sectorSize, std::ios::cur);						// rewind to build binary search tree
	rootEntry.bldTree(rootEntry, stream, sectorSize);

	/*	
	const int entrPerSctr = sectorSize / sizeof(DirEntry);
	*/
	// Locate WordDocument stream and read File Information Block
	std::u16string srchName(u"WordDocument");
	int offset = rootEntry.fndDrctStrm(srchName, sectorSize);
	stream.seekg(offset, std::ios::beg);
	offset = -1;
	
	Fib fileInfoBlock;
	fileInfoBlock.readFib(stream);
	
	// Locate Table Stream and read Clx
	if (fileInfoBlock.base.fWhichTblStm)
		srchName = u"1Table";
	else { srchName = u"0Table"; }
	
	offset = rootEntry.fndDrctStrm(srchName, sectorSize);
	stream.seekg(offset, std::ios::beg);

	Clx charProc;
	

	// Testing...
	std::cout << std::showbase << std::internal;
	printFibBase(fileInfoBlock.base);
	std::cout << "The file pointer is now at offset " << stream.tellg() <<
		" and the size of the File Information Block is " << sizeof(fileInfoBlock) << std::endl << std::endl;

	stream.close();

	return 0;
}


// Prints output (for testing purposes only)
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
	std::cout << "The value of \"fMac\" is " << std::bitset<8>(obj.fMac) << std::endl;
	std::cout << "The value of \"fHasPic\" is " << std::bitset<8>(obj.fHasPic) << std::endl;
	std::cout << "The value of \"fEmptySpecial\" is " << std::bitset<8>(obj.fEmptySpecial) << std::endl;
	std::cout << "The value of \"fLoadOverridePage\" is " << std::bitset<8>(obj.fLoadOverridePage) << std::endl;
	std::cout << "The value of \"reserved1\" is " << std::bitset<8>(obj.reserved1) << std::endl;
	std::cout << "The value of \"reserved2\" is " << std::bitset<8>(obj.reserved2) << std::endl;
	std::cout << "The value of \"fSpare0\" is " << std::bitset<8>(obj.fSpare0) << std::endl;
	std::cout << "The value of \"reserved3\" is " << obj.reserved3 << std::endl;
	std::cout << "The value of \"reserved4\" is " << obj.reserved4 << std::endl;
	std::cout << "The value of \"reserved5\" is " << obj.reserved5 << std::endl;
	std::cout << "The value of \"reserved6\" is " << obj.reserved6 << std::endl;

	return;
}


