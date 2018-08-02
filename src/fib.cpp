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
#include <fstream>
#include <iostream>
#include <cassert>

constexpr USHORT WORD_BINARY_FILE = 0xA5EC;

constexpr USHORT NFIB_FOR_97   = 0x00C1;
constexpr USHORT NFIB_FOR_2000 = 0x00D9;
constexpr USHORT NFIB_FOR_2002 = 0x0101;
constexpr USHORT NFIB_FOR_2003 = 0x010C;
constexpr USHORT NFIB_FOR_2007 = 0x0112;
constexpr USHORT NFIB_SPECIAL  = 0x00C0;
constexpr USHORT NFIB_BIDI_BLD = 0x00C2;

constexpr USHORT EXPECTED_CSW             = 0x000E;
constexpr USHORT EXPECTED_CSLW            = 0x0016;

constexpr USHORT EXPECTED_CBRGFCLCB_97    = 0x005D;
constexpr USHORT EXPECTED_CBRGFCLCB_2000  = 0x006C;
constexpr USHORT EXPECTED_CBRGFCLCB_2002  = 0x0088;
constexpr USHORT EXPECTED_CBRGFCLCB_2003  = 0x00A4;
constexpr USHORT EXPECTED_CBRGFCLCB_2007  = 0x00B7;

constexpr USHORT EXPECTED_CSWNEW_97       = 0x0000;
constexpr USHORT EXPECTED_CSWNEW_2000     = 0x0002;
constexpr USHORT EXPECTED_CSWNEW_2002     = 0x0002;
constexpr USHORT EXPECTED_CSWNEW_2003     = 0x0002;
constexpr USHORT EXPECTED_CSWNEW_2007     = 0x0005;

constexpr USHORT MULTIPLIER_FOR_CSW        = 16 / 8;
constexpr USHORT MULTIPLIER_FOR_CSLW       = 32 / 8;
constexpr USHORT MULTIPLIER_FOR_CBRGFCLCB  = 64 / 8;
constexpr USHORT MULTIPLIER_FOR_CSWNEW     = 16 / 8;

