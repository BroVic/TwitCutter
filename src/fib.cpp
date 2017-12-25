#include "FIB.h"
#include <fstream>
#include <iostream>
#include <cassert>

// nFib values
constexpr USHORT FOR_USHORT_97   = 0x00C1;
constexpr USHORT FOR_USHORT_2000 = 0x00D9;
constexpr USHORT FOR_USHORT_2002 = 0x0101;
constexpr USHORT FOR_USHORT_2003 = 0x010C;
constexpr USHORT FOR_USHORT_2007 = 0x0112;



Fib::Fib()
{
	csw         = { };
	cslw	    = { };
	cbRgFcLcb   = { };
	cswNew	    = { };
}

Fib::~Fib()
{
}

Fib::FibBase::FibBase()
{
	wIdent		       = { };
	nFib		       = { };
	unused		       = { };
	lid		       = { };
	pnNext		       = { };
	fDot		       = _SET_BITS_1;
	fGlsy		       = _SET_BITS_1;
	fComplex	       = _SET_BITS_1;
	fHasPic		       = _SET_BITS_1;
	cQuickSaves	       = _SET_BITS_4;
	fEncrypted	       = _SET_BITS_1;
	fWhichTblStm	       = _SET_BITS_1;
	fReadOnlyRecommended   = _SET_BITS_1;
	fWriteReservation      = _SET_BITS_1;
	fExtChar	       = _SET_BITS_1;
	fLoadOverride	       = _SET_BITS_1;
	fFarEast	       = _SET_BITS_1;
	fObfuscated	       = _SET_BITS_1;
	nFibBack	       = { };
	lkey		       = { };
	envr		       = { };
	fMac		       = _SET_BITS_1;
	fEmptySpecial	       = _SET_BITS_1;
	fLoadOverridePage      = _SET_BITS_1;
	reserved1	       = _SET_BITS_1;
	reserved2	       = _SET_BITS_1;
	fSpare0		       = _SET_BITS_3;
	reserved3	       = { };
	reserved4	       = { };
	reserved5	       = { };
	reserved6	       = { };
}

Fib::FibBase::~FibBase()
{
}

Fib::FibRgW97::FibRgW97()
{
	reserved1	= { };
	reserved2	= { };
	reserved3	= { };
	reserved4	= { };
	reserved5	= { };
	reserved6	= { };
	reserved7	= { };
	reserved8	= { };
	reserved9	= { };
	reserved10	= { };
	reserved11	= { };
	reserved12	= { };
	reserved13	= { };
	lidFE           = { };
}

Fib::FibRgW97::~FibRgW97()
{
}

Fib::FibRgLw97::FibRgLw97()
{
	cbMac		= { };
	reserved1	= { };
	reserved2	= { };
	ccpText		= { };
	ccpFtn		= { };
	ccpHdd		= { };
	reserved3	= { };
	ccpAtn		= { };
	ccpEdn		= { };
	ccpTxbx		= { };
	ccpHdrTxbx	= { };
	reserved4	= { };
	reserved5	= { };
	reserved6	= { };
	reserved7	= { };
	reserved8	= { };
	reserved9	= { };
	reserved10	= { };
	reserved11	= { };
	reserved12	= { };
	reserved13	= { };
	reserved14	= { };
}

Fib::FibRgLw97::~FibRgLw97()
{
}

Fib::FibRgFcLcb::FibRgFcLcb()
{
}

Fib::FibRgFcLcb::~FibRgFcLcb()
{
}

Fib::FibRgFcLcb::FibRgFcLcb97::FibRgFcLcb97()
{
	fcStshfOrig			= { };
	lcbStshfOrig		= { };
	fcStshf				= { };
	lcbStshf			= { };
	fcPlcffndRef		= { };
	lcbPlcffndRef		= { };
	fcPlcffndTxt		= { };
	lcbPlcffndTxt		= { };
	fcPlcfandRef		= { };
	lcbPlcfandRef		= { };
	fcPlcfandTxt		= { };
	lcbPlcfandTxt		= { };
	fcPlcfSed			= { };
	lcbPlcfSed			= { };
	fcPlcPad			= { };
	lcbPlcPad			= { };
	fcPlcfPhe			= { };
	lcbPlcfPhe			= { };
	fcSttbfGlsy			= { };
	lcbSttbfGlsy		= { };
	fcPlcfGlsy			= { };
	lcbPlcfGlsy			= { };
	fcPlcfHdd			= { };
	lcbPlcfHdd			= { };
	fcPlcfBteChpx		= { };
	lcbPlcfBteChpx		= { };
	fcPlcfBtePapx		= { };
	lcbPlcfBtePapx		= { };
	fcPlcfSea			= { };
	lcbPlcfSea			= { };
	fcSttbfFfn			= { };
	lcbSttbfFfn			= { };
	fcPlcfFldMom		= { };
	lcbPlcfFldMom		= { };
	fcPlcfFldHdr		= { };
	lcbPlcfFldHdr		= { };
	fcPlcfFldFtn		= { };
	lcbPlcfFldFtn		= { };
	fcPlcfFldAtn		= { };
	lcbPlcfFldAtn		= { };
	fcPlcfFldMcr		= { };
	lcbPlcfFldMcr		= { };
	fcSttbfBkmk			= { };
	lcbSttbfBkmk		= { };
	fcPlcfBkf			= { };
	lcbPlcfBkf			= { };
	fcPlcfBkl			= { };
	lcbPlcfBkl			= { };
	fcCmds				= { };
	lcbCmds				= { };
	fcUnused1			= { };
	lcbUnused1			= { };
	fcSttbfMcr			= { };
	lcbSttbfMcr			= { };
	fcPrDrvr			= { };
	lcbPrDrvr			= { };
	fcPrEnvPort			= { };
	lcbPrEnvPort		= { };
	fcPrEnvLand			= { };
	lcbPrEnvLand		= { };
	fcWss				= { };
	lcbWss				= { };
	fcDop				= { };
	lcbDop				= { };
	fcSttbfAssoc		= { };
	lcbSttbfAssoc		= { };
	fcClx				= { };
	lcbClx				= { };
	fcPlcfPgdFtn		= { };
	lcbPlcfPgdFtn		= { };
	fcAutosaveSource	= { };
	lcbAutosaveSource	= { };
	fcGrpXstAtnOwners	= { };
	lcbGrpXstAtnOwners	= { };
	fcSttbfAtnBkmk		= { };
	lcbSttbfAtnBkmk		= { };
	fcUnused2			= { };
	lcbUnused2			= { };
	fcUnused3			= { };
	lcbUnused3			= { };
	fcPlcSpaMom			= { };
	lcbPlcSpaMom		= { };
	fcPlcSpaHdr			= { };
	lcbPlcSpaHdr		= { };
	fcPlcfAtnBkf		= { };
	lcbPlcfAtnBkf		= { };
	fcPlcfAtnBkl		= { };
	lcbPlcfAtnBkl		= { };
	fcPms				= { };
	lcbPms				= { };
	fcFormFldSttbs		= { };
	lcbFormFldSttbs		= { };
	fcPlcfendRef		= { };
	lcbPlcfendRef		= { };
	fcPlcfendTxt		= { };
	lcbPlcfendTxt		= { };
	fcPlcfFldEdn		= { };
	lcbPlcfFldEdn		= { };
	fcUnused4			= { };
	lcbUnused4			= { };
	fcDggInfo			= { };
	lcbDggInfo			= { };
	fcSttbfRMark		= { };
	lcbSttbfRMark		= { };
	fcSttbfCaption		= { };
	lcbSttbfCaption		= { };
	fcSttbfAutoCaption	= { };
	lcbSttbfAutoCaption = { };
	fcPlcfWkb			= { };
	lcbPlcfWkb			= { };
	fcPlcfSpl			= { };
	lcbPlcfSpl			= { };
	fcPlcftxbxTxt		= { };
	lcbPlcftxbxTxt		= { };
	fcPlcfFldTxbx		= { };
	lcbPlcfFldTxbx		= { };
	fcPlcfHdrtxbxTxt	= { };
	lcbPlcfHdrtxbxTxt	= { };
	fcPlcffldHdrTxbx	= { };
	lcbPlcffldHdrTxbx	= { };
	fcStwUser			= { };
	lcbStwUser			= { };
	fcSttbTtmbd			= { };
	lcbSttbTtmbd		= { };
	fcCookieData		= { };
	lcbCookieData		= { };
	fcPgdMotherOldOld	= { };
	lcbPgdMotherOldOld	= { };
	fcBkdMotherOldOld	= { };
	lcbBkdMotherOldOld	= { };
	fcPgdFtnOldOld		= { };
	lcbPgdFtnOldOld		= { };
	fcBkdFtnOldOld		= { };
	lcbBkdFtnOldOld		= { };
	fcPgdEdnOldOld		= { };
	lcbPgdEdnOldOld		= { };
	fcBkdEdnOldOld		= { };
	lcbBkdEdnOldOld		= { };
	fcSttbfIntlFld		= { };
	lcbSttbfIntlFld		= { };
	fcRouteSlip			= { };
	lcbRouteSlip		= { };
	fcSttbSavedBy		= { };
	lcbSttbSavedBy		= { };
	fcSttbFnm			= { };
	lcbSttbFnm			= { };
	fcPlfLst			= { };
	lcbPlfLst			= { };
	fcPlfLfo			= { };
	lcbPlfLfo			= { };
	fcPlcfTxbxBkd		= { };
	lcbPlcfTxbxBkd		= { };
	fcPlcfTxbxHdrBkd	= { };
	lcbPlcfTxbxHdrBkd	= { };
	fcDocUndoUSHORT9		= { };
	lcbDocUndoUSHORT9		= { };
	fcRgbUse			= { };
	lcbRgbUse			= { };
	fcUsp				= { };
	lcbUsp				= { };
	fcUskf				= { };
	lcbUskf				= { };
	fcPlcupcRgbUse		= { };
	lcbPlcupcRgbUse		= { };
	fcPlcupcUsp			= { };
	lcbPlcupcUsp		= { };
	fcSttbGlsyStyle		= { };
	lcbSttbGlsyStyle	= { };
	fcPlgosl			= { };
	lcbPlgosl			= { };
	fcPlcocx			= { };
	lcbPlcocx			= { };
	fcPlcfBteLvc		= { };
	lcbPlcfBteLvc		= { };
	dwLowDateTime		= { };
	dwHighDateTime		= { };
	fcPlcfLvcPre10		= { };
	lcbPlcfLvcPre10		= { };
	fcPlcfAsumy			= { };
	lcbPlcfAsumy		= { };
	fcPlcfGram			= { };
	lcbPlcfGram			= { };
	fcSttbListNames		= { };
	lcbSttbListNames	= { };
	fcSttbfUssr			= { };
	lcbSttbfUssr		= { };
}

