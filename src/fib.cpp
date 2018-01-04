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
constexpr USHORT ENGLISH_HONG_KONG_SAR		 = 15369;
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
  fDot		         = _SET_BITS_1;
  fGlsy		         = _SET_BITS_1;
  fComplex	         = _SET_BITS_1;
  fHasPic	         = _SET_BITS_1;
  cQuickSaves	         = _SET_BITS_4;
  fEncrypted	         = _SET_BITS_1;
  fWhichTblStm           = _SET_BITS_1;
  fReadOnlyRecommended   = _SET_BITS_1;
  fWriteReservation      = _SET_BITS_1;
  fExtChar	         = _SET_BITS_1;
  fLoadOverride	         = _SET_BITS_1;
  fFarEast	         = _SET_BITS_1;
  fObfuscated	         = _SET_BITS_1;
  nFibBack	         = { };
  lkey		         = { };
  envr		         = { };
  fMac		         = _SET_BITS_1;
  fEmptySpecial	         = _SET_BITS_1;
  fLoadOverridePage      = _SET_BITS_1;
  reserved1	         = _SET_BITS_1;
  reserved2	         = _SET_BITS_1;
  fSpare0		 = _SET_BITS_3;
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
  lidFE         = { };
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
// This method also calls other functions that read relevant
// parts of the FIB.
VOID Fib::readFib(std::ifstream &docstream)
{
  base.readFibBase(docstream);
  
  docstream.read(reinterpret_cast<char *>(&csw), sizeof(USHORT));
  verifyValues(csw, EXPECTED_CSW);
  
  fibRgW.readFibRgW(docstream);
    USHORT readSize = computeStructSize(fibRgW, csw, EXPECTED_CSW, MULTIPLIER_FOR_CSW);
  adjust_file_pointer(docstream, objSize, readSize);

  docstream.read(reinterpret_cast<char *>(&cslw), sizeof(USHORT));
  verifyValues(cslw, EXPECTED_CSLW);

  fibRgLw.readFibRgLw(docstream);
  readSize = computeStructSize(fibRgLw, cslw, EXPECTED_CSLW, MULTIPLIER_FOR_CSLW);
  adjust_file_pointer(docstream, objSize, readSize);
			       
  docstream.read(reinterpret_cast<char *>(&cbRgFcLcb), sizeof(USHORT));
  USHORT expCbVal = fibRgFcLcbBlob.readRgFcLcbBlob(docstream, base.nFib);
  verifyValues(cbRgFcLcb, expCbVal);

  readSize = computeStructSize(fibRgFcLcbBlob, cbRgFcLcb, expCbVal, MULTIPLIER_FOR_CBRGFCLCB);
  adjust_file_pointer(docstream, objSize, readSize);
  
  docstream.read(reinterpret_cast<char *>(&cswNew), sizeof(USHORT));
  expCbVal = fibRgCswNew.readFibRgCswNew(docstream, cswNew);
  verifyValues(cswNew, expCbVal);
  readSize = computeStructSize(fibRgCswNew, cswNew, expCbVal, MULTIPLIER_FOR_CSWNEW);
  adjust_file_pointer(docstream, objSize, readSize);
}

// Reads the FibBase from the WordDocument Stream
// Those parts that are bit fields are extracted using
// bit masks and other relevant constructs
VOID Fib::FibBase::readFibBase(std::ifstream &docfile)
{
  docfile.read(reinterpret_cast<char *>(&wIdent), sizeof(USHORT));
  docfile.read(reinterpret_cast<char *>(&nFib), sizeof(USHORT));
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
v  add_member_sizes += sizeof(ccpAtn);
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
}

// Reads the value of a part of the FIB that varies in content and structure
  // with different versions of Word (97 - 2007). The nFib (a member of the FibBase
  // data structure) is what determines which version is used.
