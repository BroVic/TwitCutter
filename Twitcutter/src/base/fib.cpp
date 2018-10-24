// fib.cpp

// Implementation of Methods Declared in 'fib.h'

// PURPOSE:
// Principally, we're here to read the data from
// the File Information Block (FIB) of a MS .DOC
// file, which has already been opened as an
// instance of an std::ifstream object. The
// instantiation of the Fib struct, is outside the
// scope of this file.

///////////////////////////////////////////////
//             Mnemonic                      //
///////////////////////////////////////////////
// These are the FIRST-LEVEL variables/objects
// that we're dealing with here:
// 1. base
// 2. csw
// 3. fibRgW
// 4. cslw
// 5. fibRgLw
// 6. cbRgFcLcb
// 7. fibRgFcLcbBlob
// 8. cswNew
// 9. fibRgCswNew
////////////////////////////////////////////////

#include "fib.h"


constexpr unsigned short WORD_BINARY_FILE = 0xA5EC;

constexpr unsigned short NFIB_FOR_97   = 0x00C1;
constexpr unsigned short NFIB_FOR_2000 = 0x00D9;
constexpr unsigned short NFIB_FOR_2002 = 0x0101;
constexpr unsigned short NFIB_FOR_2003 = 0x010C;
constexpr unsigned short NFIB_FOR_2007 = 0x0112;
constexpr unsigned short NFIB_SPECIAL  = 0x00C0;
constexpr unsigned short NFIB_BIDI_BLD = 0x00C2;

constexpr unsigned short EXPECTED_CSW             = 0x000E;
constexpr unsigned short EXPECTED_CSLW            = 0x0016;

constexpr unsigned short EXPECTED_CBRGFCLCB_97    = 0x005D;
constexpr unsigned short EXPECTED_CBRGFCLCB_2000  = 0x006C;
constexpr unsigned short EXPECTED_CBRGFCLCB_2002  = 0x0088;
constexpr unsigned short EXPECTED_CBRGFCLCB_2003  = 0x00A4;
constexpr unsigned short EXPECTED_CBRGFCLCB_2007  = 0x00B7;

constexpr unsigned short EXPECTED_CSWNEW_97       = 0x0000;
constexpr unsigned short EXPECTED_CSWNEW_2000     = 0x0002;
constexpr unsigned short EXPECTED_CSWNEW_2002     = 0x0002;
constexpr unsigned short EXPECTED_CSWNEW_2003     = 0x0002;
constexpr unsigned short EXPECTED_CSWNEW_2007     = 0x0005;

constexpr unsigned short MULTIPLIER_FOR_CSW        = 16 / 8;
constexpr unsigned short MULTIPLIER_FOR_CSLW       = 32 / 8;
constexpr unsigned short MULTIPLIER_FOR_CBRGFCLCB  = 64 / 8;
constexpr unsigned short MULTIPLIER_FOR_CSWNEW     = 16 / 8;

