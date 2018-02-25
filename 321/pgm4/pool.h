// pool.h

#ifndef _LRUPOOL_H_
#define _LRUPOOL_H_

#include <fstream>
#include "bufferpool.h"
#include "frame.h"
using namespace std;

class	LRUBufferPool  :  public BufferPool {

private:
	int	 frameSize;
	int	 numberOfFrames;
	int	 maximumFrames;
	int	 top;
	Frame	 **bufferPool;   // array of (pointer to Frame)
	fstream  *dB;
	ofstream log;

	int hits;
	int misses;
	int writeBacks;

	int  isBuffered(int fileOffset) const;
	void writeToDisk (int fileOffset, int frameNumber);
	void moveToFront (int f);
	void insertIntoBufferPool(Frame * toAdd, ostream & logf);  // ?

		// disable Copy Constructor and Copy Assignment Operator
	LRUBufferPool(const LRUBufferPool & );
	LRUBufferPool operator= (const LRUBufferPool & );

public:
	virtual ~LRUBufferPool();


	// Application Programming Interface defined by class BufferPool

	LRUBufferPool(int frameSizeInBytes, int maxFrames, fstream * in );
	char	*get(int fileOffset, ofstream & logf);
	void	put(char *toPut, int fileOffset, int size, ostream&);
	void	flushToDisk(ostream&);
	void	showPoolInHex( ostream& );
	void    getStats(int&,int&,int&);
};

#endif
