#include "FIB.h"

dtdoc::Fib::Fib()
{
	csw = 0x00;
	cslw = 0x00;
	cbRgFcLcb = 0x00;
	cswNew = 0x00;
}

dtdoc::FibRgCswNew::FibRgCswNew()
{
	nFibNew = 0x00;
}

dtdoc::FibRgCswNewData::FibRgCswNewData2007::FibRgCswNewData2007()
{
	lidThemeOther = 0x00;
	lidThemeFE = 0x00;
	lidThemeCS = 0x00;
}

dtdoc::FibRgCswNewData::FibRgCswNewData2000::FibRgCswNewData2000()
{
	cQuickSavesNew = 0x00;
}

dtdoc::FibRgFcLcb::FibRgFcLcb2007::FibRgFcLcb2007()
{
	fcPlcfmthd = 0x00;
	lcbPlcfmthd = 0x00;
	fcSttbfBkmkMoveFrom = 0x00;
	lcbSttbfBkmkMoveFrom = 0x00;
	fcPlcfBkfMoveFrom = 0x00;
	lcbPlcfBkfMoveFrom = 0x00;
	fcPlcfBklMoveFrom = 0x00;
	lcbPlcfBklMoveFrom = 0x00;
	fcSttbfBkmkMoveTo = 0x00;
	lcbSttbfBkmkMoveTo = 0x00;
	fcPlcfBkfMoveTo = 0x00;
	lcbPlcfBkfMoveTo = 0x00;
	fcPlcfBklMoveTo = 0x00;
	lcbPlcfBklMoveTo = 0x00;
	fcUnused1 = 0x00;
	lcbUnused1 = 0x00;
	fcUnused2 = 0x00;
	lcbUnused2 = 0x00;
	fcUnused3 = 0x00;
	lcbUnused3 = 0x00;
	fcSttbfBkmkArto = 0x00;
	lcbSttbfBkmkArto = 0x00;
	fcPlcfBkfArto = 0x00;
	lcbPlcfBkfArto = 0x00;
	fcPlcfBklArto = 0x00;
	lcbPlcfBklArto = 0x00;
	fcArtoData = 0x00;
	lcbArtoData = 0x00;
	fcUnused4 = 0x00;
	lcbUnused4 = 0x00;
	fcUnused5 = 0x00;
	lcbUnused5 = 0x00;
	fcUnused6 = 0x00;
	lcbUnused6 = 0x00;
	fcOssTheme = 0x00;
	lcbOssTheme = 0x00;
	fcColorSchemeMapping = 0x00;
	lcbColorSchemeMapping = 0x00;
}

dtdoc::FibRgFcLcb::FibRgFcLcb2003::FibRgFcLcb2003()
{
	fcHplxsdr = 0x00;
	lcbHplxsdr = 0x00;
	fcSttbfBkmkSdt = 0x00;
	lcbSttbfBkmkSdt = 0x00;
	fcPlcfBkfSdt = 0x00;
	lcbPlcfBkfSdt = 0x00;
	fcPlcfBklSdt = 0x00;
	lcbPlcfBklSdt = 0x00;
	fcCustomXForm = 0x00;
	lcbCustomXForm = 0x00;
	fcSttbfBkmkProt = 0x00;
	lcbSttbfBkmkProt = 0x00;
	fcPlcfBkfProt = 0x00;
	lcbPlcfBkfProt = 0x00;
	fcPlcfBklProt = 0x00;
	lcbPlcfBklProt = 0x00;
	fcSttbProtUser = 0x00;
	lcbSttbProtUser = 0x00;
	fcUnused = 0x00;
	lcbUnused = 0x00;
	fcPlcfpmiOld = 0x00;
	lcbPlcfpmiOld = 0x00;
	fcPlcfpmiOldInline = 0x00;
	lcbPlcfpmiOldInline = 0x00;
	fcPlcfpmiNew = 0x00;
	lcbPlcfpmiNew = 0x00;
	fcPlcfpmiNewInline = 0x00;
	lcbPlcfpmiNewInline = 0x00;
	fcPlcflvcOld = 0x00;
	lcbPlcflvcOld = 0x00;
	fcPlcflvcOldInline = 0x00;
	lcbPlcflvcOldInline = 0x00;
	fcPlcflvcNew = 0x00;
	lcbPlcflvcNew = 0x00;
	fcPlcflvcNewInline = 0x00;
	lcbPlcflvcNewInline = 0x00;
	fcPgdMother = 0x00;
	lcbPgdMother = 0x00;
	fcBkdMother = 0x00;
	lcbBkdMother = 0x00;
	fcAfdMother = 0x00;
	lcbAfdMother = 0x00;
	fcPgdFtn = 0x00;
	lcbPgdFtn = 0x00;
	fcBkdFtn = 0x00;
	lcbBkdFtn = 0x00;
	fcAfdFtn = 0x00;
	lcbAfdFtn = 0x00;
	fcPgdEdn = 0x00;
	lcbPgdEdn = 0x00;
	fcBkdEdn = 0x00;
	lcbBkdEdn = 0x00;
	fcAfdEdn = 0x00;
	lcbAfdEdn = 0x00;
	fcAfd = 0x00;
	lcbAfd = 0x00;

}

