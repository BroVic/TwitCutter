// fib.h

// In-memory data structures for MS Word's .DOC File Information Block
// https://msdn.microsoft.com/en-us/library/office/dd952676(v=office.14).aspx

// The File Information Block is a data structure that contains information
// about any document, as well as links to various parts of the file. It 
// begins at offset 0 of a WordDocument stream. Its compoments are as follows:
// 1. base (Here named FibBase)
// 2. csw
// 3. fibRgW
// 4. cslw
// 5. fibRgLw
// 6. cbRgFcLcb
// 7. fibRgFcLcbBlob
// 8. cswNew
// 9. fibRgCswNew

// Various C++ structs have been defined to capture these elements from a
// Microsoft Word Document of the Binary File Format i.e. one that has the 
// .DOC extension.

// Apart from 'base', which is fixed in size (32 B), the structures that are
// prefixed with 'fib-' have their sizes determined by the immediately 
// precedent stucture e.g. 'csw' defines the size of 'fibRgW'.
// Also some structures have a degree of variablity that reflects the
// version of Word ('97, 2000, 2002 or 2003). In such instances, a C++ union
// has been used to enable the provision of sufficient memory regardless of
// which structure is used. This can be prominently seen, for example
// in the 'fibRgFcLcbBlob' data structure.

// For each data structure, a number of methods are declared for reading
// data from an appropriate file stream as well as some ancillary tasks.

#ifndef FIB_H_INCLUDED
#define FIB_H_INCLUDED

#include <fstream>
#include <iostream>
#include <cassert>

struct Fib
{
  Fib();
  ~Fib();
  void read_Fib(std::ifstream&);
  inline void skip_fields(std::ifstream&, unsigned long) const;
  inline static unsigned char assignBits(unsigned char, unsigned char, int);
  void inspectFibStructs();
  
  struct FibBase
  {
    FibBase();
    ~FibBase();
    void read_FibBase(std::ifstream&);
    void process_FibBase();

    unsigned short wIdent;
    unsigned short nFib;
    unsigned short unused;
    unsigned short lid;
    unsigned short pnNext;
    unsigned char fDot : 1;
    unsigned char fGlsy : 1;
    unsigned char fComplex : 1;
    unsigned char fHasPic : 1;
    unsigned char cQuickSaves : 4;
    unsigned char fEncrypted : 1;
    unsigned char fWhichTblStm : 1;
    unsigned char fReadOnlyRecommended : 1;
    unsigned char fWriteReservation : 1;
    unsigned char fExtChar : 1;
    unsigned char fLoadOverride : 1;
    unsigned char fFarEast : 1;
    unsigned char fObfuscated : 1;
    unsigned short nFibBack;
    unsigned long lkey;
    unsigned char envr;
    unsigned char fMac : 1;
    unsigned char fEmptySpecial : 1;
    unsigned char fLoadOverridePage : 1;
    unsigned char reserved1 : 1;
    unsigned char reserved2 : 1;
    unsigned char fSpare0 : 3;
    unsigned short reserved3;
    unsigned short reserved4;
    unsigned long reserved5;
    unsigned long reserved6;
  } base; // !struct FibBase

  unsigned short csw;
  
  struct FibRgW97
  {
    FibRgW97();
    ~FibRgW97();
    void read_FibRgW(std::ifstream &);
    void process_FibRgW97();

    unsigned short reserved1;
    unsigned short reserved2;
    unsigned short reserved3;
    unsigned short reserved4;
    unsigned short reserved5;
    unsigned short reserved6;
    unsigned short reserved7;
    unsigned short reserved8;
    unsigned short reserved9;
    unsigned short reserved10;
    unsigned short reserved11;
    unsigned short reserved12;
    unsigned short reserved13;
    unsigned short lidFE;    
  } fibRgW; // !struct FibRgW97

  unsigned short cslw;
  
  struct FibRgLw97
  {
    FibRgLw97();
    ~FibRgLw97();
    void read_FibRgLw(std::ifstream&);
    void process_FibRgLw97();