// LID values (Language Code)
// as specified by ECMA 376 Part 4 section 2.18.52
constexpr USHORT ARABIC_SAUDI_ARABIA             = 1025;
constexpr USHORT BULGARIAN                       = 1026;
constexpr USHORT CATALAN                         = 1027;
constexpr USHORT CHINESE_TAIWAN                  = 1028;
constexpr USHORT CZECH                           = 1029;
constexpr USHORT DANISH                          = 1030;
constexpr USHORT GERMAN_GERMANY                  = 1031;
constexpr USHORT GREEK                           = 1032;
constexpr USHORT ENGLISH_UNITED_STATES           = 1033;
constexpr USHORT SPANISH_SPAIN_TRADITIONAL       = 1034;
constexpr USHORT FINNISH                         = 1035;
constexpr USHORT FRENCH_FRANCE                   = 1036;
constexpr USHORT HEBREW                          = 1037;
constexpr USHORT HUNGARIAN                       = 1038;
constexpr USHORT ICELANDIC                       = 1039;
constexpr USHORT ITALIAN_ITALY                   = 1040;
constexpr USHORT JAPANESE                        = 1041;
constexpr USHORT KOREAN                          = 1042;
constexpr USHORT DUTCH_NETHERLANDS               = 1043;
constexpr USHORT NORWEGIAN_BOKMAL                = 1044;
constexpr USHORT POLISH                          = 1045;
constexpr USHORT PORTUGUESE_BRAZIL               = 1046;
constexpr USHORT RHAETO_ROMANIC                  = 1047;
constexpr USHORT ROMANIAN                        = 1048;
constexpr USHORT RUSSIAN                         = 1049;
constexpr USHORT CROATIAN                        = 1050;
constexpr USHORT SLOVAK                          = 1051;
constexpr USHORT ALBANIAN_ALBANIA                = 1052;
constexpr USHORT SWEDISH                         = 1053;
constexpr USHORT THAI                            = 1054;
constexpr USHORT TURKISH                         = 1055;
constexpr USHORT URDU                            = 1056;
constexpr USHORT INDONESIAN                      = 1057;
constexpr USHORT UKRAINIAN                       = 1058;
constexpr USHORT BELARUSIAN                      = 1059;
constexpr USHORT SLOVENIAN                       = 1060;
constexpr USHORT ESTONIAN                        = 1061;
constexpr USHORT LATVIAN                         = 1062;
constexpr USHORT LITHUANIAN                      = 1063;
constexpr USHORT TAJIK                           = 1064;
constexpr USHORT FARSI                           = 1065;
constexpr USHORT VIETNAMESE                      = 1066;
constexpr USHORT ARMENIAN_ARMENIA                = 1067;
constexpr USHORT AZERI_LATIN                     = 1068;
constexpr USHORT BASQUE                          = 1069;
constexpr USHORT SORBIAN                         = 1070;
constexpr USHORT FYRO_MACEDONIAN                 = 1071;
constexpr USHORT SUTU                            = 1072;
constexpr USHORT TSONGA                          = 1073;
constexpr USHORT TSWANA                          = 1074;
constexpr USHORT VENDA                           = 1075;
constexpr USHORT XHOSA                           = 1076;
constexpr USHORT ZULU                            = 1077;
constexpr USHORT AFRIKAANS_SOUTH_AFRICA          = 1078;
constexpr USHORT GEORGIAN                        = 1079;
constexpr USHORT FAROESE                         = 1080;
constexpr USHORT HINDI                           = 1081;
constexpr USHORT MALTESE                         = 1082;
constexpr USHORT SAMI_LAPPISH                    = 1083;
constexpr USHORT GAELIC_SCOTLAND                 = 1084;
constexpr USHORT YIDDISH                         = 1085;
constexpr USHORT MALAY_MALAYSIA                  = 1086;
constexpr USHORT KAZAKH                          = 1087;
constexpr USHORT KYRGYZ_CYRILLIC                 = 1088;
constexpr USHORT SWAHILI                         = 1089;
constexpr USHORT TURKMEN                         = 1090;
constexpr USHORT UZBEK_LATIN                     = 1091;
constexpr USHORT TATAR                           = 1092;
constexpr USHORT BENGALI_INDIA                   = 1093;
constexpr USHORT PUNJABI                         = 1094;
constexpr USHORT GUJARATI                        = 1124;
constexpr USHORT DIVEHI                          = 1125;
constexpr USHORT EDO                             = 1126;
constexpr USHORT FULFULDE_NIGERIA                = 1127;
constexpr USHORT HAUSA_NIGERIA                   = 1128;
constexpr USHORT IBIBIO_NIGERIA                  = 1129;
constexpr USHORT YORUBA                          = 1130;
constexpr USHORT QUECHA_BOLIVIA                  = 1131;
constexpr USHORT SEPEDI                          = 1132;
constexpr USHORT IGBO_NIGERIA                    = 1136;
constexpr USHORT KANURI_NIGERIA                  = 1137;
constexpr USHORT OROMO                           = 1138;
constexpr USHORT TIGRIGNA_ETHIOPIA               = 1139;
constexpr USHORT GUARANI_PARAGUAY                = 1140;
constexpr USHORT HAWAIIAN_UNITED_STATES          = 1141;
constexpr USHORT LATIN                           = 1142;
constexpr USHORT SOMALI                          = 1143;
constexpr USHORT YI                              = 1144;
constexpr USHORT PAPIAMENTU                      = 1145;
constexpr USHORT UIGHUR_CHINA                    = 1152;
constexpr USHORT MAORI_NEW_ZEALAND               = 1153;
constexpr USHORT HID_HUMAN_INTERFACE_DEVICE      = 1279;
constexpr USHORT ARABIC_IRAQ                     = 2049;
constexpr USHORT CHINESE_PEOPLES_REPUBLIC_CHINA  = 2052;
constexpr USHORT GERMAN_SWITZERLAND              = 2055;
constexpr USHORT ENGLISH_UNITED_KINGDOM          = 2057;
constexpr USHORT SPANISH_MEXICO                  = 2058;
constexpr USHORT FRENCH_BELGIUM                  = 2060;
constexpr USHORT ITALIAN_SWITZERLAND             = 2064;
constexpr USHORT DUTCH_BELGIUM                   = 2067;
constexpr USHORT NORWEGIAN_NYNORSK               = 2068;
constexpr USHORT PORTUGUESE_PORTUGAL             = 2070;
constexpr USHORT ROMANIAN_MOLDAVA                = 2072;
constexpr USHORT RUSSIAN_MOLDAVA                 = 2073;
constexpr USHORT SERBIAN_LATIN                   = 2074;
constexpr USHORT SWEDISH_FINLAND                 = 2077;
constexpr USHORT URDU_INDIA                      = 2080;
constexpr USHORT AZERI_CYRILLIC                  = 2092;
constexpr USHORT GAELIC_IRELAND                  = 2108;
constexpr USHORT MALAY_BRUNEI_DARUSSALAM         = 2110;
constexpr USHORT UZBEK_CYRILLIC                  = 2115;
constexpr USHORT BENGALI_BANGLADESH              = 2117;
constexpr USHORT PUNJABI_PAKISTAN                = 2118;
constexpr USHORT MONGOLIAN_MONGOLIAN             = 2128;
constexpr USHORT TIBETAN_BHUTAN                  = 2129;
constexpr USHORT SINDHI_PAKISTAN                 = 2137;
constexpr USHORT TAMAZIGHT_LATIN                 = 2143;
constexpr USHORT KASHMIRI                        = 2144;
constexpr USHORT NEPALI_INDIA                    = 2145;
constexpr USHORT QUECHA_ECUADOR                  = 2155;
constexpr USHORT TIGRIGNA_ERITREA                = 2163;
constexpr USHORT ARABIC_EGYPT                    = 3073;
constexpr USHORT CHINESE_HONG_KONG_SAR		 = 3076;
constexpr USHORT GERMAN_AUSTRIA                  = 3079;
constexpr USHORT ENGLISH_AUSTRALIA               = 3081;
constexpr USHORT SPANISH_SPAIN_MODERN		 = 3082;
constexpr USHORT FRENCH_CANADA                   = 3084;
constexpr USHORT SERBIAN_CYRILLIC                = 3098;
constexpr USHORT QUECHA_PERU                     = 3179;
constexpr USHORT ARABIC_LIBYA                    = 4097;
constexpr USHORT CHINESE_SINGAPORE               = 4100;
constexpr USHORT GERMAN_LUXEMBOURG               = 4103;
constexpr USHORT ENGLISH_CANADA                  = 4105;
constexpr USHORT SPANISH_GUATEMALA               = 4106;
constexpr USHORT FRENCH_SWITZERLAND              = 4108;
constexpr USHORT CROATIAN_BOSNIA_HERZEGOVINA     = 4122;
constexpr USHORT ARABIC_ALGERIA                  = 5121;
constexpr USHORT CHINESE_MACAO_SAR               = 5124;
constexpr USHORT GERMAN_LIECHTENSTEIN            = 5127;
constexpr USHORT ENGLISH_NEW_ZEALAND             = 5129;
constexpr USHORT SPANISH_COSTA_RICA              = 5130;
constexpr USHORT FRENCH_LUXEMBOURG               = 5132;
constexpr USHORT BOSNIAN_BOSNIA_HERZEGOVINA      = 5146;
constexpr USHORT ARABIC_MOROCCO                  = 6145;
constexpr USHORT ENGLISH_IRELAND                 = 6153;
constexpr USHORT SPANISH_PANAMA                  = 6154;
constexpr USHORT FRENCH_MONACO                   = 6156;
constexpr USHORT ARABIC_TUNISIA                  = 7169;
constexpr USHORT ENGLISH_SOUTH_AFRICA            = 7177;
constexpr USHORT SPANISH_DOMINICAN_REPUBLIC      = 7178;
constexpr USHORT FRENCH_WEST_INDIES              = 7180;
constexpr USHORT ARABIC_OMAN                     = 8193;
constexpr USHORT ENGLISH_JAMAICA                 = 8201;
constexpr USHORT SPANISH_VENEZUELA               = 8202;
constexpr USHORT FRENCH_REUNION                  = 8204;
constexpr USHORT ARABIC_YEMEN                    = 9217;
constexpr USHORT ENGLISH_CARIBBEAN               = 9225;
constexpr USHORT SPANISH_COLOMBIA                = 9226;
constexpr USHORT FRENCH_DEMOCRATIC_REP_OF_CONGO	 = 9228;
constexpr USHORT ARABIC_SYRIA                    = 10241;
constexpr USHORT ENGLISH_BELIZE                  = 10249;
constexpr USHORT SPANISH_PERU                    = 10250;
constexpr USHORT FRENCH_SENEGAL                  = 10252;
constexpr USHORT ARABIC_JORDAN                   = 11265;
constexpr USHORT ENGLISH_TRINIDAD                = 11273;
constexpr USHORT SPANISH_ARGENTINA               = 11274;
constexpr USHORT FRENCH_CAMEROON                 = 11276;
constexpr USHORT ARABIC_LEBANON                  = 12289;
constexpr USHORT ENGLISH_ZIMBABWE                = 12297;
constexpr USHORT SPANISH_ECUADOR                 = 12298;
constexpr USHORT FRENCH_COTE_DIVOIRE             = 12300;
constexpr USHORT ARABIC_KUWAIT                   = 13313;
constexpr USHORT ENGLISH_PHILIPPINES             = 13321;
constexpr USHORT SPANISH_CHILE                   = 13322;
constexpr USHORT FRENCH_MALI                     = 13324;
constexpr USHORT ARABIC_UAE                      = 14337;
constexpr USHORT ENGLISH_INDONESIA               = 14345;
constexpr USHORT SPANISH_URUGUAY                 = 14346;
constexpr USHORT FRENCH_MOROCCO                  = 14348;
constexpr USHORT ARABIC_BAHRAIN                  = 15361;
constexpr USHORT ENGLISH_HONG_KONG_SAR		       = 15369;
constexpr USHORT SPANISH_PARAGUAY                = 15370;
constexpr USHORT FRENCH_HAITI                    = 15372;
constexpr USHORT ARABIC_QATAR                    = 16385;
constexpr USHORT ENGLISH_INDIA                   = 16393;
constexpr USHORT SPANISH_BOLIVIA                 = 16394;
constexpr USHORT ENGLISH_MALAYSIA                = 17417;
constexpr USHORT SPANISH_EL_SALVADOR             = 17418;
constexpr USHORT ENGLISH_SINGAPORE               = 18441;
constexpr USHORT SPANISH_HONDURAS                = 18442;
constexpr USHORT SPANISH_NICARAGUA               = 19466;
constexpr USHORT SPANISH_PUERTO_RICO             = 20490;
constexpr USHORT SPANISH_UNITED_STATES           = 21514;
constexpr USHORT SPANISH_LATIN_AMERICA           = 58378;
constexpr USHORT FRENCH_NORTH_AFRICA             = 58380;

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
  fcDocUndoUSHORT9	= { };
  lcbDocUndoUSHORT9	= { };
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
VOID Fib::read_Fib(std::ifstream &docstream)
{
  base.read_FibBase(docstream);  
  docstream.read(reinterpret_cast<char *>(&csw), sizeof(USHORT));
  fibRgW.read_FibRgW(docstream);
  docstream.read(reinterpret_cast<char *>(&cslw), sizeof(USHORT));
  fibRgLw.read_FibRgLw(docstream);
  docstream.read(reinterpret_cast<char *>(&cbRgFcLcb), sizeof(USHORT));
  fibRgFcLcbBlob.read_FibRgFcLcbBlob(docstream, cbRgFcLcb);
  docstream.read(reinterpret_cast<char *>(&cswNew), sizeof(USHORT));
  fibRgCswNew.read_FibRgCswNew(docstream, cswNew);
  if (cswNew != EXPECTED_CSWNEW_97)
  {
    base.nFib = fibRgCswNew.nFibNew;
  }
}

