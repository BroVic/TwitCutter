#include "CFDirEntry.h"

DirEntry::DirEntry()
{
	for (int i = 0; i < 32; i++)
		name[i]		= SET_ZERO;
	nameLength		= SET_ZERO;
	objType			= SET_ZERO;
	colorFlag		= SET_ZERO;
	leftSibID		= SET_ZERO;
	rightSibID		= SET_ZERO;
	childID			= SET_ZERO;
	stateBits		= SET_ZERO;
	startSectorLoc	= SET_ZERO;
	streamSize		= SET_ZERO;
}

DirEntry::~DirEntry()
{
}

VOID DirEntry::readDirEntry(std::ifstream& flstrm)
{
	flstrm.read(reinterpret_cast<char *>(&name), sizeof(name));
	flstrm.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
	flstrm.read(reinterpret_cast<char *>(&objType), sizeof(objType));
	flstrm.read(reinterpret_cast<char *>(&colorFlag), sizeof(colorFlag));
	flstrm.read(reinterpret_cast<char *>(&leftSibID), sizeof(leftSibID));
	flstrm.read(reinterpret_cast<char *>(&rightSibID), sizeof(rightSibID));
	flstrm.read(reinterpret_cast<char *>(&childID), sizeof(childID));
	flstrm.read(reinterpret_cast<char *>(&clsid), sizeof(clsid));
	flstrm.read(reinterpret_cast<char *>(&stateBits), sizeof(stateBits));
	flstrm.read(reinterpret_cast<char *>(&creationTime), sizeof(creationTime));
	flstrm.read(reinterpret_cast<char *>(&modTime), sizeof(modTime));
	flstrm.read(reinterpret_cast<char *>(&startSectorLoc), sizeof(startSectorLoc));
	flstrm.read(reinterpret_cast<char *>(&streamSize), sizeof(streamSize));

	return;
}

USHORT DirEntry::find_directory(std::ifstream& stream, std::u16string str, CFHeader &obj)
{
	const int d1      = obj.DirSect1;
	const int sctSz   = obj.set_sector_size();
	const int offset  = (d1 + 1) * sctSz;
	
	std::vector<ULONG> fat  = obj.loadFat(stream, sctSz);
	int sectors             = d1;

	while (fat[sectors] != ENDOFCHAIN)
	{
		sectors++;
	}

	const int n = ((sectors - d1) + 1) * (sctSz / DIRENTRY_SIZE);
	int id = 0;
	for (int i = 1; i <= n; i++)
	{
		if (this->objType == DIR_ROOT || this->objType == DIR_STORAGE)
		{
			id = this->childID;
		}
		else if (this->objType == DIR_STREAM)
		{
			if (((str.length() + 1) * 2) > this->nameLength)
			{
				id = this->rightSibID;
			}
			else if (((str.length() + 1) * 2) < this->nameLength)
			{
				id = this->leftSibID;
			}
			else
			{
				if (str.compare(this->name) == 0)
				{
					return (this->startSectorLoc + 1) * sctSz;
				}
			}
		} 
		stream.seekg(offset, std::ios::beg);
		stream.seekg((id * sizeof(DirEntry)), std::ios::cur);
		this->readDirEntry(stream);
	}
	return 0;
}
