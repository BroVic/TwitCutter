#include "FIB.h"
#include <fstream>
#include <iostream>
#include <cassert>

// nFib values
#define FOR_WORD_97 0x00C1
#define FOR_WORD_2000 0x00D9
#define FOR_WORD_2002 0x0101
#define FOR_WORD_2003 0x010C
#define FOR_WORD_2007 0x0112

// Default constructors/decostructors
Fib::Fib()
{
	csw = _SET_BYTES;
	cslw = _SET_BYTES;
	cbRgFcLcb = _SET_BYTES;
	cswNew = _SET_BYTES;
}

Fib::~Fib()
{
}

Fib::FibBase::FibBase()
{
	wIdent = _SET_BYTES;
	nFib = _SET_BYTES;
	unused = _SET_BYTES;
	lid = _SET_BYTES;
	pnNext = _SET_BYTES;
	fDot = _SET_BITS_1;
	fGlsy = _SET_BITS_1;
	fComplex = _SET_BITS_1;
	fHasPic = _SET_BITS_1;
	cQuickSaves = _SET_BITS_4;
	fEncrypted = _SET_BITS_1;
	fWhichTblStm = _SET_BITS_1;
	fReadOnlyRecommended = _SET_BITS_1;
	fWriteReservation = _SET_BITS_1;
	fExtChar = _SET_BITS_1;
	fLoadOverride = _SET_BITS_1;
	fFarEast = _SET_BITS_1;
	fObfuscated = _SET_BITS_1;
	nFibBack = _SET_BYTES;
	lkey = _SET_BYTES;
	envr = _SET_BYTES;
	flags2 = _SET_BYTES;
	// fMac = _SET_BITS_1;
	// fEmptySpecial = _SET_BITS_1;
	// fLoadOverridePage = _SET_BITS_1;
	// reserved1 = _SET_BITS_1;
	// reserved2 = _SET_BITS_1;
	// fSpare0 = _SET_BITS_3;
	reserved3 = _SET_BYTES;
	reserved4 = _SET_BYTES;
	reserved5 = _SET_BYTES;
	reserved6 = _SET_BYTES;
}

Fib::FibBase::~FibBase()
{
}

Fib::FibRgW97::FibRgW97()
{
	reserved1 = _SET_BYTES;
	reserved2 = _SET_BYTES;
	reserved3 = _SET_BYTES;
	reserved4 = _SET_BYTES;
	reserved5 = _SET_BYTES;
	reserved6 = _SET_BYTES;
	reserved7 = _SET_BYTES;
	reserved8 = _SET_BYTES;
	reserved9 = _SET_BYTES;
	reserved10 = _SET_BYTES;
	reserved11 = _SET_BYTES;
	reserved12 = _SET_BYTES;
	reserved13 = _SET_BYTES;
	lidFE = _SET_BYTES;
}

Fib::FibRgW97::~FibRgW97()
{
}

