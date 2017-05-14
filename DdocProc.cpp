#include "DdocProc.h"

DdocProc::DdocProc()
{
	this->setANSIexceptions();
}

DdocProc::~DdocProc()
{	
}

void DdocProc::read_file_data(std::ifstream &stream)
{
	olehdr.readCFHeader(stream);
	_sectSz = olehdr.get_sector_size();
	stream.seekg(olehdr.DirSect1 * _sectSz, std::ios::cur);

	root.readDirEntry(stream);
	_strmName = u"WordDocument";

	_wdocStart = root.find_directory(stream, olehdr, _strmName);
	stream.seekg(_wdocStart, std::ios::beg);
	
	fib.readFib(stream);
	if (fib.base.fWhichTblStm)
	{
		_strmName = u"1Table";
	}
	else
	{
		_strmName = u"0Table";
	}

	_tablStart = root.find_directory(stream, olehdr, _strmName);

	stream.seekg(_tablStart, std::ios::beg);
	
	_clxOffset = fib.fibRgFcLcbBlob.fibRgFcLcb97.fcClx;
	stream.seekg(_clxOffset, std::ios::cur);

	clxobj.readToClx(stream);

	return;
}

void DdocProc::collect_text(std::ifstream &filestrm)
{	
	const unsigned int numElem = clxobj.pcdt.plcPcd.pcdLength(clxobj);
	int encoding{};
	size_t index{};

	while (index < numElem)
	{
		this->_strmOffset = clxobj.pcdt.plcPcd.aPcd[index].defineOffset();
		
		encoding = clxobj.pcdt.plcPcd.aPcd[index].defineEncoding();
		if (encoding == ANSI)
		{
			this->_strmOffset /= 2;
		}
		
		filestrm.seekg(_wdocStart, std::ios::beg);
		filestrm.seekg(_strmOffset, std::ios::cur);

		// Build string object
		int currentCP = clxobj.pcdt.plcPcd.getCharPos(index);
		int nextCP = clxobj.pcdt.plcPcd.getCharPos(index + 1);
		std::string temp;
		if (encoding == UNICODE)
		{
			this->_wstringColl = transferUTFString(filestrm, currentCP, nextCP);
			temp = std::string(_wstringColl.begin(), _wstringColl.end());
		}
		else if (encoding == ANSI)
		{
			temp = transferANSIString(filestrm, currentCP, nextCP);
		}
		
		this->_stringColl.append(temp);
			
		index++;
	}

	return;
}

inline std::wstring DdocProc::transferUTFString(std::ifstream &giv, int cur, int nxt)
{
	std::wstring wstr;
	while (cur < nxt)
	{
		giv.read(reinterpret_cast<char *>(&_utfChar), sizeof(_utfChar));
		wstr.push_back(_utfChar);
		cur++;
	}

	return wstr;
}

inline std::string DdocProc::transferANSIString(std::ifstream &giv, int cur, int nxt)
{
	std::string str;
	while ( cur < nxt)
	{
		giv.read(reinterpret_cast<char *>(&_ansiChar), sizeof(_ansiChar));
		str.push_back(_ansiChar);
		cur++;
	}

	return str;

}

void DdocProc::setANSIexceptions()
{
	_altANSI[0x82] = 0x201A;
	_altANSI[0x83] = 0x0192;
	_altANSI[0x84] = 0x201E;
	_altANSI[0x85] = 0x2026;
	_altANSI[0x86] = 0x2020;
	_altANSI[0x87] = 0x2021;
	_altANSI[0x88] = 0x02C6;
	_altANSI[0x89] = 0x2030;
	_altANSI[0x8A] = 0x0160;
	_altANSI[0x8B] = 0x2039;
	_altANSI[0x8C] = 0x0152;
	_altANSI[0x91] = 0x2018;
	_altANSI[0x92] = 0x2019;
	_altANSI[0x93] = 0x201C;
	_altANSI[0x94] = 0x201D;
	_altANSI[0x95] = 0x2022;
	_altANSI[0x96] = 0x2013;
	_altANSI[0x97] = 0x2014;
	_altANSI[0x98] = 0x02DC;
	_altANSI[0x99] = 0x2122;
	_altANSI[0x9A] = 0x0161;
	_altANSI[0x9B] = 0x2034;
	_altANSI[0x9C] = 0x0153;
	_altANSI[0x9F] = 0x0178;

	return;
}

void DdocProc::process_file(std::ifstream & strm)
{
	this->read_file_data(strm);
	this->collect_text(strm);

	return;
}