// LID values (Language Code)
// as specified by ECMA 376 Part 4 section 2.18.52
constexpr unsigned short ARABIC_SAUDI_ARABIA             = 1025;
constexpr unsigned short BULGARIAN                       = 1026;
constexpr unsigned short CATALAN                         = 1027;
constexpr unsigned short CHINESE_TAIWAN                  = 1028;
constexpr unsigned short CZECH                           = 1029;
constexpr unsigned short DANISH                          = 1030;
constexpr unsigned short GERMAN_GERMANY                  = 1031;
constexpr unsigned short GREEK                           = 1032;
constexpr unsigned short ENGLISH_UNITED_STATES           = 1033;
constexpr unsigned short SPANISH_SPAIN_TRADITIONAL       = 1034;
constexpr unsigned short FINNISH                         = 1035;
constexpr unsigned short FRENCH_FRANCE                   = 1036;
constexpr unsigned short HEBREW                          = 1037;
constexpr unsigned short HUNGARIAN                       = 1038;
constexpr unsigned short ICELANDIC                       = 1039;
constexpr unsigned short ITALIAN_ITALY                   = 1040;
constexpr unsigned short JAPANESE                        = 1041;
constexpr unsigned short KOREAN                          = 1042;
constexpr unsigned short DUTCH_NETHERLANDS               = 1043;
constexpr unsigned short NORWEGIAN_BOKMAL                = 1044;
constexpr unsigned short POLISH                          = 1045;
constexpr unsigned short PORTUGUESE_BRAZIL               = 1046;
constexpr unsigned short RHAETO_ROMANIC                  = 1047;
constexpr unsigned short ROMANIAN                        = 1048;
constexpr unsigned short RUSSIAN                         = 1049;
constexpr unsigned short CROATIAN                        = 1050;
constexpr unsigned short SLOVAK                          = 1051;
constexpr unsigned short ALBANIAN_ALBANIA                = 1052;
constexpr unsigned short SWEDISH                         = 1053;
constexpr unsigned short THAI                            = 1054;
constexpr unsigned short TURKISH                         = 1055;
constexpr unsigned short URDU                            = 1056;
constexpr unsigned short INDONESIAN                      = 1057;
constexpr unsigned short UKRAINIAN                       = 1058;
constexpr unsigned short BELARUSIAN                      = 1059;
constexpr unsigned short SLOVENIAN                       = 1060;
constexpr unsigned short ESTONIAN                        = 1061;
constexpr unsigned short LATVIAN                         = 1062;
constexpr unsigned short LITHUANIAN                      = 1063;
constexpr unsigned short TAJIK                           = 1064;
constexpr unsigned short FARSI                           = 1065;
constexpr unsigned short VIETNAMESE                      = 1066;
constexpr unsigned short ARMENIAN_ARMENIA                = 1067;
constexpr unsigned short AZERI_LATIN                     = 1068;
constexpr unsigned short BASQUE                          = 1069;
constexpr unsigned short SORBIAN                         = 1070;
constexpr unsigned short FYRO_MACEDONIAN                 = 1071;
constexpr unsigned short SUTU                            = 1072;
constexpr unsigned short TSONGA                          = 1073;
constexpr unsigned short TSWANA                          = 1074;
constexpr unsigned short VENDA                           = 1075;
constexpr unsigned short XHOSA                           = 1076;
constexpr unsigned short ZULU                            = 1077;
constexpr unsigned short AFRIKAANS_SOUTH_AFRICA          = 1078;
constexpr unsigned short GEORGIAN                        = 1079;
constexpr unsigned short FAROESE                         = 1080;
constexpr unsigned short HINDI                           = 1081;
constexpr unsigned short MALTESE                         = 1082;
constexpr unsigned short SAMI_LAPPISH                    = 1083;
constexpr unsigned short GAELIC_SCOTLAND                 = 1084;
constexpr unsigned short YIDDISH                         = 1085;
constexpr unsigned short MALAY_MALAYSIA                  = 1086;
constexpr unsigned short KAZAKH                          = 1087;
constexpr unsigned short KYRGYZ_CYRILLIC                 = 1088;
constexpr unsigned short SWAHILI                         = 1089;
constexpr unsigned short TURKMEN                         = 1090;
constexpr unsigned short UZBEK_LATIN                     = 1091;
constexpr unsigned short TATAR                           = 1092;
constexpr unsigned short BENGALI_INDIA                   = 1093;
constexpr unsigned short PUNJABI                         = 1094;
constexpr unsigned short GUJARATI                        = 1124;
constexpr unsigned short DIVEHI                          = 1125;
constexpr unsigned short EDO                             = 1126;
constexpr unsigned short FULFULDE_NIGERIA                = 1127;
constexpr unsigned short HAUSA_NIGERIA                   = 1128;
constexpr unsigned short IBIBIO_NIGERIA                  = 1129;
constexpr unsigned short YORUBA                          = 1130;
constexpr unsigned short QUECHA_BOLIVIA                  = 1131;
constexpr unsigned short SEPEDI                          = 1132;
constexpr unsigned short IGBO_NIGERIA                    = 1136;
constexpr unsigned short KANURI_NIGERIA                  = 1137;
constexpr unsigned short OROMO                           = 1138;
constexpr unsigned short TIGRIGNA_ETHIOPIA               = 1139;
constexpr unsigned short GUARANI_PARAGUAY                = 1140;
constexpr unsigned short HAWAIIAN_UNITED_STATES          = 1141;
constexpr unsigned short LATIN                           = 1142;
constexpr unsigned short SOMALI                          = 1143;
constexpr unsigned short YI                              = 1144;
constexpr unsigned short PAPIAMENTU                      = 1145;
constexpr unsigned short UIGHUR_CHINA                    = 1152;
constexpr unsigned short MAORI_NEW_ZEALAND               = 1153;
constexpr unsigned short HID_HUMAN_INTERFACE_DEVICE      = 1279;
constexpr unsigned short ARABIC_IRAQ                     = 2049;
constexpr unsigned short CHINESE_PEOPLES_REPUBLIC_CHINA  = 2052;
constexpr unsigned short GERMAN_SWITZERLAND              = 2055;
constexpr unsigned short ENGLISH_UNITED_KINGDOM          = 2057;
constexpr unsigned short SPANISH_MEXICO                  = 2058;
constexpr unsigned short FRENCH_BELGIUM                  = 2060;
constexpr unsigned short ITALIAN_SWITZERLAND             = 2064;
constexpr unsigned short DUTCH_BELGIUM                   = 2067;
constexpr unsigned short NORWEGIAN_NYNORSK               = 2068;
constexpr unsigned short PORTUGUESE_PORTUGAL             = 2070;
constexpr unsigned short ROMANIAN_MOLDAVA                = 2072;
constexpr unsigned short RUSSIAN_MOLDAVA                 = 2073;
constexpr unsigned short SERBIAN_LATIN                   = 2074;
constexpr unsigned short SWEDISH_FINLAND                 = 2077;
constexpr unsigned short URDU_INDIA                      = 2080;
constexpr unsigned short AZERI_CYRILLIC                  = 2092;
constexpr unsigned short GAELIC_IRELAND                  = 2108;
constexpr unsigned short MALAY_BRUNEI_DARUSSALAM         = 2110;
constexpr unsigned short UZBEK_CYRILLIC                  = 2115;
constexpr unsigned short BENGALI_BANGLADESH              = 2117;
constexpr unsigned short PUNJABI_PAKISTAN                = 2118;
constexpr unsigned short MONGOLIAN_MONGOLIAN             = 2128;
constexpr unsigned short TIBETAN_BHUTAN                  = 2129;
constexpr unsigned short SINDHI_PAKISTAN                 = 2137;
constexpr unsigned short TAMAZIGHT_LATIN                 = 2143;
constexpr unsigned short KASHMIRI                        = 2144;
constexpr unsigned short NEPALI_INDIA                    = 2145;
constexpr unsigned short QUECHA_ECUADOR                  = 2155;
constexpr unsigned short TIGRIGNA_ERITREA                = 2163;
constexpr unsigned short ARABIC_EGYPT                    = 3073;
constexpr unsigned short CHINESE_HONG_KONG_SAR		 = 3076;
constexpr unsigned short GERMAN_AUSTRIA                  = 3079;
constexpr unsigned short ENGLISH_AUSTRALIA               = 3081;
constexpr unsigned short SPANISH_SPAIN_MODERN		 = 3082;
constexpr unsigned short FRENCH_CANADA                   = 3084;
constexpr unsigned short SERBIAN_CYRILLIC                = 3098;
constexpr unsigned short QUECHA_PERU                     = 3179;
constexpr unsigned short ARABIC_LIBYA                    = 4097;
constexpr unsigned short CHINESE_SINGAPORE               = 4100;
constexpr unsigned short GERMAN_LUXEMBOURG               = 4103;
constexpr unsigned short ENGLISH_CANADA                  = 4105;
constexpr unsigned short SPANISH_GUATEMALA               = 4106;
constexpr unsigned short FRENCH_SWITZERLAND              = 4108;
constexpr unsigned short CROATIAN_BOSNIA_HERZEGOVINA     = 4122;
constexpr unsigned short ARABIC_ALGERIA                  = 5121;
constexpr unsigned short CHINESE_MACAO_SAR               = 5124;
constexpr unsigned short GERMAN_LIECHTENSTEIN            = 5127;
constexpr unsigned short ENGLISH_NEW_ZEALAND             = 5129;
constexpr unsigned short SPANISH_COSTA_RICA              = 5130;
constexpr unsigned short FRENCH_LUXEMBOURG               = 5132;
constexpr unsigned short BOSNIAN_BOSNIA_HERZEGOVINA      = 5146;
constexpr unsigned short ARABIC_MOROCCO                  = 6145;
constexpr unsigned short ENGLISH_IRELAND                 = 6153;
constexpr unsigned short SPANISH_PANAMA                  = 6154;
constexpr unsigned short FRENCH_MONACO                   = 6156;
constexpr unsigned short ARABIC_TUNISIA                  = 7169;
constexpr unsigned short ENGLISH_SOUTH_AFRICA            = 7177;
constexpr unsigned short SPANISH_DOMINICAN_REPUBLIC      = 7178;
constexpr unsigned short FRENCH_WEST_INDIES              = 7180;
constexpr unsigned short ARABIC_OMAN                     = 8193;
constexpr unsigned short ENGLISH_JAMAICA                 = 8201;
constexpr unsigned short SPANISH_VENEZUELA               = 8202;
constexpr unsigned short FRENCH_REUNION                  = 8204;
constexpr unsigned short ARABIC_YEMEN                    = 9217;
constexpr unsigned short ENGLISH_CARIBBEAN               = 9225;
constexpr unsigned short SPANISH_COLOMBIA                = 9226;
constexpr unsigned short FRENCH_DEMOCRATIC_REP_OF_CONGO	 = 9228;
constexpr unsigned short ARABIC_SYRIA                    = 10241;
constexpr unsigned short ENGLISH_BELIZE                  = 10249;
constexpr unsigned short SPANISH_PERU                    = 10250;
constexpr unsigned short FRENCH_SENEGAL                  = 10252;
constexpr unsigned short ARABIC_JORDAN                   = 11265;
constexpr unsigned short ENGLISH_TRINIDAD                = 11273;
constexpr unsigned short SPANISH_ARGENTINA               = 11274;
constexpr unsigned short FRENCH_CAMEROON                 = 11276;
constexpr unsigned short ARABIC_LEBANON                  = 12289;
constexpr unsigned short ENGLISH_ZIMBABWE                = 12297;
constexpr unsigned short SPANISH_ECUADOR                 = 12298;
constexpr unsigned short FRENCH_COTE_DIVOIRE             = 12300;
constexpr unsigned short ARABIC_KUWAIT                   = 13313;
constexpr unsigned short ENGLISH_PHILIPPINES             = 13321;
constexpr unsigned short SPANISH_CHILE                   = 13322;
constexpr unsigned short FRENCH_MALI                     = 13324;
constexpr unsigned short ARABIC_UAE                      = 14337;
constexpr unsigned short ENGLISH_INDONESIA               = 14345;
constexpr unsigned short SPANISH_URUGUAY                 = 14346;
constexpr unsigned short FRENCH_MOROCCO                  = 14348;
constexpr unsigned short ARABIC_BAHRAIN                  = 15361;
constexpr unsigned short ENGLISH_HONG_KONG_SAR		       = 15369;
constexpr unsigned short SPANISH_PARAGUAY                = 15370;
constexpr unsigned short FRENCH_HAITI                    = 15372;
constexpr unsigned short ARABIC_QATAR                    = 16385;
constexpr unsigned short ENGLISH_INDIA                   = 16393;
constexpr unsigned short SPANISH_BOLIVIA                 = 16394;
constexpr unsigned short ENGLISH_MALAYSIA                = 17417;
constexpr unsigned short SPANISH_EL_SALVADOR             = 17418;
constexpr unsigned short ENGLISH_SINGAPORE               = 18441;
constexpr unsigned short SPANISH_HONDURAS                = 18442;
constexpr unsigned short SPANISH_NICARAGUA               = 19466;
constexpr unsigned short SPANISH_PUERTO_RICO             = 20490;
constexpr unsigned short SPANISH_UNITED_STATES           = 21514;
constexpr unsigned short SPANISH_LATIN_AMERICA           = 58378;
constexpr unsigned short FRENCH_NORTH_AFRICA             = 58380;

// In the constructors that follow, all data members
// are being set to zero, in line with recommendation
// in [MS-DOC] - 20170112
Fib::Fib()
{
  csw         = { };
  cslw	      = { };
  cbRgFcLcb   = { };
  cswNew      = { };
}

Fib::~Fib()
{
}

Fib::FibBase::FibBase()
{
  wIdent		 = { };
  nFib		         = { };
  unused		 = { };
  lid		         = { };
  pnNext		 = { };
  fDot		         = 0;
  fGlsy		         = 0;
  fComplex	         = 0;
  fHasPic	         = 0;
  cQuickSaves	         = 0;
  fEncrypted	         = 0;
  fWhichTblStm           = 0;
  fReadOnlyRecommended   = 0;
  fWriteReservation      = 0;
  fExtChar	         = 0;
  fLoadOverride	         = 0;
  fFarEast	         = 0;
  fObfuscated	         = 0;
  nFibBack	         = { };
  lkey		         = { };
  envr		         = { };
  fMac		         = 0;
  fEmptySpecial	         = 0;
  fLoadOverridePage      = 0;
  reserved1	         = 0;
  reserved2	         = 0;
  fSpare0		 = 0;
  reserved3	         = { };
  reserved4	         = { };
  reserved5	         = { };
  reserved6	         = { };
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
  lidFE       = { };
}

Fib::FibRgW97::~FibRgW97()
{
}

