// wdim.h

// Window Dimensions: A Derived Class of Class WindowSettings

#ifndef _WDIM_H_INCLUDED
#define _WDIM_H_INCLUDED

#include "wset.h"

class WindowDimensions
	: public WindowSettings
{
public:
	WindowDimensions();

	void setX(const unsigned int);
	void setY(const unsigned int);
	void setWidth(const unsigned int);
	void setHeight(const unsigned int);
	unsigned int getX() const;
	unsigned int getY() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
private:
	unsigned int xPos;
	unsigned int yPos;
	unsigned int width;
	unsigned int height;
};

using WDim = WindowDimensions;
#endif // !_WDIM_H_INCLUDED

