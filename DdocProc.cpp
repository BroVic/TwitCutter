#include "DdocProc.h"

DdocProc::DdocProc()
{
}

DdocProc::~DdocProc()
{
}

VOID DdocProc::read_file_data(std::ifstream & stream)
{
	olehdr.readCFHeader(stream);
	_sectSz = olehdr.get_sector_size();
	stream.seekg(olehdr.DirSect1 * _sectSz, std::ios::cur);

	readDirEntry(stream);
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
	ULONG numElem = pcdt.calcArrayLength();
	size_t index = 0;
	while (index < numElem)
	{
		if (pcdt.plcPcd.aPcd[index].fc.fCompressed == 0)
		{
			_strmOffset = pcdt.plcPcd.aPcd[index].fc.fc;
		}
		else if (pcdt.plcPcd.aPcd[index].fc.fCompressed == 1)
		{
			_strmOffset = pcdt.plcPcd.aPcd[index].fc.fc / 2;
		}
		
		
		filestrm.seekg(_wdocStart, std::ios::beg);
		filestrm.seekg(_strmOffset, std::ios::cur);

		while (pcdt.plcPcd.aCP[index] < pcdt.plcPcd.aCP[index + 1])
		{
			transferUTFStreams(filestrm);
			pcdt.plcPcd.aCP[index]++;
		}

		index++;
	}

	transferUTFStreams(filestrm);

	return;
}

inline VOID DdocProc::transferUTFStreams(std::ifstream &giv)
{
	giv.read(reinterpret_cast<char *>(&_utfChar), sizeof(_utfChar));
	_stringColl.write(reinterpret_cast<char *>(_utfChar), sizeof(_utfChar));
}

void DdocProc::setANSIexceptions()
{

}

void DdocProc::process_file(std::ifstream & strm)
{
	read_file_data(strm);
	collect_text(strm);
	transferUTFStreams(strm);

	return;
}