Fib::FibRgLw97::FibRgLw97()
{
  cbMac		= { };
  reserved1	= { };
  reserved2	= { };
  ccpText	= { };
  ccpFtn	= { };
  ccpHdd	= { };
  reserved3	= { };
  ccpAtn	= { };
  ccpEdn	= { };
  ccpTxbx	= { };
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
  fcStshfOrig		= { };
  lcbStshfOrig		= { };
  fcStshf		= { };
  lcbStshf		= { };
  fcPlcffndRef		= { };
  lcbPlcffndRef		= { };
  fcPlcffndTxt		= { };
  lcbPlcffndTxt		= { };
  fcPlcfandRef		= { };
  lcbPlcfandRef		= { };
  fcPlcfandTxt		= { };
  lcbPlcfandTxt		= { };
  fcPlcfSed		= { };
  lcbPlcfSed		= { };
  fcPlcPad		= { };
  lcbPlcPad		= { };
  fcPlcfPhe		= { };
  lcbPlcfPhe		= { };
  fcSttbfGlsy		= { };
  lcbSttbfGlsy		= { };
  fcPlcfGlsy		= { };
  lcbPlcfGlsy		= { };
  fcPlcfHdd		= { };
  lcbPlcfHdd		= { };
  fcPlcfBteChpx		= { };
  lcbPlcfBteChpx	= { };
  fcPlcfBtePapx		= { };
  lcbPlcfBtePapx	= { };
  fcPlcfSea		= { };
  lcbPlcfSea		= { };
  fcSttbfFfn		= { };
  lcbSttbfFfn		= { };
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
  fcSttbfBkmk		= { };
  lcbSttbfBkmk		= { };
  fcPlcfBkf		= { };
  lcbPlcfBkf		= { };
  fcPlcfBkl		= { };
  lcbPlcfBkl		= { };
  fcCmds		= { };
  lcbCmds		= { };
  fcUnused1		= { };
  lcbUnused1		= { };
  fcSttbfMcr		= { };
  lcbSttbfMcr		= { };
  fcPrDrvr		= { };
  lcbPrDrvr		= { };
  fcPrEnvPort		= { };
  lcbPrEnvPort		= { };
  fcPrEnvLand		= { };
  lcbPrEnvLand		= { };
  fcWss			= { };
  lcbWss		= { };
  fcDop			= { };
  lcbDop		= { };
  fcSttbfAssoc		= { };
  lcbSttbfAssoc		= { };
  fcClx			= { };
  lcbClx		= { };
  fcPlcfPgdFtn		= { };
  lcbPlcfPgdFtn		= { };
  fcAutosaveSource	= { };
  lcbAutosaveSource	= { };
  fcGrpXstAtnOwners	= { };
  lcbGrpXstAtnOwners	= { };
  fcSttbfAtnBkmk	= { };
  lcbSttbfAtnBkmk	= { };
  fcUnused2		= { };
  lcbUnused2		= { };
  fcUnused3		= { };
  lcbUnused3		= { };
  fcPlcSpaMom		= { };
  lcbPlcSpaMom		= { };
  fcPlcSpaHdr		= { };
  lcbPlcSpaHdr		= { };
  fcPlcfAtnBkf		= { };
  lcbPlcfAtnBkf		= { };
  fcPlcfAtnBkl		= { };
  lcbPlcfAtnBkl		= { };
  fcPms			= { };
  lcbPms		= { };
  fcFormFldSttbs	= { };
  lcbFormFldSttbs	= { };
  fcPlcfendRef		= { };
  lcbPlcfendRef		= { };
  fcPlcfendTxt		= { };
  lcbPlcfendTxt		= { };
  fcPlcfFldEdn		= { };
  lcbPlcfFldEdn		= { };
  fcUnused4		= { };
  lcbUnused4		= { };
  fcDggInfo		= { };
  lcbDggInfo		= { };
  fcSttbfRMark		= { };
  lcbSttbfRMark		= { };
  fcSttbfCaption	= { };
  lcbSttbfCaption	= { };
  fcSttbfAutoCaption	= { };
  lcbSttbfAutoCaption   = { };
  fcPlcfWkb		= { };
  lcbPlcfWkb		= { };
  fcPlcfSpl		= { };
  lcbPlcfSpl		= { };
  fcPlcftxbxTxt		= { };
  lcbPlcftxbxTxt	= { };
  fcPlcfFldTxbx		= { };
  lcbPlcfFldTxbx	= { };
  fcPlcfHdrtxbxTxt	= { };
  lcbPlcfHdrtxbxTxt	= { };
  fcPlcffldHdrTxbx	= { };
  lcbPlcffldHdrTxbx	= { };
  fcStwUser		= { };
  lcbStwUser		= { };
  fcSttbTtmbd		= { };
  lcbSttbTtmbd		= { };
  fcCookieData		= { };
  lcbCookieData		= { };
  fcPgdMotherOldOld	= { };
  lcbPgdMotherOldOld	= { };
  fcBkdMotherOldOld	= { };
  lcbBkdMotherOldOld	= { };
  fcPgdFtnOldOld	= { };
  lcbPgdFtnOldOld	= { };
  fcBkdFtnOldOld	= { };
  lcbBkdFtnOldOld	= { };
  fcPgdEdnOldOld	= { };
  lcbPgdEdnOldOld	= { };
  fcBkdEdnOldOld	= { };
  lcbBkdEdnOldOld	= { };
  fcSttbfIntlFld	= { };
  lcbSttbfIntlFld	= { };
  fcRouteSlip		= { };
  lcbRouteSlip		= { };
  fcSttbSavedBy		= { };
  lcbSttbSavedBy	= { };
  fcSttbFnm		= { };
  lcbSttbFnm		= { };
  fcPlfLst		= { };
  lcbPlfLst		= { };
  fcPlfLfo		= { };
  lcbPlfLfo		= { };
  fcPlcfTxbxBkd		= { };
  lcbPlcfTxbxBkd	= { };
  fcPlcfTxbxHdrBkd	= { };
  lcbPlcfTxbxHdrBkd	= { };
  fcDocUndoWord9	= { };
  lcbDocUndoWord9	= { };
  fcRgbUse		= { };
  lcbRgbUse		= { };
  fcUsp			= { };
  lcbUsp		= { };
  fcUskf		= { };
  lcbUskf		= { };
  fcPlcupcRgbUse	= { };
  lcbPlcupcRgbUse	= { };
  fcPlcupcUsp		= { };
  lcbPlcupcUsp		= { };
  fcSttbGlsyStyle	= { };
  lcbSttbGlsyStyle	= { };
  fcPlgosl		= { };
  lcbPlgosl		= { };
  fcPlcocx		= { };
  lcbPlcocx		= { };
  fcPlcfBteLvc		= { };
  lcbPlcfBteLvc		= { };
  dwLowDateTime		= { };
  dwHighDateTime	= { };
  fcPlcfLvcPre10	= { };
  lcbPlcfLvcPre10	= { };
  fcPlcfAsumy		= { };
  lcbPlcfAsumy		= { };
  fcPlcfGram		= { };
  lcbPlcfGram		= { };
  fcSttbListNames	= { };
  lcbSttbListNames	= { };
  fcSttbfUssr		= { };
  lcbSttbfUssr		= { };
}

Fib::FibRgFcLcb::FibRgFcLcb97::~FibRgFcLcb97()
{
}

Fib::FibRgFcLcb::FibRgFcLcb2000::FibRgFcLcb2000()
{
  fcPlcfTch		= { };
  lcbPlcfTch		= { };
  fcRmdThreading	= { };
  lcbRmdThreading	= { };
  fcMid			= { };
  lcbMid		= { };
  fcSttbRgtplc		= { };
  lcbSttbRgtplc		= { };
  fcMsoEnvelope		= { };
  lcbMsoEnvelope	= { };
  fcPlcfLad		= { };
  lcbPlcfLad		= { };
  fcRgDofr		= { };
  lcbRgDofr		= { };
  fcPlcosl		= { };
  lcbPlcosl		= { };
  fcPlcfCookieOld	= { };
  lcbPlcfCookieOld	= { };
  fcPgdMotherOld	= { };
  lcbPgdMotherOld	= { };
  fcBkdMotherOld	= { };
  lcbBkdMotherOld	= { };
  fcPgdFtnOld		= { };
  lcbPgdFtnOld		= { };
  fcBkdFtnOld		= { };
  lcbBkdFtnOld		= { };
  fcPgdEdnOld		= { };
  lcbPgdEdnOld		= { };
  fcBkdEdnOld		= { };
  lcbBkdEdnOld		= { };
}

Fib::FibRgFcLcb::FibRgFcLcb2000::~FibRgFcLcb2000()
{
}

Fib::FibRgFcLcb::FibRgFcLcb2002::FibRgFcLcb2002()
{
  fcUnused1		= { };
  lcbUnused1		= { };
  fcPlcfPgp		= { };
  lcbPlcfPgp		= { };
  fcPlcfuim		= { };
  lcbPlcfuim		= { };
  fcPlfguidUim		= { };
  lcbPlfguidUim		= { };
  fcAtrdExtra		= { };
  lcbAtrdExtra		= { };
  fcPlrsid		= { };
  lcbPlrsid		= { };
  fcSttbfBkmkFactoid	= { };
  lcbSttbfBkmkFactoid	= { };
  fcPlcfBkfFactoid	= { };
  lcbPlcfBkfFactoid	= { };
  fcPlcfcookie		= { };
  lcbPlcfcookie		= { };
  fcPlcfBklFactoid	= { };
  lcbPlcfBklFactoid	= { };
  fcFactoidData		= { };
  lcbFactoidData	= { };
  fcDocUndo		= { };
  lcbDocUndo		= { };
  fcSttbfBkmkFcc	= { };
  lcbSttbfBkmkFcc	= { };
  fcPlcfBkfFcc		= { };
  lcbPlcfBkfFcc		= { };
  fcPlcfBklFcc		= { };
  lcbPlcfBklFcc		= { };
  fcSttbfbkmkBPRepairs	= { };
  lcbSttbfbkmkBPRepairs	= { };
  fcPlcfbkfBPRepairs	= { };
  lcbPlcfbkfBPRepairs	= { };
  fcPlcfbklBPRepairs	= { };
  lcbPlcfbklBPRepairs	= { };
  fcPmsNew		= { };
  lcbPmsNew		= { };
  fcODSO		= { };
  lcbODSO		= { };
  fcPlcfpmiOldXP	= { };
  lcbPlcfpmiOldXP	= { };
  fcPlcfpmiNewXP	= { };
  lcbPlcfpmiNewXP	= { };
  fcPlcfpmiMixedXP	= { };
  lcbPlcfpmiMixedXP     = { };
  fcUnused2		= { };
  lcbUnused2		= { };
  fcPlcffactoid		= { };
  lcbPlcffactoid	= { };
  fcPlcflvcOldXP	= { };
  lcbPlcflvcOldXP	= { };
  fcPlcflvcNewXP	= { };
  lcbPlcflvcNewXP	= { };
  fcPlcflvcMixedXP	= { };
  lcbPlcflvcMixedXP	= { };
}

