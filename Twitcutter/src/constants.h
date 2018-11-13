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

constexpr int ZERO_OFFSET = 0;

// For pagination
constexpr char OPEN_TAG = '(';    // TODO: Make mutable; use struct.
constexpr char DIVISOR = '/';
constexpr char CLOSE_TAG = ')';
constexpr char SPACE = ' ';

//
// Character limits for text blocs
constexpr unsigned int CHARACTER_MAX = 140;
constexpr unsigned int CHARACTER_LIMIT = 120;
#endif // !_CONSTANTS_H_INCLUDED_

