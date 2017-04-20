#include "Clx.h"

Clx::Clx()
{
}

Clx::~Clx()
{
}

void Clx::readClx(std::ifstream & strom)
{
	Prc::readPrc(strom);
	Pcdt::readPcdt(strom);

	return;
}

Sprm::Sprm()
{
	ispmd	= SET_BITS_9;
	fspec	= SET_BITS_1;
	sgc		= SET_BITS_3;
	spra	= SET_BITS_3;
	
}

Sprm::~Sprm()
{
}

void Sprm::readSprm(std::ifstream &streams)
{
	WORD temp = SET_BYTES;
	streams.read(reinterpret_cast<char *>(&temp), sizeof(temp));
	// ...

	return;
}

Prc::Prc()
{
	clxt = SET_BYTES;
}

Prc::~Prc()
{
}

void Prc::readPrc(std::ifstream & filestream)
{
	filestream.read(reinterpret_cast<char *>(&clxt), sizeof(clxt));
	readPcdt(filestream);

	return;
}

Pcdt::Pcdt()
{
	clxt = SET_BYTES;
	lcb = SET_BYTES;
}

Pcdt::~Pcdt()
{
}

void Pcdt::readPcdt(std::ifstream &docstream)
{
	docstream.read(reinterpret_cast<char *>(&clxt), sizeof(clxt));
	docstream.read(reinterpret_cast<char *>(&lcb), sizeof(lcb));
	readPlcpcd(docstream);
	return;
}

PrcData::PrcData()
{
	cbGrpprl	= SET_BYTES;
	GrpPrl		= nullptr;
}

PrcData::~PrcData()
{
}

void PrcData::readPrcdata(std::ifstream &streem)
{
	streem.read(reinterpret_cast<char *>(&cbGrpprl), sizeof(cbGrpprl));
	readPrl(streem);

	return;
}

PlcPcd::PlcPcd()
{
	aCP = nullptr;
}

PlcPcd::~PlcPcd()
{
}

void PlcPcd::readPlcpcd(std::ifstream & docstr)
{
	docstr.read(reinterpret_cast<char *>(&aCP), sizeof(aCP));
	readPcd(docstr);
	return;
}

Pcd::Pcd()
{
	fNoParaLast = SET_BITS_1;
	fR1			= SET_BITS_1;
	fDirty		= SET_BITS_1;
	fR2			= SET_BITS_13;
}

Pcd::~Pcd()
{
}

void Pcd::readPcd(std::ifstream &dstream)
{
	WORD tmp = SET_BYTES;
	dstream.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
	// ...

	readFccomp(dstream);
	readPrm(dstream);

	return;
}

Prm::Prm()
{
	fComplex	= SET_BITS_1;
	data		= SET_BITS_15;
}

Prm::~Prm()
{
}

void Prm::readPrm(std::ifstream &thisstrm)
{
	WORD tmp = SET_BYTES;
	thisstrm.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
	// ...

	return;
}

FcCompressed::FcCompressed()
{
	fc			= SET_BITS_30;
	fCompressed = SET_BITS_1;
	r1			= SET_BITS_1;
}

FcCompressed::~FcCompressed()
{
}

void FcCompressed::readFccomp(std::ifstream &strming)
{
	DWORD temp = SET_BYTES;
	strming.read(reinterpret_cast<char *>(&temp), sizeof(temp));
	// ...
	return;
}

Prl::Prl()
{
}

Prl::~Prl()
{
}

void Prl::readPrl(std::ifstream &mystrm)
{
	
	Sprm::readSprm(mystrm);
	return;
}

//offset = fileInfoBlock.fibRgFcLcbBlob.fibRgFcLcb97.fcClx;
//int szClx = fileInfoBlock.fibRgFcLcbBlob.fibRgFcLcb97.lcbClx;
//stream.seekg(offset, std::ios::cur);
//stream.read(reinterpret_cast<char *>(&charProc), sizeof(charProc));