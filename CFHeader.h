// CFH.h

// Data structure(s) for the OLE Compound File Header
// (adapted from https://msdn.microsoft.com/en-us/library/dd941946.aspx)

#ifndef CFH_H_INCLUDED
#define CFH_H_INCLUDED

#include <fstream>
#include <vector>
#include <cmath>
#include "dtypes.h"

#define _SET_BYTES_ 0

// Special values for Compound File data structures
#define MAXREGSECT	0xFFFFFFFA
#define RESERVED	0xFFFFFFFB		// not applicable
#define DIFSECT		0xFFFFFFFC
#define FATSECT		0xFFFFFFFD
#define ENDOFCHAIN	0xFFFFFFFE
#define FREESECT	0xFFFFFFFF

#pragma pack(push, 1)
struct OLESSHEADER
{
	BYTE Sig[8];
	CLSID CLSID_NULL;
	WORD VerMinor;
	WORD VerDll;
	WORD ByteOrder;
	WORD SectorShift;
	WORD MinSectorShift;
	WORD Reserved;
	DWORD Reserved2;
	DWORD NumDirSects;
	DWORD NumFatSects;
	DWORD DirSect1;
	DWORD TransactSig;
	DWORD MiniStrMax;
	DWORD MiniFatSect1;
	DWORD NumMiniFatSects;
	DWORD DifatSect1;
	DWORD NumDifatSects;
	DWORD Difat[109];

	OLESSHEADER();
	~OLESSHEADER();

	void readCFHeader(std::ifstream&);
	std::vector<DWORD> loadFat(std::ifstream &);

}; // struct OLESSHEADER
#pragma pack(pop)
#endif // !CFH_H_INCLUDED