USHORT Fib::FibRgFcLcb::readFibRgFcLcbBlob(const std::ifstream& flStream, const USHORT version)
{
  if ((nFib == NFIB_FOR_97 && this->cbRgFcLcb == EXPECTED_CBRGFCLCB_97)
      || (nFib == NFIB_FOR_2000 && this->cbRgFcLcb == EXPECTED_CBRGFCLCB_2000)
      || (nFib == NFIB_FOR_2002 && this->cbRgFcLcb == EXPECTED_CBRGFCLCB_2002)
      || (nFib == NFIB_FOR_2003 && this->cbRgFcLcb == EXPECTED_CBRGFCLCB_2003)
      || (nFib == NFIB_FOR_2007 && this->cbRgFcLcb == EXPECTED_CBRGFCLCB_2007))
  {
    switch (version)
    {
    case NFIB_FOR_97:
      fibRgFcLcbBlob.fibRgFcLcb97.readFibRgFcLcb97(flStream);
      return EXPECTED_CBRGFCLCB_97;
    case NFIB_FOR_2000:
      fibRgFcLcbBlob.fibRgFcLcb2000.readFibRgFcLcb2000(flStream);
      return EXPECTED_CBRGFCLCB_2000;
    case NFIB_FOR_2002:
      fibRgFcLcbBlob.fibRgFcLcb2002.readFibRgFcLcb2002(flStream);
      return EXPECTED_CBRGFCLCB_2002;
    case NFIB_FOR_2003:
      fibRgFcLcbBlob.fibRgFcLcb2003.readFibRgFcLcb2003(flStream);
      return EXPECTED_CBRGFCLCB_2003;
    case NFIB_FOR_2007:
      fibRgFcLcbBlob.fibRgFcLcb2007.readFibRgFcLcb2007(flStream);
      return EXPECTED_CBRGFCLCB_2007;
    }
  }
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
}

// Reads an FibRgCswNew, using the current version of Word (97 -2007) to
// select the appropriate data structure to read into memory, whilst
// returning the size of data read for use in subsequent methods
USHORT Fib::FibRgCswNew::readFibRgCswNew(std::ifstream& stream, const USHORT cswNewValue)
{
  USHORT retVal;
  if (cswNewValue == EXPECTED_CSWNEW_97)
  {
    std::cout << "This version does not have the 'FibRgCswNew' structure.\n";
    retVal = EXPECTED_CSWNEW_97;
  }
  else
  {
    stream.read(reinterpret_cast<char *>(&nFibNew), sizeof(USHORT));
    retVal = this->rgCswNewData.readRgCswNewData(stream, nFibNew);
  }
  return retVal;
}

// Reads from FibRgCswNewData structure, but what exactly is read depends
// on the verion of Word. This version is determined by the 2nd argument
// This function will return the size of the dat structure that was read
USHORT Fib::FibRgCswNew::FibRgCswNewData::readFibRgCswNewData(std::ifstream& filestrm, const USHORT newVer)
{
  USHORT retValue
    if (newVer == NFIB_FOR_2000 || (newVer == NFIB_FOR_2002 || newVer == NFIB_FOR_2003))
    {
      this->fibRgCswNewData2000.read2000(filestrm);
      retValue = EXPECTED_CSWNEW_2000;
    }
    else if (newVer == NFIB_FOR_2007)
    {
      this->fibRgCswNewData2007.read2007(filestrm);
      retValue = EXPECTED_CSWNEW_2007;
    }
    return retValue;
}

VOID Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::read2000(std::ifstream & instream)
{
  instream.read(reinterpret_cast<char *>(&cQuickSavesNew), sizeof(USHORT));
}

VOID Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2007::read2007(std::ifstream & streamin)
{
  FibRgCswNewData2000 newdat2000;
  newdat2000.readFibRgCswNewData2000(streamin);

  streamin.read(reinterpret_cast<char *>(&lidThemeOther), sizeof(USHORT));
  streamin.read(reinterpret_cast<char *>(&lidThemeFE), sizeof(USHORT));
  streamin.read(reinterpret_cast<char *>(&lidThemeCS), sizeof(USHORT));
}

// Inspects the entire data read into the in-memory copy of the
// main data structures that represent the File Information Block.
// Where appropriate, minor adjustments are to be made
VOID Fib::inspectFibStructs(const USHORT ver)
{
  base.process_FibBase();
  fibRgW.process_FibRgW97();
  fibRgLw.process_FibRgLw97();
  fibRgFcLcbBlob.process_FibRgFcLcbBlob(ver);
  rgCswNew.process_FibRgCswNew(ver);
}