    unsigned long cbMac;
    unsigned long reserved1;
    unsigned long reserved2;
    int ccpText;
    int ccpFtn;
    int ccpHdd;
    unsigned long reserved3;
    int ccpAtn;
    int ccpEdn;
    int ccpTxbx;
    int ccpHdrTxbx;
    unsigned long reserved4;
    unsigned long reserved5;
    unsigned long reserved6;
    unsigned long reserved7;
    unsigned long reserved8;
    unsigned long reserved9;
    unsigned long reserved10;
    unsigned long reserved11;
    unsigned long reserved12;
    unsigned long reserved13;
    unsigned long reserved14;    
  } fibRgLw; // !struct FibRgLw97
 	
  unsigned short cbRgFcLcb;
  
  union FibRgFcLcb
  {
    FibRgFcLcb();
    ~FibRgFcLcb();
    void read_FibRgFcLcbBlob(std::ifstream&, const unsigned short);
    void process_FibRgFcLcbBlob(const FibBase&, const FibRgLw97&);

    struct FibRgFcLcb97
    {
      FibRgFcLcb97();
      ~FibRgFcLcb97();
      void read_FibRgFcLcb97(std::ifstream&);
      void process_FibRgFcLcb97(const FibBase&, const FibRgLw97&);

      unsigned long fcStshfOrig;
      unsigned long lcbStshfOrig;
      unsigned long fcStshf;
      unsigned long lcbStshf;
      unsigned long fcPlcffndRef;
      unsigned long lcbPlcffndRef;
      unsigned long fcPlcffndTxt;
      unsigned long lcbPlcffndTxt;
      unsigned long fcPlcfandRef;
      unsigned long lcbPlcfandRef;
      unsigned long fcPlcfandTxt;
      unsigned long lcbPlcfandTxt;
      unsigned long fcPlcfSed;
      unsigned long lcbPlcfSed;
      unsigned long fcPlcPad;
      unsigned long lcbPlcPad;
      unsigned long fcPlcfPhe;
      unsigned long lcbPlcfPhe;
      unsigned long fcSttbfGlsy;
      unsigned long lcbSttbfGlsy;
      unsigned long fcPlcfGlsy;
      unsigned long lcbPlcfGlsy;
      unsigned long fcPlcfHdd;
      unsigned long lcbPlcfHdd;
      unsigned long fcPlcfBteChpx;
      unsigned long lcbPlcfBteChpx;
      unsigned long fcPlcfBtePapx;
      unsigned long lcbPlcfBtePapx;
      unsigned long fcPlcfSea;
      unsigned long lcbPlcfSea;
      unsigned long fcSttbfFfn;
      unsigned long lcbSttbfFfn;
      unsigned long fcPlcfFldMom;		// refers to offset for PlcFld
      unsigned long lcbPlcfFldMom;
      unsigned long fcPlcfFldHdr;
      unsigned long lcbPlcfFldHdr;
      unsigned long fcPlcfFldFtn;
      unsigned long lcbPlcfFldFtn;
      unsigned long fcPlcfFldAtn;
      unsigned long lcbPlcfFldAtn;
      unsigned long fcPlcfFldMcr;
      unsigned long lcbPlcfFldMcr;
      unsigned long fcSttbfBkmk;
      unsigned long lcbSttbfBkmk;
      unsigned long fcPlcfBkf;
      unsigned long lcbPlcfBkf;
      unsigned long fcPlcfBkl;
      unsigned long lcbPlcfBkl;
      unsigned long fcCmds;
      unsigned long lcbCmds;
      unsigned long fcUnused1;
      unsigned long lcbUnused1;
      unsigned long fcSttbfMcr;
      unsigned long lcbSttbfMcr;
      unsigned long fcPrDrvr;
      unsigned long lcbPrDrvr;
      unsigned long fcPrEnvPort;
      unsigned long lcbPrEnvPort;
      unsigned long fcPrEnvLand;
      unsigned long lcbPrEnvLand;
      unsigned long fcWss;
      unsigned long lcbWss;
      unsigned long fcDop;
      unsigned long lcbDop;
      unsigned long fcSttbfAssoc;
      unsigned long lcbSttbfAssoc;
      unsigned long fcClx;
      unsigned long lcbClx;
      unsigned long fcPlcfPgdFtn;
      unsigned long lcbPlcfPgdFtn;
      unsigned long fcAutosaveSource;
      unsigned long lcbAutosaveSource;
      unsigned long fcGrpXstAtnOwners;
      unsigned long lcbGrpXstAtnOwners;
      unsigned long fcSttbfAtnBkmk;
      unsigned long lcbSttbfAtnBkmk;
      unsigned long fcUnused2;
      unsigned long lcbUnused2;
      unsigned long fcUnused3;
      unsigned long lcbUnused3;
      unsigned long fcPlcSpaMom;
      unsigned long lcbPlcSpaMom;
      unsigned long fcPlcSpaHdr;
      unsigned long lcbPlcSpaHdr;
      unsigned long fcPlcfAtnBkf;
      unsigned long lcbPlcfAtnBkf;
      unsigned long fcPlcfAtnBkl;
      unsigned long lcbPlcfAtnBkl;
      unsigned long fcPms;
      unsigned long lcbPms;
      unsigned long fcFormFldSttbs;
      unsigned long lcbFormFldSttbs;
      unsigned long fcPlcfendRef;
      unsigned long lcbPlcfendRef;
      unsigned long fcPlcfendTxt;
      unsigned long lcbPlcfendTxt;
      unsigned long fcPlcfFldEdn;
      unsigned long lcbPlcfFldEdn;
      unsigned long fcUnused4;
      unsigned long lcbUnused4;
      unsigned long fcDggInfo;
      unsigned long lcbDggInfo;
      unsigned long fcSttbfRMark;
      unsigned long lcbSttbfRMark;
      unsigned long fcSttbfCaption;
      unsigned long lcbSttbfCaption;
      unsigned long fcSttbfAutoCaption;
      unsigned long lcbSttbfAutoCaption;
      unsigned long fcPlcfWkb;
      unsigned long lcbPlcfWkb;
      unsigned long fcPlcfSpl;
      unsigned long lcbPlcfSpl;
      unsigned long fcPlcftxbxTxt;
      unsigned long lcbPlcftxbxTxt;
      unsigned long fcPlcfFldTxbx;
      unsigned long lcbPlcfFldTxbx;
      unsigned long fcPlcfHdrtxbxTxt;
      unsigned long lcbPlcfHdrtxbxTxt;
      unsigned long fcPlcffldHdrTxbx;
      unsigned long lcbPlcffldHdrTxbx;
      unsigned long fcStwUser;
      unsigned long lcbStwUser;
      unsigned long fcSttbTtmbd;
      unsigned long lcbSttbTtmbd;
      unsigned long fcCookieData;
      unsigned long lcbCookieData;
      unsigned long fcPgdMotherOldOld;
      unsigned long lcbPgdMotherOldOld;
      unsigned long fcBkdMotherOldOld;
      unsigned long lcbBkdMotherOldOld;
      unsigned long fcPgdFtnOldOld;
      unsigned long lcbPgdFtnOldOld;
      unsigned long fcBkdFtnOldOld;
      unsigned long lcbBkdFtnOldOld;
      unsigned long fcPgdEdnOldOld;
      unsigned long lcbPgdEdnOldOld;
      unsigned long fcBkdEdnOldOld;
      unsigned long lcbBkdEdnOldOld;
      unsigned long fcSttbfIntlFld;
      unsigned long lcbSttbfIntlFld;
      unsigned long fcRouteSlip;
      unsigned long lcbRouteSlip;
      unsigned long fcSttbSavedBy;
      unsigned long lcbSttbSavedBy;
      unsigned long fcSttbFnm;
      unsigned long lcbSttbFnm;
      unsigned long fcPlfLst;
      unsigned long lcbPlfLst;
      unsigned long fcPlfLfo;
      unsigned long lcbPlfLfo;
      unsigned long fcPlcfTxbxBkd;
      unsigned long lcbPlcfTxbxBkd;
      unsigned long fcPlcfTxbxHdrBkd;
      unsigned long lcbPlcfTxbxHdrBkd;
      unsigned long fcDocUndoWord9;
      unsigned long lcbDocUndoWord9;
      unsigned long fcRgbUse;
      unsigned long lcbRgbUse;
      unsigned long fcUsp;
      unsigned long lcbUsp;
      unsigned long fcUskf;
      unsigned long lcbUskf;
      unsigned long fcPlcupcRgbUse;
      unsigned long lcbPlcupcRgbUse;
      unsigned long fcPlcupcUsp;
      unsigned long lcbPlcupcUsp;
      unsigned long fcSttbGlsyStyle;
      unsigned long lcbSttbGlsyStyle;
      unsigned long fcPlgosl;
      unsigned long lcbPlgosl;
      unsigned long fcPlcocx;
      unsigned long lcbPlcocx;
      unsigned long fcPlcfBteLvc;
      unsigned long lcbPlcfBteLvc;
      unsigned long dwLowDateTime;
      unsigned long dwHighDateTime;
      unsigned long fcPlcfLvcPre10;
      unsigned long lcbPlcfLvcPre10;
      unsigned long fcPlcfAsumy;
      unsigned long lcbPlcfAsumy;
      unsigned long fcPlcfGram;
      unsigned long lcbPlcfGram;
      unsigned long fcSttbListNames;
      unsigned long lcbSttbListNames;
      unsigned long fcSttbfUssr;
      unsigned long lcbSttbfUssr;
    } fibRgFcLcb97;         // !struct FibRgFcLcb97
   
