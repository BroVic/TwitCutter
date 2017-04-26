#include "Clx.h"

Clx::Prc::PrcData::PrcData()
{
}

Clx::Prc::PrcData::~PrcData()
{
}

Clx::Prc::Prc()
{
}

Clx::Prc::~Prc()
{
}

Clx::Prc::PrcData::Prl::Prl()
{
}

Clx::Prc::PrcData::Prl::~Prl()
{
}

Clx::Prc::PrcData::Prl::Sprm::Sprm()
{
}

Clx::Prc::PrcData::Prl::Sprm::~Sprm()
{
}

Clx::Pcdt::PlcPcd::Pcd::FcCompressed::FcCompressed()
{
}

Clx::Pcdt::PlcPcd::Pcd::FcCompressed::~FcCompressed()
{
}

VOID Clx::Pcdt::PlcPcd::Pcd::FcCompressed::readFcData(std::ifstream &stream)
{
	DWORD temp   = 0;
	DWORD mask   = 0x3FFFFFFF;
	BYTE fCmprsd = 0x40000000;
	BYTE rBit    = 0x80000000;

	stream.read(reinterpret_cast<char *>(&temp), sizeof(temp));
	fc &= mask;
	fCompressed &= fCmprsd >> 30;
	r1 &= rBit >> 31;

	return;
}

Clx::Pcdt::PlcPcd::Pcd::Prm::Prm()
{
}

Clx::Pcdt::PlcPcd::Pcd::Prm::~Prm()
{
}

VOID Clx::Pcdt::PlcPcd::Pcd::Prm::readPrmData(std::ifstream &curstream)
{
	WORD tmp  = 0;
	WORD mask = 0xFFFE;
	BYTE fC   = 0x1;

	curstream.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
	fComplex &= fC;
	data &= mask >> 1;

	return;
}

void Clx::Pcdt::PlcPcd::Pcd::readPcd(std::ifstream &flsrc)
{
	WORD temp  = 0;
	WORD mask  = 0xFFFB;
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

Clx::Pcdt::PlcPcd::Pcd::Pcd()
{
}

Clx::Pcdt::PlcPcd::Pcd::~Pcd()
{
}

Clx::Pcdt::PlcPcd::PlcPcd()
{
}

Clx::Pcdt::PlcPcd::~PlcPcd()
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

VOID Clx::Pcdt::readPcdt(std::ifstream &strm)
{
	strm.read(reinterpret_cast<char *>(this->clxt), sizeof(this->clxt));
	strm.read(reinterpret_cast<char *>(this->lcb), sizeof(this->lcb));
	readPlcPcd(strm, lcb);
	
	return;
}

VOID Clx::readToClx(std::ifstream &stream, DWORD lcb)
{
	BYTE tmpClxt = 0x00;
	int shift    = sizeof(BYTE);
	stream.read(reinterpret_cast<char *>(&tmpClxt), shift);
	stream.seekg(-shift, std::ios::cur);
	if (tmpClxt == 0x01)
	{
		// readPrc();
	}
	
	if (tmpClxt == 0x02)
	{
		
	}
	
	return;
}


VOID Clx::Pcdt::readPlcPcd(std::ifstream &strm)
{
	plcPcd.aCP = new DWORD[lcb]; // ???
	strm.read(reinterpret_cast<char *>(&plcPcd.aCP), lcb);
	plcPcd.aPcd.readPcd(strm);

	return;
}