// Screens the members of FibBase to make sure all conditions are met
VOID Fib::FibBase::process_FibBase()
{
  if (wIdent != WORD_BINARY_FILE)
  {
    throw "Fle is either corrupted or not of the specidied format.";
  }
  
  if (this->nFib == NFIB_SPECIAL || this->nFib == NFIB_BIDI_BLD)
  {
    this->nFib = NFIB_FOR_97;
  }

  if (this->nFib >= NFIB_FOR_2000)
  {
    switch(this->lid)
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
      this->lid = ENGLISH_UNITED_STATES;
      break;
    }
  }

  if (this->nFib >= NFIB_FOR_2002)
  {
    switch(this->lid)
    {
    case THAI;
    case VIETNAMESE:
    case HINDI:
      this->lid = ENGLISH_UNITED_STATES;
      break;
    }
  }
  
  if (pnNext != 0)
  {
    if (this->fGlsy == 1 || this->fDot == 0)
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
  
  if (this->nFib >= NFIB_FOR_2000)
  {
    if (this->cQuickSaves != 0xF)
    {
      throw "cQuickSaves is not equal to 0xF.";
    }
  }

  if (this->fExtChar != 1)
  {
    throw "fExtChar MUST be 1.";
  }

  if (this->nFibBack != 0x00BF || this->nFibBack 1= 0x00C1)
  {
    throw "Incorrect values for nFibBack.";
  }
}

VOID Fib::FibRgW97::process_FibRgW97()
{
}
 
VOID Fib::FibRgLw97::process_FibRgLw97()
{
  if (this->ccpText < 0)
  {
    throw "ccpText must be greater than or equal to 0.";
  }

  if (this->ccpFtn < 0)
  {
    throw "ccpFtn must be greater than or equal to 0.";
  }
  if (this->ccpHdd < 0)
  {
    throw "ccpHdd must be greater than or equal to 0.";
  }

  if (this->ccpAtn < 0)
  {
    throw "ccpAtn must be greater than or equal to 0.";
  }
  
  if (ccpEdn < 0)
  {
    throw "ccpEdn must be greater than or equal to 0."
  }
  
  if (ccpTxbx < 0)
  {
    throw "ccpTxbx must be greater than or equal to 0."
  }

  if (ccpHdrTxbx < 0)
  {
    throw "ccpKdrTxbx must be greater than or equal to 0."
  }

}

VOID Fib::FibRgFcLcb::process_FibRgFcLcbBlob(const USHORT version);
{
  switch(version)
  {
  case NFIB_FOR_97:
    fibRgFcLcb97.process_FibRgFcLcb97();
    break;
  case NFIB_FOR_2000:
    fibRgFcLcb2000.process_FibRgFcLcb2000();
    break;
  case NFIB_FOR_2002:
    fibRgFcLcb2002.process_FibRgFcLcb2002();
    break;
  case NFIB_FOR_2003:
    fibRgFcLcb2003.process_FibRgFcLcb2003();
    break;
  case NFIB_FOR_2007:
    fibRgFcLcb2007.process_FibRgFcLcb2007();
    break;
  }
}