    struct FibRgFcLcb2000
    {
      FibRgFcLcb2000();
      ~FibRgFcLcb2000();
      void read_FibRgFcLcb2000(std::ifstream &);
      void process_FibRgFcLcb2000(const FibBase&, const FibRgLw97&);

      FibRgFcLcb97 rgFcLcb97;
      unsigned long fcPlcfTch;
      unsigned long lcbPlcfTch;
      unsigned long fcRmdThreading;
      unsigned long lcbRmdThreading;
      unsigned long fcMid;
      unsigned long lcbMid;
      unsigned long fcSttbRgtplc;
      unsigned long lcbSttbRgtplc;
      unsigned long fcMsoEnvelope;
      unsigned long lcbMsoEnvelope;
      unsigned long fcPlcfLad;
      unsigned long lcbPlcfLad;
      unsigned long fcRgDofr;
      unsigned long lcbRgDofr;
      unsigned long fcPlcosl;
      unsigned long lcbPlcosl;
      unsigned long fcPlcfCookieOld;
      unsigned long lcbPlcfCookieOld;
      unsigned long fcPgdMotherOld;
      unsigned long lcbPgdMotherOld;
      unsigned long fcBkdMotherOld;
      unsigned long lcbBkdMotherOld;
      unsigned long fcPgdFtnOld;
      unsigned long lcbPgdFtnOld;
      unsigned long fcBkdFtnOld;
      unsigned long lcbBkdFtnOld;
      unsigned long fcPgdEdnOld;
      unsigned long lcbPgdEdnOld;
      unsigned long fcBkdEdnOld;
      unsigned long lcbBkdEdnOld;
    } fibRgFcLcb2000;    // !struct FibRgFcLcb2000
 
