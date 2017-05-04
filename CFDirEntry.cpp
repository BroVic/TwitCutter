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

