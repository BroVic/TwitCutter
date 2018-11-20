// constants.h

#ifndef _CONSTANTS_H_INCLUDED_
#define _CONSTANTS_H_INCLUDED_

enum FileExtension
{
	STATIC = -1,
	NOFILE,
	DOC,
	TXT
};

constexpr int zeroOffset = 0;

// For pagination
constexpr char openingTag  = '(';    // TODO: Make mutable; use struct.
constexpr char divisor     = '/';
constexpr char closingTag  = ')';
constexpr char spaceChar   = ' ';

//
// Character limits for text blocs
constexpr unsigned int characterMax = 140;
constexpr unsigned int characterLimit = 120;
#endif // !_CONSTANTS_H_INCLUDED_

