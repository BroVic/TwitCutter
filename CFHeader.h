// CFH.h

// Data structure(s) for the OLE Compound File Header
// (adapted from https://msdn.microsoft.com/en-us/library/dd941946.aspx)

#ifndef CFH_H_INCLUDED
#define CFH_H_INCLUDED

#include <fstream>
#include <vector>
#include <cmath>
#include "dtypes.h"

#define SET_ZERO 0

// Special values for Compound File data structures
const DWORD MAXREGSECT  = 0xFFFFFFFA;
const DWORD RESERVED    = 0xFFFFFFFB;		// not applicable
const DWORD DIFSECT     = 0xFFFFFFFC;
const DWORD FATSECT     = 0xFFFFFFFD;
const DWORD ENDOFCHAIN  = 0xFFFFFFFE;
const DWORD FREESECT    = 0xFFFFFFFF;

#pragma pack(push, 1)
struct CFHeader
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
	static DWORD DirSect1;
	DWORD TransactSig;
	DWORD MiniStrMax;
	DWORD MiniFatSect1;
	DWORD NumMiniFatSects;
	DWORD DifatSect1;
	DWORD NumDifatSects;
	static DWORD Difat[109];

	CFHeader();
	~CFHeader();

	VOID readCFHeader(std::ifstream&);
	static std::vector<DWORD> loadFat(std::ifstream&, const WORD);
	BOOL use_difat_sect();
	DWORD fat_len(std::ifstream&, const WORD);
	
	WORD set_sector_size() const;


}; // struct CFHeader
#pragma pack(pop)
#endif // !CFH_H_INCLUDED

