// Clx.h
// Define in-memory structures for reading and working with a Clx

#ifndef CLX_H_INCLUDED
#define CLX_H_INCLUDED

#include <fstream>
#include <cassert>
#include "fib.h"

constexpr ULONG SIZE_OF_PCD = 8;

// Sprm values
//constexpr USHORT sprmCFRMarkDel    = 0x0800;
//constexpr USHORT sprmCFRMarkIns    = 0x0801;
//constexpr USHORT sprmCFFldVanish   = 0x0802;
//constexpr USHORT sprmCPicLocation  = 0x6A03;
//constexpr USHORT sprmCIbstRMark    = 0x4804;
//constexpr USHORT sprmCDttmRMark    = 0x6805;
//constexpr USHORT sprmCFData        = 0x0806;
//constexpr USHORT sprmCIdslRMark    = 0x07;
//constexpr USHORT sprmCSymbol       = 0x6A09;
//constexpr USHORT sprmCFOle2        = 0x080A;
//constexpr USHORT sprmCHighlight    = 0x2A0C;
//constexpr USHORT sprmCFWebHidden   = 0x0811;

// Nested data structure, Clx, which is found in the Table Stream.
// This stucture contains the character positions and other related data.
struct Clx
{
  Clx();
  ~Clx();
  VOID readToClx(std::ifstream&);

  struct Prc
  {
    Prc();
    ~Prc();

    BYTE clxt;

    struct PrcData
    {
      PrcData();
      ~PrcData();

      SHORT cbGrpprl;
      struct Prl
      {
	Prl();
	~Prl();

	struct Sprm
	{
	  Sprm();
	  ~Sprm();
	  VOID readSprm(std::ifstream&);

	  USHORT ispmd : 9;
	  BYTE fSpec : 1;
	  BYTE sgc : 3;
	  BYTE spra : 3;
	} sprm; // !struct Sprm
	// operand
      } *GrpPrl;
    } data; // !struct PrcData
  } *rgPrc; // !struct Prc

  struct Pcdt
  {
    Pcdt();
    ~Pcdt();
    VOID readPcdt(std::ifstream&, BYTE, Clx&);

    BYTE clxt;
    ULONG lcb;

    struct PlcPcd
    {
      PlcPcd();
      ~PlcPcd();
      VOID readPlcPcd(std::ifstream&, ULONG);
      ULONG getCharPos(int);
      ULONG pcdLength(Clx&);

      ULONG *aCP;

      struct Pcd
      {
	Pcd();
	~Pcd();
	VOID readPcdData(std::ifstream&);
	USHORT defineOffset() const;
	LONG defineEncoding() const;

	BYTE fNoParaLast : 1;
	BYTE fR1 : 1;
	BYTE fDirty : 1;
	USHORT fR2 : 13;

	struct FcCompressed
	{
	  FcCompressed();
	  ~FcCompressed();
	  VOID readFcData(std::ifstream&);

	  ULONG fc : 30;
	  BYTE fCompressed : 1;
	  BYTE r1 : 1;
	} fc; // !struct FcCompressed

	struct Prm
	{
	  Prm();
	  ~Prm();
	  VOID readPrmData(std::ifstream&);

	  BYTE fComplex : 1;
	  USHORT data : 15;
       	} prm; // !struct Prm
      } *aPcd; // !struct Pcd
    } plcPcd; // !struct PlcPcd
  } pcdt; // !struct Pcdt
}; // !struct Clx
#endif // !CLX_H_INCLUDED
