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
	ULONG fS = 0x200;
	ULONG msk_sgc = 0x1C00;
	ULONG msk_spra = 0xE00;

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
	ULONG temp    = 0x00000000;
	ULONG mask    = 0x3FFFFFFF;
	stream.read(reinterpret_cast<char *>(&temp), sizeof(temp));
	fc = mask & temp;

	const int shift = sizeof(BYTE);
	BYTE temp2 = 0x00;
	BYTE fCmprsd = 0x40;
	BYTE rBit = 0x80;
	stream.seekg(-shift, std::ios::cur);
	stream.read(reinterpret_cast<char *>(&temp2), sizeof(BYTE));
	fCmprsd &= temp2;
	fCompressed = fCmprsd >> 6;
	rBit &= temp2;
	r1 = rBit >> 7;

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
	USHORT fC   = 0x1;

	curstream.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
	fComplex = fC & tmp;
	data = (mask & tmp ) >> 1;

	return;
}

Pcd Pcd::readPcdData(std::ifstream &flsrc)
{
	USHORT temp  = 0x0000;
	USHORT mask  = 0xFFF8;
	BYTE fNPL    = 0x1;
	BYTE fROne   = 0x2;
	BYTE fD      = 0x4;
	BYTE fRTwo   = 0x8;

	flsrc.read(reinterpret_cast<char *>(&temp), sizeof(temp));
	fNoParaLast = fNPL & temp;
	fR1         = (fROne & temp) >> 1;
	fDirty      = (fD & temp) >> 2;
	fR2         = (temp & mask) >> 3;
	
	fc.readFcData(flsrc);
	prm.readPrmData(flsrc);

	return *this;
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
	return (cbSz - 4) / (4 + SIZE_OF_PCD);
}

VOID Clx::Pcdt::readPcdt(std::ifstream &strm, BYTE fstVar)
{
	clxt = fstVar;
	strm.read(reinterpret_cast<char *>(&lcb), sizeof(ULONG));
	
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
		// prc.readPrc(stream, tmpClxt);

		// NB: if this branch is followed, end with a reading of the first 
		// field of the next structure, for a smooth transition
	}
	
	pcdt.readPcdt(stream, tmpClxt);
	
	return;
}


VOID PlcPcd::readPlcPcd(std::ifstream &strm, ULONG num)
{
	// aCP = new ULONG[num]{};
	strm.read(reinterpret_cast<char *>(&aCP), sizeof(ULONG) * (num + 1));
	
	// strm.read(reinterpret_cast<char *>(&aPcd), sizeof(Pcd) * num);
	aPcd = new Pcd[num]{};
	for (size_t i = 0; i < num; i++)
	{
		aPcd[i] = aPcd[i].readPcdData(strm);
	}
	
	return;
}
