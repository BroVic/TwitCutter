#include "CFH.h"

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

GUID::GUID()
{
	 Data1 = _SET_BYTES_;
	 Data2 = _SET_BYTES_;
	 Data3 = _SET_BYTES_;
	 for (int i = 0; i < 8; i++) { Data4[i] = _SET_BYTES_; }
}

GUID::~GUID()
{
}
