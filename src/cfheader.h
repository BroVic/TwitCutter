// CFH.h

// Data structure(s) for the OLE Compound File
// (adapted from https://msdn.microsoft.com/en-us/library/dd941946.aspx)
// The main structures copied into memory through this header and its
// accompanying implementation file are:
// 1. Compound File Header: This  references all the key parts of the file.
//
// 2. Double indirect file allocation table (Difat): This structure's life
//    begins in the CFH as an array of 109 fields and it provides reference to
//    the FAT.
//
// 3. File Allocation Table (FAT): This is an array that references all the
//    sectors of the file, with the sole expection of the CFH, to which it is
//    linked through the Difat.
//
// 4. Mini FAT: For files that are small, this structures a mini stream
//
// 5. Directory Entry: These are partitions of sectors that contain information
//    on storage and stream objects (that contain user-defined data), arranged in //    hierarchical tree structure to enable the location of the different streams
//    within a file e.g. a WordDocument stream.



#ifndef CFHEADER_H_INCLUDED
#define CFHEADER_H_INCLUDED

#include <fstream>
#include <vector>
#include <cmath>
#include "dtypes.h"

constexpr int SIGN_ELEMENTS = 8;
constexpr int DIFAT_LENGTH  = 109;
constexpr int DIFAT_NEXT_LOC= 1;

constexpr USHORT MINOR_VERSION     = 0x003E;
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
  std::vector<ULONG> copy_difat(std::istream&);
  std::vector<ULONG> loadFat(std::ifstream&);
  VOID readCFHeader(std::ifstream&);  
  ULONG get_sector_offset(const ULONG);  
  inline USHORT get_sector_size();
  
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

// Data structure to represent a typical directory entry
// This contains metadata that refer to either storage objects
// or stream objects that exist somewhere in the compound file
struct DirEntry
{
  DirEntry();
  ~DirEntry();
  VOID readDirEntry(std::ifstream&);
  ULONG find_stream_object(std::ifstream&, CFHeader&, std::u16string);
  inline unsigned int get_direntry_offset(const CFHeader&, const USHORT);

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