// Reads the FibBase from the WordDocument Stream
// Those parts that are bit fields are extracted using
// bit masks and other relevant constructs
VOID Fib::FibBase::read_FibBase(std::ifstream &docfile)
{
  docfile.read(reinterpret_cast<char *>(&wIdent), sizeof(USHORT));
  docfile.read(reinterpret_cast<char *>(&nFib), sizeof(USHORT));
  if (nFib == NFIB_SPECIAL || nFib == NFIB_BIDI_BLD)
  {
    nFib = NFIB_FOR_97;
  }

  docfile.read(reinterpret_cast<char *>(&unused), sizeof(USHORT));
  docfile.read(reinterpret_cast<char *>(&lid), sizeof(USHORT));
  docfile.read(reinterpret_cast<char *>(&pnNext), sizeof(USHORT));

  BYTE		tmp = 0x0;
  const BYTE	fD  = 0x1;
  const BYTE	fG  = 0x2;
  const BYTE	fC  = 0x4;
  const BYTE	fHP = 0x8;
  BYTE		msk = 0x0F;

  docfile.read(reinterpret_cast<char *>(&tmp), sizeof(BYTE));
  fDot	      = assignBits(fD, tmp, 0);
  fGlsy	      = assignBits(fG, tmp, 1);
  fComplex    = assignBits(fC, tmp, 2);
  fHasPic     = assignBits(fHP, tmp, 3);
  tmp >>= 4;
  cQuickSaves = tmp & msk;

  const BYTE fE	   = 0x1;
  const BYTE fWT   = 0x2;
  const BYTE fROR  = 0x4;
  const BYTE fWR   = 0x8;
  const BYTE fEC   = 0x10;
  const BYTE fLO   = 0x20;
  const BYTE fFE   = 0x40;
  const BYTE fO	   = 0x80;
  docfile.read(reinterpret_cast<char *>(&tmp), sizeof(BYTE));
  fEncrypted            = assignBits(fE, tmp, 0);
  fWhichTblStm          = assignBits(fWT, tmp, 1);
  fReadOnlyRecommended	= assignBits(fROR, tmp, 2);
  fWriteReservation     = assignBits(fWR, tmp, 3);
  fExtChar              = assignBits(fEC, tmp, 4);
  fLoadOverride         = assignBits(fLO, tmp, 5);
  fFarEast              = assignBits(fFE, tmp, 6);
  fObfuscated           = assignBits(fO, tmp, 7);

  docfile.read(reinterpret_cast<char *>(&nFibBack), sizeof(USHORT));
  docfile.read(reinterpret_cast<char *>(&lkey), sizeof(ULONG));
  docfile.read(reinterpret_cast<char *>(&envr), sizeof(BYTE));

  const BYTE fM	  = 0x1;
  const BYTE fES  = 0x2;
  const BYTE fLOP = 0x4;
  const BYTE res1 = 0x8;
  const BYTE res2 = 0x10;
  msk = 0x9;
  docfile.read(reinterpret_cast<char *>(&tmp), sizeof(BYTE));
  fMac              = assignBits(fM, tmp, 0);
  fEmptySpecial     = assignBits(fES, tmp, 1);
  fLoadOverridePage = assignBits(fLOP, tmp, 2);
  reserved1         = assignBits(res1, tmp, 3);
  reserved2         = assignBits(res2, tmp, 4);
  tmp >>= 5;
  fSpare0 = tmp & msk;

  docfile.read(reinterpret_cast<char *>(&reserved3), sizeof(USHORT));
  docfile.read(reinterpret_cast<char *>(&reserved4), sizeof(USHORT));
  docfile.read(reinterpret_cast<char *>(&reserved5), sizeof(ULONG));
  docfile.read(reinterpret_cast<char *>(&reserved6), sizeof(ULONG));
}