Fib::FibRgFcLcb::FibRgFcLcb97::~FibRgFcLcb97()
{
}

Fib::FibRgFcLcb::FibRgFcLcb2000::FibRgFcLcb2000()
{
	fcPlcfTch			= { };
	lcbPlcfTch			= { };
	fcRmdThreading		= { };
	lcbRmdThreading		= { };
	fcMid				= { };
	lcbMid				= { };
	fcSttbRgtplc		= { };
	lcbSttbRgtplc		= { };
	fcMsoEnvelope		= { };
	lcbMsoEnvelope		= { };
	fcPlcfLad			= { };
	lcbPlcfLad			= { };
	fcRgDofr			= { };
	lcbRgDofr			= { };
	fcPlcosl			= { };
	lcbPlcosl			= { };
	fcPlcfCookieOld		= { };
	lcbPlcfCookieOld	= { };
	fcPgdMotherOld		= { };
	lcbPgdMotherOld		= { };
	fcBkdMotherOld		= { };
	lcbBkdMotherOld		= { };
	fcPgdFtnOld			= { };
	lcbPgdFtnOld		= { };
	fcBkdFtnOld			= { };
	lcbBkdFtnOld		= { };
	fcPgdEdnOld			= { };
	lcbPgdEdnOld		= { };
	fcBkdEdnOld			= { };
	lcbBkdEdnOld		= { };
}

Fib::FibRgFcLcb::FibRgFcLcb2000::~FibRgFcLcb2000()
{
}


VOID Fib::FibRgFcLcb::FibRgFcLcb2000::process_FibRgFcLcb2000()
{
	assert(lcbRmdThreading != 0);
	return;
}

Fib::FibRgFcLcb::FibRgFcLcb2002::FibRgFcLcb2002()
{
	fcUnused1				= { };
	lcbUnused1				= { };
	fcPlcfPgp				= { };
	lcbPlcfPgp				= { };
	fcPlcfuim				= { };
	lcbPlcfuim				= { };
	fcPlfguidUim			= { };
	lcbPlfguidUim			= { };
	fcAtrdExtra				= { };
	lcbAtrdExtra			= { };
	fcPlrsid				= { };
	lcbPlrsid				= { };
	fcSttbfBkmkFactoid		= { };
	lcbSttbfBkmkFactoid		= { };
	fcPlcfBkfFactoid		= { };
	lcbPlcfBkfFactoid		= { };
	fcPlcfcookie			= { };
	lcbPlcfcookie			= { };
	fcPlcfBklFactoid		= { };
	lcbPlcfBklFactoid		= { };
	fcFactoidData			= { };
	lcbFactoidData			= { };
	fcDocUndo				= { };
	lcbDocUndo				= { };
	fcSttbfBkmkFcc			= { };
	lcbSttbfBkmkFcc			= { };
	fcPlcfBkfFcc			= { };
	lcbPlcfBkfFcc			= { };
	fcPlcfBklFcc			= { };
	lcbPlcfBklFcc			= { };
	fcSttbfbkmkBPRepairs	= { };
	lcbSttbfbkmkBPRepairs	= { };
	fcPlcfbkfBPRepairs		= { };
	lcbPlcfbkfBPRepairs		= { };
	fcPlcfbklBPRepairs		= { };
	lcbPlcfbklBPRepairs		= { };
	fcPmsNew				= { };
	lcbPmsNew				= { };
	fcODSO					= { };
	lcbODSO					= { };
	fcPlcfpmiOldXP			= { };
	lcbPlcfpmiOldXP			= { };
	fcPlcfpmiNewXP			= { };
	lcbPlcfpmiNewXP			= { };
	fcPlcfpmiMixedXP		= { };
	lcbPlcfpmiMixedXP		= { };
	fcUnused2				= { };
	lcbUnused2				= { };
	fcPlcffactoid			= { };
	lcbPlcffactoid			= { };
	fcPlcflvcOldXP			= { };
	lcbPlcflvcOldXP			= { };
	fcPlcflvcNewXP			= { };
	lcbPlcflvcNewXP			= { };
	fcPlcflvcMixedXP		= { };
	lcbPlcflvcMixedXP		= { };

}

Fib::FibRgFcLcb::FibRgFcLcb2002::~FibRgFcLcb2002()
{
}

VOID Fib::FibRgFcLcb::FibRgFcLcb2002::process_FibRgFcLcb2002()
{
	assert(lcbUnused1 == 0);

	return;
}

Fib::FibRgFcLcb::FibRgFcLcb2003::FibRgFcLcb2003()
{
	fcHplxsdr				= { };
	lcbHplxsdr				= { };
	fcSttbfBkmkSdt			= { };
	lcbSttbfBkmkSdt			= { };
	fcPlcfBkfSdt			= { };
	lcbPlcfBkfSdt			= { };
	fcPlcfBklSdt			= { };
	lcbPlcfBklSdt			= { };
	fcCustomXForm			= { };
	lcbCustomXForm			= { };
	fcSttbfBkmkProt			= { };
	lcbSttbfBkmkProt		= { };
	fcPlcfBkfProt			= { };
	lcbPlcfBkfProt			= { };
	fcPlcfBklProt			= { };
	lcbPlcfBklProt			= { };
	fcSttbProtUser			= { };
	lcbSttbProtUser			= { };
	fcUnused				= { };
	lcbUnused				= { };
	fcPlcfpmiOld			= { };
	lcbPlcfpmiOld			= { };
	fcPlcfpmiOldInline		= { };
	lcbPlcfpmiOldInline		= { };
	fcPlcfpmiNew			= { };
	lcbPlcfpmiNew			= { };
	fcPlcfpmiNewInline		= { };
	lcbPlcfpmiNewInline		= { };
	fcPlcflvcOld			= { };
	lcbPlcflvcOld			= { };
	fcPlcflvcOldInline		= { };
	lcbPlcflvcOldInline		= { };
	fcPlcflvcNew			= { };
	lcbPlcflvcNew			= { };
	fcPlcflvcNewInline		= { };
	lcbPlcflvcNewInline		= { };
	fcPgdMother				= { };
	lcbPgdMother			= { };
	fcBkdMother				= { };
	lcbBkdMother			= { };
	fcAfdMother				= { };
	lcbAfdMother			= { };
	fcPgdFtn				= { };
	lcbPgdFtn				= { };
	fcBkdFtn				= { };
	lcbBkdFtn				= { };
	fcAfdFtn				= { };
	lcbAfdFtn				= { };
	fcPgdEdn				= { };
	lcbPgdEdn				= { };
	fcBkdEdn				= { };
	lcbBkdEdn				= { };
	fcAfdEdn				= { };
	lcbAfdEdn				= { };
	fcAfd					= { };
	lcbAfd					= { };

}

Fib::FibRgFcLcb::FibRgFcLcb2003::~FibRgFcLcb2003()
{
}


VOID Fib::FibRgFcLcb::FibRgFcLcb2003::process_FibRgFcLcb2003()
{
	assert(lcbCustomXForm <= 4168 && lcbCustomXForm % 2 == 0);
	assert(fcUnused == 0);
	assert(lcbUnused == 0);
	return;
}

