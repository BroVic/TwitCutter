// CFH.h

// Data structure(s) for the OLE Compound File Header
// (adapted from https://msdn.microsoft.com/en-us/library/dd941946.aspx)

#ifndef CFH_H_INCLUDED
#define CFH_H_INCLUDED

#include "dtypes.h"

#define _SET_BYTES_ 0


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
}; // struct OLESSHEADER
#pragma pack(pop)

#endif // !CFH_H_INCLUDED