VOID Fib::FibRgLw97::read_FibRgLw(std::ifstream & mystream)
{ // TODO: Clean this thing up!
  USHORT add_member_sizes = 0;   // What on earth was I thinking???

  mystream.read(reinterpret_cast<char *>(&cbMac), sizeof(ULONG));
  add_member_sizes += sizeof(cbMac);  // these lines! What the heck?
  mystream.read(reinterpret_cast<char *>(&reserved1), sizeof(ULONG));
  add_member_sizes += sizeof(reserved1);
  mystream.read(reinterpret_cast<char *>(&reserved2), sizeof(ULONG));
  add_member_sizes += sizeof(reserved2);
  mystream.read(reinterpret_cast<char *>(&ccpText), sizeof(ULONG));
  add_member_sizes += sizeof(ccpText);
  mystream.read(reinterpret_cast<char *>(&ccpFtn), sizeof(ULONG));
  add_member_sizes += sizeof(ccpFtn);
  mystream.read(reinterpret_cast<char *>(&ccpHdd), sizeof(ULONG));
  add_member_sizes += sizeof(ccpHdd);
  mystream.read(reinterpret_cast<char *>(&reserved3), sizeof(ULONG));
  add_member_sizes += sizeof(reserved3);
  mystream.read(reinterpret_cast<char *>(&ccpAtn), sizeof(ULONG));
  add_member_sizes += sizeof(ccpAtn);
  mystream.read(reinterpret_cast<char *>(&ccpEdn), sizeof(ULONG));
  add_member_sizes += sizeof(ccpEdn);
  mystream.read(reinterpret_cast<char *>(&ccpTxbx), sizeof(ULONG));
  add_member_sizes += sizeof(ccpTxbx);
  mystream.read(reinterpret_cast<char *>(&ccpHdrTxbx), sizeof(ULONG));
  add_member_sizes += sizeof(ccpHdrTxbx);
  mystream.read(reinterpret_cast<char *>(&reserved4), sizeof(ULONG));
  add_member_sizes += sizeof(reserved4);
  mystream.read(reinterpret_cast<char *>(&reserved5), sizeof(ULONG));
  add_member_sizes += sizeof(reserved5);
  mystream.read(reinterpret_cast<char *>(&reserved6), sizeof(ULONG));
  add_member_sizes += sizeof(reserved6);
  mystream.read(reinterpret_cast<char *>(&reserved7), sizeof(ULONG));
  add_member_sizes += sizeof(reserved7);
  mystream.read(reinterpret_cast<char *>(&reserved8), sizeof(ULONG));
  add_member_sizes += sizeof(reserved8);
  mystream.read(reinterpret_cast<char *>(&reserved9), sizeof(ULONG));
  add_member_sizes += sizeof(reserved9);
  mystream.read(reinterpret_cast<char *>(&reserved10), sizeof(ULONG));
  add_member_sizes += sizeof(reserved10);
  mystream.read(reinterpret_cast<char *>(&reserved11), sizeof(ULONG));
  add_member_sizes += sizeof(reserved11);
  mystream.read(reinterpret_cast<char *>(&reserved12), sizeof(ULONG));
  add_member_sizes += sizeof(reserved12);
  mystream.read(reinterpret_cast<char *>(&reserved13), sizeof(ULONG));
  add_member_sizes += sizeof(reserved13);
  mystream.read(reinterpret_cast<char *>(&reserved14), sizeof(ULONG));
  add_member_sizes += sizeof(reserved14);
}