Fib::FibRgFcLcb::FibRgFcLcb2007::FibRgFcLcb2007()
{
	fcPlcfmthd            = { };
	lcbPlcfmthd           = { };
	fcSttbfBkmkMoveFrom   = { };
	lcbSttbfBkmkMoveFrom  = { };
	fcPlcfBkfMoveFrom     = { };
	lcbPlcfBkfMoveFrom    = { };
	fcPlcfBklMoveFrom     = { };
	lcbPlcfBklMoveFrom    = { };
	fcSttbfBkmkMoveTo     = { };
	lcbSttbfBkmkMoveTo    = { };
	fcPlcfBkfMoveTo       = { };
	lcbPlcfBkfMoveTo      = { };
	fcPlcfBklMoveTo       = { };
	lcbPlcfBklMoveTo      = { };
	fcUnused1             = { };
	lcbUnused1            = { };
	fcUnused2             = { };
	lcbUnused2            = { };
	fcUnused3             = { };
	lcbUnused3            = { };
	fcSttbfBkmkArto       = { };
	lcbSttbfBkmkArto      = { };
	fcPlcfBkfArto         = { };
	lcbPlcfBkfArto        = { };
	fcPlcfBklArto         = { };
	lcbPlcfBklArto        = { };
	fcArtoData            = { };
	lcbArtoData           = { };
	fcUnused4             = { };
	lcbUnused4            = { };
	fcUnused5             = { };
	lcbUnused5            = { };
	fcUnused6             = { };
	lcbUnused6            = { };
	fcOssTheme            = { };
	lcbOssTheme           = { };
	fcColorSchemeMapping  = { };
	lcbColorSchemeMapping = { };
}

Fib::FibRgFcLcb::FibRgFcLcb2007::~FibRgFcLcb2007()
{
}


VOID Fib::FibRgFcLcb::FibRgFcLcb2007::process_FibRgFcLcb2007()
{
	assert(lcbPlcfmthd == 0);
	assert(lcbSttbfBkmkMoveFrom == 0);
	assert(lcbPlcfBkfMoveFrom == 0);
	assert(lcbPlcfBklMoveFrom == 0);
	assert(lcbSttbfBkmkMoveTo == 0);
	assert(lcbPlcfBkfMoveTo == 0);
	assert(lcbPlcfBklMoveTo == 0);
	assert(lcbUnused1 == 0);
	assert(lcbUnused2 == 0);
	assert(lcbUnused3 == 0);
	assert(lcbSttbfBkmkArto == 0);
	assert(lcbPlcfBkfArto == 0);
	assert(lcbPlcfBklArto == 0);
	assert(lcbArtoData == 0);
	assert(lcbUnused4 == 0);
	assert(lcbUnused5 == 0);
	assert(lcbUnused6 == 0);
	
	return;


}

Fib::FibRgCswNew::FibRgCswNew()
{
	nFibNew = { };
}

Fib::FibRgCswNew::~FibRgCswNew()
{
}

VOID Fib::FibRgCswNew::readFibRgCswNew(std::ifstream & ldedstrm)
{
	ldedstrm.read(reinterpret_cast<char *>(&nFibNew), sizeof(nFibNew));

	if (nFibNew == 0x0112)
		rgCswNewData.fibRgCswNewData2007.readFibRgCswNewData2007(ldedstrm);
	else if ((nFibNew == 0x00D9 || nFibNew == 0x0101) || nFibNew == 0x010C)
		rgCswNewData.fibRgCswNewData2000.readFibRgCswNewData2000(ldedstrm);
	else { assert(!" value of nFibNew not valid"); }

	return;
}

Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData()
{
}

Fib::FibRgCswNew::FibRgCswNewData::~FibRgCswNewData()
{
}

Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2007::FibRgCswNewData2007()
{
	lidThemeOther = { };
	lidThemeFE    = { };
	lidThemeCS    = { };
}

Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2007::~FibRgCswNewData2007()
{
}


Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::FibRgCswNewData2000()
{
	cQuickSavesNew = { };
}

Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::~FibRgCswNewData2000()
{
}

VOID Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::process_FibRgCswNewData2000()
{
	assert(cQuickSavesNew >= 0 && cQuickSavesNew <= 0x000F);
	return;
}

// Reads the File Information Block (FIB)
VOID Fib::readFib(std::ifstream &docstream)
{
	int readSize = 0;
	int objSize = sizeof(FibBase);
	docstream.read(reinterpret_cast<char *>(&base), objSize); // base.readFibBase(docstream);

	docstream.read(reinterpret_cast<char *>(&csw), sizeof(USHORT));
	readSize = csw * 2;
	objSize = sizeof(FibRgW97);
	docstream.read(reinterpret_cast<char *>(&fibRgW), objSize); // fibRgW.readFibRgW(docstream); 
	adjust_file_pointer(docstream, objSize, readSize);

	docstream.read(reinterpret_cast<char *>(&cslw), sizeof(USHORT));
	readSize = cslw * 4;
	objSize = sizeof(FibRgLw97);
	docstream.read(reinterpret_cast<char *>(&fibRgLw), objSize); // fibRgLw.readFibRgLw(docstream);
	adjust_file_pointer(docstream, objSize, readSize);

	docstream.read(reinterpret_cast<char *>(&cbRgFcLcb), sizeof(USHORT));
	readSize = cbRgFcLcb * 8;
	objSize = sizeof(FibRgFcLcb);
	docstream.read(reinterpret_cast<char *>(&fibRgFcLcbBlob), objSize);
	adjust_file_pointer(docstream, objSize, readSize);
	
	docstream.read(reinterpret_cast<char *>(&cswNew), sizeof(USHORT));
	const unsigned int ver = determine_nFib_use();
	if (cswNew != 0x00)
	{
		readSize = cswNew * 2;
		objSize = sizeof(FibRgCswNew);
		docstream.read(reinterpret_cast<char *>(&fibRgCswNew), objSize); // fibRgCswNew.readFibRgCswNew(docstream);
		adjust_file_pointer(docstream, objSize, readSize);
	}
	return;
}

// Reads various structures from the stream into memory
VOID Fib::FibBase::readFibBase(std::ifstream &docfile)
{
	docfile.read(reinterpret_cast<char *>(&wIdent), sizeof(wIdent));
	docfile.read(reinterpret_cast<char *>(&nFib), sizeof(nFib));
	docfile.read(reinterpret_cast<char *>(&unused), sizeof(unused));
	docfile.read(reinterpret_cast<char *>(&lid), sizeof(lid));
	docfile.read(reinterpret_cast<char *>(&pnNext), sizeof(pnNext));

	BYTE		tmp = 0x0;			// temporary storage
	const BYTE	fD  = 0x1;
	const BYTE	fG  = 0x2;
	const BYTE	fC  = 0x4;
	const BYTE	fHP = 0x8;
	BYTE		msk = 0x0F;			// mask last 4 bits
	
	docfile.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
	fDot		= assignBits(fD, tmp, 0);
	fGlsy		= assignBits(fG, tmp, 1);
	fComplex	= assignBits(fC, tmp, 2);
	fHasPic		= assignBits(fHP, tmp, 3);
	tmp >>= 4;
	cQuickSaves = tmp & msk;
	
	const BYTE fE	= 0x1;
	const BYTE fWT	= 0x2;
	const BYTE fROR = 0x4;
	const BYTE fWR	= 0x8;
	const BYTE fEC	= 0x10;
	const BYTE fLO	= 0x20;
	const BYTE fFE	= 0x40;
	const BYTE fO	= 0x80;
	docfile.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
	fEncrypted				= assignBits(fE, tmp, 0);
	fWhichTblStm			= assignBits(fWT, tmp, 1);
	fReadOnlyRecommended	= assignBits(fROR, tmp, 2);
	fWriteReservation		= assignBits(fWR, tmp, 3);
	fExtChar				= assignBits(fEC, tmp, 4);
	fLoadOverride			= assignBits(fLO, tmp, 5);
	fFarEast				= assignBits(fFE, tmp, 6);
	fObfuscated				= assignBits(fO, tmp, 7);

	docfile.read(reinterpret_cast<char *>(&nFibBack), sizeof(nFibBack));
	docfile.read(reinterpret_cast<char *>(&lkey), sizeof(lkey));
	docfile.read(reinterpret_cast<char *>(&envr), sizeof(envr));
	
	const BYTE fM	= 0x1;
	const BYTE fES  = 0x2;
	const BYTE fLOP = 0x4;
	const BYTE res1 = 0x8;
	const BYTE res2 = 0x10;
	msk = 0x9;
	docfile.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
	fMac              = assignBits(fM, tmp, 0);
	fEmptySpecial     = assignBits(fES, tmp, 1);
	fLoadOverridePage = assignBits(fLOP, tmp, 2);
	reserved1         = assignBits(res1, tmp, 3);
	reserved2         = assignBits(res2, tmp, 4);
	tmp >>= 5;
	fSpare0 = tmp & msk;

	docfile.read(reinterpret_cast<char *>(&reserved3), sizeof(reserved3));
	docfile.read(reinterpret_cast<char *>(&reserved4), sizeof(reserved4));
	docfile.read(reinterpret_cast<char *>(&reserved5), sizeof(reserved5));
	docfile.read(reinterpret_cast<char *>(&reserved6), sizeof(reserved6));
	
	return;
}

