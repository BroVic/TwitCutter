// CFDirEntry.h
// Data structure(s) for the Compund File Directory Entry

#ifndef CFDIRENTRY_H_INCLUDED
#define CFDIRENTRY_H_INCLUDED

#include "dtypes.h"
#include <fstream>

#define MAXREGSID 0xFFFFFFFA
#define NOSTREAM  0xFFFFFFFF

#define RED		0xOO
#define BLACK	0x01

#define DIR_UNUSED  0x00
#define DIR_STORAGE 0x01
#define DIR_STREAM  0x02
#define DIR_ROOT    0x05

struct DirEntry
{
	WCHAR name[32];
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

	DirEntry* down;
	DirEntry* lt;
	DirEntry* rt;

	DirEntry();
	~DirEntry();
	void readDirEntry(std::ifstream &);
	void bldTree(DirEntry&, std::ifstream&, int) const;
	int fndDrctStrm(std::u16string, const int) const;
};
#endif // !CFDIRENTRY_H_INCLUDED