VOID Fib::FibRgW97::read_FibRgW(std::ifstream & filestrm)
{
  filestrm.read(reinterpret_cast<char *>(&reserved1), sizeof(USHORT));
  filestrm.read(reinterpret_cast<char *>(&reserved2), sizeof(USHORT));
  filestrm.read(reinterpret_cast<char *>(&reserved3), sizeof(USHORT));
  filestrm.read(reinterpret_cast<char *>(&reserved4), sizeof(USHORT));
  filestrm.read(reinterpret_cast<char *>(&reserved5), sizeof(USHORT));
  filestrm.read(reinterpret_cast<char *>(&reserved6), sizeof(USHORT));
  filestrm.read(reinterpret_cast<char *>(&reserved7), sizeof(USHORT));
  filestrm.read(reinterpret_cast<char *>(&reserved8), sizeof(USHORT));
  filestrm.read(reinterpret_cast<char *>(&reserved9), sizeof(USHORT));
  filestrm.read(reinterpret_cast<char *>(&reserved10), sizeof(USHORT));
  filestrm.read(reinterpret_cast<char *>(&reserved11), sizeof(USHORT));
  filestrm.read(reinterpret_cast<char *>(&reserved12), sizeof(USHORT));
  filestrm.read(reinterpret_cast<char *>(&reserved13), sizeof(USHORT));
  filestrm.read(reinterpret_cast<char *>(&lidFE), sizeof(USHORT));
}

// Reads the value of a part of the FIB that varies in content and structure
  // with different versions of Word (97 - 2007). The nFib (a member of the FibBase
  // data structure) is what determines which version is used.
VOID Fib::FibRgFcLcb::read_FibRgFcLcbBlob(std::ifstream& flStream, const USHORT newVer)
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

