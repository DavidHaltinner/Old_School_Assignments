// disk.cc

#include <iostream>
#include <iomanip>
#include <fstream>

#include "btree.h"
using namespace std;
//==========================================================================
//
//                     INDEX  FILE  ROUTINES
//
//==========================================================================

//====================================
//          newIndexPage
//====================================
// return "address" of a node in the index file (like C++ new)
// the node is obtained from the free-space list

int btreeType::newIndexPage()
{
  availIndexType head = GetIndexHomePage();
  btreePageType page;

  if (head.avail == NIL) { // get more disk space

    for (int i=head.high+1; i<=head.high+MOREINDEX-1; i++) {
	page.u.next = i+1;
	PutIndexPage( i, page );
    }
    page.u.next = NIL;
    PutIndexPage( head.high+MOREINDEX, page );

    head.avail  = head.high + 1;
    head.high  += MOREINDEX;
    head.free   = MOREINDEX;
  }

  // there "is" an index page
  int newCell = head.avail;

  btreePageType node = GetIndexPage( newCell );
  int next = node.u.next;

  head.free -= 1;
  head.avail = next;
  PutIndexHomePage( head );

  return newCell;
}

//====================================
//         ReadIndexPage
//====================================
// read a page from the index file into
// a node of type memoryNodeType

memoryNodeType btreeType::ReadIndexPage( int rrn )
{
  int i;
  memoryNodeType node;

  // read from disk
  btreePageType page = GetIndexPage( rrn );

  // transfer to in-memory node from disk node
  node.n = page.u.btree.n;
  for (i=1; i<=node.n; i++) node.key [i] = page.u.btree.key [i-1];
  for (i=0; i<=node.n; i++) node.indx[i] = page.u.btree.indx[i  ];

  return node;
}

//====================================
//         WriteIndexPage
//====================================
// write a page to the index file from
// a node of type memoryNodeType

void btreeType::WriteIndexPage( int rrn, memoryNodeType node )
{
  int i;
  btreePageType page;

  // transfer to disk node from in-memory node
  page.u.btree.n = node.n;
  for (i=1; i<=node.n; i++) page.u.btree.key [i-1] = node.key [i];
  for (i=0; i<=node.n; i++) page.u.btree.indx[i  ] = node.indx[i];

  // write to disk
  PutIndexPage( rrn, page );
}

//====================================
//         WriteFirstExternalNode
//====================================
// save address of first external node in cell 0 (b+tree specific)

void btreeType::WriteFirstExternalNode( int rrn )
{
  availIndexType page0 = GetIndexHomePage();
  page0.first = rrn;
  PutIndexHomePage( page0 );
}

//====================================
//          WriteRoot
//====================================
// save address of root node in cell 0 of the index file

void btreeType::WriteRoot( int rrn )
{
  availIndexType page0 = GetIndexHomePage();
  page0.root = rrn;
  PutIndexHomePage( page0 );
}

//====================================
//          GetIndexHomePage
//====================================
// read cell 0 from index file into memory

availIndexType btreeType::GetIndexHomePage()
{
  availIndexType page;

  ixf.seekg(0L);
  ixf.read ( (char *)&page, sizeof(page) );
  return page;
}

//====================================
//          PutIndexHomePage
//====================================
// write cell 0 to index file from memory

void btreeType::PutIndexHomePage( availIndexType page )
{
  ixf.seekp(0L);
  ixf.write( (char *)&page, sizeof(page) );
}

//====================================
//          GetIndexPage
//====================================
// read a page from the index file into memory

btreePageType btreeType::GetIndexPage( long rrn )
{
  btreePageType page;

  ixf.seekg( sizeof(availIndexType) + (rrn-1)*sizeof(page) );
  ixf.read ( (char *)&page, sizeof(page) );
  return page;
}

//====================================
//          PutIndexPage
//====================================
// write a page to the index file from memory

void btreeType::PutIndexPage( long rrn, btreePageType page )
{
  ixf.seekp( sizeof(availIndexType) + (rrn-1)*sizeof(page) );
  ixf.write( (char *)&page, sizeof(page) );
}

