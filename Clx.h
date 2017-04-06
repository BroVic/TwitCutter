// Clx.h
// 

#include <cstdint>
#include "FIB.h"

struct Sprm
{
	BYTE ispmd;
	// A - fspec
	// sgc
	// spra
};

struct Prl
{
	WORD sprm;
};

struct FcCompressed
{
	BYTE fc : 30;
	BYTE fCompressed : 1;
	BYTE r1 : 1;
};

struct Prm
{
	BYTE fComplex : 1;
	BYTE data : 15;
};

struct Pcd
{
	BYTE fNoParaLast : 1;
	BYTE fR1 : 1;
	BYTE fDirty : 1;
	BYTE fR2 : 13;
	FcCompressed fc;
	Prm prm;
};

struct PlcPcd
{
	DWORD *aCP;
	Pcd aPcd;
};

struct PrcData
{
	WORD cbGrpprl;
	Prl *GrpPrl;
};

struct Pcdt
{
	BYTE clxt;
	DWORD lcb;
	PlcPcd PlcPcd;
};

struct Prc
{
	BYTE clxt;
	PrcData data;
};

struct Clx
{
	Prc *RgPrc;
	Pcdt Pcdt;
};