// pool.cc

#include <iostream>
#include <cstdlib>    // exit is here
#include "pool.h"


// ========================
// 	LRUBufferPool
// ========================
// constructor

LRUBufferPool :: LRUBufferPool(int frameSizeInBytes,int maxFrames,fstream *dB)
               :    BufferPool(frameSizeInBytes, maxFrames, dB)
{
  this->frameSize      = frameSizeInBytes;
  this->maximumFrames  = maxFrames;
  this->dB             = dB;
  this->numberOfFrames = 0;
  this->top            = -1;

  this->hits       = 0;
  this->misses     = 0;
  this->writeBacks = 0;

	// create initially empty buffer pool
  bufferPool = new Frame*[maxFrames];
}

// =========================
// 	~LRUBufferPool
// =========================
// destructor

LRUBufferPool :: ~LRUBufferPool ()
{
  for (int i=0; i<maximumFrames; i++)  delete bufferPool[i];
  delete [] bufferPool;
}

// ==================
//	getStats
// ==================
// return statistics

void LRUBufferPool :: getStats( int & hits, int & misses, int & writeBacks )
{
  hits       = this->hits;
  misses     = this->misses;
  writeBacks = this->writeBacks;
}

// ====================
//	isBuffered
// ====================
// is logical record at offset "fileOffset" in the buffer pool?
// no: return -1 ; yes: return frameNumber

int  LRUBufferPool :: isBuffered(int fileOffset) const
{
  int slot=fileOffset/frameSize;
  slot *= frameSize;
  Frame * temp=new Frame(frameSize,slot);
  dB->seekg(slot);
  dB->read((char*)temp, frameSize);
  for (int i=0; i<numberOfFrames-1; i++)
    if (bufferPool[i]->baseOffset==temp->baseOffset) return i;
  return -1;
}

// =============
//	get
// =============
// return "address" of logical record at offset "fileOffset"

char* LRUBufferPool :: get(int fileOffset, ofstream & logf)
{
  int slot=isBuffered(fileOffset);
  if (slot>-1) {
    logf<<"     buffer pool: record found in frame "<<slot<<endl;
    logf<<"     buffer pool: record now in frame "<<top<<endl;
    moveToFront(slot);
    hits++;
    return (char*)bufferPool[top];
  }
  else {
    int slot=fileOffset/frameSize;
    slot *= frameSize;
    Frame* temp=new Frame(frameSize,slot); 
    dB->seekg(slot);
    dB->read((char*)temp,frameSize);
    insertIntoBufferPool(temp, logf);
    misses++;
    return (char*)temp;
  }
}

// ==============================
// 	insertIntoBufferPool  ?
// ==============================
// insert frame "toAdd" into buffer pool
// called by get

void LRUBufferPool :: insertIntoBufferPool(Frame * toAdd, ostream & logf)
{
  if (numberOfFrames==maximumFrames) {
    logf<<"     buffer pool: removing block in frame 0"<<endl;
    if (bufferPool[0]->dirty) writeBacks++;
    for (int i=0; i<numberOfFrames-1; i++)
      bufferPool[i]=bufferPool[i+1];
    bufferPool[top]=toAdd;
  }
  else {
    bufferPool[numberOfFrames]=toAdd;
    top=numberOfFrames;
    numberOfFrames++;
  }
  logf<<"     buffer pool: insert page into frame "<<top<<endl;
}

// =============
//	put
// =============
// update data in a frame

void LRUBufferPool :: put(char* toPut,int fileOffset,int size, ostream & logf)
{
  int slot=isBuffered(fileOffset);
  if (slot<0) {
    int BOffset=fileOffset/frameSize;
    BOffset *= frameSize;
    Frame * temp=new Frame(size, BOffset);
    temp->byte=toPut;
    temp->dirty=true;
    insertIntoBufferPool(temp, logf);
    writeToDisk(fileOffset, top);
    misses++;
  }
  else {
    logf<<"     buffer pool: record found in frame "<<slot<<endl;
    logf<<"     buffer pool: updating record in frame "<<slot<<endl;
    bufferPool[slot]->byte=toPut;
    bufferPool[slot]->dirty=true;
    moveToFront(slot);
    writeToDisk(fileOffset, top);
    logf<<"     buffer pool: record now in frame "<<top<<endl;
    hits++;
  }
}

// =====================
//	moveToFront
// =====================
// move frameNumber "f" to top(front) of list

void LRUBufferPool :: moveToFront( int f )
{
  Frame * temp=bufferPool[f];
  for (int i=f; i<numberOfFrames-1; i++)
    bufferPool[i]=bufferPool[i+1];
  bufferPool[top]=temp;
}

// =====================
//	flushToDisk
// =====================
// on exit, write all dirty frames to disk

void LRUBufferPool :: flushToDisk(ostream & logf)
{
   for ( int f=top; f>=0; f--) {
     if (bufferPool[f]->dirty) logf<<"     buffer pool flush: frame "<<f<<endl;
   }
}

// =====================
//	writeToDisk
// =====================
// write buffer frame "frameNumber" to disk

void LRUBufferPool :: writeToDisk(int fileOffset, int frameNumber)
{
  int slot=fileOffset/frameSize;
  slot *= frameSize;
  dB -> seekp(slot);
  dB -> write((char *)bufferPool[frameNumber], frameSize);
}
