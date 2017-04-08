// TwitCutter
//
// CmdMain.cpp
// Main source file for command-line access to the application
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include "FIB.h"
#include "Clx.h"

using namespace std;

void printFibBase(dtdoc::FibBase obj)
{
	cout << "The value of \"wIdent\" is " << hex << uppercase << obj.wIdent << endl;
	cout << "The value of \"nFib\" is " << obj.nFib << endl;
	cout << "The value of \"unused\" is " << obj.unused << endl;
	cout << "The value of \"lid\" is " << obj.lid << endl;
	cout << "The value of \"pnNext is " << obj.pnNext << endl;
	cout << "The value of \"fDot\" is " << obj.fDot << endl;
	cout << "The value of \"fGlsy\" is " << obj.fGlsy << endl;
	cout << "The value of \"fComplex\" is " << obj.fComplex << endl;
	cout << "The value of \"fHasPic\" is " << obj.fHasPic << endl;
	cout << "The value of \"cQuickSaves\" is " << obj.cQuickSaves << endl;
	cout << "The value of \"fEncrypted\" is " << obj.fEncrypted << endl;
	cout << "The value of \"fWhichTblStm\" is " << obj.fWhichTblStm << endl;
	cout << "The value of \"fReadOnlyRecommended\" is " << obj.fReadOnlyRecommended << endl;
	cout << "The value of \"fWriteReservation\" is " << obj.fWriteReservation << endl;
	cout << "The value of \"fExtChar\" is " << obj.fExtChar << endl;
	cout << "The value of \"fLoadOverride\" is " << obj.fLoadOverride << endl;
	cout << "The value of \"fFarEast\" is " << obj.fFarEast << endl;
	cout << "The value of \"fObfuscated\" is " << obj.fObfuscated << endl;
	cout << "The value of \"lkey\" is " << obj.lkey << endl;
	cout << "The value of \"envr\" is " << obj.envr << endl;
	cout << "The value of \"fMac\" is " << obj.fMac << endl;
	cout << "The value of \"fHasPic\" is " << obj.fHasPic << endl;
	cout << "The value of \"fEmptySpecial\" is " << obj.fEmptySpecial << endl;
	cout << "The value of \"fLoadOverridePage\" is " << obj.fLoadOverridePage << endl;
	cout << "The value of \"reserved1\" is " << obj.reserved1 << endl;
	cout << "The value of \"reserved2\" is " << obj.reserved2 << endl;
	cout << "The value of \"fSpare0\" is " << obj.fSpare0 << endl;
	cout << "The value of \"reserved3\" is " << obj.reserved3 << endl;
	cout << "The value of \"reserved4\" is " << obj.reserved4 << endl;
	cout << "The value of \"reserved5\" is " << obj.reserved5 << endl;
	cout << "The value of \"reserved6\" is " << obj.reserved6 << endl << endl << endl;

	return;
}
// const unsigned int szFibBs = 32;
// ifstream::pos_type szFibBs = 32;

int main()
{
	dtdoc::FibBase infoblkBase;
	ifstream docfile;

	docfile.open("test.doc");

	if (!docfile.is_open())
	{
		cerr << "Could not open the file." << endl;
		return 0x001;
	}

	if (!docfile.good())
	{
		cerr << "The file is probably corrupted." << endl;
		return 0x002;
	}
	
	// Read members one after the other
	docfile.seekg(0, ios::beg);
		
	docfile.read(reinterpret_cast<char *>(&infoblkBase.wIdent), sizeof(infoblkBase.wIdent));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.nFib), sizeof(infoblkBase.nFib));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.unused), sizeof(infoblkBase.unused));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.lid), sizeof(infoblkBase.lid));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.pnNext), sizeof(infoblkBase.pnNext));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fDot), sizeof(infoblkBase.fDot));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fGlsy), sizeof(infoblkBase.fGlsy));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fComplex), sizeof(infoblkBase.fComplex));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fHasPic), sizeof(infoblkBase.fHasPic));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.cQuickSaves), sizeof(infoblkBase.cQuickSaves));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fEncrypted), sizeof(infoblkBase.fEncrypted));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fWhichTblStm), sizeof(infoblkBase.fWhichTblStm));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fReadOnlyRecommended), sizeof(infoblkBase.fReadOnlyRecommended));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fWriteReservation), sizeof(infoblkBase.fWriteReservation));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fExtChar), sizeof(infoblkBase.fExtChar));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fLoadOverride), sizeof(infoblkBase.fLoadOverride));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fFarEast), sizeof(infoblkBase.fFarEast));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fObfuscated), sizeof(infoblkBase.fObfuscated));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.nFibBack), sizeof(infoblkBase.nFibBack));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.lkey), sizeof(infoblkBase.lkey));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.envr), sizeof(infoblkBase.envr));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fMac), sizeof(infoblkBase.fMac));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fEmptySpecial), sizeof(infoblkBase.fEmptySpecial));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fLoadOverridePage), sizeof(infoblkBase.fLoadOverridePage));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.reserved1), sizeof(infoblkBase.reserved1));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.reserved2), sizeof(infoblkBase.reserved2));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.fSpare0), sizeof(infoblkBase.fSpare0));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.reserved3), sizeof(infoblkBase.reserved3));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.reserved4), sizeof(infoblkBase.reserved4));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.reserved5), sizeof(infoblkBase.reserved5));
	docfile.read(reinterpret_cast<char *>(&infoblkBase.reserved6), sizeof(infoblkBase.reserved6));

	// Testing...
	cout << showbase << internal;
	printFibBase(infoblkBase);

	// Try again, reading entire structure in one go.
	docfile.seekg(0, ios::beg);
	docfile.read(reinterpret_cast<char *>(&infoblkBase), sizeof(infoblkBase));
	printFibBase(infoblkBase);
	
	docfile.close();

	return 0x00;
}