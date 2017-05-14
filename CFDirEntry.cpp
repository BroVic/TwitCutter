#include "CFDirEntry.h"

DirEntry::DirEntry()
{
	for (int i = 0; i < 32; i++)
		name[i]		= { };
	nameLength		= { };
	objType			= { };
	colorFlag		= { };
	leftSibID		= { };
	rightSibID		= { };
	childID			= { };
	stateBits		= { };
	startSectorLoc	= { };
	streamSize		= { };
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

inline unsigned int DirEntry::get_direntry_offset(CFHeader &cfh, const USHORT sZ)
{
	return  (cfh.DirSect1 + 1) * sZ;
}

USHORT DirEntry::find_directory(std::ifstream &stream, CFHeader &header, std::u16string str)
{
	const USHORT sectorSize = header.get_sector_size();
	const unsigned int offset = get_direntry_offset(header, sectorSize);
	std::vector<ULONG> fat = header.loadFat(stream, header);

	int sectors = header.DirSect1;

	while (fat[sectors] != ENDOFCHAIN)
	{
		sectors++;
	}

	const int n = ((sectors - header.DirSect1) + 1) * (sectorSize / DIRENTRY_SIZE);
	int id{};
	for (int i = 1; i <= n; i++)
	{
		readDirEntry(stream);
		if (objType == DIR_ROOT || objType == DIR_STORAGE)
		{
			id = childID;
		}
		else if (objType == DIR_STREAM)
		{
			if (((str.length() + 1) * 2) > nameLength)
			{
				id = rightSibID;
			}
			else if (((str.length() + 1) * 2) < nameLength)
			{
				id = leftSibID;
			}
			else
			{
				if (str.compare(name) == 0)
				{
					return (startSectorLoc + 1) * sectorSize;
				}
			}
		}
		stream.seekg(offset, std::ios::beg);
		stream.seekg((id * sizeof(DirEntry)), std::ios::cur);
	}
	return 0;
}