dtdoc::FibRgFcLcb::FibRgFcLcb2002::FibRgFcLcb2002()
{
	fcUnused1 = 0x00;
	lcbUnused1 = 0x00;
	fcPlcfPgp = 0x00;
	lcbPlcfPgp = 0x00;
	fcPlcfuim = 0x00;
	lcbPlcfuim = 0x00;
	fcPlfguidUim = 0x00;
	lcbPlfguidUim = 0x00;
	fcAtrdExtra = 0x00;
	lcbAtrdExtra = 0x00;
	fcPlrsid = 0x00;
	lcbPlrsid = 0x00;
	fcSttbfBkmkFactoid = 0x00;
	lcbSttbfBkmkFactoid = 0x00;
	fcPlcfBkfFactoid = 0x00;
	lcbPlcfBkfFactoid = 0x00;
	fcPlcfcookie = 0x00;
	lcbPlcfcookie = 0x00;
	fcPlcfBklFactoid = 0x00;
	lcbPlcfBklFactoid = 0x00;
	fcFactoidData = 0x00;
	lcbFactoidData = 0x00;
	fcDocUndo = 0x00;
	lcbDocUndo = 0x00;
	fcSttbfBkmkFcc = 0x00;
	lcbSttbfBkmkFcc = 0x00;
	fcPlcfBkfFcc = 0x00;
	lcbPlcfBkfFcc = 0x00;
	fcPlcfBklFcc = 0x00;
	lcbPlcfBklFcc = 0x00;
	fcSttbfbkmkBPRepairs = 0x00;
	lcbSttbfbkmkBPRepairs = 0x00;
	fcPlcfbkfBPRepairs = 0x00;
	lcbPlcfbkfBPRepairs = 0x00;
	fcPlcfbklBPRepairs = 0x00;
	lcbPlcfbklBPRepairs = 0x00;
	fcPmsNew = 0x00;
	lcbPmsNew = 0x00;
	fcODSO = 0x00;
	lcbODSO = 0x00;
	fcPlcfpmiOldXP = 0x00;
	lcbPlcfpmiOldXP = 0x00;
	fcPlcfpmiNewXP = 0x00;
	lcbPlcfpmiNewXP = 0x00;
	fcPlcfpmiMixedXP = 0x00;
	lcbPlcfpmiMixedXP = 0x00;
	fcUnused2 = 0x00;
	lcbUnused2 = 0x00;
	fcPlcffactoid = 0x00;
	lcbPlcffactoid = 0x00;
	fcPlcflvcOldXP = 0x00;
	lcbPlcflvcOldXP = 0x00;
	fcPlcflvcNewXP = 0x00;
	lcbPlcflvcNewXP = 0x00;
	fcPlcflvcMixedXP = 0x00;
	lcbPlcflvcMixedXP = 0x00;

}

