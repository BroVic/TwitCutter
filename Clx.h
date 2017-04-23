// Clx.h
// Define in-memory data structures for use with MS-Word .DOC Clx format

#ifndef CLX_H_INCLUDED
#define CLX_H_INCLUDED

#include <fstream>
#include "dtypes.h"
#include "FIB.h"

#define SET_BITS_1	0x0
#define SET_BITS_3	0x0
#define SET_BITS_9	0x0
#define SET_BITS_13 0x0
#define SET_BITS_15 0x0
#define SET_BITS_30 0x0

#pragma pack(push, 1)
struct Sprm
{

	WORD ispmd : 9;
	BYTE fspec : 1;
	BYTE sgc : 3;
	BYTE spra : 3;

	Sprm();
	~Sprm();

	VOID readSprm(std::ifstream&);

};

struct Prl
{
	Sprm sprm;

	Prl();
	~Prl();
	VOID readPrl(std::ifstream&);
}; // struct Prl

struct FcCompressed
{
	DWORD fc : 30;
	BYTE fCompressed : 1;
	BYTE r1 : 1;

	FcCompressed();
	~FcCompressed();

	VOID readFccomp(std::ifstream&);
}; // struct FcCompressed

struct Prm
{
	BYTE fComplex : 1;
	WORD data : 15;

	Prm();
	~Prm();

	VOID readPrm(std::ifstream&);
}; // struct Prm

struct Pcd
{
	BYTE fNoParaLast : 1;
	BYTE fR1 : 1;
	BYTE fDirty : 1;
	WORD fR2 : 13;
	FcCompressed fc;
	Prm prm; 

	Pcd();
	~Pcd();

	VOID readPcd(std::ifstream&);
}; // struct Pcd

struct PlcPcd
{
	DWORD *aCP;
	Pcd aPcd;

	PlcPcd();
	~PlcPcd();

	VOID readPlcpcd(std::ifstream&);

}; // struct PlcPcd

struct PrcData
{
	WORD cbGrpprl;
	Prl *GrpPrl;

	PrcData();
	~PrcData();

	VOID readPrcdata(std::ifstream&);
}; // struct PrcData

struct Pcdt
{
	BYTE clxt;
	DWORD lcb;
	PlcPcd plcPcd;

	Pcdt();
	~Pcdt();

	VOID readPcdt(std::ifstream&);
}; // struct Pcdt

struct Prc
{
	BYTE clxt;
	PrcData data;

	Prc();
	~Prc();

	VOID readPrc(std::ifstream&);
}; // struct Prc

struct Clx
{
	Prc *RgPrc;
	Pcdt Pcdt;

	Clx();
	~Clx();

	VOID readToClx(std::ifstream&);
}; // struct Clx
#pragma pack(pop)
#endif // !CLX_H_INCLUDED