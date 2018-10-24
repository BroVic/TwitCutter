// Clx.h
// Define in-memory structures for reading and working with a Clx

#ifndef CLX_H_INCLUDED
#define CLX_H_INCLUDED

#include <fstream>
#include <cassert>
#include "fib.h"

constexpr unsigned long SIZE_OF_PCD = 8;

// Sprm values
//constexpr unsigned short sprmCFRMarkDel    = 0x0800;
//constexpr unsigned short sprmCFRMarkIns    = 0x0801;
//constexpr unsigned short sprmCFFldVanish   = 0x0802;
//constexpr unsigned short sprmCPicLocation  = 0x6A03;
//constexpr unsigned short sprmCIbstRMark    = 0x4804;
//constexpr unsigned short sprmCDttmRMark    = 0x6805;
//constexpr unsigned short sprmCFData        = 0x0806;
//constexpr unsigned short sprmCIdslRMark    = 0x07;
//constexpr unsigned short sprmCSymbol       = 0x6A09;
//constexpr unsigned short sprmCFOle2        = 0x080A;
//constexpr unsigned short sprmCHighlight    = 0x2A0C;
//constexpr unsigned short sprmCFWebHidden   = 0x0811;

// Nested data structure, Clx, which is found in the Table Stream.
// This stucture contains the character positions and other related data.
struct Clx
{
  Clx();
  ~Clx();
  void readToClx(std::ifstream&);

  struct Prc
  {
    Prc();
    ~Prc();

    unsigned char clxt;

    struct PrcData
    {
      PrcData();
      ~PrcData();

      short cbGrpprl;
      struct Prl
      {
	Prl();
	~Prl();

	struct Sprm
	{
	  Sprm();
	  ~Sprm();
	  void readSprm(std::ifstream&);

	  unsigned short ispmd : 9;
	  unsigned char fSpec : 1;
	  unsigned char sgc : 3;
	  unsigned char spra : 3;
	} sprm; // !struct Sprm
	// operand
      } *GrpPrl;
    } data; // !struct PrcData
  } *rgPrc; // !struct Prc

  struct Pcdt
  {
    Pcdt();
    ~Pcdt();
    void readPcdt(std::ifstream&, unsigned char, Clx&);

    unsigned char clxt;
    unsigned long lcb;

    struct PlcPcd
    {
      PlcPcd();
      ~PlcPcd();
      void readPlcPcd(std::ifstream&, unsigned long);
      unsigned long getCharPos(int);
      unsigned long pcdLength(Clx&);

      unsigned long *aCP;

      struct Pcd
      {
	Pcd();
	~Pcd();
	void            readPcdData(std::ifstream&);
	unsigned short  defineOffset() const;
	int             defineEncoding() const;

	unsigned char   fNoParaLast : 1;
	unsigned char   fR1 : 1;
	unsigned char   fDirty : 1;
	unsigned short  fR2 : 13;

	struct FcCompressed
	{
	  FcCompressed();
	  ~FcCompressed();
	  void readFcData(std::ifstream&);

	  unsigned long fc : 30;
	  unsigned char fCompressed : 1;
	  unsigned char r1 : 1;
	} fc; // !struct FcCompressed

	struct Prm
	{
	  Prm();
	  ~Prm();
	  void readPrmData(std::ifstream&);

	  unsigned char fComplex : 1;
	  unsigned short data : 15;
       	} prm; // !struct Prm
      } *aPcd; // !struct Pcd
    } plcPcd; // !struct PlcPcd
  } pcdt; // !struct Pcdt
}; // !struct Clx
#endif // !CLX_H_INCLUDED
