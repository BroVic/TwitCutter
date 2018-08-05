CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
INCLUDE_DIRECTORIES($(twtcut_project_SOURCE_DIR))
SET(CMAKE_CXX_STANDARD 14)
SET(SOURCE_FILES
    cfh.cpp
    clx.cpp
    cmdmain.cpp
    doccproc.cpp
    dtypes.cpp
    fib.cpp
    genproc.cpp
    post.cpp
    print.cpp
    starters.cpp
    txtproc.cpp)
ADD_EXECUTABLE(twtcut ${SOURCE_FILES})
