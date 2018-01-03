include_directories($(twtcut_SOURCE_DIR))

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES cmdmain.cpp genericProc.cpp doccProc.cpp textProc.cpp dtypes.cpp cfHeader.cpp cfDirEntry.cpp fib.cpp clx.cpp)
add_executable(twtcut ${SOURCE_FILES})