VOID Fib::FibRgFcLcb::FibRgFcLcb97::process_FibRgFcLcb97()
{
  if (this->lcbStshf == 0)
  {
    throw "lcbShshf must be a non-zero value.";
  }

  if ((fibRgLw.ccpFtn == 0 && this->lcbPlcffndTxt != 0) ||
      (fibRgLw.ccpFtn != 0 && this->lcbPlcffndTxt == 0))
  {
    throw "FibRgFcLcb97.lcbPlcffndTxt must be zero when"
      "FibRgLw97.ccpFtn is zero and vice versa.";
  }

  if ((fibRgLw.ccpAtn == 0 && this->lcbPlcfandTxt != 0) ||
      (fibRgLw.ccpAtn != 0 && this->lcbPlcfandTxt == 0))
  {
    throw "FibRgFcLcb97.lcbPlcfandTxt must be zero when"
      "FibRgLw97.ccpAtn is zero and vice versa.";
  }

  if (this->lcbPlcPad != 0)
  {
    throw "FibRgFcLcb97.lcbPlcPad must be zero.";
  }

  if (base.fGlsy == 0)
  {
    if (this->lcbSttbfGlsy != 0)
    {
      throw "FibRgFcLcb97.lcbSttbfGlsy must be zero when base.fGlsy is zero";
    }

    if (this->lcbPlcfGlsy != 0)
    {
      throw "FibRgFcLcb97.lcbPlcfGlsy must be zero when base.fGlsy is zero";
    }

    if (this->lcbSttbGlsyStyle != 0)
    {
      throw "FibRgFcLcb97.lcbSttbGlsyStyle must be zero when base.fGlsy is zero";
    }
  }
  else
  {
    if (this->lcbSttbGlsyStyle == 0)
    {
      throw "'FibRgFcLcb97.lcbSttbGlsyStyle' should be non-zero.";
    }
  }

  if (this->fcPlcfBteChpx <= 0 || this->lcbPlcfBteChpx <= 0)
  {
    throw "Both fcPlcfBteChpx and lcbPlcfBteChpx of FibRgFcLcb97 must be > 0.";
  }

  if (this->fcPlcfBtePapx <= 0 || this->lcbPlcfBtePapx <= 0)
  {
    throw "Both fcPlcfBtePapx and lcbPlcfBtePapx of FibRgFcLcb97 must be > 0.";
  }

  if (this->lcbPlcfSea != 0)
  {
    throw "'lcbPlcSea' must be zero.";
  }
  
  if (this->lcbPlcfFldMcr != 0)
  {
    throw "'lcbPlcfFldMcr' must be zero.";
  }

  if (this->lcbUnused1 != 0)
  {
    throw "'lcbUnused1' must be zero.";
  }

  if (this->lcbSttbfMcr != 0)
  {
    throw "'lcbSttbfMcr' must be zero.";
  }
  
  if (this->lcbDop == 0)
  {
    throw "'lcbDop must not be zero.";
  }

  
  if (this->lcbSttbfAssoc == 0)
  {
    throw "'lcbSttbfAssoc' must not be zero.";
  }
  
  if (this->lcbClx <= 0)
  {
    throw "'lcbClx' must be greater than ZERO.";
  }

  if (this->lcbPlcfPgdFtn != 0)
  {
    throw "'lcbPlcfPgdFtn' must be ZERO.";
  }

  if (this->lcbAutosaveSource != 0)
  {
    throw "'lcbAutosaveSource' must be ZERO.";
  }
  
  if (this->lcbUnused2 != 0 || this->lcbUnused3 != 0)
  {
    throw "'lcbUnsed2 /-3 must be ZERO.";
  }
  
  if (this->lcbFormFldSttbs != 0)
  {
    throw "'lcbFormFldSttbs' must be ZERO.";
  }

  if ((fibRgLw.ccpEdn == 0 && this->lcbPlcfendTxt != 0) ||
      (fibRgLw.ccpEdn != 0 && this->lcbPlcfendTxt == 0))
  {
    throw "FibRgFcLcb97.lcbPlcfendTxt must be zero when"
      "FibRgLw97.ccpEdn is zero and vice versa.";
  }

  if (lcbUnused4 != 0)
  {
    throw "'lcbUnused4' must be ZERO.";
  }

  if (base.fDot == 0)
  {
    if (this->lcbSttbfCaption != 0)
    {
      throw "'lcbSttbfCaption' must be ZERO when base.fDot is also zero.";
    }

    if (this->lcbSttbfAutoCaption != 0)
    {
      throw "'lcbSttbfAutoCaption' must be ZERO when base.fDot is also zero.";
    }
  }

  if (fibRgLw.ccpTxbx == 0)
  {
    if (this->lcbPlcftxbxTxt != 0)
    {
      throw "lcbPlcftxbxTxt' should be ZERO.";
    }

    if (this->lcbPlcfTxbxBkd != 0)
    {
      throw "'lcbPlcfTxbxBkd should be ZERO.";
    }
  }
  else
  {
    if (this->lcbPlcftxbxTxt == 0)
    {
      throw "lcbPlcftxbxTxt' should not be ZERO.";
    }

    if (this->lcbPlcfTxbxBkd == 0)
    {
      throw "'lcbPlcfTxbxBkd should not be ZERO.";
    }
  }
  
  if ((fibRgLw.ccpHdrTxbx == 0 && this->lcbPlcfHdrtxbxTxt != 0) ||
      (fibRgLw.ccpHdrTxbx != 0 && this->lcbPlcfHdrtxbxTxt != 0))
  {
    throw "FibRgFcLcb97.lcbPlcfHdrtxbxTxt must be zero when"
      "FibRgLw97.ccpHdrTxbx is zero and vice versa.";
  }

  if (fibRgLw.ccpHdrTxbx == 0)
  {
    if (this->lcbPlcfHdrtxbxTxt != 0)
    {
      throw "lcbPlcfHdrtxbxTxt' should be ZERO.";
    }

    if (this->lcbPlcfTxbxHdrBkd != 0)
    {
      throw "lcbPlcfTxbxHdrBkd' should be ZERO.";
    }
  }
  else
  {
    if (this->lcbPlcfHdrtxbxTxt == 0)
    {
      throw "lcbPlcfHdrtxbxTxt' should not be ZERO.";
    }

    if (this->lcbPlcfTxbxHdrBkd == 0)
    {
      throw "lcbPlcfTxbxHdrBkd' should be ZERO.";
    }
  }
  
  if (this->lcbSttbfIntlFld != 0)
  {
    throw "'lcbSttbfIntlFld' must be ZERO.";
  }

  if (base.nFib > NFIB_FOR_2000)
  {
    if (this->lcbSttbSavedBy != 0)
    {
      throw "'lcbSttbSavedBy' should be ZERO for tis version of Word";
    }

    if (this->lcbPlcfLvcPre10 != 0)
    {
      throw "'lcbPlcfLvcPre10' should be ZERO for this version of Word.";
    }
  }

  if (base.nFib == NFIB_FOR_2007)
  {
    if (this->lcbPlcfBteLvc != 0)
    {
      throw "'lcbPlcfBteLvc' should be zero in the version of Word.";
    }
  }  
}
 
