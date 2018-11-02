#include "doccproc.h"

DoccProcessor::DoccProcessor() 
	: olehdr{},
	fib{},
	clxobj{},
	root{},
	stringColl{},
	wstringColl{},
	strmName{},
	sectSz{},
	utfChar{},
	ansiChar{},
	wdocStart{},
	tablStart{},
	clxOffset{},
	strmOffset{},
	altAnsiExclude{
		{ 0x82, 0x201A },
		{ 0x83, 0x0192 },
		{ 0x84, 0x201E },
		{ 0x85, 0x2026 },
		{ 0x86, 0x2020 },
		{ 0x87, 0x2021 },
		{ 0x88, 0x02C6 },
		{ 0x89, 0x2030 },
		{ 0x8A, 0x0160 },
		{ 0x8B, 0x2039 },
		{ 0x8C, 0x0152 },
		{ 0x91, 0x2018 },
		{ 0x92, 0x2019 },
		{ 0x93, 0x201C },
		{ 0x94, 0x201D },
		{ 0x95, 0x2022 },
		{ 0x96, 0x2013 },
		{ 0x97, 0x2014 },
		{ 0x98, 0x02DC },
		{ 0x99, 0x2122 },
		{ 0x9A, 0x0161 },
		{ 0x9B, 0x2034 },
		{ 0x9C, 0x0153 },
		{ 0x9F, 0x0178 }}
{
}

DoccProcessor::~DoccProcessor()
{	
}

void DoccProcessor::process_file(std::ifstream & strm)
{
	read_file_data(strm);
	collect_text(strm);
}

std::string DoccProcessor::getString() const
{
	return stringColl;
}

// Reads data from the Word Binary File Format (.DOC)
void DoccProcessor::read_file_data(std::ifstream &stream)
{
	// Read the Compound File Header
	olehdr.readCFHeader(stream);
	auto offset = olehdr.get_sector_offset(olehdr.DirSect1);

	// Read the Directory Entry
	stream.seekg(offset);
	root.readDirEntry(stream);
	strmName = u"WordDocument";

	// Read the File Information Block
	wdocStart = root.find_stream_object(stream, olehdr, strmName);
	stream.seekg(wdocStart);
	fib.read_Fib(stream);

	// Find the Table Stream
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

	// Read the Clx structure
	clxOffset = fib.fibRgFcLcbBlob.fibRgFcLcb97.fcClx;
	stream.seekg(clxOffset, std::ios::cur);
	clxobj.readToClx(stream);
}

// Extracts text from the Word document stream object
void DoccProcessor::collect_text(std::ifstream &filestrm)
{	
	// For decisions on encoding
	constexpr int unicode = 0;
	constexpr int ansi = 1;

	const unsigned int numElem = clxobj.pcdt.plcPcd.pcdLength(clxobj);
	int encoding{};
	size_t index{};
	while (index < numElem)
	{
		strmOffset = clxobj.pcdt.plcPcd.aPcd[index].defineOffset();	
		encoding = clxobj.pcdt.plcPcd.aPcd[index].defineEncoding();
		if (encoding == ansi)
		{
			strmOffset /= 2;
		}		
		filestrm.seekg(wdocStart, std::ios::beg);
		filestrm.seekg(strmOffset, std::ios::cur);

		// Build string object
		int currentCP = clxobj.pcdt.plcPcd.getCharPos(index);
		int nextCP = clxobj.pcdt.plcPcd.getCharPos(index + 1);
		std::string temp;
		if (encoding == unicode)
		{
			wstringColl = transferUTFString(filestrm, currentCP, nextCP);
			temp = std::string(wstringColl.begin(), wstringColl.end());
		}
		else if (encoding == ansi)
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
