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
IF (WIN32)
  SET(SOURCE_FILES ${SOURCE_FILES}
    cfh.h
	clx.h
	doccproc.h
	dtypes.h
	fib.h
	genproc.h
	post.h
	print.h
	starters.h
	txtproc.h)
ENDIF (WIN32)
ADD_EXECUTABLE(twtcut ${SOURCE_FILES})