    struct FibRgFcLcb2002
    {
      FibRgFcLcb2002();
      ~FibRgFcLcb2002();
      void read_FibRgFcLcb2002(std::ifstream &);
      void process_FibRgFcLcb2002(const FibBase&, const FibRgLw97&);
      
      FibRgFcLcb2000 rgFcLcb2000;
      unsigned long fcUnused1;
      unsigned long lcbUnused1;
      unsigned long fcPlcfPgp;
      unsigned long lcbPlcfPgp;
      unsigned long fcPlcfuim;
      unsigned long lcbPlcfuim;
      unsigned long fcPlfguidUim;
      unsigned long lcbPlfguidUim;
      unsigned long fcAtrdExtra;
      unsigned long lcbAtrdExtra;
      unsigned long fcPlrsid;
      unsigned long lcbPlrsid;
      unsigned long fcSttbfBkmkFactoid;
      unsigned long lcbSttbfBkmkFactoid;
      unsigned long fcPlcfBkfFactoid;
      unsigned long lcbPlcfBkfFactoid;
      unsigned long fcPlcfcookie;
      unsigned long lcbPlcfcookie;
      unsigned long fcPlcfBklFactoid;
      unsigned long lcbPlcfBklFactoid;
      unsigned long fcFactoidData;
      unsigned long lcbFactoidData;
      unsigned long fcDocUndo;
      unsigned long lcbDocUndo;
      unsigned long fcSttbfBkmkFcc;
      unsigned long lcbSttbfBkmkFcc;
      unsigned long fcPlcfBkfFcc;
      unsigned long lcbPlcfBkfFcc;
      unsigned long fcPlcfBklFcc;
      unsigned long lcbPlcfBklFcc;
      unsigned long fcSttbfbkmkBPRepairs;
      unsigned long lcbSttbfbkmkBPRepairs;
      unsigned long fcPlcfbkfBPRepairs;
      unsigned long lcbPlcfbkfBPRepairs;
      unsigned long fcPlcfbklBPRepairs;
      unsigned long lcbPlcfbklBPRepairs;
      unsigned long fcPmsNew;
      unsigned long lcbPmsNew;
      unsigned long fcODSO;
      unsigned long lcbODSO;
      unsigned long fcPlcfpmiOldXP;
      unsigned long lcbPlcfpmiOldXP;
      unsigned long fcPlcfpmiNewXP;
      unsigned long lcbPlcfpmiNewXP;
      unsigned long fcPlcfpmiMixedXP;
      unsigned long lcbPlcfpmiMixedXP;
      unsigned long fcUnused2;
      unsigned long lcbUnused2;
      unsigned long fcPlcffactoid;
      unsigned long lcbPlcffactoid;
      unsigned long fcPlcflvcOldXP;
      unsigned long lcbPlcflvcOldXP;
      unsigned long fcPlcflvcNewXP;
      unsigned long lcbPlcflvcNewXP;
      unsigned long fcPlcflvcMixedXP;
      unsigned long lcbPlcflvcMixedXP;
    } fibRgFcLcb2002;   // !struct FibRgFcLcb2002
 