VOID Fib::FibRgLw97::readFibRgLw(std::ifstream & mystream)
{
	USHORT add_member_sizes = 0;

	mystream.read(reinterpret_cast<char *>(&cbMac), sizeof(cbMac));
	add_member_sizes += sizeof(cbMac);
	mystream.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
	add_member_sizes += sizeof(reserved1);
	mystream.read(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
	add_member_sizes += sizeof(reserved2);
	mystream.read(reinterpret_cast<char *>(&ccpText), sizeof(ccpText));
	add_member_sizes += sizeof(ccpText);
	mystream.read(reinterpret_cast<char *>(&ccpFtn), sizeof(ccpFtn));
	add_member_sizes += sizeof(ccpFtn);
	mystream.read(reinterpret_cast<char *>(&ccpHdd), sizeof(ccpHdd));
	add_member_sizes += sizeof(ccpHdd);
	mystream.read(reinterpret_cast<char *>(&reserved3), sizeof(reserved3));
	add_member_sizes += sizeof(reserved3);
	mystream.read(reinterpret_cast<char *>(&ccpAtn), sizeof(ccpAtn));
	add_member_sizes += sizeof(ccpAtn);
	mystream.read(reinterpret_cast<char *>(&ccpEdn), sizeof(ccpEdn));
	add_member_sizes += sizeof(ccpEdn);
	mystream.read(reinterpret_cast<char *>(&ccpTxbx), sizeof(ccpTxbx));
	add_member_sizes += sizeof(ccpTxbx);
	mystream.read(reinterpret_cast<char *>(&ccpHdrTxbx), sizeof(ccpHdrTxbx));
	add_member_sizes += sizeof(ccpHdrTxbx);
	mystream.read(reinterpret_cast<char *>(&reserved4), sizeof(reserved4));
	add_member_sizes += sizeof(reserved4);
	mystream.read(reinterpret_cast<char *>(&reserved5), sizeof(reserved5));
	add_member_sizes += sizeof(reserved5);
	mystream.read(reinterpret_cast<char *>(&reserved6), sizeof(reserved6));
	add_member_sizes += sizeof(reserved6);
	mystream.read(reinterpret_cast<char *>(&reserved7), sizeof(reserved7));
	add_member_sizes += sizeof(reserved7);
	mystream.read(reinterpret_cast<char *>(&reserved8), sizeof(reserved8));
	add_member_sizes += sizeof(reserved8);
	mystream.read(reinterpret_cast<char *>(&reserved9), sizeof(reserved9));
	add_member_sizes += sizeof(reserved9);
	mystream.read(reinterpret_cast<char *>(&reserved10), sizeof(reserved10));
	add_member_sizes += sizeof(reserved10);
	mystream.read(reinterpret_cast<char *>(&reserved11), sizeof(reserved11));
	add_member_sizes += sizeof(reserved11);
	mystream.read(reinterpret_cast<char *>(&reserved12), sizeof(reserved12));
	add_member_sizes += sizeof(reserved12);
	mystream.read(reinterpret_cast<char *>(&reserved13), sizeof(reserved13));
	add_member_sizes += sizeof(reserved13);
	mystream.read(reinterpret_cast<char *>(&reserved14), sizeof(reserved14));
	add_member_sizes += sizeof(reserved14);

}

VOID Fib::FibRgW97::readFibRgW(std::ifstream & filestrm)
{
	filestrm.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
	filestrm.read(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
	filestrm.read(reinterpret_cast<char *>(&reserved3), sizeof(reserved3));
	filestrm.read(reinterpret_cast<char *>(&reserved4), sizeof(reserved4));
	filestrm.read(reinterpret_cast<char *>(&reserved5), sizeof(reserved5));
	filestrm.read(reinterpret_cast<char *>(&reserved6), sizeof(reserved6));
	filestrm.read(reinterpret_cast<char *>(&reserved7), sizeof(reserved7));
	filestrm.read(reinterpret_cast<char *>(&reserved8), sizeof(reserved8));
	filestrm.read(reinterpret_cast<char *>(&reserved9), sizeof(reserved9));
	filestrm.read(reinterpret_cast<char *>(&reserved10), sizeof(reserved10));
	filestrm.read(reinterpret_cast<char *>(&reserved11), sizeof(reserved11));
	filestrm.read(reinterpret_cast<char *>(&reserved12), sizeof(reserved12));
	filestrm.read(reinterpret_cast<char *>(&reserved13), sizeof(reserved13));
	filestrm.read(reinterpret_cast<char *>(&lidFE), sizeof(lidFE));

	return;
}

VOID Fib::FibRgFcLcb::FibRgFcLcb97::readFibRgFcLcb97(std::ifstream & mainstrm)
{
	mainstrm.read(reinterpret_cast<char *>(&fcStshfOrig), sizeof(fcStshfOrig));
	mainstrm.read(reinterpret_cast<char *>(&lcbStshfOrig), sizeof(lcbStshfOrig));
	mainstrm.read(reinterpret_cast<char *>(&fcStshf), sizeof(fcStshf));
	mainstrm.read(reinterpret_cast<char *>(&lcbStshf), sizeof(lcbStshf));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcffndRef), sizeof(fcPlcffndRef));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcffndRef), sizeof(lcbPlcffndRef));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcffndTxt), sizeof(fcPlcffndTxt));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcffndTxt), sizeof(lcbPlcffndTxt));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfandRef), sizeof(fcPlcfandRef));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfandRef), sizeof(lcbPlcfandRef));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfandTxt), sizeof(fcPlcfandTxt));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfandTxt), sizeof(lcbPlcfandTxt));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfSed), sizeof(fcPlcfSed));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfSed), sizeof(lcbPlcfSed));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcPad), sizeof(fcPlcPad));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcPad), sizeof(lcbPlcPad));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfPhe), sizeof(fcPlcfPhe));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfPhe), sizeof(lcbPlcfPhe));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbfGlsy), sizeof(fcSttbfGlsy));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbfGlsy), sizeof(lcbSttbfGlsy));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfGlsy), sizeof(fcPlcfGlsy));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfGlsy), sizeof(lcbPlcfGlsy));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfHdd), sizeof(fcPlcfHdd));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfHdd), sizeof(lcbPlcfHdd));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfBteChpx), sizeof(fcPlcfBteChpx));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBteChpx), sizeof(lcbPlcfBteChpx));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfBtePapx), sizeof(fcPlcfBtePapx));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBtePapx), sizeof(lcbPlcfBtePapx));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfSea), sizeof(fcPlcfSea));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfSea), sizeof(lcbPlcfSea));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbfFfn), sizeof(fcSttbfFfn));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbfFfn), sizeof(lcbSttbfFfn));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldMom), sizeof(fcPlcfFldMom));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldMom), sizeof(lcbPlcfFldMom));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldHdr), sizeof(fcPlcfFldHdr));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldHdr), sizeof(lcbPlcfFldHdr));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldFtn), sizeof(fcPlcfFldFtn));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldFtn), sizeof(lcbPlcfFldFtn));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldAtn), sizeof(fcPlcfFldAtn));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldAtn), sizeof(lcbPlcfFldAtn));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldMcr), sizeof(fcPlcfFldMcr));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldMcr), sizeof(lcbPlcfFldMcr));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbfBkmk), sizeof(fcSttbfBkmk));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbfBkmk), sizeof(lcbSttbfBkmk));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfBkf), sizeof(fcPlcfBkf));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBkf), sizeof(lcbPlcfBkf));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfBkl), sizeof(fcPlcfBkl));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBkl), sizeof(lcbPlcfBkl));
	mainstrm.read(reinterpret_cast<char *>(&fcCmds), sizeof(fcCmds));
	mainstrm.read(reinterpret_cast<char *>(&lcbCmds), sizeof(lcbCmds));
	mainstrm.read(reinterpret_cast<char *>(&fcUnused1), sizeof(fcUnused1));
	mainstrm.read(reinterpret_cast<char *>(&lcbUnused1), sizeof(lcbUnused1));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbfMcr), sizeof(fcSttbfMcr));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbfMcr), sizeof(lcbSttbfMcr));
	mainstrm.read(reinterpret_cast<char *>(&fcPrDrvr), sizeof(fcPrDrvr));
	mainstrm.read(reinterpret_cast<char *>(&lcbPrDrvr), sizeof(lcbPrDrvr));
	mainstrm.read(reinterpret_cast<char *>(&fcPrEnvPort), sizeof(fcPrEnvPort));
	mainstrm.read(reinterpret_cast<char *>(&lcbPrEnvPort), sizeof(lcbPrEnvPort));
	mainstrm.read(reinterpret_cast<char *>(&fcPrEnvLand), sizeof(fcPrEnvLand));
	mainstrm.read(reinterpret_cast<char *>(&lcbPrEnvLand), sizeof(lcbPrEnvLand));
	mainstrm.read(reinterpret_cast<char *>(&fcWss), sizeof(fcWss));
	mainstrm.read(reinterpret_cast<char *>(&lcbWss), sizeof(lcbWss));
	mainstrm.read(reinterpret_cast<char *>(&fcDop), sizeof(fcDop));
	mainstrm.read(reinterpret_cast<char *>(&lcbDop), sizeof(lcbDop));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbfAssoc), sizeof(fcSttbfAssoc));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbfAssoc), sizeof(lcbSttbfAssoc));
	mainstrm.read(reinterpret_cast<char *>(&fcClx), sizeof(fcClx));
	mainstrm.read(reinterpret_cast<char *>(&lcbClx), sizeof(lcbClx));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfPgdFtn), sizeof(fcPlcfPgdFtn));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfPgdFtn), sizeof(lcbPlcfPgdFtn));
	mainstrm.read(reinterpret_cast<char *>(&fcAutosaveSource), sizeof(fcAutosaveSource));
	mainstrm.read(reinterpret_cast<char *>(&lcbAutosaveSource), sizeof(lcbAutosaveSource));
	mainstrm.read(reinterpret_cast<char *>(&fcGrpXstAtnOwners), sizeof(fcGrpXstAtnOwners));
	mainstrm.read(reinterpret_cast<char *>(&lcbGrpXstAtnOwners), sizeof(lcbGrpXstAtnOwners));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbfAtnBkmk), sizeof(fcSttbfAtnBkmk));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbfAtnBkmk), sizeof(lcbSttbfAtnBkmk));
	mainstrm.read(reinterpret_cast<char *>(&fcUnused2), sizeof(fcUnused2));
	mainstrm.read(reinterpret_cast<char *>(&lcbUnused2), sizeof(lcbUnused2));
	mainstrm.read(reinterpret_cast<char *>(&fcUnused3), sizeof(fcUnused3));
	mainstrm.read(reinterpret_cast<char *>(&lcbUnused3), sizeof(lcbUnused3));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcSpaMom), sizeof(fcPlcSpaMom));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcSpaMom), sizeof(lcbPlcSpaMom));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcSpaHdr), sizeof(fcPlcSpaHdr));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcSpaHdr), sizeof(lcbPlcSpaHdr));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfAtnBkf), sizeof(fcPlcfAtnBkf));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfAtnBkf), sizeof(lcbPlcfAtnBkf));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfAtnBkl), sizeof(fcPlcfAtnBkl));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfAtnBkl), sizeof(lcbPlcfAtnBkl));
	mainstrm.read(reinterpret_cast<char *>(&fcPms), sizeof(fcPms));
	mainstrm.read(reinterpret_cast<char *>(&lcbPms), sizeof(lcbPms));
	mainstrm.read(reinterpret_cast<char *>(&fcFormFldSttbs), sizeof(fcFormFldSttbs));
	mainstrm.read(reinterpret_cast<char *>(&lcbFormFldSttbs), sizeof(lcbFormFldSttbs));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfendRef), sizeof(fcPlcfendRef));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfendRef), sizeof(lcbPlcfendRef));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfendTxt), sizeof(fcPlcfendTxt));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfendTxt), sizeof(lcbPlcfendTxt));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldEdn), sizeof(fcPlcfFldEdn));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldEdn), sizeof(lcbPlcfFldEdn));
	mainstrm.read(reinterpret_cast<char *>(&fcUnused4), sizeof(fcUnused4));
	mainstrm.read(reinterpret_cast<char *>(&lcbUnused4), sizeof(lcbUnused4));
	mainstrm.read(reinterpret_cast<char *>(&fcDggInfo), sizeof(fcDggInfo));
	mainstrm.read(reinterpret_cast<char *>(&lcbDggInfo), sizeof(lcbDggInfo));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbfRMark), sizeof(fcSttbfRMark));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbfRMark), sizeof(lcbSttbfRMark));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbfCaption), sizeof(fcSttbfCaption));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbfCaption), sizeof(lcbSttbfCaption));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbfAutoCaption), sizeof(fcSttbfAutoCaption));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbfAutoCaption), sizeof(lcbSttbfAutoCaption));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfWkb), sizeof(fcPlcfWkb));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfWkb), sizeof(lcbPlcfWkb));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfSpl), sizeof(fcPlcfSpl));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfSpl), sizeof(lcbPlcfSpl));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcftxbxTxt), sizeof(fcPlcftxbxTxt));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcftxbxTxt), sizeof(lcbPlcftxbxTxt));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldTxbx), sizeof(fcPlcfFldTxbx));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldTxbx), sizeof(lcbPlcfFldTxbx));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfHdrtxbxTxt), sizeof(fcPlcfHdrtxbxTxt));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfHdrtxbxTxt), sizeof(lcbPlcfHdrtxbxTxt));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcffldHdrTxbx), sizeof(fcPlcffldHdrTxbx));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcffldHdrTxbx), sizeof(lcbPlcffldHdrTxbx));
	mainstrm.read(reinterpret_cast<char *>(&fcStwUser), sizeof(fcStwUser));
	mainstrm.read(reinterpret_cast<char *>(&lcbStwUser), sizeof(lcbStwUser));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbTtmbd), sizeof(fcSttbTtmbd));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbTtmbd), sizeof(lcbSttbTtmbd));
	mainstrm.read(reinterpret_cast<char *>(&fcCookieData), sizeof(fcCookieData));
	mainstrm.read(reinterpret_cast<char *>(&lcbCookieData), sizeof(lcbCookieData));
	mainstrm.read(reinterpret_cast<char *>(&fcPgdMotherOldOld), sizeof(fcPgdMotherOldOld));
	mainstrm.read(reinterpret_cast<char *>(&lcbPgdMotherOldOld), sizeof(lcbPgdMotherOldOld));
	mainstrm.read(reinterpret_cast<char *>(&fcBkdMotherOldOld), sizeof(fcBkdMotherOldOld));
	mainstrm.read(reinterpret_cast<char *>(&lcbBkdMotherOldOld), sizeof(lcbBkdMotherOldOld));
	mainstrm.read(reinterpret_cast<char *>(&fcPgdFtnOldOld), sizeof(fcPgdFtnOldOld));
	mainstrm.read(reinterpret_cast<char *>(&lcbPgdFtnOldOld), sizeof(lcbPgdFtnOldOld));
	mainstrm.read(reinterpret_cast<char *>(&fcBkdFtnOldOld), sizeof(fcBkdFtnOldOld));
	mainstrm.read(reinterpret_cast<char *>(&lcbBkdFtnOldOld), sizeof(lcbBkdFtnOldOld));
	mainstrm.read(reinterpret_cast<char *>(&fcPgdEdnOldOld), sizeof(fcPgdEdnOldOld));
	mainstrm.read(reinterpret_cast<char *>(&lcbPgdEdnOldOld), sizeof(lcbPgdEdnOldOld));
	mainstrm.read(reinterpret_cast<char *>(&fcBkdEdnOldOld), sizeof(fcBkdEdnOldOld));
	mainstrm.read(reinterpret_cast<char *>(&lcbBkdEdnOldOld), sizeof(lcbBkdEdnOldOld));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbfIntlFld), sizeof(fcSttbfIntlFld));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbfIntlFld), sizeof(lcbSttbfIntlFld));
	mainstrm.read(reinterpret_cast<char *>(&fcRouteSlip), sizeof(fcRouteSlip));
	mainstrm.read(reinterpret_cast<char *>(&lcbRouteSlip), sizeof(lcbRouteSlip));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbSavedBy), sizeof(fcSttbSavedBy));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbSavedBy), sizeof(lcbSttbSavedBy));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbFnm), sizeof(fcSttbFnm));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbFnm), sizeof(lcbSttbFnm));
	mainstrm.read(reinterpret_cast<char *>(&fcPlfLst), sizeof(fcPlfLst));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlfLst), sizeof(lcbPlfLst));
	mainstrm.read(reinterpret_cast<char *>(&fcPlfLfo), sizeof(fcPlfLfo));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlfLfo), sizeof(lcbPlfLfo));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfTxbxBkd), sizeof(fcPlcfTxbxBkd));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfTxbxBkd), sizeof(lcbPlcfTxbxBkd));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfTxbxHdrBkd), sizeof(fcPlcfTxbxHdrBkd));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfTxbxHdrBkd), sizeof(lcbPlcfTxbxHdrBkd));
	mainstrm.read(reinterpret_cast<char *>(&fcDocUndoUSHORT9), sizeof(fcDocUndoUSHORT9));
	mainstrm.read(reinterpret_cast<char *>(&lcbDocUndoUSHORT9), sizeof(lcbDocUndoUSHORT9));
	mainstrm.read(reinterpret_cast<char *>(&fcRgbUse), sizeof(fcRgbUse));
	mainstrm.read(reinterpret_cast<char *>(&lcbRgbUse), sizeof(lcbRgbUse));
	mainstrm.read(reinterpret_cast<char *>(&fcUsp), sizeof(fcUsp));
	mainstrm.read(reinterpret_cast<char *>(&lcbUsp), sizeof(lcbUsp));
	mainstrm.read(reinterpret_cast<char *>(&fcUskf), sizeof(fcUskf));
	mainstrm.read(reinterpret_cast<char *>(&lcbUskf), sizeof(lcbUskf));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcupcRgbUse), sizeof(fcPlcupcRgbUse));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcupcRgbUse), sizeof(lcbPlcupcRgbUse));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcupcUsp), sizeof(fcPlcupcUsp));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcupcUsp), sizeof(lcbPlcupcUsp));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbGlsyStyle), sizeof(fcSttbGlsyStyle));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbGlsyStyle), sizeof(lcbSttbGlsyStyle));
	mainstrm.read(reinterpret_cast<char *>(&fcPlgosl), sizeof(fcPlgosl));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlgosl), sizeof(lcbPlgosl));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcocx), sizeof(fcPlcocx));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcocx), sizeof(lcbPlcocx));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfBteLvc), sizeof(fcPlcfBteLvc));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBteLvc), sizeof(lcbPlcfBteLvc));
	mainstrm.read(reinterpret_cast<char *>(&dwLowDateTime), sizeof(dwLowDateTime));
	mainstrm.read(reinterpret_cast<char *>(&dwHighDateTime), sizeof(dwHighDateTime));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfLvcPre10), sizeof(fcPlcfLvcPre10));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfLvcPre10), sizeof(lcbPlcfLvcPre10));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfAsumy), sizeof(fcPlcfAsumy));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfAsumy), sizeof(lcbPlcfAsumy));
	mainstrm.read(reinterpret_cast<char *>(&fcPlcfGram), sizeof(fcPlcfGram));
	mainstrm.read(reinterpret_cast<char *>(&lcbPlcfGram), sizeof(lcbPlcfGram));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbListNames), sizeof(fcSttbListNames));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbListNames), sizeof(lcbSttbListNames));
	mainstrm.read(reinterpret_cast<char *>(&fcSttbfUssr), sizeof(fcSttbfUssr));
	mainstrm.read(reinterpret_cast<char *>(&lcbSttbfUssr), sizeof(lcbSttbfUssr));

	return;
}