Fib::FibRgFcLcb::FibRgFcLcb2002::~FibRgFcLcb2002()
{
}

Fib::FibRgFcLcb::FibRgFcLcb2003::FibRgFcLcb2003()
{
  fcHplxsdr	       = { };
  lcbHplxsdr	       = { };
  fcSttbfBkmkSdt       = { };
  lcbSttbfBkmkSdt      = { };
  fcPlcfBkfSdt	       = { };
  lcbPlcfBkfSdt	       = { };
  fcPlcfBklSdt	       = { };
  lcbPlcfBklSdt	       = { };
  fcCustomXForm	       = { };
  lcbCustomXForm       = { };
  fcSttbfBkmkProt      = { };
  lcbSttbfBkmkProt     = { };
  fcPlcfBkfProt	       = { };
  lcbPlcfBkfProt       = { };
  fcPlcfBklProt	       = { };
  lcbPlcfBklProt       = { };
  fcSttbProtUser       = { };
  lcbSttbProtUser      = { };
  fcUnused	       = { };
  lcbUnused	       = { };
  fcPlcfpmiOld	       = { };
  lcbPlcfpmiOld	       = { };
  fcPlcfpmiOldInline   = { };
  lcbPlcfpmiOldInline  = { };
  fcPlcfpmiNew	       = { };
  lcbPlcfpmiNew	       = { };
  fcPlcfpmiNewInline   = { };
  lcbPlcfpmiNewInline  = { };
  fcPlcflvcOld	       = { };
  lcbPlcflvcOld	       = { };
  fcPlcflvcOldInline   = { };
  lcbPlcflvcOldInline  = { };
  fcPlcflvcNew	       = { };
  lcbPlcflvcNew	       = { };
  fcPlcflvcNewInline   = { };
  lcbPlcflvcNewInline  = { };
  fcPgdMother	       = { };
  lcbPgdMother	       = { };
  fcBkdMother	       = { };
  lcbBkdMother	       = { };
  fcAfdMother	       = { };
  lcbAfdMother	       = { };
  fcPgdFtn	       = { };
  lcbPgdFtn	       = { };
  fcBkdFtn	       = { };
  lcbBkdFtn	       = { };
  fcAfdFtn	       = { };
  lcbAfdFtn	       = { };
  fcPgdEdn	       = { };
  lcbPgdEdn	       = { };
  fcBkdEdn	       = { };
  lcbBkdEdn	       = { };
  fcAfdEdn	       = { };
  lcbAfdEdn	       = { };
  fcAfd		       = { };
  lcbAfd               = { };
}   

