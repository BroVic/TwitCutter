#include "DdocProc.h"

DdocProc::DdocProc()
{
}

DdocProc::~DdocProc()
{
}

VOID DdocProc::process_file(std::ifstream & stream)
{
	olehdr.readCFHeader(stream);
	stream.seekg(DirSect1 * _sectSz, std::ios::cur);

	readDirEntry(stream);
	_strmName = u"WordDocument";

	_wdocStart = find_directory(stream, _strmName);

	stream.seekg(_wdocStart, std::ios::beg);
	fib.readFib(stream);
	
	if (base.fWhichTblStm)
		_strmName = u"1Table";
	else { _strmName = u"0Table"; }

	_tablStart = find_directory(stream, _strmName);

	stream.seekg(_tablStart, std::ios::beg);
	
	_clxOffset = fibRgFcLcbBlob.fibRgFcLcb97.fcClx;
	stream.seekg(_clxOffset, std::ios::cur);

	readToClx(stream);

	return;
}

USHORT DdocProc::find_directory(std::ifstream& stream, std::u16string str)
{
	const int d1 = olehdr.DirSect1;
	const int sctSz = olehdr.set_sector_size();
	const int offset = (d1 + 1) * sctSz;

	std::vector<ULONG> fat = olehdr.loadFat(stream, sctSz);
	int sectors = d1;

	while (fat[sectors] != ENDOFCHAIN)
	{
		sectors++;
	}

	const int n = ((sectors - d1) + 1) * (sctSz / DIRENTRY_SIZE);
	int id = 0;
	for (int i = 1; i <= n; i++)
	{
		if (this->objType == DIR_ROOT || this->objType == DIR_STORAGE)
		{
			id = this->childID;
		}
		else if (this->objType == DIR_STREAM)
		{
			if (((str.length() + 1) * 2) > this->nameLength)
			{
				id = this->rightSibID;
			}
			else if (((str.length() + 1) * 2) < this->nameLength)
			{
				id = this->leftSibID;
			}
			else
			{
				if (str.compare(this->name) == 0)
				{
					return (this->startSectorLoc + 1) * sctSz;
				}
			}
		}
		stream.seekg(offset, std::ios::beg);
		stream.seekg((id * sizeof(DirEntry)), std::ios::cur);
		this->readDirEntry(stream);
	}
	return 0;
}

VOID DdocProc::collect_text(std::ifstream &filestrm)
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
	stringColl.write(reinterpret_cast<char *>(_utfChar), sizeof(_utfChar));
}