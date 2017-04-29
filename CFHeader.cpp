#include "CFHeader.h"

// static member variables
ULONG CFHeader::DirSect1;
ULONG CFHeader::Difat[109];

CFHeader::CFHeader()
{
	for (int i = 0; i < 8; i++)
	{
		Sig[i] = SET_ZERO;
	}
	VerMinor          = SET_ZERO;
	VerDll            = SET_ZERO;
	ByteOrder         = SET_ZERO;
	SectorShift       = SET_ZERO;
	MinSectorShift    = SET_ZERO;
	Reserved          = SET_ZERO;
	Reserved2         = SET_ZERO;
	NumDirSects       = SET_ZERO;
	NumFatSects       = SET_ZERO;
	DirSect1          = SET_ZERO;
	TransactSig       = SET_ZERO;
	MiniStrMax        = SET_ZERO;
	MiniFatSect1      = SET_ZERO;
	NumMiniFatSects   = SET_ZERO;
	DifatSect1        = SET_ZERO;
	NumDifatSects     = SET_ZERO;
	for (int i = 0; i < 109; i++) 
	{
		Difat[i] = SET_ZERO; 
	}
}

CFHeader::~CFHeader()
{
}

VOID CFHeader::readCFHeader(std::ifstream & dcstream)
{ 
	 dcstream.read(reinterpret_cast<char *>(&Sig), sizeof(Sig));
	 dcstream.read(reinterpret_cast<char *>(&CLSID_NULL), sizeof(CLSID_NULL));
	 dcstream.read(reinterpret_cast<char *>(&VerMinor), sizeof(VerMinor));
	 dcstream.read(reinterpret_cast<char *>(&VerDll), sizeof(VerDll));
	 dcstream.read(reinterpret_cast<char *>(&ByteOrder), sizeof(ByteOrder));
	 dcstream.read(reinterpret_cast<char *>(&SectorShift), sizeof(SectorShift));
	 dcstream.read(reinterpret_cast<char *>(&MinSectorShift), sizeof(MinSectorShift));
	 dcstream.read(reinterpret_cast<char *>(&Reserved), sizeof(Reserved));
	 dcstream.read(reinterpret_cast<char *>(&Reserved2), sizeof(Reserved2));
	 dcstream.read(reinterpret_cast<char *>(&NumDirSects), sizeof(NumDirSects));
	 dcstream.read(reinterpret_cast<char *>(&NumFatSects), sizeof(NumFatSects));
	 dcstream.read(reinterpret_cast<char *>(&DirSect1), sizeof(DirSect1));
	 dcstream.read(reinterpret_cast<char *>(&TransactSig), sizeof(TransactSig));
	 dcstream.read(reinterpret_cast<char *>(&MiniStrMax), sizeof(MiniStrMax));
	 dcstream.read(reinterpret_cast<char *>(&MiniFatSect1), sizeof(MiniFatSect1));
	 dcstream.read(reinterpret_cast<char *>(&NumMiniFatSects), sizeof(NumMiniFatSects));
	 dcstream.read(reinterpret_cast<char *>(&DifatSect1), sizeof(DifatSect1));
	 dcstream.read(reinterpret_cast<char *>(&NumDifatSects), sizeof(NumDifatSects));
	 dcstream.read(reinterpret_cast<char *>(&Difat), sizeof(Difat));

	 return;
}

std::vector<ULONG> CFHeader::loadFat(std::ifstream & stream, const USHORT szSect) 
{
	std::vector<ULONG> fat;
	
	int i = 0;
	while (Difat[i] != FREESECT)
	{
		ULONG fatValue;
		ULONG offset = (Difat[i] + 1) * szSect;
		stream.seekg(offset, std::ios::beg);
		const ULONG len = szSect / sizeof(fatValue);
		for (ULONG j = 0; j < len; j++)
		{
			stream.read(reinterpret_cast<char *>(&fatValue), sizeof(fatValue));
			fat.push_back(fatValue);
		}
		i++;
	}
	return fat;
}

BOOL CFHeader::use_difat_sect()
{
	if (NumDifatSects == 0 && DifatSect1 == ENDOFCHAIN)
	{
		return false;
	}
	return true;
	
}

ULONG CFHeader::fat_len(std::ifstream& streams, const USHORT sctSz)
{
	ULONG val;
	val = Difat[0];
	val = (val - 1) + NumFatSects;
	val = (val + 1) * sctSz;
	
	ULONG temp[128];
	streams.seekg(val, std::ios::beg);
	streams.read(reinterpret_cast<char *>(&temp), sctSz);
	
	int ovrflw = 0;
	while (temp[ovrflw] != FREESECT)
	{
		ovrflw++;
	}
	val = ((NumFatSects - 1) * sctSz) + ovrflw;

	return val;
}

USHORT CFHeader::set_sector_size() const
{
	return static_cast<USHORT>(pow(2, SectorShift));
}
