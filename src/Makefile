# Makefile for TwitCutter (twitcut.exe)

OBJS= CFDirEntry.o \
      Clx.o \
	  DdocProc.o \
	  GenericProc.o \
	  CmdMain.o \
	  FIB.o \
	  CFHeader.o \
	  dtypes.o \
          cmdctrl.o
CC=g++
CPP_FLAGS= -std=c++11 -g -Wall -pedantic
PROG=twitcut

$(PROG): $(OBJS)
	$(CC) $(CPP_FLAGS) -o $(PROG) $(OBJS)

CmdMain.o: GenericProc.h cmdctrl.h
	$(CC) $(CPP_FLAGS) -c CmdMain.cpp

dtypes.o: dtypes.h
	$(CC) $(CPP_FLAGS) -c dtypes.cpp

CFHeader.o: CFHeader.h
	$(CC) $(CPP_FLAGS) -c CFHeader.cpp

CFDirEntry.o: CFDirEntry.h
	$(CC) $(CPP_FLAGS) -c CFDirEntry.cpp

FIB.o: FIB.h
	$(CC) $(CPP_FLAGS) -c FIB.cpp

Clx.o: Clx.h
	$(CC) $(CPP_FLAGS) -c Clx.cpp

GenericProc.o: GenericProc.h
	$(CC) $(CPP_FLAGS) -c GenericProc.cpp

DdocProc.o: DdocProc.h
	$(CC) $(CPP_FLAGS) -c DdocProc.cpp

cmdctrl.o: cmdctrl.h
	$(CC) $(CPPS_FLAGS) -c cmdctrl.cpp

.Phony: clean
clean:
	rm $(PROG) $(OBJS)
