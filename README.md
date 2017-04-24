# TwitCutter
... is currently under development.

## How the code is supposed to work (written in C++11, a lot of it *C-style*)

* Parse
    + for Word .DOC Binary Files
		- Open a .doc file
	    - Read the *Compound File Header (CFH)*.
		- Locate the offset of the *WordDocument* stream.
		- Read the *File Information Block (FIB)* from offset 0 of this stream.
		- Locate the *Table* stream.
		- Locate the *Clx* using data available on the FIB.
		- Read the *Clx* from the stream.
		- ...
