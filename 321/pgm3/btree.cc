// btree.cc

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <string>    // C++ string class
#include <string.h>  // C strings (strcpy, etc.)

#include "btree.h"


//============================
//
//         btreeType
//
//============================
// constructor to create an initialized, empty Indexed File

btreeType::btreeType( string flag, char IndexFileName[], char DataFileName[] )
{
  if (flag != "create") {
    cerr << "\nbtreeType::btreeType: invalid create flag\n\n";
    exit(1);
  }

  strcpy(indexFileName , IndexFileName);
  strcpy(dataFileName  , DataFileName );

  root = NIL;  //empty btree

  // Index File

  ixf.open( indexFileName, ios::out );
  if ( ixf.fail() ) {
    cerr << "\nbtree create: could not open file " << indexFileName <<"\n\n";
    exit(1);
  }

  createIndexPages();
  ixf.close();

  ixf.open( indexFileName, ios::in | ios::out );
  if ( ixf.fail() ) {
    cerr << "\nbtree create: could not open file " << indexFileName <<"\n\n";
    exit(1);
  }

  // Data File

  df.open( dataFileName, ios::out );
  if ( df.fail() ) {
    cerr << "\nbtree create: could not open file " << dataFileName <<"\n\n";
    exit(1);
  }

  createDataPages();
  df.close();

  df.open( dataFileName, ios::in | ios::out );
  if ( df.fail() ) {
    cerr << "\nbtree create: could not open file " << dataFileName <<"\n\n";
    exit(1);
  }

}


//============================
//
//         btreeType
//
//============================
// constructor to open an existing Indexed File

btreeType::btreeType( char IndexFileName[], char DataFileName[] )
{
  strcpy(indexFileName,IndexFileName);
  strcpy(dataFileName ,DataFileName );

  df.open( dataFileName, ios::in | ios::out );
  if ( df.fail() ) {
    cerr << "\nbtree create: could not open file " << dataFileName <<"\n\n";
    exit(1);
  }

  ixf.open( indexFileName, ios::in | ios::out );
  if ( ixf.fail() ) {
    cerr << "\nbtree create: could not open file " << indexFileName <<"\n\n";
    exit(1);
  }

  availIndexType node = GetIndexHomePage();
  root = node.root;
}

//==========================
//
//          FIND
//
//==========================
// Try to find a record in the Indexed-Sequential File given the primary key

void btreeType :: Find
   (
     //in
     int key,

     //out
     bool           & found,
     int            & rrn,
     memoryNodeType & node,
     int            & position
   )
{
  int parent = NIL;
  rrn = root;

  //it is essential that we start with an empty stack on each call!
  //make the stack empty
  while (!path.empty()) path.pop();
  //push a bottom marker onto the stack
  PathType pathData;
  pathData.rrn = NIL;
  path.push(pathData);

  //search for key
  //we are at an external node when node.indx[k]<0 (k>=1)
  while (rrn > NIL) {
    pathData.rrn=rrn;
    path.push(pathData);
    node = ReadIndexPage( rrn );
    if (node.indx[1]<=0) {
      for (position=0; position<=node.n; position++)
        if (node.key[position]==key) {
          found=true;
          return;
        }
        found=false; 
        return; 
    }
    if (key > node.key[node.n])
      position=node.n+1;
    else {
      position=1;
      while (key>=node.key[position]) position++;
    }
    parent=rrn;
    rrn=node.indx[position-1];
  }
  // did not find key
  found = false;
  rrn   = parent;  //leaf node where search failed
}

//================================
//
//             INSERT
//
//================================
// Try to add a record to the Indexed-Sequential File
// if the record exists, do not insert and return false
// if the record does not exist, insert it and return true

