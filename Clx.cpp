#include "Clx.h"



Clx::Clx()
{
}

Clx::~Clx()
{
}

VOID Clx::readToClx(std::ifstream & strom)
{
	strom.read(reinterpret_cast<char *>(this), Fib::FibRgFcLcb::FibRgFcLcb97::lcbClx);
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

VOID Sprm::readSprm(std::ifstream &streams)
{
	WORD temp = SET_ZERO;
	streams.read(reinterpret_cast<char *>(&temp), sizeof(temp));
	// ...

	return;
}

Prc::Prc()
{
	clxt = SET_ZERO;
}

Prc::~Prc()
{
}

Pcdt::Pcdt()
{
	clxt = SET_ZERO;
	lcb = SET_ZERO;
}

Pcdt::~Pcdt()
{
}

PrcData::PrcData()
{
	cbGrpprl	= SET_ZERO;
	GrpPrl		= nullptr;
}

PrcData::~PrcData()
{
}


PlcPcd::PlcPcd()
{
	aCP = nullptr;
}

PlcPcd::~PlcPcd()
{
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

Prm::Prm()
{
	fComplex	= SET_BITS_1;
	data		= SET_BITS_15;
}

Prm::~Prm()
{
}
//
//VOID Prm::readPrm(std::ifstream &thisstrm)
//{
//	WORD tmp = SET_ZERO;
//	thisstrm.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
//	// ...
//
//	return;
//}
//
FcCompressed::FcCompressed()
{
	fc			= SET_BITS_30;
	fCompressed = SET_BITS_1;
	r1			= SET_BITS_1;
}

FcCompressed::~FcCompressed()
{
}
//
//VOID FcCompressed::readFccomp(std::ifstream &strming)
//{
//	DWORD temp = SET_ZERO;
//	strming.read(reinterpret_cast<char *>(&temp), sizeof(temp));
//	// ...
//	return;
//}
//
Prl::Prl()
{
}

Prl::~Prl()
{
}