Fib::FibRgLw97::FibRgLw97()
{
	cbMac = _SET_BYTES;
	reserved1 = _SET_BYTES;
	reserved2 = _SET_BYTES;
	ccpText = _SET_BYTES;
	ccpFtn = _SET_BYTES;
	ccpHdd = _SET_BYTES;
	reserved3 = _SET_BYTES;
	ccpAtn = _SET_BYTES;
	ccpEdn = _SET_BYTES;
	ccpTxbx = _SET_BYTES;
	ccpHdrTxbx = _SET_BYTES;
	reserved4 = _SET_BYTES;
	reserved5 = _SET_BYTES;
	reserved6 = _SET_BYTES;
	reserved7 = _SET_BYTES;
	reserved8 = _SET_BYTES;
	reserved9 = _SET_BYTES;
	reserved10 = _SET_BYTES;
	reserved11 = _SET_BYTES;
	reserved12 = _SET_BYTES;
	reserved13 = _SET_BYTES;
	reserved14 = _SET_BYTES;
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
	fcStshfOrig = _SET_BYTES;
	lcbStshfOrig = _SET_BYTES;
	fcStshf = _SET_BYTES;
	lcbStshf = _SET_BYTES;
	fcPlcffndRef = _SET_BYTES;
	lcbPlcffndRef = _SET_BYTES;
	fcPlcffndTxt = _SET_BYTES;
	lcbPlcffndTxt = _SET_BYTES;
	fcPlcfandRef = _SET_BYTES;
	lcbPlcfandRef = _SET_BYTES;
	fcPlcfandTxt = _SET_BYTES;
	lcbPlcfandTxt = _SET_BYTES;
	fcPlcfSed = _SET_BYTES;
	lcbPlcfSed = _SET_BYTES;
	fcPlcPad = _SET_BYTES;
	lcbPlcPad = _SET_BYTES;
	fcPlcfPhe = _SET_BYTES;
	lcbPlcfPhe = _SET_BYTES;
	fcSttbfGlsy = _SET_BYTES;
	lcbSttbfGlsy = _SET_BYTES;
	fcPlcfGlsy = _SET_BYTES;
	lcbPlcfGlsy = _SET_BYTES;
	fcPlcfHdd = _SET_BYTES;
	lcbPlcfHdd = _SET_BYTES;
	fcPlcfBteChpx = _SET_BYTES;
	lcbPlcfBteChpx = _SET_BYTES;
	fcPlcfBtePapx = _SET_BYTES;
	lcbPlcfBtePapx = _SET_BYTES;
	fcPlcfSea = _SET_BYTES;
	lcbPlcfSea = _SET_BYTES;
	fcSttbfFfn = _SET_BYTES;
	lcbSttbfFfn = _SET_BYTES;
	fcPlcfFldMom = _SET_BYTES;
	lcbPlcfFldMom = _SET_BYTES;
	fcPlcfFldHdr = _SET_BYTES;
	lcbPlcfFldHdr = _SET_BYTES;
	fcPlcfFldFtn = _SET_BYTES;
	lcbPlcfFldFtn = _SET_BYTES;
	fcPlcfFldAtn = _SET_BYTES;
	lcbPlcfFldAtn = _SET_BYTES;
	fcPlcfFldMcr = _SET_BYTES;
	lcbPlcfFldMcr = _SET_BYTES;
	fcSttbfBkmk = _SET_BYTES;
	lcbSttbfBkmk = _SET_BYTES;
	fcPlcfBkf = _SET_BYTES;
	lcbPlcfBkf = _SET_BYTES;
	fcPlcfBkl = _SET_BYTES;
	lcbPlcfBkl = _SET_BYTES;
	fcCmds = _SET_BYTES;
	lcbCmds = _SET_BYTES;
	fcUnused1 = _SET_BYTES;
	lcbUnused1 = _SET_BYTES;
	fcSttbfMcr = _SET_BYTES;
	lcbSttbfMcr = _SET_BYTES;
	fcPrDrvr = _SET_BYTES;
	lcbPrDrvr = _SET_BYTES;
	fcPrEnvPort = _SET_BYTES;
	lcbPrEnvPort = _SET_BYTES;
	fcPrEnvLand = _SET_BYTES;
	lcbPrEnvLand = _SET_BYTES;
	fcWss = _SET_BYTES;
	lcbWss = _SET_BYTES;
	fcDop = _SET_BYTES;
	lcbDop = _SET_BYTES;
	fcSttbfAssoc = _SET_BYTES;
	lcbSttbfAssoc = _SET_BYTES;
	fcClx = _SET_BYTES;
	lcbClx = _SET_BYTES;
	fcPlcfPgdFtn = _SET_BYTES;
	lcbPlcfPgdFtn = _SET_BYTES;
	fcAutosaveSource = _SET_BYTES;
	lcbAutosaveSource = _SET_BYTES;
	fcGrpXstAtnOwners = _SET_BYTES;
	lcbGrpXstAtnOwners = _SET_BYTES;
	fcSttbfAtnBkmk = _SET_BYTES;
	lcbSttbfAtnBkmk = _SET_BYTES;
	fcUnused2 = _SET_BYTES;
	lcbUnused2 = _SET_BYTES;
	fcUnused3 = _SET_BYTES;
	lcbUnused3 = _SET_BYTES;
	fcPlcSpaMom = _SET_BYTES;
	lcbPlcSpaMom = _SET_BYTES;
	fcPlcSpaHdr = _SET_BYTES;
	lcbPlcSpaHdr = _SET_BYTES;
	fcPlcfAtnBkf = _SET_BYTES;
	lcbPlcfAtnBkf = _SET_BYTES;
	fcPlcfAtnBkl = _SET_BYTES;
	lcbPlcfAtnBkl = _SET_BYTES;
	fcPms = _SET_BYTES;
	lcbPms = _SET_BYTES;
	fcFormFldSttbs = _SET_BYTES;
	lcbFormFldSttbs = _SET_BYTES;
	fcPlcfendRef = _SET_BYTES;
	lcbPlcfendRef = _SET_BYTES;
	fcPlcfendTxt = _SET_BYTES;
	lcbPlcfendTxt = _SET_BYTES;
	fcPlcfFldEdn = _SET_BYTES;
	lcbPlcfFldEdn = _SET_BYTES;
	fcUnused4 = _SET_BYTES;
	lcbUnused4 = _SET_BYTES;
	fcDggInfo = _SET_BYTES;
	lcbDggInfo = _SET_BYTES;
	fcSttbfRMark = _SET_BYTES;
	lcbSttbfRMark = _SET_BYTES;
	fcSttbfCaption = _SET_BYTES;
	lcbSttbfCaption = _SET_BYTES;
	fcSttbfAutoCaption = _SET_BYTES;
	lcbSttbfAutoCaption = _SET_BYTES;
	fcPlcfWkb = _SET_BYTES;
	lcbPlcfWkb = _SET_BYTES;
	fcPlcfSpl = _SET_BYTES;
	lcbPlcfSpl = _SET_BYTES;
	fcPlcftxbxTxt = _SET_BYTES;
	lcbPlcftxbxTxt = _SET_BYTES;
	fcPlcfFldTxbx = _SET_BYTES;
	lcbPlcfFldTxbx = _SET_BYTES;
	fcPlcfHdrtxbxTxt = _SET_BYTES;
	lcbPlcfHdrtxbxTxt = _SET_BYTES;
	fcPlcffldHdrTxbx = _SET_BYTES;
	lcbPlcffldHdrTxbx = _SET_BYTES;
	fcStwUser = _SET_BYTES;
	lcbStwUser = _SET_BYTES;
	fcSttbTtmbd = _SET_BYTES;
	lcbSttbTtmbd = _SET_BYTES;
	fcCookieData = _SET_BYTES;
	lcbCookieData = _SET_BYTES;
	fcPgdMotherOldOld = _SET_BYTES;
	lcbPgdMotherOldOld = _SET_BYTES;
	fcBkdMotherOldOld = _SET_BYTES;
	lcbBkdMotherOldOld = _SET_BYTES;
	fcPgdFtnOldOld = _SET_BYTES;
	lcbPgdFtnOldOld = _SET_BYTES;
	fcBkdFtnOldOld = _SET_BYTES;
	lcbBkdFtnOldOld = _SET_BYTES;
	fcPgdEdnOldOld = _SET_BYTES;
	lcbPgdEdnOldOld = _SET_BYTES;
	fcBkdEdnOldOld = _SET_BYTES;
	lcbBkdEdnOldOld = _SET_BYTES;
	fcSttbfIntlFld = _SET_BYTES;
	lcbSttbfIntlFld = _SET_BYTES;
	fcRouteSlip = _SET_BYTES;
	lcbRouteSlip = _SET_BYTES;
	fcSttbSavedBy = _SET_BYTES;
	lcbSttbSavedBy = _SET_BYTES;
	fcSttbFnm = _SET_BYTES;
	lcbSttbFnm = _SET_BYTES;
	fcPlfLst = _SET_BYTES;
	lcbPlfLst = _SET_BYTES;
	fcPlfLfo = _SET_BYTES;
	lcbPlfLfo = _SET_BYTES;
	fcPlcfTxbxBkd = _SET_BYTES;
	lcbPlcfTxbxBkd = _SET_BYTES;
	fcPlcfTxbxHdrBkd = _SET_BYTES;
	lcbPlcfTxbxHdrBkd = _SET_BYTES;
	fcDocUndoWord9 = _SET_BYTES;
	lcbDocUndoWord9 = _SET_BYTES;
	fcRgbUse = _SET_BYTES;
	lcbRgbUse = _SET_BYTES;
	fcUsp = _SET_BYTES;
	lcbUsp = _SET_BYTES;
	fcUskf = _SET_BYTES;
	lcbUskf = _SET_BYTES;
	fcPlcupcRgbUse = _SET_BYTES;
	lcbPlcupcRgbUse = _SET_BYTES;
	fcPlcupcUsp = _SET_BYTES;
	lcbPlcupcUsp = _SET_BYTES;
	fcSttbGlsyStyle = _SET_BYTES;
	lcbSttbGlsyStyle = _SET_BYTES;
	fcPlgosl = _SET_BYTES;
	lcbPlgosl = _SET_BYTES;
	fcPlcocx = _SET_BYTES;
	lcbPlcocx = _SET_BYTES;
	fcPlcfBteLvc = _SET_BYTES;
	lcbPlcfBteLvc = _SET_BYTES;
	dwLowDateTime = _SET_BYTES;
	dwHighDateTime = _SET_BYTES;
	fcPlcfLvcPre10 = _SET_BYTES;
	lcbPlcfLvcPre10 = _SET_BYTES;
	fcPlcfAsumy = _SET_BYTES;
	lcbPlcfAsumy = _SET_BYTES;
	fcPlcfGram = _SET_BYTES;
	lcbPlcfGram = _SET_BYTES;
	fcSttbListNames = _SET_BYTES;
	lcbSttbListNames = _SET_BYTES;
	fcSttbfUssr = _SET_BYTES;
	lcbSttbfUssr = _SET_BYTES;
}

