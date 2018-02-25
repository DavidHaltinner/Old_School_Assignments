// typedefs.h

/*
	Do not modify anything here
	If you think I made a mistake, ask me about it
*/


#ifndef TYPEDEFS_H 
#define TYPEDEFS_H

#include <math.h>    //ceil is here

const int DEGREE =  7;
const int NIL    =  0;
const int MID    =  (int) ceil((float)DEGREE/2.0);

const int INITIALINDEX   = 51;
const int MOREINDEX      = 10;
const int INITIALPRIMARY = 51;
const int MOREPRIMARY    = 10;

//=====================================================================
//
//                    btree nodes on disk
//
//=====================================================================

struct availIndexType {
	int first;  // address of first (left-most) external node
	int root;   // address(rrn) of Btree root node
	int high;   // highest numbered cell currently allocated
	int free;   // number of cells on free space list
	int avail;  // address(rrn) of first cell on free space list
};

struct diskNodeType {
	int n;
	int key [DEGREE-1];
	int indx[DEGREE  ];
};

struct btreePageType {
  union{
	long         next ;  // address of next cell on free space list
	diskNodeType btree;
  }u;
};

//=====================================================================
//
//                    btree nodes in memory
//
//=====================================================================

struct memoryNodeType {
	int n;		    //number of primary keys in page(node)
	int key [DEGREE+1]; //primary keys
	int indx[DEGREE+1]; //address of page(node) in index file
};

//=====================================================================
//
//                    logical records on disk
//
//=====================================================================

struct logicalRecordType {
	int  key    ;
	char name[8];
};

struct availDataType {
	int high;   // highest numbered cell currently allocated
	int free;   // number of cells on free space list
	int avail;  // address(rrn) of first cell on free space list
};

struct dataPageType {
  union{
	long              next;
	logicalRecordType record;
  }u;
};

//=====================================================================
//
//                    disk access counts (insert and delete)
//
//=====================================================================

struct Count {
   //searching
   int  search;

   //delete algorithm
   int  right, borrowRight, mergeRight, inorder,
	left , borrowLeft , mergeLeft , reduceRoot;
};

//=====================================================================
//
//                            PathType
//
//=====================================================================

struct PathType {
	int            rrn ;
	memoryNodeType node;
};

#endif
