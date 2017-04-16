// CFDirEntry.h
// Data structure(s) for the Compund File Directory Entry

#ifndef CFDIRENTRY_H_INCLUDED
#define CFDIRENTRY_H_INCLUDED

#include "dtypes.h"

#define MAXREGSID 0xFFFFFFFA
#define NOSTREAM 0xFFFFFFFF

#pragma pack(push, 1)
struct DirEntry
{
	WCHAR name;
	WORD nameLength;
	BYTE objType;
	BYTE colorFlag;
	DWORD leftSibID;
	DWORD rightSibID;
	DWORD childID;
	CLSID clsid;
	DWORD stateBits;
	FILETIME creationTime;
	FILETIME modTime;
	DWORD startSectorLoc;
	ULONGLONG streamSize;
};
#pragma (pop)

#endif // !CFDIRENTRY_H_INCLUDED