Fib::FibRgFcLcb::FibRgFcLcb97::~FibRgFcLcb97()
{
}

Fib::FibRgFcLcb::FibRgFcLcb2000::FibRgFcLcb2000()
{
	fcPlcfTch= _SET_BYTES;
	lcbPlcfTch= _SET_BYTES;
	fcRmdThreading= _SET_BYTES;
	lcbRmdThreading= _SET_BYTES;
	fcMid= _SET_BYTES;
	lcbMid= _SET_BYTES;
	fcSttbRgtplc= _SET_BYTES;
	lcbSttbRgtplc= _SET_BYTES;
	fcMsoEnvelope= _SET_BYTES;
	lcbMsoEnvelope= _SET_BYTES;
	fcPlcfLad= _SET_BYTES;
	lcbPlcfLad= _SET_BYTES;
	fcRgDofr= _SET_BYTES;
	lcbRgDofr= _SET_BYTES;
	fcPlcosl= _SET_BYTES;
	lcbPlcosl= _SET_BYTES;
	fcPlcfCookieOld= _SET_BYTES;
	lcbPlcfCookieOld= _SET_BYTES;
	fcPgdMotherOld= _SET_BYTES;
	lcbPgdMotherOld= _SET_BYTES;
	fcBkdMotherOld= _SET_BYTES;
	lcbBkdMotherOld= _SET_BYTES;
	fcPgdFtnOld= _SET_BYTES;
	lcbPgdFtnOld= _SET_BYTES;
	fcBkdFtnOld= _SET_BYTES;
	lcbBkdFtnOld= _SET_BYTES;
	fcPgdEdnOld= _SET_BYTES;
	lcbPgdEdnOld= _SET_BYTES;
	fcBkdEdnOld= _SET_BYTES;
	lcbBkdEdnOld= _SET_BYTES;

}

