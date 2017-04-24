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
struct Clx
{
	struct Prc
	{
		BYTE clxt;
		struct PrcData
		{
			WORD cbGrpprl;
			struct Prl
			{
				struct Sprm
				{
					WORD ispmd : 9;
					BYTE fspec : 1;
					BYTE sgc : 3;
					BYTE spra : 3;

					Sprm();
					~Sprm();

				} sprm; // struct Sprm

				Prl();
				~Prl();

			} GrpPrl; // struct Prl

			PrcData();
			~PrcData();

		} data; // struct PrcData

		Prc();
		~Prc();

	} rgPrc; // struct Prc
	struct Pcdt
	{
		BYTE clxt;
		DWORD lcb;
		struct PlcPcd
		{
			DWORD aCP;
			struct Pcd
			{
				BYTE fNoParaLast : 1;
				BYTE fR1 : 1;
				BYTE fDirty : 1;
				WORD fR2 : 13;
				struct FcCompressed
				{
					DWORD fc : 30;
					BYTE fCompressed : 1;
					BYTE r1 : 1;

					FcCompressed();
					~FcCompressed();

				} fc; // struct FcCompressed
				struct Prm
				{
					BYTE fComplex : 1;
					WORD data : 15;

					Prm();
					~Prm();

				} prm; // struct Prm

				Pcd();
				~Pcd();

			} aPcd; // struct Pcd

			PlcPcd();
			~PlcPcd();

		} plcPcd; // struct PlcPcd

		Pcdt();
		~Pcdt();

	} pcdt; // struct Pcdt

	Clx();
	~Clx();

	VOID readToClx(std::ifstream&, DWORD);

}; // struct Clx

#pragma pack(pop)

#endif // !CLX_H_INCLUDED