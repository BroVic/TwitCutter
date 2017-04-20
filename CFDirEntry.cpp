#include "CFDirEntry.h"

DirEntry::DirEntry()
{
	for (int i = 0; i < 32; i++)
		name[i]		= SET_BYTES;
	nameLength		= SET_BYTES;
	objType			= SET_BYTES;
	colorFlag		= SET_BYTES;
	leftSibID		= SET_BYTES;
	rightSibID		= SET_BYTES;
	childID			= SET_BYTES;
	stateBits		= SET_BYTES;
	startSectorLoc	= SET_BYTES;
	streamSize		= SET_BYTES;

	down	= nullptr;
	lt		= nullptr;
	rt		= nullptr;
}

DirEntry::~DirEntry()
{
}

void DirEntry::readDirEntry(std::ifstream& flstrm)
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

// Builds a red-black binary search tree
void DirEntry::bldTree(DirEntry& root, std::ifstream& strm, int szObj) const
{
	int dirOffset = strm.tellg();
	szObj /= sizeof(DirEntry);
	DirEntry* trav	=  &root;
	do
	{
		// introduce conditioning HERE to decide which pointer to link to allocated object
		bool downOpen;
		bool rightOpen;
		bool leftOpen;

		if (trav->childID == NOSTREAM)
		{
			downOpen = false;
		}
		if (trav->rightSibID == NOSTREAM)
		{
			rightOpen = false;
		}
		if (trav->leftSibID == NOSTREAM)
		{
			leftOpen = false;
		}
		
		if (downOpen || rightOpen || leftOpen)
		{
			int sectNum = 0;
			if (downOpen)
			{
				trav->down = new (std::nothrow) DirEntry;
				trav = trav->down;
				sectNum = trav->childID;
			}
			else if (rightOpen)
			{
				trav->rt = new (std::nothrow) DirEntry;
				trav = trav->rt;
				sectNum = trav->rightSibID;
			}
			else if (leftOpen)
			{
				trav->lt = new (std::nothrow) DirEntry;
				trav = trav->lt;
				sectNum = trav->leftSibID;
			}
			
			strm.seekg(dirOffset, std::ios::beg);
			strm.seekg(szObj * sectNum);
			trav->readDirEntry(strm);
		}
	} while (true);

	return;
}

// Finds the stream for a particular Directory Entry and returns its offset
int DirEntry::fndDrctStrm(std::u16string str, const int sctSz) const
{
	DirEntry* tracker = nullptr;
	
	if (this->objType == DIR_ROOT)
	{
		tracker = this->down;
	}
	
	if (tracker->objType == DIR_STORAGE)
	{
		tracker = tracker->down;
	}

	if (tracker->objType == DIR_STREAM)
	{
		if (str.length() > tracker->nameLength)
		{
			tracker = tracker->rt;
		}
		else if (str.length() < tracker->nameLength)
		{
			tracker = tracker->lt;
		}
		else
		{
			// iterate through strings and compare
		}
	}
	return (tracker->startSectorLoc + 1) * sctSz;
}