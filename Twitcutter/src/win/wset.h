// wset.h

// Window Settings

#ifndef _WSET_H_INCLUDED_
#define _WSET_H_INCLUDED_

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

#endif // !_WSET_H_INCLUDED_