Fib::FibRgFcLcb::FibRgFcLcb2003::~FibRgFcLcb2003()
{
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

Fib::FibRgCswNew::FibRgCswNew()
{
  nFibNew = { };
}

Fib::FibRgCswNew::~FibRgCswNew()
{
}

Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData()
{
}

Fib::FibRgCswNew::FibRgCswNewData::~FibRgCswNewData()
{
}
Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::FibRgCswNewData2000()
{
  cQuickSavesNew = { };
}

Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::~FibRgCswNewData2000()
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

// Reads the File Information Block (FIB)
// This method also calls other functions that read relevant parts of the FIB.
void Fib::read_Fib(std::ifstream &docstream)
{
  base.read_FibBase(docstream);  
  docstream.read(reinterpret_cast<char *>(&csw), sizeof(unsigned short));
  fibRgW.read_FibRgW(docstream);
  docstream.read(reinterpret_cast<char *>(&cslw), sizeof(unsigned short));
  fibRgLw.read_FibRgLw(docstream);
  docstream.read(reinterpret_cast<char *>(&cbRgFcLcb), sizeof(unsigned short));
  fibRgFcLcbBlob.read_FibRgFcLcbBlob(docstream, cbRgFcLcb);
  docstream.read(reinterpret_cast<char *>(&cswNew), sizeof(unsigned short));
  fibRgCswNew.read_FibRgCswNew(docstream, cswNew);
  if (cswNew != EXPECTED_CSWNEW_97)
  {
    base.nFib = fibRgCswNew.nFibNew;
  }
}

// Reads the FibBase from the WordDocument Stream
// Those parts that are bit fields are extracted using
// bit masks and other relevant constructs
void Fib::FibBase::read_FibBase(std::ifstream &docfile)
{
  docfile.read(reinterpret_cast<char *>(&wIdent), sizeof(unsigned short));
  docfile.read(reinterpret_cast<char *>(&nFib), sizeof(unsigned short));
  if (nFib == NFIB_SPECIAL || nFib == NFIB_BIDI_BLD)
  {
    nFib = NFIB_FOR_97;
  }

  docfile.read(reinterpret_cast<char *>(&unused), sizeof(unsigned short));
  docfile.read(reinterpret_cast<char *>(&lid), sizeof(unsigned short));
  docfile.read(reinterpret_cast<char *>(&pnNext), sizeof(unsigned short));

  unsigned char		tmp = 0x0;
  const unsigned char	fD  = 0x1;
  const unsigned char	fG  = 0x2;
  const unsigned char	fC  = 0x4;
  const unsigned char	fHP = 0x8;
  unsigned char		msk = 0x0F;

  docfile.read(reinterpret_cast<char *>(&tmp), sizeof(unsigned char));
  fDot	      = assignBits(fD, tmp, 0);
  fGlsy	      = assignBits(fG, tmp, 1);
  fComplex    = assignBits(fC, tmp, 2);
  fHasPic     = assignBits(fHP, tmp, 3);
  tmp >>= 4;
  cQuickSaves = tmp & msk;

  const unsigned char fE	   = 0x1;
  const unsigned char fWT   = 0x2;
  const unsigned char fROR  = 0x4;
  const unsigned char fWR   = 0x8;
  const unsigned char fEC   = 0x10;
  const unsigned char fLO   = 0x20;
  const unsigned char fFE   = 0x40;
  const unsigned char fO	   = 0x80;
  docfile.read(reinterpret_cast<char *>(&tmp), sizeof(unsigned char));
  fEncrypted            = assignBits(fE, tmp, 0);
  fWhichTblStm          = assignBits(fWT, tmp, 1);
  fReadOnlyRecommended	= assignBits(fROR, tmp, 2);
  fWriteReservation     = assignBits(fWR, tmp, 3);
  fExtChar              = assignBits(fEC, tmp, 4);
  fLoadOverride         = assignBits(fLO, tmp, 5);
  fFarEast              = assignBits(fFE, tmp, 6);
  fObfuscated           = assignBits(fO, tmp, 7);

  docfile.read(reinterpret_cast<char *>(&nFibBack), sizeof(unsigned short));
  docfile.read(reinterpret_cast<char *>(&lkey), sizeof(unsigned long));
  docfile.read(reinterpret_cast<char *>(&envr), sizeof(unsigned char));

  const unsigned char fM	  = 0x1;
  const unsigned char fES  = 0x2;
  const unsigned char fLOP = 0x4;
  const unsigned char res1 = 0x8;
  const unsigned char res2 = 0x10;
  msk = 0x9;
  docfile.read(reinterpret_cast<char *>(&tmp), sizeof(unsigned char));
  fMac              = assignBits(fM, tmp, 0);
  fEmptySpecial     = assignBits(fES, tmp, 1);
  fLoadOverridePage = assignBits(fLOP, tmp, 2);
  reserved1         = assignBits(res1, tmp, 3);
  reserved2         = assignBits(res2, tmp, 4);
  tmp >>= 5;
  fSpare0 = tmp & msk;

  docfile.read(reinterpret_cast<char *>(&reserved3), sizeof(unsigned short));
  docfile.read(reinterpret_cast<char *>(&reserved4), sizeof(unsigned short));
  docfile.read(reinterpret_cast<char *>(&reserved5), sizeof(unsigned long));
  docfile.read(reinterpret_cast<char *>(&reserved6), sizeof(unsigned long));
}

void Fib::FibRgLw97::read_FibRgLw(std::ifstream & mystream)
{ // TODO: Clean this thing up!
  unsigned short add_member_sizes = 0;   // What on earth was I thinking???

  mystream.read(reinterpret_cast<char *>(&cbMac), sizeof(unsigned long));
  add_member_sizes += sizeof(cbMac);  // these lines! What the heck?
  mystream.read(reinterpret_cast<char *>(&reserved1), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved1);
  mystream.read(reinterpret_cast<char *>(&reserved2), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved2);
  mystream.read(reinterpret_cast<char *>(&ccpText), sizeof(unsigned long));
  add_member_sizes += sizeof(ccpText);
  mystream.read(reinterpret_cast<char *>(&ccpFtn), sizeof(unsigned long));
  add_member_sizes += sizeof(ccpFtn);
  mystream.read(reinterpret_cast<char *>(&ccpHdd), sizeof(unsigned long));
  add_member_sizes += sizeof(ccpHdd);
  mystream.read(reinterpret_cast<char *>(&reserved3), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved3);
  mystream.read(reinterpret_cast<char *>(&ccpAtn), sizeof(unsigned long));
  add_member_sizes += sizeof(ccpAtn);
  mystream.read(reinterpret_cast<char *>(&ccpEdn), sizeof(unsigned long));
  add_member_sizes += sizeof(ccpEdn);
  mystream.read(reinterpret_cast<char *>(&ccpTxbx), sizeof(unsigned long));
  add_member_sizes += sizeof(ccpTxbx);
  mystream.read(reinterpret_cast<char *>(&ccpHdrTxbx), sizeof(unsigned long));
  add_member_sizes += sizeof(ccpHdrTxbx);
  mystream.read(reinterpret_cast<char *>(&reserved4), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved4);
  mystream.read(reinterpret_cast<char *>(&reserved5), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved5);
  mystream.read(reinterpret_cast<char *>(&reserved6), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved6);
  mystream.read(reinterpret_cast<char *>(&reserved7), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved7);
  mystream.read(reinterpret_cast<char *>(&reserved8), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved8);
  mystream.read(reinterpret_cast<char *>(&reserved9), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved9);
  mystream.read(reinterpret_cast<char *>(&reserved10), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved10);
  mystream.read(reinterpret_cast<char *>(&reserved11), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved11);
  mystream.read(reinterpret_cast<char *>(&reserved12), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved12);
  mystream.read(reinterpret_cast<char *>(&reserved13), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved13);
  mystream.read(reinterpret_cast<char *>(&reserved14), sizeof(unsigned long));
  add_member_sizes += sizeof(reserved14);
}

void Fib::FibRgW97::read_FibRgW(std::ifstream & filestrm)
{
  filestrm.read(reinterpret_cast<char *>(&reserved1), sizeof(unsigned short));
  filestrm.read(reinterpret_cast<char *>(&reserved2), sizeof(unsigned short));
  filestrm.read(reinterpret_cast<char *>(&reserved3), sizeof(unsigned short));
  filestrm.read(reinterpret_cast<char *>(&reserved4), sizeof(unsigned short));
  filestrm.read(reinterpret_cast<char *>(&reserved5), sizeof(unsigned short));
  filestrm.read(reinterpret_cast<char *>(&reserved6), sizeof(unsigned short));
  filestrm.read(reinterpret_cast<char *>(&reserved7), sizeof(unsigned short));
  filestrm.read(reinterpret_cast<char *>(&reserved8), sizeof(unsigned short));
  filestrm.read(reinterpret_cast<char *>(&reserved9), sizeof(unsigned short));
  filestrm.read(reinterpret_cast<char *>(&reserved10), sizeof(unsigned short));
  filestrm.read(reinterpret_cast<char *>(&reserved11), sizeof(unsigned short));
  filestrm.read(reinterpret_cast<char *>(&reserved12), sizeof(unsigned short));
  filestrm.read(reinterpret_cast<char *>(&reserved13), sizeof(unsigned short));
  filestrm.read(reinterpret_cast<char *>(&lidFE), sizeof(unsigned short));
}

// Reads the value of a part of the FIB that varies in content and structure
  // with different versions of Word (97 - 2007). The nFib (a member of the FibBase
  // data structure) is what determines which version is used.
void Fib::FibRgFcLcb::read_FibRgFcLcbBlob(std::ifstream& flStream, const unsigned short newVer)
{
  switch (newVer)
  {
  case EXPECTED_CBRGFCLCB_97:
    fibRgFcLcb97.read_FibRgFcLcb97(flStream);
    break;
  case EXPECTED_CBRGFCLCB_2000:
    fibRgFcLcb2000.read_FibRgFcLcb2000(flStream);
    break;
  case EXPECTED_CBRGFCLCB_2002:
    fibRgFcLcb2002.read_FibRgFcLcb2002(flStream);
    break;
  case EXPECTED_CBRGFCLCB_2003:
    fibRgFcLcb2003.read_FibRgFcLcb2003(flStream);
    break;
  case EXPECTED_CBRGFCLCB_2007:
    fibRgFcLcb2007.read_FibRgFcLcb2007(flStream);
    break;
  default:
    throw "çbRgFcLbc' is holding an invalid value.";
  }
}

void Fib::FibRgFcLcb::FibRgFcLcb97::read_FibRgFcLcb97(std::ifstream & mainstrm)
{
  mainstrm.read(reinterpret_cast<char *>(&fcStshfOrig), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbStshfOrig), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcStshf), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbStshf), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcffndRef), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcffndRef), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcffndTxt), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcffndTxt), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfandRef), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfandRef), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfandTxt), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfandTxt), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfSed), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfSed), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcPad), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcPad), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfPhe), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfPhe), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfGlsy), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfGlsy), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfGlsy), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfGlsy), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfHdd), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfHdd), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfBteChpx), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBteChpx), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfBtePapx), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBtePapx), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfSea), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfSea), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfFfn), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfFfn), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldMom), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldMom), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldHdr), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldHdr), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldFtn), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldFtn), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldAtn), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldAtn), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldMcr), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldMcr), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfBkmk), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfBkmk), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfBkf), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBkf), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfBkl), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBkl), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcCmds), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbCmds), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcUnused1), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbUnused1), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfMcr), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfMcr), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPrDrvr), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPrDrvr), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPrEnvPort), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPrEnvPort), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPrEnvLand), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPrEnvLand), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcWss), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbWss), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcDop), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbDop), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfAssoc), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfAssoc), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcClx), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbClx), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfPgdFtn), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfPgdFtn), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcAutosaveSource), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbAutosaveSource), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcGrpXstAtnOwners), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbGrpXstAtnOwners), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfAtnBkmk), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfAtnBkmk), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcUnused2), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbUnused2), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcUnused3), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbUnused3), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcSpaMom), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcSpaMom), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcSpaHdr), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcSpaHdr), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfAtnBkf), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfAtnBkf), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfAtnBkl), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfAtnBkl), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPms), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPms), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcFormFldSttbs), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbFormFldSttbs), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfendRef), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfendRef), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfendTxt), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfendTxt), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldEdn), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldEdn), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcUnused4), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbUnused4), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcDggInfo), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbDggInfo), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfRMark), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfRMark), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfCaption), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfCaption), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfAutoCaption), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfAutoCaption), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfWkb), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfWkb), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfSpl), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfSpl), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcftxbxTxt), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcftxbxTxt), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldTxbx), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldTxbx), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfHdrtxbxTxt), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfHdrtxbxTxt), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcffldHdrTxbx), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcffldHdrTxbx), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcStwUser), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbStwUser), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbTtmbd), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbTtmbd), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcCookieData), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbCookieData), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPgdMotherOldOld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPgdMotherOldOld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcBkdMotherOldOld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbBkdMotherOldOld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPgdFtnOldOld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPgdFtnOldOld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcBkdFtnOldOld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbBkdFtnOldOld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPgdEdnOldOld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPgdEdnOldOld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcBkdEdnOldOld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbBkdEdnOldOld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfIntlFld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfIntlFld), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcRouteSlip), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbRouteSlip), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbSavedBy), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbSavedBy), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbFnm), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbFnm), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlfLst), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlfLst), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlfLfo), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlfLfo), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfTxbxBkd), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfTxbxBkd), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfTxbxHdrBkd), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfTxbxHdrBkd), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcDocUndoWord9), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbDocUndoWord9), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcRgbUse), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbRgbUse), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcUsp), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbUsp), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcUskf), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbUskf), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcupcRgbUse), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcupcRgbUse), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcupcUsp), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcupcUsp), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbGlsyStyle), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbGlsyStyle), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlgosl), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlgosl), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcocx), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcocx), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfBteLvc), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBteLvc), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&dwLowDateTime), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&dwHighDateTime), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfLvcPre10), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfLvcPre10), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfAsumy), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfAsumy), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfGram), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfGram), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbListNames), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbListNames), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfUssr), sizeof(unsigned long));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfUssr), sizeof(unsigned long));
}

void Fib::FibRgFcLcb::FibRgFcLcb2000::read_FibRgFcLcb2000(std::ifstream & wrdfile)
{
  rgFcLcb97.read_FibRgFcLcb97(wrdfile);
  
  wrdfile.read(reinterpret_cast<char *>(&fcPlcfTch), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbPlcfTch), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcRmdThreading), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbRmdThreading), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcMid), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbMid), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcSttbRgtplc), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbSttbRgtplc), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcMsoEnvelope), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbMsoEnvelope), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcPlcfLad), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbPlcfLad), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcRgDofr), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbRgDofr), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcPlcosl), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbPlcosl), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcPlcfCookieOld), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbPlcfCookieOld), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcPgdMotherOld), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbPgdMotherOld), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcBkdMotherOld), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbBkdMotherOld), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcPgdFtnOld), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbPgdFtnOld), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcBkdFtnOld), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbBkdFtnOld), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcPgdEdnOld), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbPgdEdnOld), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&fcBkdEdnOld), sizeof(unsigned long));
  wrdfile.read(reinterpret_cast<char *>(&lcbBkdEdnOld), sizeof(unsigned long));
}


