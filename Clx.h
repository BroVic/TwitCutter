// Clx.h
// Define in-memory data structures for use with MS-Word .DOC Clx format

#include "dtypes.h"

#ifndef CLX_H_INCLUDED
#define CLX_H_INCLUDED

namespace dtdoc {

	struct Sprm
	{
		WORD ispmd : 9;
		BYTE fspec : 1;
		BYTE sgc : 3;
		BYTE spra : 3;

		Sprm();
		~Sprm();
	};

	struct Prl
	{
		Sprm sprm;

		Prl();
		~Prl();
	}; // struct Prl

	struct FcCompressed
	{
		DWORD fc : 30;
		BYTE fCompressed : 1;
		BYTE r1 : 1;

		FcCompressed();
		~FcCompressed();
	}; // struct FcCompressed

	struct Prm
	{
		BYTE fComplex : 1;
		WORD data : 15;

		Prm();
		~Prm();
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
	}; // struct Pcd

	struct PlcPcd
	{
		DWORD *aCP;
		Pcd aPcd;

		PlcPcd();
		~PlcPcd();
	}; // struct PlcPcd

	struct PrcData
	{
		WORD cbGrpprl;
		Prl *GrpPrl;

		PrcData();
		~PrcData();
	}; // struct PrcData

	struct Pcdt
	{
		BYTE clxt;
		DWORD lcb;
		PlcPcd PlcPcd;

		Pcdt();
		~Pcdt();
	}; // struct Pcdt

	struct Prc
	{
		BYTE clxt;
		PrcData data;

		Prc();
		~Prc();
	}; // struct Prc

	struct Clx
	{
		Prc *RgPrc;
		Pcdt Pcdt;

		Clx();
		~Clx();
	}; // struct Clx

}; // namespace dtdoc
#endif // !CLX_H_INCLUDED