bool btreeType :: Insert ( logicalRecordType record )
{
  int key=record.key;
  bool found;
  int rrn;
  memoryNodeType node;
  int pos;

  //is the record already in the file? if yes, return false
  Find( record.key, found,rrn,node,pos );
  if ( found )  return false;

  // A. store logical record in data file
  int dataslot=newDataPage();
  dataPageType dataPage;
  dataPage.u.record=record;
  WriteDataPage(dataslot, dataPage);

  // B. node is an EXTERNAL node upon function entry

  // B1. check for empty file
  if ( rrn == NIL ) { //index set is empty; create root node (external node)
    node.n=1;	
    for (int i=0; i<=DEGREE; i++) {
      node.indx[i]=0;
      node.key[i]=0;
    }
    node.key[1]=key;
    node.indx[1]=-dataslot;
    int address=newIndexPage();
    WriteIndexPage(address,node);
    WriteRoot(address);
    WriteFirstExternalNode(address);
    root=address;
    return true;
  }

  // assert: file is not empty
  // B2. insert info into EXTERNAL node
  bool inserted=false;
  for (int i=1; i<node.n+1; i++) {
    if (key<node.key[i]) {
      for (int j=node.n+1; j>=i+1; j--) {
        node.key[j]=node.key[j-1];
        node.indx[j]=node.indx[j-1];
      }
      node.key[i]=key;
      node.indx[i]=-dataslot;
      node.n++;
      inserted=true;
      break;
    }
  }
  if (!inserted) {
    node.key[node.n+1]=key;
    node.indx[node.n+1]=-dataslot;
    node.n++;
  }

  // B3. was the insertion legal?
  if ( node.n <= DEGREE-1 ) {
    WriteIndexPage( rrn, node );
    return true;
  }
  
  // B4. overflow: split the external node into left half and right half
  // B4(a) node <- left half; rightNode <- right half
  int middleKey=node.key[MID];
  int oldSize=node.n;
  node.n=MID-1;
  int rightSlot=newIndexPage();
  int oldRightSlot=node.indx[0];
  node.indx[0]=-rightSlot;
  WriteIndexPage(rrn,node); //SAVE LEFT NODE
  for (int i=0; i<MID+1; i++) {
    node.key[i]=node.key[oldSize-MID+i];
    node.indx[i]=node.indx[oldSize-MID+i];
  }
  node.n=MID;
  node.indx[0]=oldRightSlot;
  WriteIndexPage(rightSlot, node); //SAVE RIGHT NODE

//BROKE THE ROOT NODE, NEED NON-EXTERNAL NEW ROOT
  if (root==rrn) {
    node.n=1;	
    for (int i=0; i<=DEGREE; i++) {
      node.indx[i]=0;
      node.key[i]=0;
    }
    node.key[1]=middleKey;
    node.indx[0]=rrn;
    node.indx[1]=rightSlot;
    int address=newIndexPage();
    WriteIndexPage(address,node);
    WriteRoot(address);
    root=address;
    return true;
  }

//SEND MIDDLE KEY TO PARENT, AND IM NOT THE ROOT NODE
//COMBINE WITH ROOT THING SINCE STACK WILL HAVE 0 ON IT AT THE END
  PathType pathData;
  memoryNodeType parentNode;
  int leftSlot;
//BEGIN PARENT STUFF
  while(1) {
    path.pop();
    pathData=path.top();

    if (0==pathData.rrn) { //I AM THE ROOT!!!!
  //MAKE NEW ROOT
      memoryNodeType newRoot;
      newRoot.n=1;	
      for (int i=0; i<=DEGREE; i++) {
        newRoot.indx[i]=0;
        newRoot.key[i]=0;
      }
      newRoot.key[1]=middleKey;
      newRoot.indx[0]=leftSlot;
      newRoot.indx[1]=rightSlot;
      int address=newIndexPage();
      WriteIndexPage(address,newRoot);
      WriteRoot(address);
      root=address;
      return true;
    }
    leftSlot=pathData.rrn;
    parentNode=ReadIndexPage(pathData.rrn);
    inserted=false;
    for (int i=1; i<parentNode.n+1; i++) {
      if (middleKey<parentNode.key[i]) {
        for (int j=parentNode.n+1; j>=i+1; j--) {
          parentNode.key[j]=parentNode.key[j-1];
          parentNode.indx[j]=parentNode.indx[j-1];
        }
        parentNode.key[i]=middleKey;
        parentNode.indx[i]=rightSlot;
        parentNode.n++;
        inserted=true;
        break;
      }
    }
    if (!inserted) {
      parentNode.key[parentNode.n+1]=middleKey;
      parentNode.indx[parentNode.n+1]=rightSlot;
      parentNode.n++;
    }
  
//CHECK FOR PARENT OVERFLOW NOW
    if (parentNode.n <= DEGREE-1) {
      WriteIndexPage(pathData.rrn,parentNode);
      return true;
    }
//OVERFLOW
    leftSlot=pathData.rrn;
    middleKey=parentNode.key[MID];
    oldSize=parentNode.n;
    parentNode.n=MID-1;
    WriteIndexPage(leftSlot,parentNode);
    rightSlot=newIndexPage();
    for (int i=0; i<MID+1; i++) {
      parentNode.key[i]=parentNode.key[oldSize-MID+i+1];
      parentNode.indx[i]=parentNode.indx[oldSize-MID+i+1];
    }
    WriteIndexPage(rightSlot, parentNode);
  }//END PARENT STUFF

  return true;
}

//================================
//
//           SEQUENTIAL
//
//================================
/*
 * Print the primary keys in order from first (smallest primary key)
 * to last (highest primary key) by starting at the left-most external
 * node and visiting all external nodes via the external node link field
 *
 * Important
 * print at most 11 keys per line!!
 * use a field width so that the line length will be <= 80 characters!!
 */

void btreeType :: Sequential()
{
  availIndexType page=GetIndexHomePage();
  int nodeSlot=page.first;
  memoryNodeType node;
  int numInLine=0;
  while (nodeSlot != 0) {
  node=ReadIndexPage(nodeSlot);
  for (int i=1; i<=node.n; i++) {
    cout<<" "<<setw(6)<<node.key[i];
    numInLine++;
    if (numInLine==11) {
      cout<<endl;
      numInLine=0;
    }
  }
  nodeSlot=-node.indx[0];
  }
  cout<<endl;
}

void btreeType :: GetRecord(int key, bool &found, 
                            logicalRecordType &record, long &address)
{
  memoryNodeType node;
  int rrn;
  Find(key, found, rrn, node, (int)address);
  if (found) { 
    for (int i=0; i<node.n; i++)
	if (node.key[i]==key)
          address=-node.indx[i];
    dataPageType page=ReadDataPage(address);
    record=page.u.record;
  }
}