void Fib::FibRgFcLcb::FibRgFcLcb2002::read_FibRgFcLcb2002(std::ifstream &documentStr)
{
  rgFcLcb2000.read_FibRgFcLcb2000(documentStr);

  documentStr.read(reinterpret_cast<char *>(&fcUnused1), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbUnused1), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfPgp), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfPgp), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfuim), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfuim), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlfguidUim), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlfguidUim), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcAtrdExtra), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbAtrdExtra), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlrsid), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlrsid), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcSttbfBkmkFactoid), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbSttbfBkmkFactoid), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfBkfFactoid), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfBkfFactoid), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfcookie), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfcookie), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfBklFactoid), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfBklFactoid), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcFactoidData), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbFactoidData), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcDocUndo), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbDocUndo), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcSttbfBkmkFcc), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbSttbfBkmkFcc), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfBkfFcc), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfBkfFcc), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfBklFcc), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfBklFcc), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcSttbfbkmkBPRepairs), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbSttbfbkmkBPRepairs), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfbkfBPRepairs), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfbkfBPRepairs), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfbklBPRepairs), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfbklBPRepairs), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPmsNew), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPmsNew), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcODSO), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbODSO), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfpmiOldXP), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfpmiOldXP), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfpmiNewXP), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfpmiNewXP), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfpmiMixedXP), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfpmiMixedXP), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcUnused2), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbUnused2), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcffactoid), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcffactoid), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcflvcOldXP), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcflvcOldXP), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcflvcNewXP), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcflvcNewXP), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&fcPlcflvcMixedXP), sizeof(unsigned long));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcflvcMixedXP), sizeof(unsigned long));
}


void Fib::FibRgFcLcb::FibRgFcLcb2003::read_FibRgFcLcb2003(std::ifstream & dotdocstrm)
{  
  rgFcLcb2002.read_FibRgFcLcb2002(dotdocstrm);

  dotdocstrm.read(reinterpret_cast<char *>(&fcHplxsdr), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbHplxsdr), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcSttbfBkmkSdt), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbSttbfBkmkSdt), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfBkfSdt), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfBkfSdt), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfBklSdt), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfBklSdt), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcCustomXForm), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbCustomXForm), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcSttbfBkmkProt), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbSttbfBkmkProt), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfBkfProt), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfBkfProt), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfBklProt), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfBklProt), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcSttbProtUser), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbSttbProtUser), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcUnused), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbUnused), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfpmiOld), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfpmiOld), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfpmiOldInline), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfpmiOldInline), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfpmiNew), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfpmiNew), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfpmiNewInline), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfpmiNewInline), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcflvcOld), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcflvcOld), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcflvcOldInline), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcflvcOldInline), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcflvcNew), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcflvcNew), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcflvcNewInline), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcflvcNewInline), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPgdMother), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPgdMother), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcBkdMother), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbBkdMother), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcAfdMother), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbAfdMother), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPgdFtn), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPgdFtn), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcBkdFtn), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbBkdFtn), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcAfdFtn), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbAfdFtn), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPgdEdn), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPgdEdn), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcBkdEdn), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbBkdEdn), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcAfdEdn), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbAfdEdn), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&fcAfd), sizeof(unsigned long));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbAfd), sizeof(unsigned long));
}

void Fib::FibRgFcLcb::FibRgFcLcb2007::read_FibRgFcLcb2007(std::ifstream & dStream)
{  
  rgFcLcb2003.read_FibRgFcLcb2003(dStream);

  dStream.read(reinterpret_cast<char *>(&fcPlcfmthd), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfmthd), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcSttbfBkmkMoveFrom), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbSttbfBkmkMoveFrom), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcPlcfBkfMoveFrom), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfBkfMoveFrom), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcPlcfBklMoveFrom), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfBklMoveFrom), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcSttbfBkmkMoveTo), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbSttbfBkmkMoveTo), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcPlcfBkfMoveTo), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfBkfMoveTo), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcPlcfBklMoveTo), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfBklMoveTo), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcUnused1), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbUnused1), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcUnused2), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbUnused2), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcUnused3), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbUnused3), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcSttbfBkmkArto), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbSttbfBkmkArto), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcPlcfBkfArto), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfBkfArto), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcPlcfBklArto), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfBklArto), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcArtoData), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbArtoData), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcUnused4), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbUnused4), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcUnused5), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbUnused5), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcUnused6), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbUnused6), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcOssTheme), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbOssTheme), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&fcColorSchemeMapping), sizeof(unsigned long));
  dStream.read(reinterpret_cast<char *>(&lcbColorSchemeMapping), sizeof(unsigned long));
}

// Reads an FibRgCswNew, using the current version of Word (97 -2007) to
// select the appropriate data structure to read into memory, whilst
// returning the size of data read for use in subsequent methods
void Fib::FibRgCswNew::read_FibRgCswNew(std::ifstream& stream, const unsigned short cswNewVal)
{
  if (cswNewVal == EXPECTED_CSWNEW_97)
  {
    std::cout << "This version does not have the 'FibRgCswNew' structure.\n";
  }
  else
  {
    stream.read(reinterpret_cast<char *>(&nFibNew), sizeof(unsigned short));
    rgCswNewData.read_FibRgCswNewData(stream, cswNewVal);
  }
}

// Reads from FibRgCswNewData structure, but what exactly is read depends
// on the verion of Word. This version is determined by the 2nd argument
// This function will return the size of the dat structure that was read
void Fib::FibRgCswNew::FibRgCswNewData::read_FibRgCswNewData(std::ifstream& filestrm, const unsigned short cswVer)
{
  if (cswVer == EXPECTED_CSWNEW_2000)
  {
    fibRgCswNewData2000.read_2000(filestrm);
  }
  else if (cswVer == EXPECTED_CSWNEW_2007)
  {
    fibRgCswNewData2007.read_2007(filestrm);
  }
}

void Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::read_2000(std::ifstream & instream)
{
  instream.read(reinterpret_cast<char *>(&cQuickSavesNew), sizeof(unsigned short));
}

void Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2007::read_2007(std::ifstream & streamin)
{
  FibRgCswNewData2000 newdat2000;
  newdat2000.read_2000(streamin);

  streamin.read(reinterpret_cast<char *>(&lidThemeOther), sizeof(unsigned short));
  streamin.read(reinterpret_cast<char *>(&lidThemeFE), sizeof(unsigned short));
  streamin.read(reinterpret_cast<char *>(&lidThemeCS), sizeof(unsigned short));
}

// Inspects the entire data read into the in-memory copy of the
// main data structures that represent the File Information Block.
// Where appropriate, minor adjustments are to be made
void Fib::inspectFibStructs()
{
  base.process_FibBase();
  fibRgW.process_FibRgW97();
  fibRgLw.process_FibRgLw97();
  fibRgFcLcbBlob.process_FibRgFcLcbBlob(base, fibRgLw);
  fibRgCswNew.process_FibRgCswNew(base);
}

// Screens the members of FibBase to make sure all conditions are met
void Fib::FibBase::process_FibBase()
{
  if (wIdent != WORD_BINARY_FILE)
  {
    throw "Fle is either corrupted or not of the specidied format.";
  }
  
  if (nFib >= NFIB_FOR_2000)
  {
    switch(lid)
    {
    case CHINESE_TAIWAN:
    case GERMAN_GERMANY:
    case SPANISH_SPAIN_TRADITIONAL:
    case FRENCH_FRANCE:
    case JAPANESE:
    case KOREAN:
    case CHINESE_PEOPLES_REPUBLIC_CHINA:
    case GERMAN_SWITZERLAND:
    case SPANISH_MEXICO:
    case CHINESE_HONG_KONG_SAR:
    case GERMAN_AUSTRIA:
    case SPANISH_SPAIN_MODERN:
    case FRENCH_CANADA:
    case CHINESE_SINGAPORE:
    case GERMAN_LUXEMBOURG:
    case FRENCH_SWITZERLAND:
    case CHINESE_MACAO_SAR:
    case GERMAN_LIECHTENSTEIN:
    case SPANISH_COSTA_RICA:
    case FRENCH_LUXEMBOURG:
    case SPANISH_PANAMA:
    case FRENCH_MONACO:
    case SPANISH_DOMINICAN_REPUBLIC:
    case FRENCH_WEST_INDIES:
    case SPANISH_VENEZUELA:
    case FRENCH_REUNION:
    case SPANISH_COLOMBIA:
    case FRENCH_DEMOCRATIC_REP_OF_CONGO:
    case SPANISH_PERU:
    case FRENCH_SENEGAL:
    case SPANISH_ARGENTINA:
    case FRENCH_CAMEROON:
    case SPANISH_ECUADOR:
    case FRENCH_COTE_DIVOIRE:
    case SPANISH_CHILE:
    case FRENCH_MALI:
    case SPANISH_URUGUAY:
    case FRENCH_MOROCCO:
    case SPANISH_PARAGUAY:
    case FRENCH_HAITI:
    case SPANISH_BOLIVIA:
    case SPANISH_EL_SALVADOR:
    case SPANISH_HONDURAS:
    case SPANISH_NICARAGUA:
    case SPANISH_PUERTO_RICO:
    case SPANISH_UNITED_STATES:
    case SPANISH_LATIN_AMERICA:
    case FRENCH_NORTH_AFRICA:
      lid = ENGLISH_UNITED_STATES;
      break;
    }
  }

  if (nFib >= NFIB_FOR_2002)
  {
    switch(lid)
    {
    case THAI:
    case VIETNAMESE:
    case HINDI:
      lid = ENGLISH_UNITED_STATES;
      break;
    }
  }
  
  if (pnNext != 0)
  {
    if (fGlsy == 1 || fDot == 0)
    {
      throw "pnNext MUST be zero.";
    }
    else
    {
      // open file stream
      // read a new FIB from offset pnMext x 512
      // close file stream
      // compare members of FibRgFcLcb97
      // - fcPlcBteChpx
      // - lcbPlcBteChpx
      // - fcPlcBtePapx
      // - lcbPlcBtePapx
      // and FibRgLw97.cbMac
      // Their values in both FIBs should be the same.
    }
  }
  
  if (nFib >= NFIB_FOR_2000)
  {
    if (cQuickSaves != 0xF)
    {
      throw "cQuickSaves is not equal to 0xF.";
    }
  }

  if (fExtChar != 1)
  {
    throw "fExtChar MUST be 1.";
  }

  if (nFibBack != 0x00BF || nFibBack != 0x00C1)
  {
    throw "Incorrect values for nFibBack.";
  }
}

