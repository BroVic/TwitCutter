// appset.h

// Header file for sundry app settings

#ifndef _APPSET_H_INCLUDED
#define _APPSET_H_INCLUDED

class WindowSettings
{
public:
	WindowSettings();
	static const char* get_appName();
	static const char* get_mainWinClass();
protected:
	static const char* appName;
	static const char* mainWinClass;
};

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
#endif // !_APPSET_H_INCLUDED
