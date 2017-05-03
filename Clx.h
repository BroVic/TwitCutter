// Clx.h
// Define in-memory data structures for use with MS-USHORT .DOC Clx format

#ifndef CLX_H_INCLUDED
#define CLX_H_INCLUDED

#include <fstream>
#include "dtypes.h"
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
};

struct Prc
	{
		BYTE clxt;
		struct PrcData
		{
			SHORT cbGrpprl;
			Prl *GrpPrl;

			PrcData();
			~PrcData();

		} data; // struct PrcData

		Prc();
		~Prc();

	}; // struct Prc

#pragma pack(push, 1)
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

	Pcd readPcdData(std::ifstream&);

}; // struct Pcd
#pragma pack(pop)

#pragma pack(push, 1)
struct PlcPcd
{
	ULONG aCP;
	Pcd *aPcd;

	PlcPcd();
	~PlcPcd();

	VOID readPlcPcd(std::ifstream&, ULONG);

}; // struct PlcPcd
#pragma pack(pop)

struct Clx
{
	Prc *rgPrc;
	struct Pcdt
	{
		BYTE clxt;
		ULONG lcb;
		PlcPcd plcPcd;

		Pcdt();
		~Pcdt();


		inline ULONG calcArrayLength(ULONG);
		VOID readPcdt(std::ifstream &strm, BYTE);
	} pcdt; // struct Pcdt

	Clx();
	~Clx();


	VOID readToClx(std::ifstream&);

}; // struct Clx

#endif // !CLX_H_INCLUDED