void Fib::FibRgW97::process_FibRgW97()
{
}
 
void Fib::FibRgLw97::process_FibRgLw97()
{
  if (ccpText < 0)
  {
    throw "ccpText must be greater than or equal to 0.";
  }

  if (ccpFtn < 0)
  {
    throw "ccpFtn must be greater than or equal to 0.";
  }
  if (ccpHdd < 0)
  {
    throw "ccpHdd must be greater than or equal to 0.";
  }

  if (ccpAtn < 0)
  {
    throw "ccpAtn must be greater than or equal to 0.";
  }
  
  if (ccpEdn < 0)
  {
    throw "ccpEdn must be greater than or equal to 0.";
  }
  
  if (ccpTxbx < 0)
  {
    throw "ccpTxbx must be greater than or equal to 0.";
  }

  if (ccpHdrTxbx < 0)
  {
    throw "ccpKdrTxbx must be greater than or equal to 0.";
  }

}

void Fib::FibRgFcLcb::process_FibRgFcLcbBlob(const FibBase &baseObj, const FibRgLw97 &rglwObj)
{
  unsigned short version = baseObj.nFib;
  switch(version)
  {
  case NFIB_FOR_97:
    fibRgFcLcb97.process_FibRgFcLcb97(baseObj, rglwObj);
    break;
  case NFIB_FOR_2000:
    fibRgFcLcb2000.process_FibRgFcLcb2000(baseObj, rglwObj);
    break;
  case NFIB_FOR_2002:
    fibRgFcLcb2002.process_FibRgFcLcb2002(baseObj, rglwObj);
    break;
  case NFIB_FOR_2003:
    fibRgFcLcb2003.process_FibRgFcLcb2003(baseObj, rglwObj);
    break;
  case NFIB_FOR_2007:
    fibRgFcLcb2007.process_FibRgFcLcb2007(baseObj, rglwObj);
    break;
  }
}

void Fib::FibRgFcLcb::FibRgFcLcb97::process_FibRgFcLcb97(const FibBase &bs, const FibRgLw97 &rglw)
{
  if (lcbStshf == 0)
  {
    throw "lcbShshf must be a non-zero value.";
  }

  if ((rglw.ccpFtn == 0 && lcbPlcffndTxt != 0) ||
      (rglw.ccpFtn != 0 && lcbPlcffndTxt == 0))
  {
    throw "FibRgFcLcb97.lcbPlcffndTxt must be zero when"
      "FibRgLw97.ccpFtn is zero and vice versa.";
  }

  if ((rglw.ccpAtn == 0 && lcbPlcfandTxt != 0) ||
      (rglw.ccpAtn != 0 && lcbPlcfandTxt == 0))
  {
    throw "FibRgFcLcb97.lcbPlcfandTxt must be zero when"
      "FibRgLw97.ccpAtn is zero and vice versa.";
  }

  if (lcbPlcPad != 0)
  {
    throw "FibRgFcLcb97.lcbPlcPad must be zero.";
  }

  if (bs.fGlsy == 0)
  {
    if (lcbSttbfGlsy != 0)
    {
      throw "FibRgFcLcb97.lcbSttbfGlsy must be zero when base.fGlsy is zero";
    }

    if (lcbPlcfGlsy != 0)
    {
      throw "FibRgFcLcb97.lcbPlcfGlsy must be zero when base.fGlsy is zero";
    }

    if (lcbSttbGlsyStyle != 0)
    {
      throw "FibRgFcLcb97.lcbSttbGlsyStyle must be zero when base.fGlsy is zero";
    }
  }
  else
  {
    if (lcbSttbGlsyStyle == 0)
    {
      throw "'FibRgFcLcb97.lcbSttbGlsyStyle' should be non-zero.";
    }
  }

  if (fcPlcfBteChpx <= 0 || lcbPlcfBteChpx <= 0)
  {
    throw "Both fcPlcfBteChpx and lcbPlcfBteChpx of FibRgFcLcb97 must be > 0.";
  }

  if (fcPlcfBtePapx <= 0 || lcbPlcfBtePapx <= 0)
  {
    throw "Both fcPlcfBtePapx and lcbPlcfBtePapx of FibRgFcLcb97 must be > 0.";
  }

  if (lcbPlcfSea != 0)
  {
    throw "'lcbPlcSea' must be zero.";
  }
  
  if (lcbPlcfFldMcr != 0)
  {
    throw "'lcbPlcfFldMcr' must be zero.";
  }

  if (lcbUnused1 != 0)
  {
    throw "'lcbUnused1' must be zero.";
  }

  if (lcbSttbfMcr != 0)
  {
    throw "'lcbSttbfMcr' must be zero.";
  }
  
  if (lcbDop == 0)
  {
    throw "'lcbDop must not be zero.";
  }

  
  if (lcbSttbfAssoc == 0)
  {
    throw "'lcbSttbfAssoc' must not be zero.";
  }
  
  if (lcbClx <= 0)
  {
    throw "'lcbClx' must be greater than ZERO.";
  }

  if (lcbPlcfPgdFtn != 0)
  {
    throw "'lcbPlcfPgdFtn' must be ZERO.";
  }

  if (lcbAutosaveSource != 0)
  {
    throw "'lcbAutosaveSource' must be ZERO.";
  }
  
  if (lcbUnused2 != 0 || lcbUnused3 != 0)
  {
    throw "'lcbUnsed2 /-3 must be ZERO.";
  }
  
  if (lcbFormFldSttbs != 0)
  {
    throw "'lcbFormFldSttbs' must be ZERO.";
  }

  if ((rglw.ccpEdn == 0 && lcbPlcfendTxt != 0) ||
      (rglw.ccpEdn != 0 && lcbPlcfendTxt == 0))
  {
    throw "FibRgFcLcb97.lcbPlcfendTxt must be zero when"
      "FibRgLw97.ccpEdn is zero and vice versa.";
  }

  if (lcbUnused4 != 0)
  {
    throw "'lcbUnused4' must be ZERO.";
  }

  if (bs.fDot == 0)
  {
    if (lcbSttbfCaption != 0)
    {
      throw "'lcbSttbfCaption' must be ZERO when base.fDot is also zero.";
    }

    if (lcbSttbfAutoCaption != 0)
    {
      throw "'lcbSttbfAutoCaption' must be ZERO when base.fDot is also zero.";
    }
  }

  if (rglw.ccpTxbx == 0)
  {
    if (lcbPlcftxbxTxt != 0)
    {
      throw "lcbPlcftxbxTxt' should be ZERO.";
    }

    if (lcbPlcfTxbxBkd != 0)
    {
      throw "'lcbPlcfTxbxBkd should be ZERO.";
    }
  }
  else
  {
    if (lcbPlcftxbxTxt == 0)
    {
      throw "lcbPlcftxbxTxt' should not be ZERO.";
    }

    if (lcbPlcfTxbxBkd == 0)
    {
      throw "'lcbPlcfTxbxBkd should not be ZERO.";
    }
  }
  
  if ((rglw.ccpHdrTxbx == 0 && lcbPlcfHdrtxbxTxt != 0) ||
      (rglw.ccpHdrTxbx != 0 && lcbPlcfHdrtxbxTxt != 0))
  {
    throw "FibRgFcLcb97.lcbPlcfHdrtxbxTxt must be zero when"
      "FibRgLw97.ccpHdrTxbx is zero and vice versa.";
  }

  if (rglw.ccpHdrTxbx == 0)
  {
    if (lcbPlcfHdrtxbxTxt != 0)
    {
      throw "lcbPlcfHdrtxbxTxt' should be ZERO.";
    }

    if (lcbPlcfTxbxHdrBkd != 0)
    {
      throw "lcbPlcfTxbxHdrBkd' should be ZERO.";
    }
  }
  else
  {
    if (lcbPlcfHdrtxbxTxt == 0)
    {
      throw "lcbPlcfHdrtxbxTxt' should not be ZERO.";
    }

    if (lcbPlcfTxbxHdrBkd == 0)
    {
      throw "lcbPlcfTxbxHdrBkd' should be ZERO.";
    }
  }
  
  if (lcbSttbfIntlFld != 0)
  {
    throw "'lcbSttbfIntlFld' must be ZERO.";
  }

  if (bs.nFib > NFIB_FOR_2000)
  {
    if (lcbSttbSavedBy != 0)
    {
      throw "'lcbSttbSavedBy' should be ZERO for tis version of Word";
    }

    if (lcbPlcfLvcPre10 != 0)
    {
      throw "'lcbPlcfLvcPre10' should be ZERO for this version of Word.";
    }
  }

  if (bs.nFib == NFIB_FOR_2007)
  {
    if (lcbPlcfBteLvc != 0)
    {
      throw "'lcbPlcfBteLvc' should be zero in the version of Word.";
    }
  }  
}
 
