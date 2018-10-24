#include "doccproc.h"

DoccProcessor::DoccProcessor()
{
	this->setAnsiExceptions();
}

DoccProcessor::~DoccProcessor()
{	
}

void DoccProcessor::process_file(std::ifstream & strm)
{
	this->read_file_data(strm);
	this->collect_text(strm);
}

std::string DoccProcessor::getString() const
{
	return stringColl;
}

void DoccProcessor::read_file_data(std::ifstream &stream)
{
  olehdr.readCFHeader(stream);
  auto offset = olehdr.get_sector_offset(olehdr.DirSect1);

  stream.seekg(offset);
  root.readDirEntry(stream);
  strmName = u"WordDocument";

  wdocStart = root.find_stream_object(stream, olehdr, strmName);
  stream.seekg(wdocStart);
  fib.read_Fib(stream);
  
  if (fib.base.fWhichTblStm)
  {
	  strmName = u"1Table";
  }
  else
  {
	  strmName = u"0Table";
  }

  tablStart = root.find_stream_object(stream, olehdr, strmName);
  stream.seekg(tablStart);

  clxOffset = fib.fibRgFcLcbBlob.fibRgFcLcb97.fcClx;
  stream.seekg(clxOffset, std::ios::cur);

  clxobj.readToClx(stream);
}

void DoccProcessor::collect_text(std::ifstream &filestrm)
{	
	const unsigned int numElem = clxobj.pcdt.plcPcd.pcdLength(clxobj);
	int encoding{};
	size_t index{};

	while (index < numElem)
	{
		this->strmOffset = clxobj.pcdt.plcPcd.aPcd[index].defineOffset();
		
		encoding = clxobj.pcdt.plcPcd.aPcd[index].defineEncoding();
		if (encoding == ANSI)
		{
			this->strmOffset /= 2;
		}
		
		filestrm.seekg(wdocStart, std::ios::beg);
		filestrm.seekg(strmOffset, std::ios::cur);

		// Build string object
		int currentCP = clxobj.pcdt.plcPcd.getCharPos(index);
		int nextCP = clxobj.pcdt.plcPcd.getCharPos(index + 1);
		std::string temp;
		if (encoding == UNICODE)
		{
			this->wstringColl = transferUTFString(filestrm, currentCP, nextCP);
			temp = std::string(wstringColl.begin(), wstringColl.end());
		}
		else if (encoding == ANSI)
		{
			temp = transferAnsiString(filestrm, currentCP, nextCP);
		}
		
		stringColl.append(temp);
			
		index++;
	}
}

inline std::wstring DoccProcessor::transferUTFString(std::ifstream &giv, int cur, int nxt)
{
	std::wstring wstr;
	while (cur < nxt)
	{
		giv.read(reinterpret_cast<char *>(&utfChar), sizeof(utfChar));
		wstr.push_back(utfChar);
		cur++;
	}

	return wstr;
}

inline std::string DoccProcessor::transferAnsiString(std::ifstream &giv, int cur, int nxt)
{
	std::string str;
	while ( cur < nxt)
	{
		giv.read(reinterpret_cast<char *>(&ansiChar), sizeof(ansiChar));
		str.push_back(ansiChar);
		cur++;
	}

	return str;

}

inline void DoccProcessor::setAnsiExceptions()
{
	altANSI[0x82] = 0x201A;
	altANSI[0x83] = 0x0192;
	altANSI[0x84] = 0x201E;
	altANSI[0x85] = 0x2026;
	altANSI[0x86] = 0x2020;
	altANSI[0x87] = 0x2021;
	altANSI[0x88] = 0x02C6;
	altANSI[0x89] = 0x2030;
	altANSI[0x8A] = 0x0160;
	altANSI[0x8B] = 0x2039;
	altANSI[0x8C] = 0x0152;
	altANSI[0x91] = 0x2018;
	altANSI[0x92] = 0x2019;
	altANSI[0x93] = 0x201C;
	altANSI[0x94] = 0x201D;
	altANSI[0x95] = 0x2022;
	altANSI[0x96] = 0x2013;
	altANSI[0x97] = 0x2014;
	altANSI[0x98] = 0x02DC;
	altANSI[0x99] = 0x2122;
	altANSI[0x9A] = 0x0161;
	altANSI[0x9B] = 0x2034;
	altANSI[0x9C] = 0x0153;
	altANSI[0x9F] = 0x0178;
}