Fib::FibRgFcLcb::FibRgFcLcb2000::~FibRgFcLcb2000()
{
}

void Fib::FibRgFcLcb::FibRgFcLcb2000::readFibRgFcLcb2000(std::ifstream & wrdfile)
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

void Fib::FibRgFcLcb::FibRgFcLcb2000::process_FibRgFcLcb2000()
{
	assert(lcbRmdThreading != 0);
	return;
}

Fib::FibRgFcLcb::FibRgFcLcb2002::FibRgFcLcb2002()
{
	fcUnused1 = _SET_BYTES;
	lcbUnused1 = _SET_BYTES;
	fcPlcfPgp = _SET_BYTES;
	lcbPlcfPgp = _SET_BYTES;
	fcPlcfuim = _SET_BYTES;
	lcbPlcfuim = _SET_BYTES;
	fcPlfguidUim = _SET_BYTES;
	lcbPlfguidUim = _SET_BYTES;
	fcAtrdExtra = _SET_BYTES;
	lcbAtrdExtra = _SET_BYTES;
	fcPlrsid = _SET_BYTES;
	lcbPlrsid = _SET_BYTES;
	fcSttbfBkmkFactoid = _SET_BYTES;
	lcbSttbfBkmkFactoid = _SET_BYTES;
	fcPlcfBkfFactoid = _SET_BYTES;
	lcbPlcfBkfFactoid = _SET_BYTES;
	fcPlcfcookie = _SET_BYTES;
	lcbPlcfcookie = _SET_BYTES;
	fcPlcfBklFactoid = _SET_BYTES;
	lcbPlcfBklFactoid = _SET_BYTES;
	fcFactoidData = _SET_BYTES;
	lcbFactoidData = _SET_BYTES;
	fcDocUndo = _SET_BYTES;
	lcbDocUndo = _SET_BYTES;
	fcSttbfBkmkFcc = _SET_BYTES;
	lcbSttbfBkmkFcc = _SET_BYTES;
	fcPlcfBkfFcc = _SET_BYTES;
	lcbPlcfBkfFcc = _SET_BYTES;
	fcPlcfBklFcc = _SET_BYTES;
	lcbPlcfBklFcc = _SET_BYTES;
	fcSttbfbkmkBPRepairs = _SET_BYTES;
	lcbSttbfbkmkBPRepairs = _SET_BYTES;
	fcPlcfbkfBPRepairs = _SET_BYTES;
	lcbPlcfbkfBPRepairs = _SET_BYTES;
	fcPlcfbklBPRepairs = _SET_BYTES;
	lcbPlcfbklBPRepairs = _SET_BYTES;
	fcPmsNew = _SET_BYTES;
	lcbPmsNew = _SET_BYTES;
	fcODSO = _SET_BYTES;
	lcbODSO = _SET_BYTES;
	fcPlcfpmiOldXP = _SET_BYTES;
	lcbPlcfpmiOldXP = _SET_BYTES;
	fcPlcfpmiNewXP = _SET_BYTES;
	lcbPlcfpmiNewXP = _SET_BYTES;
	fcPlcfpmiMixedXP = _SET_BYTES;
	lcbPlcfpmiMixedXP = _SET_BYTES;
	fcUnused2 = _SET_BYTES;
	lcbUnused2 = _SET_BYTES;
	fcPlcffactoid = _SET_BYTES;
	lcbPlcffactoid = _SET_BYTES;
	fcPlcflvcOldXP = _SET_BYTES;
	lcbPlcflvcOldXP = _SET_BYTES;
	fcPlcflvcNewXP = _SET_BYTES;
	lcbPlcflvcNewXP = _SET_BYTES;
	fcPlcflvcMixedXP = _SET_BYTES;
	lcbPlcflvcMixedXP = _SET_BYTES;

}