VOID Fib::FibRgFcLcb::FibRgFcLcb2000::readFibRgFcLcb2000(std::ifstream & wrdfile)
{
	FibRgFcLcb97 varPortion97;
	varPortion97.readFibRgFcLcb97(wrdfile);

	wrdfile.read(reinterpret_cast<char *>(&fcPlcfTch), sizeof(fcPlcfTch));
	wrdfile.read(reinterpret_cast<char *>(&lcbPlcfTch), sizeof(lcbPlcfTch));
	wrdfile.read(reinterpret_cast<char *>(&fcRmdThreading), sizeof(fcRmdThreading));
	wrdfile.read(reinterpret_cast<char *>(&lcbRmdThreading), sizeof(lcbRmdThreading));
	wrdfile.read(reinterpret_cast<char *>(&fcMid), sizeof(fcMid));
	wrdfile.read(reinterpret_cast<char *>(&lcbMid), sizeof(lcbMid));
	wrdfile.read(reinterpret_cast<char *>(&fcSttbRgtplc), sizeof(fcSttbRgtplc));
	wrdfile.read(reinterpret_cast<char *>(&lcbSttbRgtplc), sizeof(lcbSttbRgtplc));
	wrdfile.read(reinterpret_cast<char *>(&fcMsoEnvelope), sizeof(fcMsoEnvelope));
	wrdfile.read(reinterpret_cast<char *>(&lcbMsoEnvelope), sizeof(lcbMsoEnvelope));
	wrdfile.read(reinterpret_cast<char *>(&fcPlcfLad), sizeof(fcPlcfLad));
	wrdfile.read(reinterpret_cast<char *>(&lcbPlcfLad), sizeof(lcbPlcfLad));
	wrdfile.read(reinterpret_cast<char *>(&fcRgDofr), sizeof(fcRgDofr));
	wrdfile.read(reinterpret_cast<char *>(&lcbRgDofr), sizeof(lcbRgDofr));
	wrdfile.read(reinterpret_cast<char *>(&fcPlcosl), sizeof(fcPlcosl));
	wrdfile.read(reinterpret_cast<char *>(&lcbPlcosl), sizeof(lcbPlcosl));
	wrdfile.read(reinterpret_cast<char *>(&fcPlcfCookieOld), sizeof(fcPlcfCookieOld));
	wrdfile.read(reinterpret_cast<char *>(&lcbPlcfCookieOld), sizeof(lcbPlcfCookieOld));
	wrdfile.read(reinterpret_cast<char *>(&fcPgdMotherOld), sizeof(fcPgdMotherOld));
	wrdfile.read(reinterpret_cast<char *>(&lcbPgdMotherOld), sizeof(lcbPgdMotherOld));
	wrdfile.read(reinterpret_cast<char *>(&fcBkdMotherOld), sizeof(fcBkdMotherOld));
	wrdfile.read(reinterpret_cast<char *>(&lcbBkdMotherOld), sizeof(lcbBkdMotherOld));
	wrdfile.read(reinterpret_cast<char *>(&fcPgdFtnOld), sizeof(fcPgdFtnOld));
	wrdfile.read(reinterpret_cast<char *>(&lcbPgdFtnOld), sizeof(lcbPgdFtnOld));
	wrdfile.read(reinterpret_cast<char *>(&fcBkdFtnOld), sizeof(fcBkdFtnOld));
	wrdfile.read(reinterpret_cast<char *>(&lcbBkdFtnOld), sizeof(lcbBkdFtnOld));
	wrdfile.read(reinterpret_cast<char *>(&fcPgdEdnOld), sizeof(fcPgdEdnOld));
	wrdfile.read(reinterpret_cast<char *>(&lcbPgdEdnOld), sizeof(lcbPgdEdnOld));
	wrdfile.read(reinterpret_cast<char *>(&fcBkdEdnOld), sizeof(fcBkdEdnOld));
	wrdfile.read(reinterpret_cast<char *>(&lcbBkdEdnOld), sizeof(lcbBkdEdnOld));

	return;
}