dtdoc::FibRgFcLcb::FibRgFcLcb2000::FibRgFcLcb2000()
{
	fcPlcfTch= 0x00;
	lcbPlcfTch= 0x00;
	fcRmdThreading= 0x00;
	lcbRmdThreading= 0x00;
	fcMid= 0x00;
	lcbMid= 0x00;
	fcSttbRgtplc= 0x00;
	lcbSttbRgtplc= 0x00;
	fcMsoEnvelope= 0x00;
	lcbMsoEnvelope= 0x00;
	fcPlcfLad= 0x00;
	lcbPlcfLad= 0x00;
	fcRgDofr= 0x00;
	lcbRgDofr= 0x00;
	fcPlcosl= 0x00;
	lcbPlcosl= 0x00;
	fcPlcfCookieOld= 0x00;
	lcbPlcfCookieOld= 0x00;
	fcPgdMotherOld= 0x00;
	lcbPgdMotherOld= 0x00;
	fcBkdMotherOld= 0x00;
	lcbBkdMotherOld= 0x00;
	fcPgdFtnOld= 0x00;
	lcbPgdFtnOld= 0x00;
	fcBkdFtnOld= 0x00;
	lcbBkdFtnOld= 0x00;
	fcPgdEdnOld= 0x00;
	lcbPgdEdnOld= 0x00;
	fcBkdEdnOld= 0x00;
	lcbBkdEdnOld= 0x00;

}