    struct FibRgFcLcb2003
    {
      FibRgFcLcb2003();
      ~FibRgFcLcb2003();
      void read_FibRgFcLcb2003(std::ifstream &);
      void process_FibRgFcLcb2003(const FibBase&, const FibRgLw97&);
      
      FibRgFcLcb2002 rgFcLcb2002;
      unsigned long fcHplxsdr;
      unsigned long lcbHplxsdr;
      unsigned long fcSttbfBkmkSdt;
      unsigned long lcbSttbfBkmkSdt;
      unsigned long fcPlcfBkfSdt;
      unsigned long lcbPlcfBkfSdt;
      unsigned long fcPlcfBklSdt;
      unsigned long lcbPlcfBklSdt;
      unsigned long fcCustomXForm;
      unsigned long lcbCustomXForm;
      unsigned long fcSttbfBkmkProt;
      unsigned long lcbSttbfBkmkProt;
      unsigned long fcPlcfBkfProt;
      unsigned long lcbPlcfBkfProt;
      unsigned long fcPlcfBklProt;
      unsigned long lcbPlcfBklProt;
      unsigned long fcSttbProtUser;
      unsigned long lcbSttbProtUser;
      unsigned long fcUnused;
      unsigned long lcbUnused;
      unsigned long fcPlcfpmiOld;
      unsigned long lcbPlcfpmiOld;
      unsigned long fcPlcfpmiOldInline;
      unsigned long lcbPlcfpmiOldInline;
      unsigned long fcPlcfpmiNew;
      unsigned long lcbPlcfpmiNew;
      unsigned long fcPlcfpmiNewInline;
      unsigned long lcbPlcfpmiNewInline;
      unsigned long fcPlcflvcOld;
      unsigned long lcbPlcflvcOld;
      unsigned long fcPlcflvcOldInline;
      unsigned long lcbPlcflvcOldInline;
      unsigned long fcPlcflvcNew;
      unsigned long lcbPlcflvcNew;
      unsigned long fcPlcflvcNewInline;
      unsigned long lcbPlcflvcNewInline;
      unsigned long fcPgdMother;
      unsigned long lcbPgdMother;
      unsigned long fcBkdMother;
      unsigned long lcbBkdMother;
      unsigned long fcAfdMother;
      unsigned long lcbAfdMother;
      unsigned long fcPgdFtn;
      unsigned long lcbPgdFtn;
      unsigned long fcBkdFtn;
      unsigned long lcbBkdFtn;
      unsigned long fcAfdFtn;
      unsigned long lcbAfdFtn;
      unsigned long fcPgdEdn;
      unsigned long lcbPgdEdn;
      unsigned long fcBkdEdn;
      unsigned long lcbBkdEdn;
      unsigned long fcAfdEdn;
      unsigned long lcbAfdEdn;
      unsigned long fcAfd;
      unsigned long lcbAfd;
    } fibRgFcLcb2003;    // !struct FibRgFcLcb2003
 