VOID Fib::FibRgFcLcb::FibRgFcLcb2002::readFibRgFcLcb2002(std::ifstream &documentStr)
{
	FibRgFcLcb2000 varPortion2000;
	varPortion2000.readFibRgFcLcb2000(documentStr);

	documentStr.read(reinterpret_cast<char *>(&fcUnused1), sizeof(fcUnused1));
	documentStr.read(reinterpret_cast<char *>(&lcbUnused1), sizeof(lcbUnused1));
	documentStr.read(reinterpret_cast<char *>(&fcPlcfPgp), sizeof(fcPlcfPgp));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcfPgp), sizeof(lcbPlcfPgp));
	documentStr.read(reinterpret_cast<char *>(&fcPlcfuim), sizeof(fcPlcfuim));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcfuim), sizeof(lcbPlcfuim));
	documentStr.read(reinterpret_cast<char *>(&fcPlfguidUim), sizeof(fcPlfguidUim));
	documentStr.read(reinterpret_cast<char *>(&lcbPlfguidUim), sizeof(lcbPlfguidUim));
	documentStr.read(reinterpret_cast<char *>(&fcAtrdExtra), sizeof(fcAtrdExtra));
	documentStr.read(reinterpret_cast<char *>(&lcbAtrdExtra), sizeof(lcbAtrdExtra));
	documentStr.read(reinterpret_cast<char *>(&fcPlrsid), sizeof(fcPlrsid));
	documentStr.read(reinterpret_cast<char *>(&lcbPlrsid), sizeof(lcbPlrsid));
	documentStr.read(reinterpret_cast<char *>(&fcSttbfBkmkFactoid), sizeof(fcSttbfBkmkFactoid));
	documentStr.read(reinterpret_cast<char *>(&lcbSttbfBkmkFactoid), sizeof(lcbSttbfBkmkFactoid));
	documentStr.read(reinterpret_cast<char *>(&fcPlcfBkfFactoid), sizeof(fcPlcfBkfFactoid));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcfBkfFactoid), sizeof(lcbPlcfBkfFactoid));
	documentStr.read(reinterpret_cast<char *>(&fcPlcfcookie), sizeof(fcPlcfcookie));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcfcookie), sizeof(lcbPlcfcookie));
	documentStr.read(reinterpret_cast<char *>(&fcPlcfBklFactoid), sizeof(fcPlcfBklFactoid));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcfBklFactoid), sizeof(lcbPlcfBklFactoid));
	documentStr.read(reinterpret_cast<char *>(&fcFactoidData), sizeof(fcFactoidData));
	documentStr.read(reinterpret_cast<char *>(&lcbFactoidData), sizeof(lcbFactoidData));
	documentStr.read(reinterpret_cast<char *>(&fcDocUndo), sizeof(fcDocUndo));
	documentStr.read(reinterpret_cast<char *>(&lcbDocUndo), sizeof(lcbDocUndo));
	documentStr.read(reinterpret_cast<char *>(&fcSttbfBkmkFcc), sizeof(fcSttbfBkmkFcc));
	documentStr.read(reinterpret_cast<char *>(&lcbSttbfBkmkFcc), sizeof(lcbSttbfBkmkFcc));
	documentStr.read(reinterpret_cast<char *>(&fcPlcfBkfFcc), sizeof(fcPlcfBkfFcc));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcfBkfFcc), sizeof(lcbPlcfBkfFcc));
	documentStr.read(reinterpret_cast<char *>(&fcPlcfBklFcc), sizeof(fcPlcfBklFcc));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcfBklFcc), sizeof(lcbPlcfBklFcc));
	documentStr.read(reinterpret_cast<char *>(&fcSttbfbkmkBPRepairs), sizeof(fcSttbfbkmkBPRepairs));
	documentStr.read(reinterpret_cast<char *>(&lcbSttbfbkmkBPRepairs), sizeof(lcbSttbfbkmkBPRepairs));
	documentStr.read(reinterpret_cast<char *>(&fcPlcfbkfBPRepairs), sizeof(fcPlcfbkfBPRepairs));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcfbkfBPRepairs), sizeof(lcbPlcfbkfBPRepairs));
	documentStr.read(reinterpret_cast<char *>(&fcPlcfbklBPRepairs), sizeof(fcPlcfbklBPRepairs));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcfbklBPRepairs), sizeof(lcbPlcfbklBPRepairs));
	documentStr.read(reinterpret_cast<char *>(&fcPmsNew), sizeof(fcPmsNew));
	documentStr.read(reinterpret_cast<char *>(&lcbPmsNew), sizeof(lcbPmsNew));
	documentStr.read(reinterpret_cast<char *>(&fcODSO), sizeof(fcODSO));
	documentStr.read(reinterpret_cast<char *>(&lcbODSO), sizeof(lcbODSO));
	documentStr.read(reinterpret_cast<char *>(&fcPlcfpmiOldXP), sizeof(fcPlcfpmiOldXP));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcfpmiOldXP), sizeof(lcbPlcfpmiOldXP));
	documentStr.read(reinterpret_cast<char *>(&fcPlcfpmiNewXP), sizeof(fcPlcfpmiNewXP));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcfpmiNewXP), sizeof(lcbPlcfpmiNewXP));
	documentStr.read(reinterpret_cast<char *>(&fcPlcfpmiMixedXP), sizeof(fcPlcfpmiMixedXP));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcfpmiMixedXP), sizeof(lcbPlcfpmiMixedXP));
	documentStr.read(reinterpret_cast<char *>(&fcUnused2), sizeof(fcUnused2));
	documentStr.read(reinterpret_cast<char *>(&lcbUnused2), sizeof(lcbUnused2));
	documentStr.read(reinterpret_cast<char *>(&fcPlcffactoid), sizeof(fcPlcffactoid));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcffactoid), sizeof(lcbPlcffactoid));
	documentStr.read(reinterpret_cast<char *>(&fcPlcflvcOldXP), sizeof(fcPlcflvcOldXP));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcflvcOldXP), sizeof(lcbPlcflvcOldXP));
	documentStr.read(reinterpret_cast<char *>(&fcPlcflvcNewXP), sizeof(fcPlcflvcNewXP));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcflvcNewXP), sizeof(lcbPlcflvcNewXP));
	documentStr.read(reinterpret_cast<char *>(&fcPlcflvcMixedXP), sizeof(fcPlcflvcMixedXP));
	documentStr.read(reinterpret_cast<char *>(&lcbPlcflvcMixedXP), sizeof(lcbPlcflvcMixedXP));

	return;
}

