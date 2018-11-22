#include "clx.h"

Clx::Prc::PrcData::Prl::Sprm::Sprm()
{
  ispmd = {};
  fSpec = {};
  sgc   = {};
  spra  = {};
}

Clx::Prc::PrcData::Prl::Sprm::~Sprm()
{
}

Clx::Prc::PrcData::Prl::Prl()
{
}

Clx::Prc::PrcData::Prl::~Prl()
{
}

Clx::Prc::PrcData::PrcData()
{
  cbGrpprl = {};
}

Clx::Prc::PrcData::~PrcData()
{
}

Clx::Prc::Prc()
{
  clxt = {};
}

Clx::Prc::~Prc()
{
}

Clx::Pcdt::PlcPcd::Pcd::Prm::Prm()
{
  fComplex = {};
  data     = {};
}

Clx::Pcdt::PlcPcd::Pcd::Prm::~Prm()
{
}

Clx::Pcdt::PlcPcd::Pcd::FcCompressed::FcCompressed()
{
  fc          = {};
  fCompressed = {};
  r1          = {};
}

Clx::Pcdt::PlcPcd::Pcd::FcCompressed::~FcCompressed()
{
}

Clx::Pcdt::PlcPcd::Pcd::Pcd()
{
  fNoParaLast = {};
  fR1         = {};
  fDirty      = {};
  fR2         = {};
  fc          = {};
}

Clx::Pcdt::PlcPcd::Pcd::~Pcd()
{
}

Clx::Pcdt::PlcPcd::PlcPcd()
{
  aCP  = nullptr;
  aPcd = nullptr;
}

Clx::Pcdt::PlcPcd::~PlcPcd()
{
}

Clx::Pcdt::Pcdt()
{
  clxt = {};
  lcb = {};
}

Clx::Pcdt::~Pcdt()
{
}

Clx::Clx()
{
  rgPrc = nullptr;
}

Clx::~Clx()
{
}

void Clx::Prc::PrcData::Prl::Sprm::readSprm(std::ifstream &stream)
{
  unsigned short tmp = 0x0000;
  stream.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));

  unsigned long msk_ispmd = 0x1FF;
  unsigned long fS = 0x200;
  unsigned long msk_sgc = 0x1C00;
  unsigned long msk_spra = 0xE00;

  ispmd = tmp & msk_ispmd;
  fSpec = (tmp & fS) >> 9;
  sgc = (tmp & msk_sgc) >> 10;
  spra = (tmp & msk_spra) >> 13;
}

void Clx::Pcdt::PlcPcd::Pcd::FcCompressed::readFcData(std::ifstream &stream)
{
  unsigned long temp    = 0x00000000;
  unsigned long mask    = 0x3FFFFFFF;
  stream.read(reinterpret_cast<char *>(&temp), sizeof(temp));
  fc = mask & temp;

  const int shift = sizeof(unsigned char);
  unsigned char temp2 = 0x00;
  unsigned char fCmprsd = 0x40;
  unsigned char rBit = 0x80;
  stream.seekg(-shift, std::ios::cur);
  stream.read(reinterpret_cast<char *>(&temp2), sizeof(unsigned char));
  fCmprsd &= temp2;
  fCompressed = fCmprsd >> 6;
  rBit &= temp2;
  r1 = rBit >> 7;
}

void Clx::Pcdt::PlcPcd::Pcd::Prm::readPrmData(std::ifstream &curstream)
{
  unsigned short tmp  = 0;
  unsigned short mask = 0xFFFE;
  unsigned short fC   = 0x1;

  curstream.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
  fComplex = fC & tmp;
  data = (mask & tmp ) >> 1;
}

void Clx::Pcdt::PlcPcd::Pcd::readPcdData(std::ifstream &flsrc)
{
  unsigned short temp  = 0x0000;
  unsigned short mask  = 0xFFF8;
  unsigned char fNPL    = 0x1;
  unsigned char fROne   = 0x2;
  unsigned char fD      = 0x4;

  flsrc.read(reinterpret_cast<char *>(&temp), sizeof(temp));
  fNoParaLast = fNPL & temp;
  fR1         = (fROne & temp) >> 1;
  fDirty      = (fD & temp) >> 2;
  fR2         = (temp & mask) >> 3;

  fc.readFcData(flsrc);
  prm.readPrmData(flsrc);
}

// Computes the number of elements in a Pcd array
inline unsigned long Clx::Pcdt::PlcPcd::pcdLength(Clx& cobj)
{
  return (cobj.pcdt.lcb - 4) / (4 + SIZE_OF_PCD);
}

// Reads from filestream into a Pcdt structure
void Clx::Pcdt::readPcdt(std::ifstream &strm, unsigned char fstVar, Clx &obj)
{
  clxt = fstVar;
  strm.read(reinterpret_cast<char *>(&lcb), sizeof(unsigned long));
  unsigned long numArr = obj.pcdt.plcPcd.pcdLength(obj);
  plcPcd.readPlcPcd(strm, numArr);
}

// Decides on how to start reading the structure
void Clx::readToClx(std::ifstream &stream)
{
  unsigned char tmpClxt{};
  stream.read(reinterpret_cast<char *>(&tmpClxt), sizeof(unsigned char));

  if (tmpClxt == 0x01)
  {
      // prc.readPrc(stream, tmpClxt);

      // NB: if this branch is followed, end with a reading of the first
      // field of the next structure, for a smooth transition
  }
	
  pcdt.readPcdt(stream, tmpClxt, *this);
}

// Reads from filestream into a PlPcd structure
void Clx::Pcdt::PlcPcd::readPlcPcd(std::ifstream &strm, unsigned long num)
{
  num++;
  aCP = new (std::nothrow) unsigned long[num]{};
  if (aCP == 0)
  {
    std::cerr << "Requested memory could not be allocated" << std::endl;
  }

  for (size_t i = 0; i < num; i++)
  {
    strm.read(reinterpret_cast<char *>(&aCP[i]), sizeof(unsigned long));
  }
	
  --num;
  aPcd = new (std::nothrow) Pcd[num]{};
  if (aPcd == 0)
  {
    std::cerr << "Requested memory could not be allocated" << std::endl;
  }

  for (size_t i = 0; i < num; i++)
  {
    aPcd[i].readPcdData(strm);
  }
}

// Gets the stream offset for a specific character position
unsigned short Clx::Pcdt::PlcPcd::Pcd::defineOffset() const
{
  return fc.fc;	
}

// Get the encoding to be used
int Clx::Pcdt::PlcPcd::Pcd::defineEncoding() const
{
  return static_cast<int>(fc.fCompressed);
}

// Gets a character position
unsigned long Clx::Pcdt::PlcPcd::getCharPos(int ind)
{
  return aCP[ind];
}
