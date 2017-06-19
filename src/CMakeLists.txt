cmake_minimum_required(VERSION 3.6)

project(twtcut)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES CmdMain.cpp GenericProc.cpp DdocProc.cpp TxtProc.cpp dtypes.cpp CFHeader.cpp CFDirEntry.cpp FIB.cpp Clx.cpp)

add_executable(twtcut ${SOURCE_FILES})