dtdoc::FibRgFcLcb::FibRgFcLcb97::FibRgFcLcb97()
{
	fcStshfOrig = 0x00;
	lcbStshfOrig = 0x00;
	fcStshf = 0x00;
	lcbStshf = 0x00;
	fcPlcffndRef = 0x00;
	lcbPlcffndRef = 0x00;
	fcPlcffndTxt = 0x00;
	lcbPlcffndTxt = 0x00;
	fcPlcfandRef = 0x00;
	lcbPlcfandRef = 0x00;
	fcPlcfandTxt = 0x00;
	lcbPlcfandTxt = 0x00;
	fcPlcfSed = 0x00;
	lcbPlcfSed = 0x00;
	fcPlcPad = 0x00;
	lcbPlcPad = 0x00;
	fcPlcfPhe = 0x00;
	lcbPlcfPhe = 0x00;
	fcSttbfGlsy = 0x00;
	lcbSttbfGlsy = 0x00;
	fcPlcfGlsy = 0x00;
	lcbPlcfGlsy = 0x00;
	fcPlcfHdd = 0x00;
	lcbPlcfHdd = 0x00;
	fcPlcfBteChpx = 0x00;
	lcbPlcfBteChpx = 0x00;
	fcPlcfBtePapx = 0x00;
	lcbPlcfBtePapx = 0x00;
	fcPlcfSea = 0x00;
	lcbPlcfSea = 0x00;
	fcSttbfFfn = 0x00;
	lcbSttbfFfn = 0x00;
	fcPlcfFldMom = 0x00;
	lcbPlcfFldMom = 0x00;
	fcPlcfFldHdr = 0x00;
	lcbPlcfFldHdr = 0x00;
	fcPlcfFldFtn = 0x00;
	lcbPlcfFldFtn = 0x00;
	fcPlcfFldAtn = 0x00;
	lcbPlcfFldAtn = 0x00;
	fcPlcfFldMcr = 0x00;
	lcbPlcfFldMcr = 0x00;
	fcSttbfBkmk = 0x00;
	lcbSttbfBkmk = 0x00;
	fcPlcfBkf = 0x00;
	lcbPlcfBkf = 0x00;
	fcPlcfBkl = 0x00;
	lcbPlcfBkl = 0x00;
	fcCmds = 0x00;
	lcbCmds = 0x00;
	fcUnused1 = 0x00;
	lcbUnused1 = 0x00;
	fcSttbfMcr = 0x00;
	lcbSttbfMcr = 0x00;
	fcPrDrvr = 0x00;
	lcbPrDrvr = 0x00;
	fcPrEnvPort = 0x00;
	lcbPrEnvPort = 0x00;
	fcPrEnvLand = 0x00;
	lcbPrEnvLand = 0x00;
	fcWss = 0x00;
	lcbWss = 0x00;
	fcDop = 0x00;
	lcbDop = 0x00;
	fcSttbfAssoc = 0x00;
	lcbSttbfAssoc = 0x00;
	fcClx = 0x00;
	lcbClx = 0x00;
	fcPlcfPgdFtn = 0x00;
	lcbPlcfPgdFtn = 0x00;
	fcAutosaveSource = 0x00;
	lcbAutosaveSource = 0x00;
	fcGrpXstAtnOwners = 0x00;
	lcbGrpXstAtnOwners = 0x00;
	fcSttbfAtnBkmk = 0x00;
	lcbSttbfAtnBkmk = 0x00;
	fcUnused2 = 0x00;
	lcbUnused2 = 0x00;
	fcUnused3 = 0x00;
	lcbUnused3 = 0x00;
	fcPlcSpaMom = 0x00;
	lcbPlcSpaMom = 0x00;
	fcPlcSpaHdr = 0x00;
	lcbPlcSpaHdr = 0x00;
	fcPlcfAtnBkf = 0x00;
	lcbPlcfAtnBkf = 0x00;
	fcPlcfAtnBkl = 0x00;
	lcbPlcfAtnBkl = 0x00;
	fcPms = 0x00;
	lcbPms = 0x00;
	fcFormFldSttbs = 0x00;
	lcbFormFldSttbs = 0x00;
	fcPlcfendRef = 0x00;
	lcbPlcfendRef = 0x00;
	fcPlcfendTxt = 0x00;
	lcbPlcfendTxt = 0x00;
	fcPlcfFldEdn = 0x00;
	lcbPlcfFldEdn = 0x00;
	fcUnused4 = 0x00;
	lcbUnused4 = 0x00;
	fcDggInfo = 0x00;
	lcbDggInfo = 0x00;
	fcSttbfRMark = 0x00;
	lcbSttbfRMark = 0x00;
	fcSttbfCaption = 0x00;
	lcbSttbfCaption = 0x00;
	fcSttbfAutoCaption = 0x00;
	lcbSttbfAutoCaption = 0x00;
	fcPlcfWkb = 0x00;
	lcbPlcfWkb = 0x00;
	fcPlcfSpl = 0x00;
	lcbPlcfSpl = 0x00;
	fcPlcftxbxTxt = 0x00;
	lcbPlcftxbxTxt = 0x00;
	fcPlcfFldTxbx = 0x00;
	lcbPlcfFldTxbx = 0x00;
	fcPlcfHdrtxbxTxt = 0x00;
	lcbPlcfHdrtxbxTxt = 0x00;
	fcPlcffldHdrTxbx = 0x00;
	lcbPlcffldHdrTxbx = 0x00;
	fcStwUser = 0x00;
	lcbStwUser = 0x00;
	fcSttbTtmbd = 0x00;
	lcbSttbTtmbd = 0x00;
	fcCookieData = 0x00;
	lcbCookieData = 0x00;
	fcPgdMotherOldOld = 0x00;
	lcbPgdMotherOldOld = 0x00;
	fcBkdMotherOldOld = 0x00;
	lcbBkdMotherOldOld = 0x00;
	fcPgdFtnOldOld = 0x00;
	lcbPgdFtnOldOld = 0x00;
	fcBkdFtnOldOld = 0x00;
	lcbBkdFtnOldOld = 0x00;
	fcPgdEdnOldOld = 0x00;
	lcbPgdEdnOldOld = 0x00;
	fcBkdEdnOldOld = 0x00;
	lcbBkdEdnOldOld = 0x00;
	fcSttbfIntlFld = 0x00;
	lcbSttbfIntlFld = 0x00;
	fcRouteSlip = 0x00;
	lcbRouteSlip = 0x00;
	fcSttbSavedBy = 0x00;
	lcbSttbSavedBy = 0x00;
	fcSttbFnm = 0x00;
	lcbSttbFnm = 0x00;
	fcPlfLst = 0x00;
	lcbPlfLst = 0x00;
	fcPlfLfo = 0x00;
	lcbPlfLfo = 0x00;
	fcPlcfTxbxBkd = 0x00;
	lcbPlcfTxbxBkd = 0x00;
	fcPlcfTxbxHdrBkd = 0x00;
	lcbPlcfTxbxHdrBkd = 0x00;
	fcDocUndoWord9 = 0x00;
	lcbDocUndoWord9 = 0x00;
	fcRgbUse = 0x00;
	lcbRgbUse = 0x00;
	fcUsp = 0x00;
	lcbUsp = 0x00;
	fcUskf = 0x00;
	lcbUskf = 0x00;
	fcPlcupcRgbUse = 0x00;
	lcbPlcupcRgbUse = 0x00;
	fcPlcupcUsp = 0x00;
	lcbPlcupcUsp = 0x00;
	fcSttbGlsyStyle = 0x00;
	lcbSttbGlsyStyle = 0x00;
	fcPlgosl = 0x00;
	lcbPlgosl = 0x00;
	fcPlcocx = 0x00;
	lcbPlcocx = 0x00;
	fcPlcfBteLvc = 0x00;
	lcbPlcfBteLvc = 0x00;
	dwLowDateTime = 0x00;
	dwHighDateTime = 0x00;
	fcPlcfLvcPre10 = 0x00;
	lcbPlcfLvcPre10 = 0x00;
	fcPlcfAsumy = 0x00;
	lcbPlcfAsumy = 0x00;
	fcPlcfGram = 0x00;
	lcbPlcfGram = 0x00;
	fcSttbListNames = 0x00;
	lcbSttbListNames = 0x00;
	fcSttbfUssr = 0x00;
	lcbSttbfUssr = 0x00;
}

