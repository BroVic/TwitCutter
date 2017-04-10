// TwitCutter
//
// CmdMain.cpp
// Main source file for command-line access to the application
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <intrin.h>
#include "CFH.h"
#include "FIB.h"
#include "Clx.h"

void printFibBase(dtdoc::FibBase obj)
{
	std::cout << "The value of \"wIdent\" is " << std::hex << std::uppercase << obj.wIdent << std::endl;
	std::cout << "The value of \"nFib\" is " << obj.nFib << std::endl;
	std::cout << "The value of \"unused\" is " << obj.unused << std::endl;
	std::cout << "The value of \"lid\" is " << obj.lid << std::endl;
	std::cout << "The value of \"pnNext is " << obj.pnNext << std::endl;
	std::cout << "The value of \"fDot\" is " << obj.fDot << std::endl;
	std::cout << "The value of \"fGlsy\" is " << obj.fGlsy << std::endl;
	std::cout << "The value of \"fComplex\" is " << obj.fComplex << std::endl;
	std::cout << "The value of \"fHasPic\" is " << obj.fHasPic << std::endl;
	std::cout << "The value of \"cQuickSaves\" is " << obj.cQuickSaves << std::endl;
	std::cout << "The value of \"fEncrypted\" is " << obj.fEncrypted << std::endl;
	std::cout << "The value of \"fWhichTblStm\" is " << obj.fWhichTblStm << std::endl;
	std::cout << "The value of \"fReadOnlyRecommended\" is " << obj.fReadOnlyRecommended << std::endl;
	std::cout << "The value of \"fWriteReservation\" is " << obj.fWriteReservation << std::endl;
	std::cout << "The value of \"fExtChar\" is " << obj.fExtChar << std::endl;
	std::cout << "The value of \"fLoadOverride\" is " << obj.fLoadOverride << std::endl;
	std::cout << "The value of \"fFarEast\" is " << obj.fFarEast << std::endl;
	std::cout << "The value of \"fObfuscated\" is " << obj.fObfuscated << std::endl;
	std::cout << "The value of \"lkey\" is " << obj.lkey << std::endl;
	std::cout << "The value of \"envr\" is " << obj.envr << std::endl;
	std::cout << "The value of \"fMac\" is " << obj.fMac << std::endl;
	std::cout << "The value of \"fHasPic\" is " << obj.fHasPic << std::endl;
	std::cout << "The value of \"fEmptySpecial\" is " << obj.fEmptySpecial << std::endl;
	std::cout << "The value of \"fLoadOverridePage\" is " << obj.fLoadOverridePage << std::endl;
	std::cout << "The value of \"reserved1\" is " << obj.reserved1 << std::endl;
	std::cout << "The value of \"reserved2\" is " << obj.reserved2 << std::endl;
	std::cout << "The value of \"fSpare0\" is " << obj.fSpare0 << std::endl;
	std::cout << "The value of \"reserved3\" is " << obj.reserved3 << std::endl;
	std::cout << "The value of \"reserved4\" is " << obj.reserved4 << std::endl;
	std::cout << "The value of \"reserved5\" is " << obj.reserved5 << std::endl;
	std::cout << "The value of \"reserved6\" is " << obj.reserved6 << std::endl;

	return;
}
// const unsigned int szFibBs = 32;
// ifstream::pos_type szFibBs = 32;

int main()
{
	OLESSHEADER oleBlock;
	dtdoc::Fib fileInfoBlock;
	std::ifstream docfile;

	docfile.open("test.doc", std::ios::binary);

	if (!docfile.is_open())
	{
		std::cerr << "Could not open the file." << std::endl;
		return 0x001;
	}

	if (!docfile.good())
	{
		std::cerr << "The file is probably corrupted." << std::endl;
		return 0x002;
	}
	
	if (!docfile.tellg() == 0)
		docfile.seekg(0, std::ios::beg);

	docfile.seekg(0, std::ios::end);
	int length = docfile.tellg();

	std::cout << "The stream for this file is " << length << " bytes long." << std::endl << std::endl;
	
	// Read Compound File Header first
	docfile.seekg(0, std::ios::beg);
	std::cout << "Stream is at location " << docfile.tellg() << ", while Compound File Header's allocated memory is " << sizeof(oleBlock) << " bytes." << std::endl;
	std::cout << "Reading this header..." << std::endl;
	docfile.read(reinterpret_cast<char *>(&oleBlock), sizeof(oleBlock));
	
	// Read the File Information Block
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.base.wIdent), sizeof(fileInfoBlock.base.wIdent));
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.base.nFib), sizeof(fileInfoBlock.base.nFib));
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.base.unused), sizeof(fileInfoBlock.base.unused));
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.base.lid), sizeof(fileInfoBlock.base.lid));
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.base.pnNext), sizeof(fileInfoBlock.base.pnNext));
	
	docfile.seekg(2, docfile.cur);		// deal with this later

	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.base.nFibBack), sizeof(fileInfoBlock.base.nFibBack));
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.base.lkey), sizeof(fileInfoBlock.base.lkey));
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.base.envr), sizeof(fileInfoBlock.base.envr));
	
	docfile.seekg(1, docfile.cur);		// ditto

	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.base.reserved3), sizeof(fileInfoBlock.base.reserved3));
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.base.reserved4), sizeof(fileInfoBlock.base.reserved4));
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.base.reserved5), sizeof(fileInfoBlock.base.reserved5));
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.base.reserved6), sizeof(fileInfoBlock.base.reserved6));

	// Testing...
	std::cout << std::showbase << std::internal;
	printFibBase(fileInfoBlock.base);
	length = docfile.tellg();
	std::cout << "The stream is at offset " << length << std::endl << std::endl;

	// Try again, reading entire structure in one go.
	docfile.seekg(512, std::ios::beg);
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.base), sizeof(fileInfoBlock.base));
	printFibBase(fileInfoBlock.base);
	std::cout << "The stream is at offset " << length << std::endl << std::endl;
 	

	// Try out converting to little-endian
	std::cout << "The initial value of \"wIdent\" was " << fileInfoBlock.base.wIdent;
	fileInfoBlock.base.wIdent = _byteswap_ushort(fileInfoBlock.base.wIdent);
	std::cout << ", while the new value of is " << fileInfoBlock.base.wIdent << "." << std::endl;

	// Read rest of Fib
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.csw), sizeof(fileInfoBlock.csw));
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.fibRgW), sizeof(fileInfoBlock.csw) * 2);
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.cslw), sizeof(fileInfoBlock.cslw));
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.fibRgLw), sizeof(fileInfoBlock.cslw) * 4);
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.cbRgFcLcb), sizeof(fileInfoBlock.cbRgFcLcb));
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.fibRgFcLcbBlob), sizeof(fileInfoBlock.cbRgFcLcb) * 8);
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.cswNew), sizeof(fileInfoBlock.cswNew));
	docfile.read(reinterpret_cast<char *>(&fileInfoBlock.fibRgCswNew), sizeof(fileInfoBlock.cswNew) * 2);

	std::cout << "The file pointer is now at offset " << docfile.tellg() <<
		" and the size of the File Information Block is " << sizeof(fileInfoBlock) <<
		std::endl << std::endl;

	docfile.close();

	return 0;
}