VOID Fib::FibRgFcLcb::FibRgFcLcb2003::readFibRgFcLcb2003(std::ifstream & dotdocstrm)
{
	FibRgFcLcb2002 varPortion2002;
	varPortion2002.readFibRgFcLcb2002(dotdocstrm);

	dotdocstrm.read(reinterpret_cast<char *>(&fcHplxsdr), sizeof(fcHplxsdr));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbHplxsdr), sizeof(lcbHplxsdr));
	dotdocstrm.read(reinterpret_cast<char *>(&fcSttbfBkmkSdt), sizeof(fcSttbfBkmkSdt));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbSttbfBkmkSdt), sizeof(lcbSttbfBkmkSdt));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfBkfSdt), sizeof(fcPlcfBkfSdt));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfBkfSdt), sizeof(lcbPlcfBkfSdt));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfBklSdt), sizeof(fcPlcfBklSdt));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfBklSdt), sizeof(lcbPlcfBklSdt));
	dotdocstrm.read(reinterpret_cast<char *>(&fcCustomXForm), sizeof(fcCustomXForm));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbCustomXForm), sizeof(lcbCustomXForm));
	dotdocstrm.read(reinterpret_cast<char *>(&fcSttbfBkmkProt), sizeof(fcSttbfBkmkProt));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbSttbfBkmkProt), sizeof(lcbSttbfBkmkProt));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfBkfProt), sizeof(fcPlcfBkfProt));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfBkfProt), sizeof(lcbPlcfBkfProt));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfBklProt), sizeof(fcPlcfBklProt));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfBklProt), sizeof(lcbPlcfBklProt));
	dotdocstrm.read(reinterpret_cast<char *>(&fcSttbProtUser), sizeof(fcSttbProtUser));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbSttbProtUser), sizeof(lcbSttbProtUser));
	dotdocstrm.read(reinterpret_cast<char *>(&fcUnused), sizeof(fcUnused));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbUnused), sizeof(lcbUnused));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfpmiOld), sizeof(fcPlcfpmiOld));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfpmiOld), sizeof(lcbPlcfpmiOld));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfpmiOldInline), sizeof(fcPlcfpmiOldInline));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfpmiOldInline), sizeof(lcbPlcfpmiOldInline));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfpmiNew), sizeof(fcPlcfpmiNew));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfpmiNew), sizeof(lcbPlcfpmiNew));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfpmiNewInline), sizeof(fcPlcfpmiNewInline));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfpmiNewInline), sizeof(lcbPlcfpmiNewInline));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPlcflvcOld), sizeof(fcPlcflvcOld));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcflvcOld), sizeof(lcbPlcflvcOld));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPlcflvcOldInline), sizeof(fcPlcflvcOldInline));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcflvcOldInline), sizeof(lcbPlcflvcOldInline));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPlcflvcNew), sizeof(fcPlcflvcNew));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcflvcNew), sizeof(lcbPlcflvcNew));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPlcflvcNewInline), sizeof(fcPlcflvcNewInline));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcflvcNewInline), sizeof(lcbPlcflvcNewInline));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPgdMother), sizeof(fcPgdMother));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPgdMother), sizeof(lcbPgdMother));
	dotdocstrm.read(reinterpret_cast<char *>(&fcBkdMother), sizeof(fcBkdMother));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbBkdMother), sizeof(lcbBkdMother));
	dotdocstrm.read(reinterpret_cast<char *>(&fcAfdMother), sizeof(fcAfdMother));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbAfdMother), sizeof(lcbAfdMother));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPgdFtn), sizeof(fcPgdFtn));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPgdFtn), sizeof(lcbPgdFtn));
	dotdocstrm.read(reinterpret_cast<char *>(&fcBkdFtn), sizeof(fcBkdFtn));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbBkdFtn), sizeof(lcbBkdFtn));
	dotdocstrm.read(reinterpret_cast<char *>(&fcAfdFtn), sizeof(fcAfdFtn));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbAfdFtn), sizeof(lcbAfdFtn));
	dotdocstrm.read(reinterpret_cast<char *>(&fcPgdEdn), sizeof(fcPgdEdn));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbPgdEdn), sizeof(lcbPgdEdn));
	dotdocstrm.read(reinterpret_cast<char *>(&fcBkdEdn), sizeof(fcBkdEdn));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbBkdEdn), sizeof(lcbBkdEdn));
	dotdocstrm.read(reinterpret_cast<char *>(&fcAfdEdn), sizeof(fcAfdEdn));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbAfdEdn), sizeof(lcbAfdEdn));
	dotdocstrm.read(reinterpret_cast<char *>(&fcAfd), sizeof(fcAfd));
	dotdocstrm.read(reinterpret_cast<char *>(&lcbAfd), sizeof(lcbAfd));

	return;
}

