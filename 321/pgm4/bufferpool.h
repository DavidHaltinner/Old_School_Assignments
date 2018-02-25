// bufferpool.h

#ifndef _POOL_H_
#define _POOL_H_

#include <fstream>
#include "frame.h"
using namespace std;

// Abstract Base Class
// Application Programming Interface

class	BufferPool {

public:
	BufferPool(int frameSizeInBytes, int maxFrames, fstream * in) {}

	virtual char *get(int fileOffset, ofstream & logf)                =0;
	virtual void put(char* toPut, int fileOffset, int size, ostream&) =0;
	virtual void flushToDisk(ostream&)                                =0;
	virtual void showPoolInHex( ostream& )                            =0;
	virtual void getStats(int&,int&,int&)                             =0;
};

#endif
