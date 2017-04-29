// CFH.h

// Data structure(s) for the OLE Compound File Header
// (adapted from https://msdn.microsoft.com/en-us/library/dd941946.aspx)

#ifndef CFH_H_INCLUDED
#define CFH_H_INCLUDED

#include <fstream>
#include <vector>
#include <cmath>
#include "dtypes.h"

// Special values for Compound File data structures
constexpr ULONG MAXREGSECT  = 0xFFFFFFFA;
constexpr ULONG RESERVED    = 0xFFFFFFFB;		// not applicable
constexpr ULONG DIFSECT     = 0xFFFFFFFC;
constexpr ULONG FATSECT     = 0xFFFFFFFD;
constexpr ULONG ENDOFCHAIN  = 0xFFFFFFFE;
constexpr ULONG FREESECT    = 0xFFFFFFFF;

#pragma pack(push, 1)
struct CFHeader
{
	BYTE Sig[8];
	CLSID CLSID_NULL;
	USHORT VerMinor;
	USHORT VerDll;
	USHORT ByteOrder;
	USHORT SectorShift;
	USHORT MinSectorShift;
	USHORT Reserved;
	ULONG Reserved2;
	ULONG NumDirSects;
	ULONG NumFatSects;
	static ULONG DirSect1;
	ULONG TransactSig;
	ULONG MiniStrMax;
	ULONG MiniFatSect1;
	ULONG NumMiniFatSects;
	ULONG DifatSect1;
	ULONG NumDifatSects;
	static ULONG Difat[109];

	CFHeader();
	~CFHeader();

	VOID readCFHeader(std::ifstream&);
	static std::vector<ULONG> loadFat(std::ifstream&, const USHORT);
	BOOL use_difat_sect();
	ULONG fat_len(std::ifstream&, const USHORT);
	
	USHORT set_sector_size() const;


}; // struct CFHeader
#pragma pack(pop)
#endif // !CFH_H_INCLUDED

