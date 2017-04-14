// CFH.h

// Data structure(s) for the OLE Compound File Header
// (adapted from https://msdn.microsoft.com/en-us/library/dd941946.aspx)

#ifndef CFH_H_INCLUDED
#define CFH_H_INCLUDED

#include <cstdint>

// struct GUID;					// promise

using BYTE = uint8_t;
using WORD = uint16_t;
using DWORD = uint32_t;
using LONG = int32_t;
// using CLSID = GUID;

#define _SET_BYTES_ 0


#pragma pack(push, 1)
typedef struct GUID
{
	DWORD Data1;
	WORD Data2;
	WORD Data3;
	BYTE Data4[8];

	GUID();
	~GUID();
} CLSID; // struct GUID

struct OLESSHEADER
{
	BYTE Sig[8];
	CLSID clsid;
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

