// Clx.h
// Define in-memory data structures for use with MS-USHORT .DOC Clx format

#ifndef CLX_H_INCLUDED
#define CLX_H_INCLUDED

#include <fstream>
#include <cassert>
#include "FIB.h"

constexpr BYTE SET_BITS_1   = 0x0;
constexpr BYTE SET_BITS_3   = 0x0;
constexpr BYTE SET_BITS_9   = 0x0;
constexpr BYTE SET_BITS_13  = 0x0;
constexpr BYTE SET_BITS_15  = 0x0;
constexpr BYTE SET_BITS_30  = 0x0;

constexpr ULONG SIZE_OF_PCD = 8;

// Sprm values
//constexpr USHORT sprmCFRMarkDel = 0x0800;
//constexpr USHORT sprmCFRMarkIns = 0x0801;
//constexpr USHORT sprmCFFldVanish = 0x0802;
//constexpr USHORT sprmCPicLocation = 0x6A03;
//constexpr USHORT sprmCIbstRMark = 0x4804;
//constexpr USHORT sprmCDttmRMark = 0x6805;
//constexpr USHORT sprmCFData = 0x0806;
//constexpr USHORT sprmCIdslRMark = 0x07;
//constexpr USHORT sprmCSymbol = 0x6A09;
//constexpr USHORT sprmCFOle2 = 0x080A;
//constexpr USHORT sprmCHighlight = 0x2A0C;
//constexpr USHORT sprmCFWebHidden = 0x0811;

// Nested data structure, Clx, which is found on the Table stream.
// This stucture contains the character positions and related data.
struct Clx
{
	struct Prc
	{
		BYTE clxt;
		struct PrcData
		{
			SHORT cbGrpprl;
			struct Prl
			{
				struct Sprm
				{
					USHORT ispmd : 9;
					BYTE fSpec : 1;
					BYTE sgc : 3;
					BYTE spra : 3;

					Sprm();
					~Sprm();

					VOID readSprm(std::ifstream&);
				} sprm; // struct Sprm
				// operand

				Prl();
				~Prl();
			} *GrpPrl;

			PrcData();
			~PrcData();

		} data; // struct PrcData

		Prc();
		~Prc();

	} *rgPrc; // struct Prc

	struct Pcdt
	{
		BYTE clxt;
		ULONG lcb;
		struct PlcPcd
		{
			ULONG *aCP;
			struct Pcd
			{
				BYTE fNoParaLast : 1;
				BYTE fR1 : 1;
				BYTE fDirty : 1;
				USHORT fR2 : 13;
				struct FcCompressed
				{
					ULONG fc : 30;
					BYTE fCompressed : 1;
					BYTE r1 : 1;

					FcCompressed();
					~FcCompressed();
					VOID readFcData(std::ifstream&);
				} fc; // struct FcCompressed
				struct Prm
				{
					BYTE fComplex : 1;
					USHORT data : 15;

					Prm();
					~Prm();

					VOID readPrmData(std::ifstream&);
				} prm; // struct Prm

				Pcd();
				~Pcd();

				VOID readPcdData(std::ifstream&);
				USHORT defineOffset() const;
				LONG defineEncoding() const;
				

			} *aPcd; // struct Pcd

			PlcPcd();
			~PlcPcd();
			VOID readPlcPcd(std::ifstream&, ULONG);
			ULONG getCharPos(int);
			inline ULONG pcdLength(Clx&);

		} plcPcd; // struct PlcPcd

		Pcdt();
		~Pcdt();

		VOID readPcdt(std::ifstream&, BYTE, Clx&);
	} pcdt; // struct Pcdt

	Clx();
	~Clx();

	VOID readToClx(std::ifstream&);
}; // struct Clx

#endif // !CLX_H_INCLUDED
