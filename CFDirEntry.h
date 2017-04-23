// CFDirEntry.h
// Data structure(s) for the Compund File Directory Entry

#ifndef CFDIRENTRY_H_INCLUDED
#define CFDIRENTRY_H_INCLUDED

#include "dtypes.h"
#include "CFHeader.h"
#include <fstream>

constexpr DWORD MAXREGSID     = 0xFFFFFFFA;
constexpr DWORD NOSTREAM      = 0xFFFFFFFF;

constexpr BYTE RED            = 0x00;
constexpr BYTE BLACK          = 0x01;

constexpr BYTE DIR_UNUSED     = 0x00;
constexpr BYTE DIR_STORAGE    = 0x01;
constexpr BYTE DIR_STREAM     = 0x02;
constexpr BYTE DIR_ROOT       = 0x05;

struct DirEntry
{
	WCHAR      name[32];
	WORD       nameLength;
	BYTE       objType;
	BYTE       colorFlag;
	DWORD      leftSibID;
	DWORD      rightSibID;
	DWORD      childID;
	CLSID      clsid;
	DWORD      stateBits;
	FILETIME   creationTime;
	FILETIME   modTime;
	DWORD      startSectorLoc;
	ULONGLONG  streamSize;

	DirEntry();
	~DirEntry();

	VOID readDirEntry(std::ifstream &);

	WORD find_directory(std::ifstream&, std::u16string, const int);

};

constexpr BYTE DIRENTRY_SIZE = sizeof(DirEntry);
#endif // !CFDIRENTRY_H_INCLUDED
