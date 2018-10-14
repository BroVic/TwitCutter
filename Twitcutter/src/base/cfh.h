// CFH.h

// Data structure(s) for the OLE Compound File
// (adapted from https://msdn.microsoft.com/en-us/library/dd941946.aspx)
// The main structures copied into memory through this header and its
// accompanying implementation file are:
// 1. Compound File Header: This  references all the key parts of the file.
//
// 2. Double indirect file allocation table (Difat): This structure's life
//    begins in the CFH as an array of 109 elements and provides reference to
//    the FAT.
//
// 3. File Allocation Table (FAT): This is an array that references all the
//    sectors of the file, with the sole expection of the CFH, to which it is
//    linked through the Difat.
//
// 4. Mini FAT: For files that are small, this structures a mini stream.
//
// 5. Directory Entry: These are partitions of sectors that contain information
//    on storage and stream (user-defined data) objects, arranged in a
//    hierarchical tree structure to enable the location of the different 
//    streams within a file e.g. a WordDocument stream.

#ifndef CFH_H_INCLUDED
#define CFH_H_INCLUDED

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <Windows.h>
#include <minwindef.h>

constexpr int SIGN_ELEMENTS   = 8;
constexpr int DIFAT_LENGTH    = 109;
constexpr int DIFAT_NEXT_LOC  = 1;

// Key values for CFH data members
constexpr unsigned short MINOR_VERSION     = 0x003E;
constexpr unsigned short MAJOR_VERSION_3   = 0x0003;
constexpr unsigned short MAJOR_VERSION_4   = 0x0004;
constexpr unsigned short LIL_ENDIAN        = 0xFFFE;
constexpr unsigned short SECTOR_SIZE_512   = 0x0009;
constexpr unsigned short SECTOR_SIZE_4096  = 0x000C;
constexpr unsigned short SECTOR_SIZE_64    = 0x0006;

// Special values used for the FAT
constexpr unsigned long MAXREGSECT = 0xFFFFFFFA;
constexpr unsigned long RESERVED = 0xFFFFFFFB;
constexpr unsigned long DIFSECT = 0xFFFFFFFC;
constexpr unsigned long FATSECT = 0xFFFFFFFD;
constexpr unsigned long ENDOFCHAIN = 0xFFFFFFFE;
constexpr unsigned long FREESECT = 0xFFFFFFFF;

// TODO: specify
constexpr unsigned long MAXREGSID  = 0xFFFFFFFA;
constexpr unsigned long NOSTREAM   = 0xFFFFFFFF;

// Values for red-black tree
constexpr unsigned char RED    = 0x00;
constexpr unsigned char BLACK  = 0x01;

constexpr unsigned char DIR_UNUSED   = 0x00;
constexpr unsigned char DIR_STORAGE  = 0x01;
constexpr unsigned char DIR_STREAM   = 0x02;
constexpr unsigned char DIR_ROOT     = 0x05;

constexpr char16_t UTF16_CODE_POINTS = 32;

struct CFHeader
{
  CFHeader();
  ~CFHeader();
  std::vector<unsigned long> copy_difat(std::ifstream&);
  std::vector<unsigned long> loadFat(std::ifstream&);
  void readCFHeader(std::ifstream&);  
  unsigned long get_sector_offset(const unsigned long, const unsigned short);
  unsigned long get_sector_offset(const unsigned long);
  inline unsigned short get_sector_size();
  
  unsigned char   Sig[SIGN_ELEMENTS];
  CLSID  CLSID_NULL;
  unsigned short VerMinor;
  unsigned short VerDll;
  unsigned short ByteOrder;
  unsigned short SectorShift;
  unsigned short MinSectorShift;
  unsigned short Reserved;
  unsigned long  Reserved2;
  unsigned long  NumDirSects;
  unsigned long  NumFatSects;
  unsigned long  DirSect1;
  unsigned long  TransactSig;
  unsigned long  MiniStrMax;
  unsigned long  MiniFatSect1;
  unsigned long  NumMiniFatSects;
  unsigned long  DifatSect1;
  unsigned long  NumDifatSects;
  unsigned long  Difat[DIFAT_LENGTH];
}; // !struct CFHeader

// Data structure to represent a typical directory entry
// This contains metadata that refer to either storage objects
// or stream objects that exist somewhere in the compound file
struct DirEntry
{
  DirEntry();
  ~DirEntry();
  void readDirEntry(std::ifstream&);
  unsigned long find_stream_object(std::ifstream&, CFHeader&, std::u16string);
  inline long long get_direntry_offset(const CFHeader&, const unsigned short);

  char16_t             name[UTF16_CODE_POINTS];
  unsigned short       nameLength;
  unsigned char        objType;
  unsigned char        colorFlag;
  unsigned long        leftSibID;
  unsigned long        rightSibID;
  unsigned long        childID;
  CLSID                clsid;
  unsigned long        stateBits;
  FILETIME             creationTime;
  FILETIME             modTime;
  unsigned long        startSectorLoc;
  unsigned long long   streamSize;
}; // !struct DirEntry 
#endif // !CFH_H_INCLUDED

