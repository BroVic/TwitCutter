// CFH.h

// Data structure(s) for the OLE Compound File Header
// (adapted from https://msdn.microsoft.com/en-us/library/dd941946.aspx)

// PURPOSE: To read the Compound File Header into memory, as this will
// determine what else we would want to do with the file's constituent
// parts i.e. streams and objects. This is the starting point for dealing
// with files that come in this format.


#ifndef CFH_H_INCLUDED
#define CFH_H_INCLUDED

#include <fstream>
#include <vector>
#include <cmath>
#include "dtypes.h"

constexpr int SIGN_ELEMENTS = 8;
constexpr int DIFAT_LENGTH  = 109;

constexpr USHORT MINOR_VERSION     = 0X003E;
constexpr USHORT MAJOR_VERSION_3   = 0x0003;
constexpr USHORT MAJOR_VERSION_4   = 0x0004;
constexpr USHORT LIL_ENDIAN        = 0xFFFE;
constexpr USHORT SECTOR_SIZE_512   = 0x0009;
constexpr USHORT SECTOR_SIZE_4096  = 0x000C;
constexpr USHORT SECTOR_SIZE_64    = 0x0006;

constexpr ULONG MAXREGSID     = 0xFFFFFFFA;
constexpr ULONG NOSTREAM      = 0xFFFFFFFF;

constexpr BYTE RED            = 0x00;
constexpr BYTE BLACK          = 0x01;

constexpr BYTE DIR_UNUSED     = 0x00;
constexpr BYTE DIR_STORAGE    = 0x01;
constexpr BYTE DIR_STREAM     = 0x02;
constexpr BYTE DIR_ROOT       = 0x05;

constexpr WCHAR UTF16_CODE_POINTS = 32;

struct CFHeader
{
  CFHeader();
  ~CFHeader();
  VOID readCFHeader(std::ifstream&);
  std::vector<ULONG> loadFat(std::ifstream&, CFHeader&);
  BOOL use_difat_sect();
  ULONG fat_len(std::ifstream&, const USHORT);
  USHORT get_sector_size() const;
  
  BYTE   Sig[SIGN_ELEMENTS];
  CLSID  CLSID_NULL;
  USHORT VerMinor;
  USHORT VerDll;
  USHORT ByteOrder;
  USHORT SectorShift;
  USHORT MinSectorShift;
  USHORT Reserved;
  ULONG  Reserved2;
  ULONG  NumDirSects;
  ULONG  NumFatSects;
  ULONG  DirSect1;
  ULONG  TransactSig;
  ULONG  MiniStrMax;
  ULONG  MiniFatSect1;
  ULONG  NumMiniFatSects;
  ULONG  DifatSect1;
  ULONG  NumDifatSects;
  ULONG  Difat[DIFAT_LENGTH];
}; // !struct CFHeader

struct DirEntry
{
  DirEntry();
  ~DirEntry();
  VOID readDirEntry(std::ifstream &);
  unsigned short find_directory(std::ifstream&, CFHeader&, std::u16string);
  inline unsigned int get_direntry_offset(CFHeader&, const USHORT);

  WCHAR      name[UTF16_CODE_POINTS];
  USHORT     nameLength;
  BYTE       objType;
  BYTE       colorFlag;
  ULONG      leftSibID;
  ULONG      rightSibID;
  ULONG      childID;
  CLSID      clsid;
  ULONG      stateBits;
  FILETIME   creationTime;
  FILETIME   modTime;
  ULONG      startSectorLoc;
  ULONGLONG  streamSize;
}; // !struct DirEntry 
#endif // !CFH_H_INCLUDED