Fib::FibRgFcLcb::FibRgFcLcb2002::~FibRgFcLcb2002()
{
}

void Fib::FibRgFcLcb::FibRgFcLcb2002::readFibRgFcLcb2002(std::ifstream &documentStr)
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

void Fib::FibRgFcLcb::FibRgFcLcb2002::process_FibRgFcLcb2002()
{
	assert(lcbUnused1 == 0);

	return;
}

Fib::FibRgFcLcb::FibRgFcLcb2003::FibRgFcLcb2003()
{
	fcHplxsdr = _SET_BYTES;
	lcbHplxsdr = _SET_BYTES;
	fcSttbfBkmkSdt = _SET_BYTES;
	lcbSttbfBkmkSdt = _SET_BYTES;
	fcPlcfBkfSdt = _SET_BYTES;
	lcbPlcfBkfSdt = _SET_BYTES;
	fcPlcfBklSdt = _SET_BYTES;
	lcbPlcfBklSdt = _SET_BYTES;
	fcCustomXForm = _SET_BYTES;
	lcbCustomXForm = _SET_BYTES;
	fcSttbfBkmkProt = _SET_BYTES;
	lcbSttbfBkmkProt = _SET_BYTES;
	fcPlcfBkfProt = _SET_BYTES;
	lcbPlcfBkfProt = _SET_BYTES;
	fcPlcfBklProt = _SET_BYTES;
	lcbPlcfBklProt = _SET_BYTES;
	fcSttbProtUser = _SET_BYTES;
	lcbSttbProtUser = _SET_BYTES;
	fcUnused = _SET_BYTES;
	lcbUnused = _SET_BYTES;
	fcPlcfpmiOld = _SET_BYTES;
	lcbPlcfpmiOld = _SET_BYTES;
	fcPlcfpmiOldInline = _SET_BYTES;
	lcbPlcfpmiOldInline = _SET_BYTES;
	fcPlcfpmiNew = _SET_BYTES;
	lcbPlcfpmiNew = _SET_BYTES;
	fcPlcfpmiNewInline = _SET_BYTES;
	lcbPlcfpmiNewInline = _SET_BYTES;
	fcPlcflvcOld = _SET_BYTES;
	lcbPlcflvcOld = _SET_BYTES;
	fcPlcflvcOldInline = _SET_BYTES;
	lcbPlcflvcOldInline = _SET_BYTES;
	fcPlcflvcNew = _SET_BYTES;
	lcbPlcflvcNew = _SET_BYTES;
	fcPlcflvcNewInline = _SET_BYTES;
	lcbPlcflvcNewInline = _SET_BYTES;
	fcPgdMother = _SET_BYTES;
	lcbPgdMother = _SET_BYTES;
	fcBkdMother = _SET_BYTES;
	lcbBkdMother = _SET_BYTES;
	fcAfdMother = _SET_BYTES;
	lcbAfdMother = _SET_BYTES;
	fcPgdFtn = _SET_BYTES;
	lcbPgdFtn = _SET_BYTES;
	fcBkdFtn = _SET_BYTES;
	lcbBkdFtn = _SET_BYTES;
	fcAfdFtn = _SET_BYTES;
	lcbAfdFtn = _SET_BYTES;
	fcPgdEdn = _SET_BYTES;
	lcbPgdEdn = _SET_BYTES;
	fcBkdEdn = _SET_BYTES;
	lcbBkdEdn = _SET_BYTES;
	fcAfdEdn = _SET_BYTES;
	lcbAfdEdn = _SET_BYTES;
	fcAfd = _SET_BYTES;
	lcbAfd = _SET_BYTES;

}