VOID Fib::FibRgFcLcb::FibRgFcLcb97::read_FibRgFcLcb97(std::ifstream & mainstrm)
{
  mainstrm.read(reinterpret_cast<char *>(&fcStshfOrig), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbStshfOrig), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcStshf), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbStshf), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcffndRef), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcffndRef), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcffndTxt), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcffndTxt), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfandRef), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfandRef), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfandTxt), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfandTxt), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfSed), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfSed), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcPad), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcPad), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfPhe), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfPhe), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfGlsy), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfGlsy), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfGlsy), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfGlsy), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfHdd), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfHdd), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfBteChpx), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBteChpx), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfBtePapx), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBtePapx), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfSea), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfSea), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfFfn), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfFfn), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldMom), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldMom), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldHdr), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldHdr), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldFtn), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldFtn), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldAtn), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldAtn), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldMcr), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldMcr), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfBkmk), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfBkmk), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfBkf), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBkf), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfBkl), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBkl), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcCmds), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbCmds), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcUnused1), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbUnused1), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfMcr), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfMcr), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPrDrvr), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPrDrvr), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPrEnvPort), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPrEnvPort), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPrEnvLand), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPrEnvLand), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcWss), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbWss), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcDop), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbDop), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfAssoc), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfAssoc), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcClx), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbClx), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfPgdFtn), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfPgdFtn), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcAutosaveSource), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbAutosaveSource), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcGrpXstAtnOwners), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbGrpXstAtnOwners), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfAtnBkmk), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfAtnBkmk), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcUnused2), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbUnused2), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcUnused3), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbUnused3), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcSpaMom), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcSpaMom), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcSpaHdr), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcSpaHdr), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfAtnBkf), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfAtnBkf), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfAtnBkl), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfAtnBkl), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPms), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPms), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcFormFldSttbs), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbFormFldSttbs), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfendRef), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfendRef), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfendTxt), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfendTxt), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldEdn), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldEdn), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcUnused4), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbUnused4), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcDggInfo), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbDggInfo), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfRMark), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfRMark), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfCaption), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfCaption), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfAutoCaption), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfAutoCaption), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfWkb), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfWkb), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfSpl), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfSpl), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcftxbxTxt), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcftxbxTxt), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfFldTxbx), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfFldTxbx), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfHdrtxbxTxt), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfHdrtxbxTxt), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcffldHdrTxbx), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcffldHdrTxbx), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcStwUser), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbStwUser), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbTtmbd), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbTtmbd), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcCookieData), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbCookieData), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPgdMotherOldOld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPgdMotherOldOld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcBkdMotherOldOld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbBkdMotherOldOld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPgdFtnOldOld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPgdFtnOldOld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcBkdFtnOldOld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbBkdFtnOldOld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPgdEdnOldOld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPgdEdnOldOld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcBkdEdnOldOld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbBkdEdnOldOld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfIntlFld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfIntlFld), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcRouteSlip), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbRouteSlip), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbSavedBy), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbSavedBy), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbFnm), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbFnm), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlfLst), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlfLst), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlfLfo), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlfLfo), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfTxbxBkd), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfTxbxBkd), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfTxbxHdrBkd), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfTxbxHdrBkd), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcDocUndoUSHORT9), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbDocUndoUSHORT9), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcRgbUse), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbRgbUse), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcUsp), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbUsp), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcUskf), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbUskf), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcupcRgbUse), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcupcRgbUse), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcupcUsp), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcupcUsp), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbGlsyStyle), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbGlsyStyle), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlgosl), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlgosl), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcocx), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcocx), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfBteLvc), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfBteLvc), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&dwLowDateTime), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&dwHighDateTime), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfLvcPre10), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfLvcPre10), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfAsumy), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfAsumy), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcPlcfGram), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbPlcfGram), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbListNames), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbListNames), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&fcSttbfUssr), sizeof(ULONG));
  mainstrm.read(reinterpret_cast<char *>(&lcbSttbfUssr), sizeof(ULONG));
}

VOID Fib::FibRgFcLcb::FibRgFcLcb2000::read_FibRgFcLcb2000(std::ifstream & wrdfile)
{
  rgFcLcb97.read_FibRgFcLcb97(wrdfile);
  
  wrdfile.read(reinterpret_cast<char *>(&fcPlcfTch), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbPlcfTch), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcRmdThreading), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbRmdThreading), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcMid), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbMid), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcSttbRgtplc), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbSttbRgtplc), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcMsoEnvelope), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbMsoEnvelope), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcPlcfLad), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbPlcfLad), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcRgDofr), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbRgDofr), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcPlcosl), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbPlcosl), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcPlcfCookieOld), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbPlcfCookieOld), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcPgdMotherOld), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbPgdMotherOld), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcBkdMotherOld), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbBkdMotherOld), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcPgdFtnOld), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbPgdFtnOld), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcBkdFtnOld), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbBkdFtnOld), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcPgdEdnOld), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbPgdEdnOld), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&fcBkdEdnOld), sizeof(ULONG));
  wrdfile.read(reinterpret_cast<char *>(&lcbBkdEdnOld), sizeof(ULONG));
}


