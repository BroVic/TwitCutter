#include "Clx.h"

Prc::PrcData::PrcData()
{
}

Prc::PrcData::~PrcData()
{
}

Prc::Prc()
{
}

Prc::~Prc()
{
}

Prl::Prl()
{
}

Prl::~Prl()
{
}

Prl::Sprm::Sprm()
{
}

Prl::Sprm::~Sprm()
{
}

VOID Prl::Sprm::readSprm(std::ifstream &stream)
{
	USHORT tmp = 0x0000;
	stream.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));

	ULONG msk_ispmd = 0x1FF;
	BYTE fS = 0x200;
	BYTE msk_sgc = 0x1C00;
	BYTE msk_spra = 0xE00;

	ispmd = tmp & msk_ispmd;
	fSpec = (tmp & fS) >> 9;
	sgc = (tmp & msk_sgc) >> 10;
	spra = (tmp & msk_spra) >> 13;

	return;
}

Pcd::FcCompressed::FcCompressed()
{
}

Pcd::FcCompressed::~FcCompressed()
{
}

VOID Pcd::FcCompressed::readFcData(std::ifstream &stream)
{
	ULONG temp   = 0;
	ULONG mask   = 0x3FFFFFFF;
	BYTE fCmprsd = 0x40000000;
	BYTE rBit    = 0x80000000;

	stream.read(reinterpret_cast<char *>(&temp), sizeof(temp));
	fc &= mask;
	fCompressed &= fCmprsd >> 30;
	r1 &= rBit >> 31;

	return;
}
Pcd::Prm::Prm()

{
}

Pcd::Prm::~Prm()
{
}

VOID Pcd::Prm::readPrmData(std::ifstream &curstream)
{
	USHORT tmp  = 0;
	USHORT mask = 0xFFFE;
	BYTE fC   = 0x1;

	curstream.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
	fComplex &= fC;
	data &= mask >> 1;

	return;
}

void Pcd::readPcd(std::ifstream &flsrc)
{
	USHORT temp  = 0;
	USHORT mask  = 0xFFFB;
	BYTE fNPL  = 0x1;
	BYTE fROne = 0x2;
	BYTE fD    = 0x4;
	BYTE fRTwo = 0x8;

	flsrc.read(reinterpret_cast<char *>(&temp), sizeof(temp));
	fNoParaLast = fNPL & temp;
	fR1         = (fROne & temp) >> 1;
	fDirty      = (fD & temp) >> 2;
	fR2         = (temp & mask) >> 3;
	
	fc.readFcData(flsrc);
	prm.readPrmData(flsrc);

	return;
}

Pcd::Pcd()
{
}

Pcd::~Pcd()
{
}

PlcPcd::PlcPcd()
{
}

PlcPcd::~PlcPcd()
{
}

Clx::Pcdt::Pcdt()
{
}

Clx::Pcdt::~Pcdt()
{
}

Clx::Clx()
{
}

Clx::~Clx()
{
}

inline ULONG Clx::Pcdt::calcArrayLength(ULONG cbSz)
{
	return (cbSz - 4) / (4 + sizeof(Pcd));
}

VOID Clx::Pcdt::readPcdt(std::ifstream &strm)
{
	ULONG numArr = calcArrayLength(lcb);

	plcPcd.readPlcPcd(strm, numArr);
	
	return;
}

// Decides on how to start reading the structure
VOID Clx::readToClx(std::ifstream &stream)
{
	BYTE tmpClxt = 0x00;
	stream.read(reinterpret_cast<char *>(&tmpClxt), sizeof(BYTE));

	if (tmpClxt == 0x01)
	{
		// prc.readPrc();

		// NB: if this branch is followed, end with a reading of the first 
		// field of the next structure, for a smooth transition
	}
	
	pcdt.readPcdt(stream);
	
	return;
}


VOID PlcPcd::readPlcPcd(std::ifstream &strm, ULONG num)
{
	for (int i = 0; i < (num +1); i++)
	{
		strm.read(reinterpret_cast<char *>(aCP), sizeof(ULONG));
	}

	for (int i = 0; i < num; i++)
	{
		aPcd[i].readPcd(strm);
	}

	return;
}