dtdoc::FibRgLw97::FibRgLw97()
{
	cbMac = 0x00;
	reserved1 = 0x00;
	reserved2 = 0x00;
	ccpText = 0x00;
	ccpFtn = 0x00;
	ccpHdd = 0x00;
	reserved3 = 0x00;
	ccpAtn = 0x00;
	ccpEdn = 0x00;
	ccpTxbx = 0x00;
	ccpHdrTxbx = 0x00;
	reserved4 = 0x00;
	reserved5 = 0x00;
	reserved6 = 0x00;
	reserved7 = 0x00;
	reserved8 = 0x00;
	reserved9 = 0x00;
	reserved10 = 0x00;
	reserved11 = 0x00;
	reserved12 = 0x00;
	reserved13 = 0x00;
	reserved14 = 0x00;
}

dtdoc::FibBase::FibBase()
{
	wldent = 0x00;							// 0xA5EC
	nFib = 0x00;								// 0x00C1
	unused = 0x00;
	lid = 0x00;
	pnNext = 0x00;
	fDot = 0x00;
	fGlsy = 0x00;
	fComplex = 0x00;
	fHasPic = 0x00;
	cQuickSaves = 0x00;
	fEncrypted = 0x00;
	fWhichTblStm = 0x00;
	fReadOnlyRecommended = 0x00;
	fWriteReservation = 0x00;
	fExtChar = 0x00;
	fLoadOverride = 0x00;
	fFarEast = 0x00;
	fObfuscated = 0x00;
	nFibBack = 0x00;
	lkey = 0x00;
	envr = 0x00;
	fMac = 0x00;
	fEmptySpecial = 0x00;
	fLoadOverridePage = 0x00;
	reserved1 = 0x00;
	reserved2 = 0x00;
	fSpare0 = 0x00;
	reserved3 = 0x00;
	reserved4 = 0x00;
	reserved5 = 0x00;
	reserved6 = 0x00;
}

dtdoc::FibRgW97::FibRgW97()
{
	reserved1 = 0x00;
	reserved2 = 0x00;
	reserved3 = 0x00;
	reserved4 = 0x00;
	reserved5 = 0x00;
	reserved6 = 0x00;
	reserved7 = 0x00;
	reserved8 = 0x00;
	reserved9 = 0x00;
	reserved10 = 0x00;
	reserved11 = 0x00;
	reserved12 = 0x00;
	reserved13 = 0x00;
	lidFE = 0x00;
}
