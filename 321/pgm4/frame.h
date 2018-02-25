// frame.h

#ifndef _FRAME_H_
#define _FRAME_H_

#include <iostream>
#include <cstdlib>
using namespace std;

class	Frame {

public:
	bool	dirty;
	int	baseOffset;
	int	frameSize;
	char	*byte;

	Frame(int frameSize, int baseOffset)
	{
	  this->frameSize  = frameSize ;
	  this->baseOffset = baseOffset;
	  this->dirty      = false     ;

	  this->byte = new char[frameSize];
	  if (this->byte==NULL) {
	    cerr<<endl<<"new failed in Frame::Frame(int,int)"<<endl<<endl;
	    exit(1);
	  }
	}

	~Frame() { delete [] byte; }

private:
		// disable Copy Constructor and Copy Assignment Operator
	Frame(const Frame & );
	Frame operator= (const Frame & );
};

#endif
