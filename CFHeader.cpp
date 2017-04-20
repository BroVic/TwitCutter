#include "CFHeader.h"

OLESSHEADER::OLESSHEADER()
{
	for (int i = 0; i < 8; i++)
		Sig[i] = _SET_BYTES_;
	VerMinor = _SET_BYTES_;
	VerDll = _SET_BYTES_;
	ByteOrder = _SET_BYTES_;
	SectorShift = _SET_BYTES_;
	MinSectorShift = _SET_BYTES_;
	Reserved = _SET_BYTES_;
	Reserved2 = _SET_BYTES_;
	NumDirSects = _SET_BYTES_;
	NumFatSects = _SET_BYTES_;
	DirSect1 = _SET_BYTES_;
	TransactSig = _SET_BYTES_;
	MiniStrMax = _SET_BYTES_;
	MiniFatSect1 = _SET_BYTES_;
	NumMiniFatSects = _SET_BYTES_;
	DifatSect1 = _SET_BYTES_;
	NumDifatSects = _SET_BYTES_;
	for (int i = 0; i < 109; i++) { Difat[i] = _SET_BYTES_; }
}

OLESSHEADER::~OLESSHEADER()
{
}

void OLESSHEADER::readCFHeader(std::ifstream & dcstream)
{
	 Sig;
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

std::vector<DWORD> OLESSHEADER::loadFat(std::ifstream & stream)
{
	const int szSect = static_cast<int>(pow(2, SectorShift));
	// int lnFat = NumFatSects * szSect;
	std::vector<DWORD> fat;
	
	int i = 0;
	while (Difat[i] != FREESECT)
	{
		DWORD fatValue;
		int offset = Difat[i + 1] * szSect;
		stream.seekg(offset, std::ios::beg);
		for (int j = 0; j < szSect; j++)
		{
			stream.read(reinterpret_cast<char *>(&fatValue), sizeof(fatValue));
			fat.push_back(fatValue);
		}
		i++;
	}
	return fat;
}