VOID Fib::FibRgFcLcb::FibRgFcLcb2000::process_FibRgFcLcb2000()
{
  rgFcLcb97.process_FibRgFcLcb97();

  if (this->lcbRmdThreading == 0)
  {
    throw "'lcbRmdThreading' must not be ZERO.";
  }
}

VOID Fib::FibRgFcLcb::FibRgFcLcb2002::process_FibRgFcLcb2002()
{
  rgFcLcb2000.process_FibRgFcLcb2000();

  if (this->lcbUnused1 != 0)
  {
    throw "; lcbUnused1' must be ZERO.";
  }

  if (base.nFib < NFIB_FOR_2002)
  {
    if (this->lcbPlcfpmiOldXP != 0)
    {
      throw "'lcbPlcfpmiOldXP' should be zero for this version of Word.";
    }

    if (this->lcbPlcfpmiNewXP != 0)
    {
      throw "'lcbPlcfpmiNewXP'should be zero for tis version of Word.";
    }

    if (this->lcbPlcfpmiMixedXP != 0)
    {
      throw "'lcbPlcfpmiMixedXP' should be zero for this version of Word.";
    }

    if (this->lcbPlcflvcOldXP != 0)
    {
      throw "'lcbPlcflvcOldXP' should be zero for this version of Word.";
    }

    if (this->lcbPlcflvcNewXP != 0)
    {
      throw "'lcbPlcflvcNewXP' should be zero for this version of Word.";
    }

    if (this->lcbPlcflvcMixedXP != 0)
    {
      throw "'lcbPlcflvcMixedXP' should be zero for this version of Word.";
    }
  }

  if (this->lcbUnused2 != 0)
  {
    throw "'lcbUnused2' should be ZERO.";
  }
}

VOID Fib::FibRgFcLcb::FibRgFcLcb2003::process_FibRgFcLcb2003()
{
  rgFcLcb2002.process_FibRgFcLcb2002();
  
  if (this->lcbCustomXForm > 4168
      && this->lcbCustomXForm % 2 != 0)
  {
    throw "'lcbCustomXForm' must be less than or equal to 4168 & an even number.";
  }

  if (this->fcUnused != 0 && this->lcbUnused != 0)
  {
    throw "'fcUnusded' and 'lcbUnused' must be ZERO.";
  }

  if (base.nFib > NFIB_FOR_2003)
  {
    if (this->lcbPlcfpmiOld != 0)
    {
      throw "'lcbPlcfpmiOld' should be zero for this version of Word.";
    }

    if (this->lcbPlcfpmiOldInline != 0)
    {
      throw "'lcbPlcfpmiOldInline' should be zero for this version of Word.";
    }

    if (this->lcbPlcfpmiNew != 0)
    {
      throw "'lcbPlcfpmiNew' should be zero for this version of Word.";
    }

    if (this->lcbPlcfpmiNewInline != 0)
    {
      throw "'lcbPlcfpmiNewInline' should be zero for this version of Word.";
    }

    if (this->lcbPlcflvcOld != 0)
    {
      throw "'lcbPlcflvcOld' should be zero for this version of Word.";
    }

    if (this->lcbPlcflvcOldInline != 0)
    {
      throw "'lcbPlcflvcOldInline' should be zero for this version of Word.";
    }

    if (this->lcbPlcflvcNew != 0)
    {
      throw "'lcbPlcflvcNew' should be zero for this version of Word.";
    }

    if (this->lcbPlcflvcNewInline != 0)
    {
      throw "'lcbPlcflvcNewInline' should be zero for this version of Word.";
    }
  }
}