Fib::FibRgFcLcb::FibRgFcLcb2003::~FibRgFcLcb2003()
{
}

void Fib::FibRgFcLcb::FibRgFcLcb2003::readFibRgFcLcb2003(std::ifstream & dotdocstrm)
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

void Fib::FibRgFcLcb::FibRgFcLcb2003::process_FibRgFcLcb2003()
{
	assert(lcbCustomXForm <= 4168 && lcbCustomXForm % 2 == 0);
	assert(fcUnused == 0);
	assert(lcbUnused == 0);
	return;
}

Fib::FibRgFcLcb::FibRgFcLcb2007::FibRgFcLcb2007()
{
	fcPlcfmthd = _SET_BYTES;
	lcbPlcfmthd = _SET_BYTES;
	fcSttbfBkmkMoveFrom = _SET_BYTES;
	lcbSttbfBkmkMoveFrom = _SET_BYTES;
	fcPlcfBkfMoveFrom = _SET_BYTES;
	lcbPlcfBkfMoveFrom = _SET_BYTES;
	fcPlcfBklMoveFrom = _SET_BYTES;
	lcbPlcfBklMoveFrom = _SET_BYTES;
	fcSttbfBkmkMoveTo = _SET_BYTES;
	lcbSttbfBkmkMoveTo = _SET_BYTES;
	fcPlcfBkfMoveTo = _SET_BYTES;
	lcbPlcfBkfMoveTo = _SET_BYTES;
	fcPlcfBklMoveTo = _SET_BYTES;
	lcbPlcfBklMoveTo = _SET_BYTES;
	fcUnused1 = _SET_BYTES;
	lcbUnused1 = _SET_BYTES;
	fcUnused2 = _SET_BYTES;
	lcbUnused2 = _SET_BYTES;
	fcUnused3 = _SET_BYTES;
	lcbUnused3 = _SET_BYTES;
	fcSttbfBkmkArto = _SET_BYTES;
	lcbSttbfBkmkArto = _SET_BYTES;
	fcPlcfBkfArto = _SET_BYTES;
	lcbPlcfBkfArto = _SET_BYTES;
	fcPlcfBklArto = _SET_BYTES;
	lcbPlcfBklArto = _SET_BYTES;
	fcArtoData = _SET_BYTES;
	lcbArtoData = _SET_BYTES;
	fcUnused4 = _SET_BYTES;
	lcbUnused4 = _SET_BYTES;
	fcUnused5 = _SET_BYTES;
	lcbUnused5 = _SET_BYTES;
	fcUnused6 = _SET_BYTES;
	lcbUnused6 = _SET_BYTES;
	fcOssTheme = _SET_BYTES;
	lcbOssTheme = _SET_BYTES;
	fcColorSchemeMapping = _SET_BYTES;
	lcbColorSchemeMapping = _SET_BYTES;
}

Fib::FibRgFcLcb::FibRgFcLcb2007::~FibRgFcLcb2007()
{
}

void Fib::FibRgFcLcb::FibRgFcLcb2007::readFibRgFcLcb2007(std::ifstream & dStream)
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

void Fib::FibRgFcLcb::FibRgFcLcb2007::process_FibRgFcLcb2007()
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
	nFibNew = _SET_BYTES;
}

Fib::FibRgCswNew::~FibRgCswNew()
{
}

