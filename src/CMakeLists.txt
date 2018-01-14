cmake_minimum_required(VERSION 3.6)
include_directories($(twtcut_project_SOURCE_DIR))

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES cmdmain.cpp genproc.cpp doccproc.cpp textproc.cpp dtypes.cpp cfheader.cpp fib.cpp clx.cpp starters.cpp)
add_executable(twtcut ${SOURCE_FILES})
