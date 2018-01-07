// cfheader.cpp

// Implemendation for cfheader.h
#include "cfheader.h"

// The Compound File Sector Numbers
constexpr ULONG MAXREGSECT  = 0xFFFFFFFA;
constexpr ULONG RESERVED    = 0xFFFFFFFB;
constexpr ULONG DIFSECT     = 0xFFFFFFFC;
constexpr ULONG FATSECT     = 0xFFFFFFFD;
constexpr ULONG ENDOFCHAIN  = 0xFFFFFFFE;
constexpr ULONG FREESECT    = 0xFFFFFFFF;

constexpr BYTE DIRENTRY_SIZE = sizeof(DirEntry);

CFHeader::CFHeader()
{
  for (int i = 0; i < SIGN_ELEMENTS; i++)
  {
    Sig[i] = { };
  }
  VerMinor          = { };
  VerDll            = { };
  ByteOrder         = { };
  SectorShift       = { };
  MinSectorShift    = { };
  Reserved          = { };
  Reserved2         = { };
  NumDirSects       = { };
  NumFatSects       = { };
  DirSect1          = { };
  TransactSig       = { };
  MiniStrMax        = { };
  MiniFatSect1      = { };
  NumMiniFatSects   = { };
  DifatSect1        = { };
  NumDifatSects     = { };
  for (int i = 0; i < DIFAT_LENGTH; i++) 
  {
    Difat[i] = { }; 
  }
}

CFHeader::~CFHeader()
{
}

// Reads the Compound File Header 
VOID CFHeader::readCFHeader(std::ifstream & dcstream)
{
  dcstream.read(reinterpret_cast<char *>(&Sig), sizeof(BYTE) * SIGN_ELEMENTS);
  dcstream.read(reinterpret_cast<char *>(&CLSID_NULL), sizeof(CLSID));
  dcstream.read(reinterpret_cast<char *>(&VerMinor), sizeof(USHORT));
  dcstream.read(reinterpret_cast<char *>(&VerDll), sizeof(USHORT));
  dcstream.read(reinterpret_cast<char *>(&ByteOrder), sizeof(USHORT));
  dcstream.read(reinterpret_cast<char *>(&SectorShift), sizeof(USHORT));
  dcstream.read(reinterpret_cast<char *>(&MinSectorShift), sizeof(USHORT));
  dcstream.read(reinterpret_cast<char *>(&Reserved), sizeof(USHORT));
  dcstream.read(reinterpret_cast<char *>(&Reserved2), sizeof(ULONG));
  dcstream.read(reinterpret_cast<char *>(&NumDirSects), sizeof(ULONG));
  dcstream.read(reinterpret_cast<char *>(&NumFatSects), sizeof(ULONG));
  dcstream.read(reinterpret_cast<char *>(&DirSect1), sizeof(ULONG));
  dcstream.read(reinterpret_cast<char *>(&TransactSig), sizeof(ULONG));
  dcstream.read(reinterpret_cast<char *>(&MiniStrMax), sizeof(ULONG));
  dcstream.read(reinterpret_cast<char *>(&MiniFatSect1), sizeof(ULONG));
  dcstream.read(reinterpret_cast<char *>(&NumMiniFatSects), sizeof(ULONG));
  dcstream.read(reinterpret_cast<char *>(&DifatSect1), sizeof(ULONG));
  dcstream.read(reinterpret_cast<char *>(&NumDifatSects), sizeof(ULONG));
  dcstream.read(reinterpret_cast<char *>(&Difat), sizeof(ULONG) * DIFAT_LENGTH);
}

// Reads the File Allocation Table (FAT) into memory
std::vector<ULONG> CFHeader::loadFat(std::ifstream & stream, CFHeader &hdr) 
{
  std::vector<ULONG> fat;
  const USHORT szSect = hdr.get_sector_size();

  int i = 0;
  while (Difat[i] != FREESECT)
  {
    ULONG fatValue;
    ULONG offset = (Difat[i] + 1) * szSect;

    stream.seekg(offset, std::ios::beg);

    const ULONG len = szSect / sizeof(fatValue);
    for (ULONG j = 0; j < len; j++)
    {
      stream.read(reinterpret_cast<char *>(&fatValue), sizeof(fatValue));
      fat.push_back(fatValue);
    }
    i++;
  }
  return fat;
}

