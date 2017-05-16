#include "Clx.h"

Clx::Prc::PrcData::Prl::Sprm::Sprm()
{
	ispmd = {};
	fSpec = {};
	sgc   = {};
	spra  = {};
}

Clx::Prc::PrcData::Prl::Sprm::~Sprm()
{
}

Clx::Prc::PrcData::Prl::Prl()
{
}

Clx::Prc::PrcData::Prl::~Prl()
{
}

Clx::Prc::PrcData::PrcData()
{
	cbGrpprl = {};
}

Clx::Prc::PrcData::~PrcData()
{
}

Clx::Prc::Prc()
{
	clxt = {};
}

Clx::Prc::~Prc()
{
}

Clx::Pcdt::PlcPcd::Pcd::Prm::Prm()
{
	fComplex = {};
	data     = {};
}

Clx::Pcdt::PlcPcd::Pcd::Prm::~Prm()
{
}

Clx::Pcdt::PlcPcd::Pcd::FcCompressed::FcCompressed()
{
	fc          = {};
	fCompressed = {};
	r1          = {};
}

Clx::Pcdt::PlcPcd::Pcd::FcCompressed::~FcCompressed()
{
}

Clx::Pcdt::PlcPcd::Pcd::Pcd()
{
	fNoParaLast = {};
	fR1         = {};
	fDirty      = {};
	fR2         = {};
	fc          = {};
}

Clx::Pcdt::PlcPcd::Pcd::~Pcd()
{
}

Clx::Pcdt::PlcPcd::PlcPcd()
{
	aCP  = nullptr;
	aPcd = nullptr;
}

Clx::Pcdt::PlcPcd::~PlcPcd()
{
	delete aCP;
	delete aPcd;
}

Clx::Pcdt::Pcdt()
{
	clxt = {};
	lcb = {};
}

Clx::Pcdt::~Pcdt()
{
}

Clx::Clx()
{
	rgPrc = nullptr;
}

Clx::~Clx()
{
}

VOID Clx::Prc::PrcData::Prl::Sprm::readSprm(std::ifstream &stream)
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

VOID Clx::Pcdt::PlcPcd::Pcd::FcCompressed::readFcData(std::ifstream &stream)
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

VOID Clx::Pcdt::PlcPcd::Pcd::Prm::readPrmData(std::ifstream &curstream)
{
	USHORT tmp  = 0;
	USHORT mask = 0xFFFE;
	USHORT fC   = 0x1;

	curstream.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
	fComplex = fC & tmp;
	data = (mask & tmp ) >> 1;

	return;
}

VOID Clx::Pcdt::PlcPcd::Pcd::readPcdData(std::ifstream &flsrc)
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

	return;
}

// Computes the number of elements in a Pcd array
inline ULONG Clx::Pcdt::PlcPcd::pcdLength(Clx& cobj)
{
	return (cobj.pcdt.lcb - 4) / (4 + SIZE_OF_PCD);
}

// Reads from filestream into a Pcdt structure
VOID Clx::Pcdt::readPcdt(std::ifstream &strm, BYTE fstVar, Clx &obj)
{
	clxt = fstVar;
	strm.read(reinterpret_cast<char *>(&lcb), sizeof(ULONG));
	ULONG numArr = obj.pcdt.plcPcd.pcdLength(obj);
	plcPcd.readPlcPcd(strm, numArr);

	return;
}

// Decides on how to start reading the structure
VOID Clx::readToClx(std::ifstream &stream)
{
	BYTE tmpClxt{};
	stream.read(reinterpret_cast<char *>(&tmpClxt), sizeof(BYTE));

	if (tmpClxt == 0x01)
	{
		// prc.readPrc(stream, tmpClxt);

		// NB: if this branch is followed, end with a reading of the first
		// field of the next structure, for a smooth transition
	}
	
	pcdt.readPcdt(stream, tmpClxt, *this);
	
	return;
}

// Reads from filestream into a PlPcd structure
VOID Clx::Pcdt::PlcPcd::readPlcPcd(std::ifstream &strm, ULONG num)
{
	num++;
	aCP = new (std::nothrow) ULONG[num]{};
	if (aCP == 0)
	{
		std::cerr << "Requested memory could not be allocated" << std::endl;
	}

	for (size_t i = 0; i < num; i++)
	{
		strm.read(reinterpret_cast<char *>(&aCP[i]), sizeof(ULONG));
	}
	
	--num;
	aPcd = new Pcd[num]{};
	aPcd = new (std::nothrow) Pcd[num]{};
	if (aPcd == 0)
	{
		std::cerr << "Requested memory could not be allocated" << std::endl;
	}

	for (size_t i = 0; i < num; i++)
	{
		aPcd[i].readPcdData(strm);
	}

	return;
}

// Gets the stream offset for a specific character position
USHORT Clx::Pcdt::PlcPcd::Pcd::defineOffset() const
{
	return fc.fc;	
}

// Get the encoding to be used
LONG Clx::Pcdt::PlcPcd::Pcd::defineEncoding() const
{
	return static_cast<LONG>(fc.fCompressed);
}

// Gets a character position
ULONG Clx::Pcdt::PlcPcd::getCharPos(int ind)
{
	return aCP[ind];
}