// cfh.cpp
// Implemendation for cfh.h

#include "cfh.h"


// Special values used for the FAT
constexpr unsigned long MAXREGSECT  = 0xFFFFFFFA;
constexpr unsigned long RESERVED    = 0xFFFFFFFB;
constexpr unsigned long DIFSECT     = 0xFFFFFFFC;
constexpr unsigned long FATSECT     = 0xFFFFFFFD;
constexpr unsigned long ENDOFCHAIN  = 0xFFFFFFFE;
constexpr unsigned long FREESECT    = 0xFFFFFFFF;

CFHeader::CFHeader()
{
  for (auto i = 0; i < SIGN_ELEMENTS; ++i)
    Sig[i] = 0;
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
  for (auto i = 0; i < DIFAT_LENGTH; ++i)
    Difat[i] = 0;
}

CFHeader::~CFHeader()
{
}

// Reads the Compound File Header 
void CFHeader::readCFHeader(std::ifstream & dcstream)
{
  dcstream.read(reinterpret_cast<char *>(&Sig), (sizeof(unsigned char) * SIGN_ELEMENTS));
  dcstream.read(reinterpret_cast<char *>(&CLSID_NULL), sizeof(CLSID));
  dcstream.read(reinterpret_cast<char *>(&VerMinor), sizeof(unsigned short));
  dcstream.read(reinterpret_cast<char *>(&VerDll), sizeof(unsigned short));
  dcstream.read(reinterpret_cast<char *>(&ByteOrder), sizeof(unsigned short));
  dcstream.read(reinterpret_cast<char *>(&SectorShift), sizeof(unsigned short));
  dcstream.read(reinterpret_cast<char *>(&MinSectorShift), sizeof(unsigned short));
  dcstream.read(reinterpret_cast<char *>(&Reserved), sizeof(unsigned short));
  dcstream.read(reinterpret_cast<char *>(&Reserved2), sizeof(unsigned long));
  dcstream.read(reinterpret_cast<char *>(&NumDirSects), sizeof(unsigned long));
  dcstream.read(reinterpret_cast<char *>(&NumFatSects), sizeof(unsigned long));
  dcstream.read(reinterpret_cast<char *>(&DirSect1), sizeof(unsigned long));
  dcstream.read(reinterpret_cast<char *>(&TransactSig), sizeof(unsigned long));
  dcstream.read(reinterpret_cast<char *>(&MiniStrMax), sizeof(unsigned long));
  dcstream.read(reinterpret_cast<char *>(&MiniFatSect1), sizeof(unsigned long));
  dcstream.read(reinterpret_cast<char *>(&NumMiniFatSects), sizeof(unsigned long));
  dcstream.read(reinterpret_cast<char *>(&DifatSect1), sizeof(unsigned long));
  dcstream.read(reinterpret_cast<char *>(&NumDifatSects), sizeof(unsigned long));
  dcstream.read(reinterpret_cast<char *>(&Difat), (sizeof(unsigned long) * DIFAT_LENGTH));
}

// Reads the FAT into memory
// A particular field of the FAT is identified via the Difat and offset
// calculated from the sector size of file, and then copied into a vector
std::vector<unsigned long> CFHeader::loadFat(std::ifstream & stream) 
{
  const unsigned short szSect = this->get_sector_size();
  std::vector<unsigned long> difatArray(copy_difat(stream));
  std::vector<unsigned long> fat;
  unsigned long fatValue = MAXREGSECT;
  unsigned long fatSectorOffset = 0;

  auto length = difatArray.size();
  for (unsigned int i = 0; i < length; ++i)
  {
    fatSectorOffset = get_sector_offset(difatArray[i]);
    stream.seekg(fatSectorOffset);

    const int fatLengthPerSector = szSect / sizeof(unsigned long);
    for (int j = 0; j < fatLengthPerSector; ++j)
    {
      stream.read(reinterpret_cast<char *>(&fatValue), sizeof(unsigned long));
      fat.push_back(fatValue);
    }
  }
  return fat;
}

// Calculates the sector size of the file using the SectorShift value of the
// Compound File Header
inline unsigned short CFHeader::get_sector_size()
{
  return static_cast<unsigned short>(pow(2, SectorShift));
}

// Identifies the file offset for a particular sector value
unsigned long CFHeader::get_sector_offset(const unsigned long sectorNumber)
{
  return (sectorNumber + 1) * get_sector_size();
}