VOID Fib::FibRgFcLcb::FibRgFcLcb2007::readFibRgFcLcb2007(std::ifstream & dStream)
{
	FibRgFcLcb2003 varPortion2003;
	varPortion2003.readFibRgFcLcb2003(dStream);

	dStream.read(reinterpret_cast<char *>(&fcPlcfmthd), sizeof(fcPlcfmthd));
	dStream.read(reinterpret_cast<char *>(&lcbPlcfmthd), sizeof(lcbPlcfmthd));
	dStream.read(reinterpret_cast<char *>(&fcSttbfBkmkMoveFrom), sizeof(fcSttbfBkmkMoveFrom));
	dStream.read(reinterpret_cast<char *>(&lcbSttbfBkmkMoveFrom), sizeof(lcbSttbfBkmkMoveFrom));
	dStream.read(reinterpret_cast<char *>(&fcPlcfBkfMoveFrom), sizeof(fcPlcfBkfMoveFrom));
	dStream.read(reinterpret_cast<char *>(&lcbPlcfBkfMoveFrom), sizeof(lcbPlcfBkfMoveFrom));
	dStream.read(reinterpret_cast<char *>(&fcPlcfBklMoveFrom), sizeof(fcPlcfBklMoveFrom));
	dStream.read(reinterpret_cast<char *>(&lcbPlcfBklMoveFrom), sizeof(lcbPlcfBklMoveFrom));
	dStream.read(reinterpret_cast<char *>(&fcSttbfBkmkMoveTo), sizeof(fcSttbfBkmkMoveTo));
	dStream.read(reinterpret_cast<char *>(&lcbSttbfBkmkMoveTo), sizeof(lcbSttbfBkmkMoveTo));
	dStream.read(reinterpret_cast<char *>(&fcPlcfBkfMoveTo), sizeof(fcPlcfBkfMoveTo));
	dStream.read(reinterpret_cast<char *>(&lcbPlcfBkfMoveTo), sizeof(lcbPlcfBkfMoveTo));
	dStream.read(reinterpret_cast<char *>(&fcPlcfBklMoveTo), sizeof(fcPlcfBklMoveTo));
	dStream.read(reinterpret_cast<char *>(&lcbPlcfBklMoveTo), sizeof(lcbPlcfBklMoveTo));
	dStream.read(reinterpret_cast<char *>(&fcUnused1), sizeof(fcUnused1));
	dStream.read(reinterpret_cast<char *>(&lcbUnused1), sizeof(lcbUnused1));
	dStream.read(reinterpret_cast<char *>(&fcUnused2), sizeof(fcUnused2));
	dStream.read(reinterpret_cast<char *>(&lcbUnused2), sizeof(lcbUnused2));
	dStream.read(reinterpret_cast<char *>(&fcUnused3), sizeof(fcUnused3));
	dStream.read(reinterpret_cast<char *>(&lcbUnused3), sizeof(lcbUnused3));
	dStream.read(reinterpret_cast<char *>(&fcSttbfBkmkArto), sizeof(fcSttbfBkmkArto));
	dStream.read(reinterpret_cast<char *>(&lcbSttbfBkmkArto), sizeof(lcbSttbfBkmkArto));
	dStream.read(reinterpret_cast<char *>(&fcPlcfBkfArto), sizeof(fcPlcfBkfArto));
	dStream.read(reinterpret_cast<char *>(&lcbPlcfBkfArto), sizeof(lcbPlcfBkfArto));
	dStream.read(reinterpret_cast<char *>(&fcPlcfBklArto), sizeof(fcPlcfBklArto));
	dStream.read(reinterpret_cast<char *>(&lcbPlcfBklArto), sizeof(lcbPlcfBklArto));
	dStream.read(reinterpret_cast<char *>(&fcArtoData), sizeof(fcArtoData));
	dStream.read(reinterpret_cast<char *>(&lcbArtoData), sizeof(lcbArtoData));
	dStream.read(reinterpret_cast<char *>(&fcUnused4), sizeof(fcUnused4));
	dStream.read(reinterpret_cast<char *>(&lcbUnused4), sizeof(lcbUnused4));
	dStream.read(reinterpret_cast<char *>(&fcUnused5), sizeof(fcUnused5));
	dStream.read(reinterpret_cast<char *>(&lcbUnused5), sizeof(lcbUnused5));
	dStream.read(reinterpret_cast<char *>(&fcUnused6), sizeof(fcUnused6));
	dStream.read(reinterpret_cast<char *>(&lcbUnused6), sizeof(lcbUnused6));
	dStream.read(reinterpret_cast<char *>(&fcOssTheme), sizeof(fcOssTheme));
	dStream.read(reinterpret_cast<char *>(&lcbOssTheme), sizeof(lcbOssTheme));
	dStream.read(reinterpret_cast<char *>(&fcColorSchemeMapping), sizeof(fcColorSchemeMapping));
	dStream.read(reinterpret_cast<char *>(&lcbColorSchemeMapping), sizeof(lcbColorSchemeMapping));

	return;
}

VOID Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::readFibRgCswNewData2000(std::ifstream & instream)
{
	instream.read(reinterpret_cast<char *>(&cQuickSavesNew), sizeof(cQuickSavesNew));

	return;
}

VOID Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2007::readFibRgCswNewData2007(std::ifstream & streamin)
{
	FibRgCswNewData2000 newdat2000;
	newdat2000.readFibRgCswNewData2000(streamin);

	streamin.read(reinterpret_cast<char *>(&lidThemeOther), sizeof(lidThemeOther));
	streamin.read(reinterpret_cast<char *>(&lidThemeFE), sizeof(lidThemeFE));
	streamin.read(reinterpret_cast<char *>(&lidThemeCS), sizeof(lidThemeCS));

	return;
}


VOID Fib::FibRgLw97::process_fibRgLw()
{
	assert(ccpText >= 0);
	assert(ccpFtn >= 0);
	assert(ccpHdd >= 0);
	assert(reserved3 == 0);
	assert(ccpAtn >= 0);
	assert(ccpEdn >= 0);
	assert(ccpTxbx >= 0);
	assert(ccpHdrTxbx >= 0);
	// assert(reserved6 <= Fib::FibRgFcLcb::FibRgFcLcb97::fcPlcfBteChpx &&
	// reserved6 <= Fib::FibRgFcLcb::FibRgFcLcb97::lcbPlcfBteChpx)
	// assert(reserved9 .....
	assert(reserved13 == 0);
	assert(reserved14 == 0);

	return;
}

VOID Fib::FibRgFcLcb::FibRgFcLcb97::process_FibRgFcLcb97()
{
	assert(lcbStshf != 0);
	
	/*if (Fib::FibRgLw97::ccpFtn == 0)
		assert(lcbPlcffndTxt == 0);
	else if (Fib::FibRgLw97::ccpFtn != 0)
		assert(lcbPlcffndTxt != 0);

	if (Fib::FibRgLw97::ccpAtn == 0)
		assert(lcbPlcfandTxt == 0);
	else if (Fib::FibRgLw97::ccpAtn != 0)
		assert(lcbPlcfandTxt != 0);
	
	if (Fib::FibRgLw97::ccpHdd <= 0)
		assert(lcbPlcfHdd == 0);
	*/
	assert(fcPlcfBteChpx > 0);

	assert(lcbPlcfBteChpx > 0);

	assert(fcPlcfBtePapx > 0);

	assert(lcbPlcfBtePapx > 0);

	assert(lcbPlcfSea == 0);

	assert(lcbPlcfFldMcr == 0);

	// fcSttbfBkmk: review this member's details					
	
	// fcPlcfBkf: review this member's details

	// fcPlcfBkl: review this member's details

	assert(lcbDop != 0);
	
	assert(lcbSttbfAssoc != 0);
	
	assert(lcbClx > 0);
	
	// fcGrpXstAtnOwners: review documentation
	// fcSttbfAtnBkmk: review documentation

	assert(lcbUnused2 == 0);
	
	assert(lcbUnused3 == 0);

	// fcPlcSpaMom: review pls
	
	// fcPlcSpaHdr: review pls

	
	// fcPlcfAtnBkf: review
	// fcPlcfAtnBkl: review docs

	
	assert(lcbFormFldSttbs == 0);

	//if (Fib::FibRgLw97::ccpEdn == 0)
	//	assert(lcbPlcfendTxt == 0);
	//else if (Fib::FibRgLw97::ccpEdn != 0)
	//	assert(lcbPlcfendTxt != 0);
	//
	// fcPlcfFldEdn
	
	assert(lcbUnused4 == 0);

	//if (Fib::FibRgLw97::ccpTxbx == 0)
	//	assert(lcbPlcftxbxTxt == 0);
	//else if (Fib::FibRgLw97::ccpTxbx != 0)
	//	assert(lcbPlcftxbxTxt != 0);

	//if (Fib::FibRgLw97::ccpHdrTxbx == 0)
	//	assert(lcbPlcfHdrtxbxTxt == 0);
	//else if (Fib::FibRgLw97::ccpHdrTxbx != 0)
	//	assert(lcbPlcfHdrtxbxTxt != 0);

	//
	//if (Fib::FibRgLw97::ccpTxbx == 0)
	//	assert(lcbPlcfTxbxBkd == 0);
	//else if (Fib::FibRgLw97::ccpTxbx != 0)
	//	assert(lcbPlcfTxbxBkd != 0);

	//if (Fib::FibRgLw97::ccpHdrTxbx == 0)
	//	assert(lcbPlcfTxbxHdrBkd == 0);
	//else if (Fib::FibRgLw97::ccpHdrTxbx != 0)
	//	assert(lcbPlcfTxbxHdrBkd != 0);

	return;
}
VOID Fib::FibBase::process_fibBase()
{
	assert(wIdent == 0xA5EC);

	if (nFib == 0x00C0 || nFib == 0x00C2)
		nFib = 0x00C1;
	assert(nFib == 0x00C1);

	if (fGlsy == 1 || fDot == 0)
		assert(pnNext == 0);

	if (nFib >= 0x00D9)
		assert(cQuickSaves == 0xF);

	assert(fExtChar == 1);

	assert(nFibBack == 0x00BF || nFibBack == 0x00C1);

	if ((fEncrypted == 1 && fObfuscated == 1) ||
		(fEncrypted == 1 && fObfuscated == 0))
		assert(lkey == 0);

	assert(envr == 0);

	assert(reserved3 == 0);

	assert(reserved4 == 0);

	return;
}


// Assigns values from stream to bit fields
inline BYTE Fib::assignBits(BYTE flag, BYTE temp, int shftRt)
{
	temp &= flag;
	return temp >> shftRt;
}


// Checks which nFib to use for version confirmation
inline USHORT Fib::determine_nFib_use() const
{
	if (cswNew == 0)
	{
		return base.nFib;
	}
	else
	{
		return fibRgCswNew.nFibNew;
	}
}

// Ignores fields that are not to be read and moves downstream by a given number
inline VOID Fib::skip_fields(std::ifstream & docustrm, ULONG numSkipped) const
{
	docustrm.seekg(numSkipped, std::ios::cur);
	return;
}

inline VOID Fib::adjust_file_pointer(std::ifstream& strm, USHORT gvnSize, USHORT standard) const
{
	if (gvnSize < standard)
	{
		const int diff = standard - gvnSize;
		strm.seekg(diff, std::ios::cur);
	}
	return;
}
