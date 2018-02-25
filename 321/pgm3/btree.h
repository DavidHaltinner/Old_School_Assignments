// btree.h

#ifndef BTREE_H
#define BTREE_H

#include <fstream>
#include <string>    //C++ string class
#include <stack>

#include "typedefs.h"
using namespace std;

class btreeType {

  public:

	// I have written these two constructors for you
	btreeType( char indexFileName[], char primaryFileName[] );
	btreeType( string CreateFlag, char indexFileName[], char dataFileName[] );

	bool Insert( logicalRecordType record );
	void GetRecord( int key, bool & found, logicalRecordType & record, long & address );
	void Sequential();

	void printIndexFilePage0();
	void printDataFilePage0 ();

  private:

	int root;    // pointer(rrn) to root node of btree

	fstream ixf; // index file
	fstream df ; // data  file

	char indexFileName[15];
	char dataFileName [15];

	stack<PathType> path;

	Count diskCounts;

	/*
	if the record is found (found=true)
		rrn = address of external node where key was found
		position = subscript where key is located in node
	if the record is not found (found=false)
		rrn = address of external node where search failed
		position = undefined
	*/
	void Find
	    (
	      //in
	           int key,  // primary key
	      //out
	           bool           & found,   // did we find the record (t/f)?
	           int            & rrn,     // rrn = address of external node
	           memoryNodeType & node,    // node = external node at address rrn
	           int            & position // subscript where key is or undefined
	    );

	// If needed
	void btreeInsert( int key, int rrn, memoryNodeType node, int ptr );


	// I have written the following 16 functions for you
	int            newIndexPage();
	memoryNodeType ReadIndexPage ( int rrn );
	void           WriteIndexPage( int rrn, memoryNodeType node );
	void           WriteRoot( int rrn );
	void           WriteFirstExternalNode( int rrn );

	int            newDataPage();
	dataPageType   ReadDataPage ( long cellNumber );
	void           WriteDataPage( long cellNumber, dataPageType page );

	availIndexType GetIndexHomePage();
	void           PutIndexHomePage( availIndexType page );
	btreePageType  GetIndexPage( long cellNumber );
	void           PutIndexPage( long cellNumber, btreePageType page );
	void           createIndexPages();

	availDataType  GetDataHomePage();
	void           PutDataHomePage( availDataType page );
	void           createDataPages();
};

#endif