// Determines whether the Difat Sectors are to be used for
// this particular file
BOOL CFHeader::use_difat_sect()
{
  if (NumDifatSects == 0 && DifatSect1 == ENDOFCHAIN)
  {
    return false;
  }
  return true;	
}

//  
ULONG CFHeader::fat_len(std::ifstream& streams, const USHORT sctSz)
{
  ULONG val;
  val = Difat[0];
  val = (val - 1) + NumFatSects;
  val = (val + 1) * sctSz;

  ULONG temp[128];
  streams.seekg(val, std::ios::beg);
  streams.read(reinterpret_cast<char *>(&temp), sctSz);

  int ovrflw = 0;
  while (temp[ovrflw] != FREESECT)
  {
    ovrflw++;
  }
  val = ((NumFatSects - 1) * sctSz) + ovrflw;

  return val;
}

USHORT CFHeader::get_sector_size() const
{
  return static_cast<USHORT>(pow(2, SectorShift));
}

DirEntry::DirEntry()
{
  for (int i = 0; i < 32; i++)
  {
    name[i]       = { };
  }
  nameLength      = { };
  objType         = { };
  colorFlag       = { };
  leftSibID       = { };
  rightSibID      = { };
  childID         = { };
  stateBits       = { };
  startSectorLoc  = { };
  streamSize      = { };
}

DirEntry::~DirEntry()
{
}

VOID DirEntry::readDirEntry(std::ifstream& flstrm)
{
  flstrm.read(reinterpret_cast<char *>(&name), sizeof(name));
  flstrm.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
  flstrm.read(reinterpret_cast<char *>(&objType), sizeof(objType));
  flstrm.read(reinterpret_cast<char *>(&colorFlag), sizeof(colorFlag));
  flstrm.read(reinterpret_cast<char *>(&leftSibID), sizeof(leftSibID));
  flstrm.read(reinterpret_cast<char *>(&rightSibID), sizeof(rightSibID));
  flstrm.read(reinterpret_cast<char *>(&childID), sizeof(childID));
  flstrm.read(reinterpret_cast<char *>(&clsid), sizeof(clsid));
  flstrm.read(reinterpret_cast<char *>(&stateBits), sizeof(stateBits));
  flstrm.read(reinterpret_cast<char *>(&creationTime), sizeof(creationTime));
  flstrm.read(reinterpret_cast<char *>(&modTime), sizeof(modTime));
  flstrm.read(reinterpret_cast<char *>(&startSectorLoc), sizeof(startSectorLoc));
  flstrm.read(reinterpret_cast<char *>(&streamSize), sizeof(streamSize));
}

inline unsigned int DirEntry::get_direntry_offset(CFHeader &cfh, const USHORT sZ)
{
  return  (cfh.DirSect1 + 1) * sZ;
}

USHORT DirEntry::find_directory(std::ifstream &stream, CFHeader &header, std::u16string str)
{
  const USHORT sectorSize = header.get_sector_size();
  const unsigned int offset = get_direntry_offset(header, sectorSize);
  std::vector<ULONG> fat = header.loadFat(stream, header);

  int sectors = header.DirSect1;

  while (fat[sectors] != ENDOFCHAIN)
  {
    sectors++;
  }

  const int n = ((sectors - header.DirSect1) + 1) * (sectorSize / DIRENTRY_SIZE);
  int id{};

  for (int i = 1; i <= n; i++)
  {
    readDirEntry(stream);
    if (objType == DIR_ROOT || objType == DIR_STORAGE)
    {
      id = childID;
    }
    else if (objType == DIR_STREAM)
    {
      if (((str.length() + 1) * 2) > nameLength)
      {
	id = rightSibID;
      }
      else if (((str.length() + 1) * 2) < nameLength)
      {
	id = leftSibID;

      }
      else
      {
	if (str.compare(name) == 0)
	{
	  return (startSectorLoc + 1) * sectorSize;
	}
      }
    }
    stream.seekg(offset, std::ios::beg);
    stream.seekg((id * sizeof(DirEntry)), std::ios::cur);
  }
  return 0;
}