VOID Fib::FibRgFcLcb::FibRgFcLcb2002::read_FibRgFcLcb2002(std::ifstream &documentStr)
{
  rgFcLcb2000.read_FibRgFcLcb2000(documentStr);

  documentStr.read(reinterpret_cast<char *>(&fcUnused1), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbUnused1), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfPgp), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfPgp), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfuim), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfuim), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlfguidUim), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlfguidUim), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcAtrdExtra), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbAtrdExtra), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlrsid), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlrsid), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcSttbfBkmkFactoid), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbSttbfBkmkFactoid), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfBkfFactoid), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfBkfFactoid), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfcookie), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfcookie), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfBklFactoid), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfBklFactoid), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcFactoidData), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbFactoidData), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcDocUndo), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbDocUndo), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcSttbfBkmkFcc), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbSttbfBkmkFcc), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfBkfFcc), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfBkfFcc), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfBklFcc), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfBklFcc), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcSttbfbkmkBPRepairs), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbSttbfbkmkBPRepairs), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfbkfBPRepairs), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfbkfBPRepairs), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfbklBPRepairs), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfbklBPRepairs), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPmsNew), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPmsNew), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcODSO), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbODSO), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfpmiOldXP), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfpmiOldXP), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfpmiNewXP), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfpmiNewXP), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcfpmiMixedXP), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcfpmiMixedXP), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcUnused2), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbUnused2), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcffactoid), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcffactoid), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcflvcOldXP), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcflvcOldXP), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcflvcNewXP), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcflvcNewXP), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&fcPlcflvcMixedXP), sizeof(ULONG));
  documentStr.read(reinterpret_cast<char *>(&lcbPlcflvcMixedXP), sizeof(ULONG));
}


VOID Fib::FibRgFcLcb::FibRgFcLcb2003::read_FibRgFcLcb2003(std::ifstream & dotdocstrm)
{  
  rgFcLcb2002.read_FibRgFcLcb2002(dotdocstrm);

  dotdocstrm.read(reinterpret_cast<char *>(&fcHplxsdr), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbHplxsdr), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcSttbfBkmkSdt), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbSttbfBkmkSdt), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfBkfSdt), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfBkfSdt), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfBklSdt), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfBklSdt), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcCustomXForm), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbCustomXForm), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcSttbfBkmkProt), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbSttbfBkmkProt), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfBkfProt), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfBkfProt), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfBklProt), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfBklProt), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcSttbProtUser), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbSttbProtUser), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcUnused), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbUnused), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfpmiOld), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfpmiOld), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfpmiOldInline), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfpmiOldInline), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfpmiNew), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfpmiNew), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcfpmiNewInline), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcfpmiNewInline), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcflvcOld), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcflvcOld), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcflvcOldInline), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcflvcOldInline), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcflvcNew), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcflvcNew), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPlcflvcNewInline), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPlcflvcNewInline), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPgdMother), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPgdMother), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcBkdMother), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbBkdMother), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcAfdMother), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbAfdMother), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPgdFtn), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPgdFtn), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcBkdFtn), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbBkdFtn), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcAfdFtn), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbAfdFtn), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcPgdEdn), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbPgdEdn), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcBkdEdn), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbBkdEdn), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcAfdEdn), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbAfdEdn), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&fcAfd), sizeof(ULONG));
  dotdocstrm.read(reinterpret_cast<char *>(&lcbAfd), sizeof(ULONG));
}

VOID Fib::FibRgFcLcb::FibRgFcLcb2007::read_FibRgFcLcb2007(std::ifstream & dStream)
{  
  rgFcLcb2003.read_FibRgFcLcb2003(dStream);

  dStream.read(reinterpret_cast<char *>(&fcPlcfmthd), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfmthd), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcSttbfBkmkMoveFrom), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbSttbfBkmkMoveFrom), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcPlcfBkfMoveFrom), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfBkfMoveFrom), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcPlcfBklMoveFrom), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfBklMoveFrom), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcSttbfBkmkMoveTo), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbSttbfBkmkMoveTo), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcPlcfBkfMoveTo), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfBkfMoveTo), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcPlcfBklMoveTo), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfBklMoveTo), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcUnused1), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbUnused1), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcUnused2), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbUnused2), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcUnused3), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbUnused3), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcSttbfBkmkArto), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbSttbfBkmkArto), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcPlcfBkfArto), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfBkfArto), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcPlcfBklArto), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbPlcfBklArto), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcArtoData), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbArtoData), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcUnused4), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbUnused4), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcUnused5), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbUnused5), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcUnused6), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbUnused6), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcOssTheme), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbOssTheme), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&fcColorSchemeMapping), sizeof(ULONG));
  dStream.read(reinterpret_cast<char *>(&lcbColorSchemeMapping), sizeof(ULONG));
}

// Reads an FibRgCswNew, using the current version of Word (97 -2007) to
// select the appropriate data structure to read into memory, whilst
// returning the size of data read for use in subsequent methods
VOID Fib::FibRgCswNew::read_FibRgCswNew(std::ifstream& stream, const USHORT cswNewVal)
{
  if (cswNewVal == EXPECTED_CSWNEW_97)
  {
    std::cout << "This version does not have the 'FibRgCswNew' structure.\n";
  }
  else
  {
    stream.read(reinterpret_cast<char *>(&nFibNew), sizeof(USHORT));
    rgCswNewData.read_FibRgCswNewData(stream, cswNewVal);
  }
}