void Fib::FibRgCswNew::readFibRgCswNew(std::ifstream & ldedstrm)
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
	lidThemeOther = _SET_BYTES;
	lidThemeFE = _SET_BYTES;
	lidThemeCS = _SET_BYTES;
}

Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2007::~FibRgCswNewData2007()
{
}

void Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2007::readFibRgCswNewData2007(std::ifstream & streamin)
{
	FibRgCswNewData2000 newdat2000;
	newdat2000.readFibRgCswNewData2000(streamin);

	streamin.read(reinterpret_cast<char *>(&lidThemeOther), sizeof(lidThemeOther));
	streamin.read(reinterpret_cast<char *>(&lidThemeFE), sizeof(lidThemeFE));
	streamin.read(reinterpret_cast<char *>(&lidThemeCS), sizeof(lidThemeCS));

	return;
}

Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::FibRgCswNewData2000()
{
	cQuickSavesNew = _SET_BYTES;
}

Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::~FibRgCswNewData2000()
{
}

void Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::readFibRgCswNewData2000(std::ifstream & instream)
{
	instream.read(reinterpret_cast<char *>(&cQuickSavesNew), sizeof(cQuickSavesNew));

	return;
}

void Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::process_FibRgCswNewData2000()
{
	assert(cQuickSavesNew >= 0 && cQuickSavesNew <= 0x000F);
	return;
}

// Reads the File Information Block (FIB)
void Fib::readFib(std::ifstream &docstream)
{
	// TODO: Review these function calls later
	base.readFibBase(docstream);
	
	docstream.read(reinterpret_cast<char *>(&csw), sizeof(csw));
	fibRgW.readFibRgW(docstream); 

	docstream.read(reinterpret_cast<char *>(&cslw), sizeof(cslw));
	fibRgLw.readFibRgLw(docstream);

	docstream.read(reinterpret_cast<char *>(&cbRgFcLcb), sizeof(cbRgFcLcb));
	
	const unsigned int ver = determine_nFib_use();
	switch (ver)
	{
	case FOR_WORD_97:
		fibRgFcLcbBlob.fibRgFcLcb97.readFibRgFcLcb97(docstream);
		break;
	case FOR_WORD_2000:
		fibRgFcLcbBlob.fibRgFcLcb2000.readFibRgFcLcb2000(docstream);
		break;
	case FOR_WORD_2002:
		fibRgFcLcbBlob.fibRgFcLcb2002.readFibRgFcLcb2002(docstream);
		break;
	case FOR_WORD_2003:
		fibRgFcLcbBlob.fibRgFcLcb2003.readFibRgFcLcb2003(docstream);
		break;
	case FOR_WORD_2007:
		fibRgFcLcbBlob.fibRgFcLcb2007.readFibRgFcLcb2007(docstream);
		break;
	// default:
		// break;
	}
	
	docstream.read(reinterpret_cast<char *>(&cswNew), sizeof(cswNew));
	if (cswNew != 0)
		fibRgCswNew.readFibRgCswNew(docstream); 

	return;
}

// Reads FibBase ONLY from the stream into memory
void Fib::FibBase::readFibBase(std::ifstream &docfile)
{
	docfile.read(reinterpret_cast<char *>(&wIdent), sizeof(wIdent));
	docfile.read(reinterpret_cast<char *>(&nFib), sizeof(nFib));
	docfile.seekg(sizeof(unused), std::ios::cur);
	docfile.read(reinterpret_cast<char *>(&lid), sizeof(lid));
	docfile.read(reinterpret_cast<char *>(&pnNext), sizeof(pnNext));

	BYTE tmp = 0b0000'0000;			// temporary storage
	const BYTE msk = 0x0F;
	const BYTE fHP = 0x10;
	const BYTE fC = 0x20;
	const BYTE fG = 0x40;
	const BYTE fD = 0x80;
	const BYTE fO = 0x1;
	const BYTE fFE = 0x2;
	const BYTE fLO = 0x4;
	const BYTE fEC = 0x1;			// must be set to 1 and ignored
	const BYTE fWR = 0x10;
	const BYTE fROR = 0x20;
	const BYTE fWT = 0x40;
	const BYTE fE = 0x80;

	docfile.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
	cQuickSaves = tmp & msk;
	fHasPic = assignBits(fHP, 4);
	fComplex = assignBits(fC, 5);
	fGlsy = assignBits(fG, 6);
	fDot = assignBits(fD, 7);

	docfile.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
	fObfuscated = assignBits(fO, 0);
	fFarEast = assignBits(fFE, 1);
	fLoadOverride = assignBits(fLO, 2);
	fExtChar = fEC;
	fWriteReservation = assignBits(fWR, 4);
	fReadOnlyRecommended = assignBits(fROR, 5);
	fWhichTblStm = assignBits(fWT, 6);
	fEncrypted = assignBits(fE, 7);

	docfile.read(reinterpret_cast<char *>(&nFibBack), sizeof(nFibBack));
	docfile.read(reinterpret_cast<char *>(&lkey), sizeof(lkey));

	docfile.seekg(sizeof(envr), std::ios::cur);

	docfile.read(reinterpret_cast<char *>(&flags2), sizeof(flags2));
	docfile.read(reinterpret_cast<char *>(&reserved3), sizeof(reserved3));
	docfile.read(reinterpret_cast<char *>(&reserved4), sizeof(reserved4));
	docfile.read(reinterpret_cast<char *>(&reserved5), sizeof(reserved5));
	docfile.read(reinterpret_cast<char *>(&reserved6), sizeof(reserved6));
	
	return;
}