// Creates an in-memory copy of the Difat.
// This helps us make sure that anygg additional Difat sectors are
// properly captured and to serve as an anchor to the FAT.
std::vector<unsigned long> CFHeader::copy_difat(std::istream &stream)
{
  std::vector<unsigned long> difatCopy(Difat, Difat + sizeof(Difat) / sizeof(unsigned long));

  if (DifatSect1 > 0)
  { // only go this route if there are any Difat sectors
    const unsigned short sectSz = get_sector_size();    
    int difatSectOffset = get_sector_offset(DifatSect1);
    const int difatLenPerSector = sectSz / sizeof(unsigned long);
    unsigned long difatVal = 0;

    unsigned int numDifatSectors = this->NumDifatSects;
    if (this->VerDll == MAJOR_VERSION_3)
    { // exclude Difat in header and compute
      numDifatSectors = ((this->NumFatSects - DIFAT_LENGTH) / (difatLenPerSector - DIFAT_NEXT_LOC)) + 1;
    }
    // Sector-bu-sector looping
    for (unsigned int i = 0; i < numDifatSectors; ++i)
    {
      stream.seekg(difatSectOffset);
      // Loop within a sector
      for (int j = 0; j < difatLenPerSector; ++j)
      {
	stream.read(reinterpret_cast<char *>(&difatVal), sizeof(unsigned long));

	// The last field of Difat sectors do not hold FAT sector numbers
	// but instead hold the value of the next Difat sector if it exists.
	// In such a case, the offset is returned and used to reset the stream
	// atop the outer loop.
	if (j != difatLenPerSector - DIFAT_NEXT_LOC)
	{
	  difatCopy.push_back(difatVal);
	}
	else
	{
	  if (difatVal != ENDOFCHAIN)
	    difatSectOffset = get_sector_offset(difatVal);
	}
      }
    }
  }
  return difatCopy;
}

/////////////////////////////////////////////////////////
// Implementations related to the Directory Entry array
////////////////////////////////////////////////////////
constexpr unsigned char DIRENTRY_SIZE = 128;

// The usual suspects...
DirEntry::DirEntry()
{
  for (int i = 0; i < 32; i++)
    name[i]       = { };
  
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

// Looks for the file offset of a given stream object within using the stream's
// starting sector location specified in its Diretory Entry structure. This
// receives the name of the stream object we're looking for
unsigned long DirEntry::find_stream_object(std::ifstream &stream, CFHeader &header, std::u16string str)
{
  const unsigned short sectorSize = header.get_sector_size();
  const long long rootOffset = get_direntry_offset(header, sectorSize);

  // Determine length of Directory Entry array via FAT
  std::vector<unsigned long> fatArray = header.loadFat(stream);
  unsigned long sector = header.DirSect1;

  while (true)
  {
    if (fatArray[sector] == ENDOFCHAIN || fatArray[sector] == FREESECT)
      break;
    else
      ++sector;
  }
  const int arrayLen = ((sector - header.DirSect1) + 1 * (sectorSize / DIRENTRY_SIZE));
  
  // TODO: Trim unallocated fields

  // Iterate through the hierarchy of Directory Entries
  // starting from the Root Directory Entry. We are looking
  // for the one whose name matches the supplied string
  long long diff;
  int nextID = 0;
  stream.seekg(rootOffset, std::ios_base::beg);
  for (auto i = 0; i < arrayLen; ++i)
  {
    diff = 0;
    readDirEntry(stream);
    
    if (objType == DIR_ROOT || objType == DIR_STORAGE)
    {
      nextID = childID;
    }
    else if (objType == DIR_STREAM)
    {  // We alwasy add 1 to string to account for null terminator
      if (((str.length() + 1) * 2) > nameLength)
      {
	nextID = rightSibID;
      }
      else if (((str.length() + 1) * 2) < nameLength)
      {
	nextID = leftSibID;
      }
      else if (str.compare(name) == 0)
      {  // We add 1 here to account for file header
	return (startSectorLoc + 1) * sectorSize;	
      }
    }
    diff = rootOffset - stream.tellg();
    stream.seekg(diff, std::ios::cur);
    stream.seekg(nextID * DIRENTRY_SIZE, std::ios::cur);
  }
  return 0;
}

// Obtains the file offset of the first Directory Entry sector a.k.a Root Entry
// thereby giving us access to metadata on the storage and stream objects
inline long long DirEntry::get_direntry_offset(const CFHeader &cfh, const unsigned short sectorSz)
{
  return (cfh.DirSect1 + 1) * sectorSz;
}

// Reads individual data members of an indivitual Directory Entry structure
void DirEntry::readDirEntry(std::ifstream& flstrm)
{
  flstrm.read(reinterpret_cast<char *>(&name), sizeof(char16_t) * UTF16_CODE_POINTS);
  flstrm.read(reinterpret_cast<char *>(&nameLength), sizeof(unsigned short));
  flstrm.read(reinterpret_cast<char *>(&objType), sizeof(unsigned char));
  flstrm.read(reinterpret_cast<char *>(&colorFlag), sizeof(unsigned char));
  flstrm.read(reinterpret_cast<char *>(&leftSibID), sizeof(unsigned long));
  flstrm.read(reinterpret_cast<char *>(&rightSibID), sizeof(unsigned long));
  flstrm.read(reinterpret_cast<char *>(&childID), sizeof(unsigned long));
  flstrm.read(reinterpret_cast<char *>(&clsid), sizeof(CLSID));
  flstrm.read(reinterpret_cast<char *>(&stateBits), sizeof(unsigned long));
  flstrm.read(reinterpret_cast<char *>(&creationTime), sizeof(FILETIME));
  flstrm.read(reinterpret_cast<char *>(&modTime), sizeof(FILETIME));
  flstrm.read(reinterpret_cast<char *>(&startSectorLoc), sizeof(unsigned long));
  flstrm.read(reinterpret_cast<char *>(&streamSize), sizeof(unsigned long long));
}
