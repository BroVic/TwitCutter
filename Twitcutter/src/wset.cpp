// wset.cpp

#include "wset.h"

const char* WindowSettings::appName = "Twitcutter";
const char* WindowSettings::mainWinClass = "TwitCutterWindowClass";

WindowSettings::WindowSettings()
{
}

const char* WindowSettings::get_appName()
{
	return appName;
}

const char* WindowSettings::get_mainWinClass()
{
	return mainWinClass;
}
