cmake_minimum_required(VERSION 3.6)
include_directories($(twtcut_project_SOURCE_DIR))

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES cmdmain.cpp genproc.cpp doccproc.cpp txtproc.cpp dtypes.cpp cfh.cpp fib.cpp clx.cpp starters.cpp)
add_executable(twtcut ${SOURCE_FILES})