void Fib::FibRgFcLcb::FibRgFcLcb2000::process_FibRgFcLcb2000(const FibBase &bas, const FibRgLw97 &rgl)
{
  rgFcLcb97.process_FibRgFcLcb97(bas, rgl);

  if (lcbRmdThreading == 0)
  {
    throw "'lcbRmdThreading' must not be ZERO.";
  }
}

void Fib::FibRgFcLcb::FibRgFcLcb2002::process_FibRgFcLcb2002(const FibBase &bs, const FibRgLw97 &rglw)
{
  rgFcLcb2000.process_FibRgFcLcb2000(bs, rglw);

  if (lcbUnused1 != 0)
  {
    throw "; lcbUnused1' must be ZERO.";
  }

  if (bs.nFib < NFIB_FOR_2002)
  {
    if (lcbPlcfpmiOldXP != 0)
    {
      throw "'lcbPlcfpmiOldXP' should be zero for this version of Word.";
    }

    if (lcbPlcfpmiNewXP != 0)
    {
      throw "'lcbPlcfpmiNewXP'should be zero for tis version of Word.";
    }

    if (lcbPlcfpmiMixedXP != 0)
    {
      throw "'lcbPlcfpmiMixedXP' should be zero for this version of Word.";
    }

    if (lcbPlcflvcOldXP != 0)
    {
      throw "'lcbPlcflvcOldXP' should be zero for this version of Word.";
    }

    if (lcbPlcflvcNewXP != 0)
    {
      throw "'lcbPlcflvcNewXP' should be zero for this version of Word.";
    }

    if (lcbPlcflvcMixedXP != 0)
    {
      throw "'lcbPlcflvcMixedXP' should be zero for this version of Word.";
    }
  }

  if (lcbUnused2 != 0)
  {
    throw "'lcbUnused2' should be ZERO.";
  }
}

void Fib::FibRgFcLcb::FibRgFcLcb2003::process_FibRgFcLcb2003(const FibBase& bs, const FibRgLw97 &rglw)
{
  rgFcLcb2002.process_FibRgFcLcb2002(bs, rglw);
  
  if (lcbCustomXForm > 4168
      && lcbCustomXForm % 2 != 0)
  {
    throw "'lcbCustomXForm' must be less than or equal to 4168 & an even number.";
  }

  if (fcUnused != 0 && lcbUnused != 0)
  {
    throw "'fcUnusded' and 'lcbUnused' must be ZERO.";
  }

  if (bs.nFib > NFIB_FOR_2003)
  {
    if (lcbPlcfpmiOld != 0)
    {
      throw "'lcbPlcfpmiOld' should be zero for this version of Word.";
    }

    if (lcbPlcfpmiOldInline != 0)
    {
      throw "'lcbPlcfpmiOldInline' should be zero for this version of Word.";
    }

    if (lcbPlcfpmiNew != 0)
    {
      throw "'lcbPlcfpmiNew' should be zero for this version of Word.";
    }

    if (lcbPlcfpmiNewInline != 0)
    {
      throw "'lcbPlcfpmiNewInline' should be zero for this version of Word.";
    }

    if (lcbPlcflvcOld != 0)
    {
      throw "'lcbPlcflvcOld' should be zero for this version of Word.";
    }

    if (lcbPlcflvcOldInline != 0)
    {
      throw "'lcbPlcflvcOldInline' should be zero for this version of Word.";
    }

    if (lcbPlcflvcNew != 0)
    {
      throw "'lcbPlcflvcNew' should be zero for this version of Word.";
    }

    if (lcbPlcflvcNewInline != 0)
    {
      throw "'lcbPlcflvcNewInline' should be zero for this version of Word.";
    }
  }
}

void Fib::FibRgFcLcb::FibRgFcLcb2007::process_FibRgFcLcb2007(const FibBase &base, const FibRgLw97 &rglw)
{
  rgFcLcb2003.process_FibRgFcLcb2003(base, rglw);
  
  if (lcbPlcfmthd != 0)
  {
    throw "'lcbPlcfmthd' must be zero.";
  }
  
  if (lcbSttbfBkmkMoveFrom != 0)
  {
    throw "'lcbSttbfBkmkMoveFrom' must be zero.";
  }
  
  if (lcbPlcfBkfMoveFrom != 0)
  {
    throw "'lcbPlcfBkfMoveFrom' must be zero.";
  }
  
  if (lcbPlcfBklMoveFrom != 0)
  {
    throw "'lcbPlcfBklMoveFrom' must be zero.";
  }
  
  if (lcbSttbfBkmkMoveTo != 0)
  {
    throw "'lcbSttbfBkmkMoveTo' must be zero.";
  }
  
  if (lcbPlcfBkfMoveTo != 0)
  {
    throw "'lcbPlcfBkfMoveTo' must be zero.";
  }
  
  if (lcbPlcfBklMoveTo != 0)
  {
    throw "'lcbPlcfBklMoveTo' must be zero.";
  }
  
  if (lcbUnused1 != 0)
  {
    throw "'lcbUnused1' must be zero.";
  }
  
  if (lcbUnused2 != 0)
  {
    throw "'lcbUnused2' must be zero.";
  }
  
  if (lcbUnused3 != 0)
    {
    throw "'lcbUnused3' must be zero.";
  }
  
  if (lcbSttbfBkmkArto != 0)
  {
    throw "'lcbSttbfBkmkArto' must be zero.";
  }
  
  if (lcbPlcfBkfArto != 0)
  {
    throw "'lcbPlcfBkfArto' must be zero.";
  }
  
  if (lcbPlcfBklArto != 0)
  {
    throw "'lcbPlcfBklArto' must be zero.";
  }
  
  if (lcbArtoData != 0)
  {
    throw "'lcbArtoData' must be zero.";
  }
  
  if (lcbUnused4 != 0)
  {
    throw "'lcbUnused4' must be zero.";
  }
  
  if (lcbUnused5 != 0)
  {
    throw "'lcbUnused5' must be zero.";
  }
  
  if (lcbUnused6 != 0)
  {
    throw "'lcbUnused6' must be zero.";
  }
}

void Fib::FibRgCswNew::process_FibRgCswNew(const FibBase &obj)
{
  unsigned short ver = obj.nFib;
  if (ver == NFIB_FOR_2000 ||
      (ver == NFIB_FOR_2002) || (ver == NFIB_FOR_2003))
  {
    rgCswNewData.fibRgCswNewData2000.process_FibRgCswNewData2000();
  }
  else if (ver == NFIB_FOR_2007)
  {
    rgCswNewData.fibRgCswNewData2007.process_FibRgCswNewData2007();
  }
}

void Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::process_FibRgCswNewData2000()
{
  if (cQuickSavesNew < 0 || cQuickSavesNew > 0x000F)
  {
    throw "'cQuickSavesNew' should be between 0 and 0x000F, inclusively.";
  }
}

void Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2007::process_FibRgCswNewData2007()
{
  rgCswNewData2000.process_FibRgCswNewData2000();
}

// Assigns values from stream to bit fields
inline unsigned char Fib::assignBits(unsigned char flag, unsigned char temp, int shftRt)
{
  temp &= flag;
  return temp >> shftRt;
}

// Checks which nFib to use for version confirmation
/* inline unsigned short Fib::determine_nFib_use() const
{
  if (cswNew == 0)
  {
    return base.nFib;
  }
  else
  {
    return fibRgCswNew.nFibNew;
  }
} */

// Ignores fields that are not to be read and moves downstream by a given number
inline void Fib::skip_fields(std::ifstream & docustrm, unsigned long numSkipped) const
{
  docustrm.seekg(numSkipped, std::ios::cur);
}

// In the event that the amount of data read for any particular fields is
// (slightly) less than what was expected (per the documentation), this
// function will adjust the file pointer to the tune of the determined
// deficit. This is to ensure that reading of subsequent fields commences
// at the right offset.
// inline void Fib::adjust_file_pointer(std::ifstream& strm, unsigned short gvnSize, unsigned short standard) const
// {
//   if (gvnSize < standard)
//   {
//     const int diff = standard - gvnSize;
//     strm.seekg(diff, std::ios::cur);
//   }
// }

// Checks to confirm that the capacity assigned to a struct matches the expected value.
  // It may be recalled that the 'unsigned short' fields hold a value which, when multiplied by a 
  // specified value is supposed to equate the size in memory of the said struct.
// template <class T>
// unsigned short Fib::computeStructSize(const unsigned short cbValue, const unsigned short expValue, const in
// 			      t multiplier) const
// {
//   unsigned short cbSize = { };
//   if (cbValue == expValue)
//   {
//     cbSize = cbValue * multiplier;
//   }
//   return cbSize;
// }
