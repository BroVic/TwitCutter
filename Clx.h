// Clx.h
// Define in-memory data structures for use with MS-Word .DOC Clx format

#include <cstdint>
#include "FIB.h"

#ifndef CLX_H_INCLUDED
#define CLX_H_INCLUDED

namespace dtdoc {

	struct Sprm
	{
		BIT9 ispmd;
		BIT1 fspec;
		BIT3 sgc;
		BIT3 spra;
	};

	struct Prl
	{
		Sprm sprm;
	}; // struct Prl

	struct FcCompressed
	{
		BIT30 fc;
		BIT1 fCompressed;
		BIT1 r1;
	}; // struct FcCompressed

	struct Prm
	{
		BIT1 fComplex;
		BIT15 data;
	}; // struct Prm

	struct Pcd
	{
		BIT1 fNoParaLast;
		BIT1 fR1;
		BIT1 fDirty;
		BIT13 fR2;
		FcCompressed fc;
		Prm prm;
	}; // struct Pcd

	struct PlcPcd
	{
		DWORD *aCP;
		Pcd aPcd;
	}; // struct PlcPcd

	struct PrcData
	{
		WORD cbGrpprl;
		Prl *GrpPrl;
	}; // struct PrcData

	struct Pcdt
	{
		BYTE clxt;
		DWORD lcb;
		PlcPcd PlcPcd;
	}; // struct Pcdt

	struct Prc
	{
		BYTE clxt;
		PrcData data;
	}; // struct Prc

	struct Clx
	{
		Prc *RgPrc;
		Pcdt Pcdt;
	}; // struct Clx

}; // namespace dtdoc
#endif // !CLX_H_INCLUDED