// Reads FibBase ONLY from the stream into memory
void Fib::FibRgLw97::readFibRgLw(std::ifstream & mystream)
{
	mystream.read(reinterpret_cast<char *>(&cbMac), sizeof(cbMac));
	mystream.read(reinterpret_cast<char *>(&reserved1), sizeof(reserved1));
	mystream.read(reinterpret_cast<char *>(&reserved2), sizeof(reserved2));
	mystream.read(reinterpret_cast<char *>(&ccpText), sizeof(ccpText));
	mystream.read(reinterpret_cast<char *>(&ccpFtn), sizeof(ccpFtn));
	mystream.read(reinterpret_cast<char *>(&ccpHdd), sizeof(ccpHdd));
	mystream.read(reinterpret_cast<char *>(&reserved3), sizeof(reserved3));
	mystream.read(reinterpret_cast<char *>(&ccpAtn), sizeof(ccpAtn));
	mystream.read(reinterpret_cast<char *>(&ccpEdn), sizeof(ccpEdn));
	mystream.read(reinterpret_cast<char *>(&ccpTxbx), sizeof(ccpTxbx));
	mystream.read(reinterpret_cast<char *>(&ccpHdrTxbx), sizeof(ccpHdrTxbx));
	mystream.read(reinterpret_cast<char *>(&reserved4), sizeof(reserved4));
	mystream.read(reinterpret_cast<char *>(&reserved5), sizeof(reserved5));
	mystream.read(reinterpret_cast<char *>(&reserved6), sizeof(reserved6));
	mystream.read(reinterpret_cast<char *>(&reserved7), sizeof(reserved7));
	mystream.read(reinterpret_cast<char *>(&reserved8), sizeof(reserved8));
	mystream.read(reinterpret_cast<char *>(&reserved9), sizeof(reserved9));
	mystream.read(reinterpret_cast<char *>(&reserved10), sizeof(reserved10));
	mystream.read(reinterpret_cast<char *>(&reserved11), sizeof(reserved11));
	mystream.read(reinterpret_cast<char *>(&reserved12), sizeof(reserved12));
	mystream.read(reinterpret_cast<char *>(&reserved13), sizeof(reserved13));
	mystream.read(reinterpret_cast<char *>(&reserved14), sizeof(reserved14));

	return;

}

void Fib::FibRgLw97::process_fibRgLw()
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

void Fib::FibRgW97::readFibRgW(std::ifstream & filestrm)
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

void Fib::FibRgFcLcb::FibRgFcLcb97::readFibRgFcLcb97(std::ifstream & mainstrm)
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
	mainstrm.read(reinterpret_cast<char *>(&fcDocUndoWord9), sizeof(fcDocUndoWord9));
	mainstrm.read(reinterpret_cast<char *>(&lcbDocUndoWord9), sizeof(lcbDocUndoWord9));
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

void Fib::FibRgFcLcb::FibRgFcLcb97::process_FibRgFcLcb97()
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


// Assigns values from stream to bit fields
inline BYTE Fib::FibBase::assignBits(BYTE flag, int shftLeft)
{
	BYTE temp = 0b0000'0000;
	temp &= flag;
	return temp >> shftLeft;
}

void Fib::FibBase::process_fibBase()
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

// Checks which nFib to use for version confirmation
inline WORD Fib::determine_nFib_use()
{
	if (cswNew == 0)
		return base.nFib;
	else { return fibRgCswNew.nFibNew; }
}
