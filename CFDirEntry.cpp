#include "CFDirEntry.h"

DirEntry::DirEntry()
{
	for (int i = 0; i < 32; i++)
		name[i] = SET_BYTES;
	nameLength = SET_BYTES;
	objType = SET_BYTES;
	colorFlag = SET_BYTES;
	leftSibID = SET_BYTES;
	rightSibID = SET_BYTES;
	childID = SET_BYTES;
	// clsid;
	stateBits = SET_BYTES;
	// creationTime = SET_BYTES;
	// modTime = SET_BYTES;
	startSectorLoc = SET_BYTES;
	streamSize = SET_BYTES;
}

DirEntry::~DirEntry()
{
}