//====================================
//          createIndexPages
//====================================
// request disk space in the index file from the Operating System
// put "nodes" on a free-space list

void btreeType::createIndexPages()
{
  availIndexType page0;

  page0.first = NIL           ;       //b+tree specific
  page0.root  = NIL           ;
  page0.high  = INITIALINDEX-1;
  page0.free  = INITIALINDEX-1;
  page0.avail = 1             ;
  PutIndexHomePage( page0 );

  btreePageType page;

  for (int i=1; i<=INITIALINDEX-2; i++) {
     page.u.next = i+1;
     PutIndexPage( i, page );
  }

  page.u.next = NIL;
  PutIndexPage( INITIALINDEX-1, page );
}


//==========================================================================
//
//                      DATA  FILE  ROUTINES
//
//==========================================================================

//====================================
//         newDataPage
//====================================
// return "address" of a node in the data file (like C++ new)
// the node is obtained from the free-space list

int btreeType::newDataPage()
{
  availDataType head = GetDataHomePage();
  dataPageType page;

  if (head.avail == NIL) { // get more disk space
    for (int i=head.high+1; i<=head.high+MOREINDEX-1; i++) {
	page.u.next = i+1;
	WriteDataPage( i, page );
    }
    page.u.next = NIL;
    WriteDataPage( head.high+MOREINDEX, page );

    head.avail  = head.high + 1;
    head.high  += MOREINDEX;
    head.free   = MOREINDEX;
  }

  int newCell = head.avail;
  dataPageType node = ReadDataPage( newCell );
  int next = node.u.next;

  head.free  -= 1;
  head.avail = next;
  PutDataHomePage( head );

  return newCell;
}

//====================================
//          ReadDataPage
//====================================
// read a page from the data file into memory

dataPageType btreeType::ReadDataPage( long rrn )
{
  dataPageType page;

  df.seekg( sizeof(availDataType) + (rrn-1)*sizeof(page) );
  df.read ( (char *)&page, sizeof(page) );
  return page;
}

//====================================
//          WriteDataPage
//====================================
// write a page to the data file from memory

void btreeType::WriteDataPage( long rrn, dataPageType page )
{
  df.seekp( sizeof(availDataType) + (rrn-1)*sizeof(page) );
  df.write( (char *)&page, sizeof(page) );
}

//====================================
//          GetDataHomePage
//====================================
// read cell 0 from data file into memory

availDataType btreeType::GetDataHomePage()
{
  availDataType page;

  df.seekg(0L);
  df.read ( (char *)&page, sizeof(page) );
  return page;
}

//====================================
//          PutDataHomePage
//====================================
// write cell 0 to data file from memory

void btreeType::PutDataHomePage( availDataType page )
{
  df.seekp(0L);
  df.write( (char *)&page, sizeof(page) );
}

//====================================
//          createDataPages
//====================================
// request disk space in the data file from the Operating System
// put "nodes" on a free-space list

void btreeType::createDataPages()
{
  availDataType page0;

  page0.high  = INITIALINDEX-1;
  page0.free  = INITIALINDEX-1;
  page0.avail = 1             ;
  PutDataHomePage( page0 );

  dataPageType page;

  for (int i=1; i<=INITIALINDEX-2; i++) {
     page.u.next = i+1;
     WriteDataPage( i, page );
  }

  page.u.next = NIL;
  WriteDataPage( INITIALINDEX-1, page );
}


/*****************************************************************************
* MY FUNCTIONS
*****************************************************************************/

void btreeType::printIndexFilePage0() {
  cout<<"Index File Page 0"<<endl;
  cout<<"     first      root     avail      high      free"<<endl;
  availIndexType page = GetIndexHomePage();
  cout<<setw(10)<<page.first<<setw(10)<<page.root<<setw(10)<<page.avail
      <<setw(10)<<page.high<<setw(10)<<page.free<<endl;
}
void btreeType::printDataFilePage0() {
  cout<<"Data File Page 0"<<endl;
  cout<<"     avail      high      free"<<endl;
  availDataType page = GetDataHomePage();
  cout<<setw(10)<<page.avail<<setw(10)<<page.high<<setw(10)<<page.free<<endl;
}

