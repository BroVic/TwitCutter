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
		- Locate the Clx using data available on the FIB.
		- Read the Clx from the stream.
		- Make arrays for the character positions (CPs) and Pcds.
		- Retrieve the text from the *WordDocument* stream; build a string with same.
* Splice
	+ string is split into chunks
		- Set limits (less than 120 characters)
		- Add pagination
* Display
	+ send to stdout
	+ send to file
	+ ...
