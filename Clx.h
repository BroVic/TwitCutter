// Clx.h
// Define in-memory data structures for use with MS-Word .DOC Clx format

#include <fstream>
#include "dtypes.h"
#include "FIB.h"

#ifndef CLX_H_INCLUDED
#define CLX_H_INCLUDED

#define SET_BYTES	0x00
#define SET_BITS_1	0x00
#define SET_BITS_3	0x00
#define SET_BITS_9	0x00
#define SET_BITS_13 0x00
#define SET_BITS_15 0x00
#define SET_BITS_30 0x00

#pragma pack(push, 1)
struct Sprm
{

	WORD ispmd : 9;
	BYTE fspec : 1;
	BYTE sgc : 3;
	BYTE spra : 3;

	Sprm();
	~Sprm();
	friend struct FibBase;

	void readSprm(std::ifstream&);
};

struct Prl
{
	Sprm sprm;

	Prl();
	~Prl();
	void readPrl(std::ifstream&);
}; // struct Prl

struct FcCompressed
{
	DWORD fc : 30;
	BYTE fCompressed : 1;
	BYTE r1 : 1;

	FcCompressed();
	~FcCompressed();

	void readFccomp(std::ifstream&);
}; // struct FcCompressed

struct Prm
{
	BYTE fComplex : 1;
	WORD data : 15;

	Prm();
	~Prm();

	void readPrm(std::ifstream&);
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

	void readPcd(std::ifstream&);
}; // struct Pcd

struct PlcPcd
{
	DWORD *aCP;
	Pcd aPcd;

	PlcPcd();
	~PlcPcd();

	void readPlcpcd(std::ifstream&);

}; // struct PlcPcd

struct PrcData
{
	WORD cbGrpprl;
	Prl *GrpPrl;

	PrcData();
	~PrcData();

	void readPrcdata(std::ifstream&);
}; // struct PrcData

struct Pcdt
{
	BYTE clxt;
	DWORD lcb;
	PlcPcd PlcPcd;

	Pcdt();
	~Pcdt();

	void readPcdt(std::ifstream&);
}; // struct Pcdt

struct Prc
{
	BYTE clxt;
	PrcData data;

	Prc();
	~Prc();

	void readPrc(std::ifstream&);
}; // struct Prc

struct Clx
{
	Prc *RgPrc;
	Pcdt Pcdt;

	Clx();
	~Clx();

	void readClx(std::ifstream&);
}; // struct Clx
#pragma pack(pop)
#endif // !CLX_H_INCLUDED