    struct FibRgFcLcb2007
    {
      FibRgFcLcb2007();
      ~FibRgFcLcb2007();
      void read_FibRgFcLcb2007(std::ifstream &);
      void process_FibRgFcLcb2007(const FibBase&, const FibRgLw97&);

      FibRgFcLcb2003 rgFcLcb2003;
      unsigned long fcPlcfmthd;
      unsigned long lcbPlcfmthd;
      unsigned long fcSttbfBkmkMoveFrom;
      unsigned long lcbSttbfBkmkMoveFrom;
      unsigned long fcPlcfBkfMoveFrom;
      unsigned long lcbPlcfBkfMoveFrom;
      unsigned long fcPlcfBklMoveFrom;
      unsigned long lcbPlcfBklMoveFrom;
      unsigned long fcSttbfBkmkMoveTo;
      unsigned long lcbSttbfBkmkMoveTo;
      unsigned long fcPlcfBkfMoveTo;
      unsigned long lcbPlcfBkfMoveTo;
      unsigned long fcPlcfBklMoveTo;
      unsigned long lcbPlcfBklMoveTo;
      unsigned long fcUnused1;
      unsigned long lcbUnused1;
      unsigned long fcUnused2;
      unsigned long lcbUnused2;
      unsigned long fcUnused3;
      unsigned long lcbUnused3;
      unsigned long fcSttbfBkmkArto;
      unsigned long lcbSttbfBkmkArto;
      unsigned long fcPlcfBkfArto;
      unsigned long lcbPlcfBkfArto;
      unsigned long fcPlcfBklArto;
      unsigned long lcbPlcfBklArto;
      unsigned long fcArtoData;
      unsigned long lcbArtoData;
      unsigned long fcUnused4;
      unsigned long lcbUnused4;
      unsigned long fcUnused5;
      unsigned long lcbUnused5;
      unsigned long fcUnused6;
      unsigned long lcbUnused6;
      unsigned long fcOssTheme;
      unsigned long lcbOssTheme;
      unsigned long fcColorSchemeMapping;
      unsigned long lcbColorSchemeMapping;
    } fibRgFcLcb2007;    // !struct FibRgFcLcb2007   
  } fibRgFcLcbBlob; // !union FibRgFcLcb

  unsigned short cswNew;
  
  struct FibRgCswNew
  {
    FibRgCswNew();
    ~FibRgCswNew();
    void read_FibRgCswNew(std::ifstream&, const unsigned short);
    void process_FibRgCswNew(const FibBase&);
    
    unsigned short nFibNew;
  
    union FibRgCswNewData
    {
      FibRgCswNewData();      
      ~FibRgCswNewData();
      void read_FibRgCswNewData(std::ifstream&, const unsigned short);

      struct FibRgCswNewData2000
      {
	FibRgCswNewData2000();
	~FibRgCswNewData2000();
	void read_2000(std::ifstream&);
	void process_FibRgCswNewData2000();

	unsigned short cQuickSavesNew;
      } fibRgCswNewData2000; 
    
      struct FibRgCswNewData2007
      {
	FibRgCswNewData2007();
	~FibRgCswNewData2007();
	void read_2007(std::ifstream &);
	void process_FibRgCswNewData2007();
	
	FibRgCswNewData2000 rgCswNewData2000;
	unsigned short lidThemeOther;
	unsigned short lidThemeFE;
	unsigned short lidThemeCS;
      } fibRgCswNewData2007; // !struct FibRgCswNewData2007
    } rgCswNewData; // !union FibRgCswNewData
  } fibRgCswNew; // !struct FibRgCswNew
}; // !struct Fib

#endif // !FIB_H_INCLUDED