VOID Fib::FibRgFcLcb::FibRgFcLcb2007::process_FibRgFcLcb2007()
{
  rgFcLcb2003.process_FibRgFcLcb2003();
  
  if (this->lcbPlcfmthd != 0)
  {
    throw "'lcbPlcfmthd' must be zero.";
  }
  
  if (this->lcbSttbfBkmkMoveFrom != 0)
  {
    throw "'lcbSttbfBkmkMoveFrom' must be zero.";
  }
  
  if (this->lcbPlcfBkfMoveFrom != 0)
  {
    throw "'lcbPlcfBkfMoveFrom' must be zero.";
  }
  
  if (this->lcbPlcfBklMoveFrom != 0)
  {
    throw "'lcbPlcfBklMoveFrom' must be zero.";
  }
  
  if (this->lcbSttbfBkmkMoveTo != 0)
  {
    throw "'lcbSttbfBkmkMoveTo' must be zero.";
  }
  
  if (this->lcbPlcfBkfMoveTo != 0)
  {
    throw "'lcbPlcfBkfMoveTo' must be zero.";
  }
  
  if (this->lcbPlcfBklMoveTo != 0)
  {
    throw "'lcbPlcfBklMoveTo' must be zero.";
  }
  
  if (this->lcbUnused1 != 0)
  {
    throw "'lcbUnused1' must be zero.";
  }
  
  if (this->lcbUnused2 != 0)
  {
    throw "'lcbUnused2' must be zero.";
  }
  
  if (this->lcbUnused3 != 0)
    {
    throw "'lcbUnused3' must be zero.";
  }
  
  if (this->lcbSttbfBkmkArto != 0)
  {
    throw "'lcbSttbfBkmkArto' must be zero.";
  }
  
  if (this->lcbPlcfBkfArto != 0)
  {
    throw "'lcbPlcfBkfArto' must be zero.";
  }
  
  if (this->lcbPlcfBklArto != 0)
  {
    throw "'lcbPlcfBklArto' must be zero.";
  }
  
  if (this->lcbArtoData != 0)
  {
    throw "'lcbArtoData' must be zero.";
  }
  
  if (this->lcbUnused4 != 0)
  {
    throw "'lcbUnused4' must be zero.";
  }
  
  if (this->lcbUnused5 != 0)
  {
    throw "'lcbUnused5' must be zero.";
  }
  
  if (this->lcbUnused6 != 0)
  {
    throw "'lcbUnused6' must be zero.";
  }
}

VOID Fib::FibRgCswNew::process_FibRgCswNew(const USHORT ver)
{
  if (ver == NFIB_FOR_2000 ||
      (ver == NFIB_FOR_2002) || (ver == NFIB_FOR_2003))
  {
    this->rgCswNewData.fibRgCswNewData2000.process_FibRgCswNewData2000();
  }
  else if (ver == NFIB_FOR_2007)
  {
    this->rgCswNewData.fibRgCswNewData2007.process_FibRgCswNewData2007();
  }
}

VOID Fib::FibRgCswNew::FibRgCswNewData::FibRgCswNewData2000::process_FibRgCswNewData2000()
{
  if (this->cQuickSavesNew < 0 || this->cQuickSavesNew > 0x000F)
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
inline VOID Fib::adjust_file_pointer(std::ifstream& strm, USHORT gvnSize, USHORT standard) const
{
  if (gvnSize < standard)
  {
    const int diff = standard - gvnSize;
    strm.seekg(diff, std::ios::cur);
  }
}

// Checks to confirm that the capacity assigned to a struct matches the expected value.
  // It may be recalled that the 'USHORT' fields hold a value which, when multiplied by a 
  // specified value is supposed to equate the size in memory of the said struct.
template <class T>
USHORT Fib::computeStructSize(const T& fibStrct, const USHORT cbValue, const USHORT expValue, const int multiplier)
{
  USHORT cbSize;
  if (cbValue == expValue)
  {
    cbSize = cbValue * multiplier;
  }
  return cbSize;
}

// Ckecks whether the value read from the stream that reflects the capacity
// of the subsequent struct is equal to its expected value, and throws an
// expection if this confirmation is not in the affirmative, which will be
// caught only after the file stream has been safely closed post-reading
 inline VOID  Fib::verifyValues(const USHORT rd, const USHORT exp) const
 {
   if (rd != exp)
   {
     throw "'csw' is not equal to the expecte value.";
   }
 }