// Reads from FibRgCswNewData structure, but what exactly is read depends
// on the verion of Word. This version is determined by the 2nd argument
// This function will return the size of the dat structure that was read
VOID Fib::FibRgCswNew::FibRgCswNewData::read_FibRgCswNewData(std::ifstream& filestrm, const USHORT cswVer)
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

VOID Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::read_2000(std::ifstream & instream)
{
  instream.read(reinterpret_cast<char *>(&cQuickSavesNew), sizeof(USHORT));
}

VOID Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2007::read_2007(std::ifstream & streamin)
{
  FibRgCswNewData2000 newdat2000;
  newdat2000.read_2000(streamin);

  streamin.read(reinterpret_cast<char *>(&lidThemeOther), sizeof(USHORT));
  streamin.read(reinterpret_cast<char *>(&lidThemeFE), sizeof(USHORT));
  streamin.read(reinterpret_cast<char *>(&lidThemeCS), sizeof(USHORT));
}

// Inspects the entire data read into the in-memory copy of the
// main data structures that represent the File Information Block.
// Where appropriate, minor adjustments are to be made
VOID Fib::inspectFibStructs()
{
  base.process_FibBase();
  fibRgW.process_FibRgW97();
  fibRgLw.process_FibRgLw97();
  fibRgFcLcbBlob.process_FibRgFcLcbBlob(base, fibRgLw);
  fibRgCswNew.process_FibRgCswNew(base);
}

// Screens the members of FibBase to make sure all conditions are met
VOID Fib::FibBase::process_FibBase()
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

VOID Fib::FibRgW97::process_FibRgW97()
{
}
 
VOID Fib::FibRgLw97::process_FibRgLw97()
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

VOID Fib::FibRgFcLcb::process_FibRgFcLcbBlob(const FibBase &baseObj, const FibRgLw97 &rglwObj)
{
  USHORT version = baseObj.nFib;
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

VOID Fib::FibRgFcLcb::FibRgFcLcb97::process_FibRgFcLcb97(const FibBase &bs, const FibRgLw97 &rglw)
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
 
VOID Fib::FibRgFcLcb::FibRgFcLcb2000::process_FibRgFcLcb2000(const FibBase &bas, const FibRgLw97 &rgl)
{
  rgFcLcb97.process_FibRgFcLcb97(bas, rgl);

  if (lcbRmdThreading == 0)
  {
    throw "'lcbRmdThreading' must not be ZERO.";
  }
}

VOID Fib::FibRgFcLcb::FibRgFcLcb2002::process_FibRgFcLcb2002(const FibBase &bs, const FibRgLw97 &rglw)
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

VOID Fib::FibRgFcLcb::FibRgFcLcb2003::process_FibRgFcLcb2003(const FibBase& bs, const FibRgLw97 &rglw)
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

VOID Fib::FibRgFcLcb::FibRgFcLcb2007::process_FibRgFcLcb2007(const FibBase &base, const FibRgLw97 &rglw)
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

VOID Fib::FibRgCswNew::process_FibRgCswNew(const FibBase &obj)
{
  USHORT ver = obj.nFib;
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

VOID Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::process_FibRgCswNewData2000()
{
  if (cQuickSavesNew < 0 || cQuickSavesNew > 0x000F)
  {
    throw "'cQuickSavesNew' should be between 0 and 0x000F, inclusively.";
  }
}

VOID Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2007::process_FibRgCswNewData2007()
{
  rgCswNewData2000.process_FibRgCswNewData2000();
}

// Assigns values from stream to bit fields
inline BYTE Fib::assignBits(BYTE flag, BYTE temp, int shftRt)
{
  temp &= flag;
  return temp >> shftRt;
}

// Checks which nFib to use for version confirmation
/* inline USHORT Fib::determine_nFib_use() const
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
inline VOID Fib::skip_fields(std::ifstream & docustrm, ULONG numSkipped) const
{
  docustrm.seekg(numSkipped, std::ios::cur);
}

// In the event that the amount of data read for any particular fields is
// (slightly) less than what was expected (per the documentation), this
// function will adjust the file pointer to the tune of the determined
// deficit. This is to ensure that reading of subsequent fields commences
// at the right offset.
// inline VOID Fib::adjust_file_pointer(std::ifstream& strm, USHORT gvnSize, USHORT standard) const
// {
//   if (gvnSize < standard)
//   {
//     const int diff = standard - gvnSize;
//     strm.seekg(diff, std::ios::cur);
//   }
// }

// Checks to confirm that the capacity assigned to a struct matches the expected value.
  // It may be recalled that the 'USHORT' fields hold a value which, when multiplied by a 
  // specified value is supposed to equate the size in memory of the said struct.
// template <class T>
// USHORT Fib::computeStructSize(const USHORT cbValue, const USHORT expValue, const in
// 			      t multiplier) const
// {
//   USHORT cbSize = { };
//   if (cbValue == expValue)
//   {
//     cbSize = cbValue * multiplier;
//   }
//   return cbSize;
// }
