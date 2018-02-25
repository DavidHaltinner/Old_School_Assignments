// hash.cc

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include "hash.h"
using namespace std;

//==========================================================================
//
//                                CONSTRUCTORS
//
//==========================================================================
//          The constructors are complete; they need no modification

HashFile::HashFile( string flag, char primary[], char overflow[] )
{
  if (flag!="format") {
    cerr << "\nHashFile::HashFile: unrecognized argument ";
    cerr << flag;
    cerr << "\n                  : format expected\n\n";
    exit(1);
  }

  strcpy(primaryFile ,primary );
  strcpy(overflowFile,overflow);

  ofstream out;
  out.open( primaryFile, ios::out );
  if (out.fail()) {
    cerr<<"\nHashFile::HashFile: could not open "<<primaryFile<<".\n\n";
    exit(1);
  }

  bucketType bucket;
  int        s;
  int        c;
  for (s=0; s<NUMBEROFSLOTS; s++) {
     bucket.slot[s].key = EMPTYKEY;
     for (c=0; c<4; c++) bucket.slot[s].junk[c]='\0';
  }
  bucket.fill =   0;  //trick: want readable od
  bucket.next = NIL;

  int b;
  for (b=0; b<NUMBEROFBUCKETS; b++) {
     out.seekp( (long)b*sizeof(bucket) );
     out.write( (char *)&bucket, sizeof(bucket) );
  }
  out.close();

  out.open( overflowFile, ios::out );
  if (out.fail()) {
    cerr<<"\nHashFile::HashFile: could not open "<<primaryFile<<".\n\n";
    exit(1);
  }

  const int OVERFLOWNODES = NUMBEROFBUCKETS*NUMBEROFSLOTS;//4;
  nodeType node;
  node.fill           =        0;  //trick: make od readable
  node.var.data.key   = EMPTYKEY;
  for (c=0; c<4; c++) node.var.data.junk[c]='\0';
  node.var.cell0.high  = 0;//OVERFLOWNODES-1;
  node.next = 1;  //avail

  //free-space list info
  out.seekp( FREESPACE );
  out.write( (char *)&node, sizeof(node) );

  // nodes on free space list
  node.var.cell0.high = 0;  //trick: make od readable
  int i;
  for (i=1; i<=OVERFLOWNODES-2; i++) {
     node.next = i+1;
     out.seekp( (long)i*sizeof(node) );
     out.write( (char *)&node, sizeof(node) );
  }
  node.next = NIL;
  out.seekp( (long)i*sizeof(node) );
  out.write( (char *)&node, sizeof(node) );
  out.close();
}


HashFile::HashFile( char primary[], char overflow[] )
{
  strcpy(primaryFile,primary);
  strcpy(overflowFile,overflow);

  pf.open( primaryFile, ios::in | ios::out );
  if (pf.fail()) {
    cerr<<"\nHashFile::HashFile: could not open "<<primaryFile<<".\n\n";
    exit(1);
  }

  of.open( overflowFile, ios::in | ios::out );
  if (of.fail()) {
    cerr<<"\nHashFile::HashFile: could not open "<<overflowFile<<".\n\n";
    exit(1);
  }

}



//==========================================================================
//
//                            DISK ACCESS FUNCTIONS
//
//==========================================================================
//  Only the newNode function is complete; you need to implement the other 5


int HashFile::newNode()
{
  nodeType save,node;
  int      nodeAddress;

  save = GetNode( FREESPACE );

  int avail = save.next;

  if ( avail == NIL ) {
	save.var.cell0.high++;
	nodeAddress = save.var.cell0.high;
  }else{
	node = GetNode( avail );
	nodeAddress = avail;
	save.next = node.next;
  }
  PutNode( FREESPACE, save );
  return nodeAddress;
}


void HashFile::deleteNode( int cellNumber )
{
  nodeType node2=GetNode(cellNumber);
  nodeType node=GetNode(node2.next);  
  int prev=cellNumber;
  int address=node2.next;
  node2.next=node.next;
  PutNode(prev, node2);
  node2=GetNode(FREESPACE);
  node.next=node2.next;
  node2.next=address;
  node.var.data.key   = EMPTYKEY;
  for (int c=0; c<4; c++) node.var.data.junk[c]='\0';
  PutNode(FREESPACE, node2);
  PutNode(address, node);
}


void HashFile::PutBucket( int cellNumber, bucketType bucket )
{
  pf.seekp((long)cellNumber*sizeof(bucket));
  pf.write((char *)&bucket, sizeof(bucket));
}

bucketType HashFile::GetBucket( int cellNumber )
{
  bucketType bucket;
  pf.seekg((long)cellNumber*sizeof(bucket));
  pf.read((char *)&bucket, sizeof(bucket));
  return bucket;
}

void HashFile::PutNode( int cellNumber, nodeType record )
{
  of.seekp((long)cellNumber*sizeof(record));
  of.write((char *)&record, sizeof(record));
}

nodeType HashFile::GetNode( int cellNumber )
{
  nodeType node;
  of.seekg( (long)cellNumber*sizeof(node) );
  of.read((char *)&node, sizeof(node)); 
  return node;
}

//==========================================================================
//
//                           FUNCTIONS TO MODIFY RECORDS
//
//==========================================================================
//     hash and find are complete
//     InsertRecord needs to be finished; DeleteRecord needs to be written


int HashFile::hash( int key )
{
  //return 0;  // useful for testing/debugging; use with 5 buckets and 3 slots
  return key % NUMBEROFBUCKETS;
}


/*----------------------------------
              find
  ----------------------------------
  search for a logical record given its primary key value
  and the home bucket to which it belongs
*/

void HashFile::find
    (
	//in
	int        key,
	bucketType bucket,

	//out
	bool & foundInBucket,
	int  & slotNumber,
	bool & foundInOverflow,
	int  & prev,
	int  & nodeAddress
    )
{
  slotType slot;

  foundInBucket   = false;
  foundInOverflow = false;
  slotNumber = 0;

  // search bucket
  while ( slotNumber<NUMBEROFSLOTS ) {
     slot = bucket.slot[slotNumber];
     if ( slot.key == key ) {
	foundInBucket = true;
	return;
     }
     slotNumber++;
  }

  // search overflow chain
  nodeType cell;
  int next = bucket.next;
  prev = NIL;
  while ( next != NIL && prev != next ) {
	cell = GetNode( next );
	if ( cell.var.data.key == key ) {
		foundInOverflow = true;
		nodeAddress = next;
		return;
	}else{
		prev = next;
		next = cell.next;
	}
  }
}


void HashFile::InsertRecord
 (
  slotType record,    //record to be inserted
  bool & inserted,    //was the insertion actually done? t/f
  bool & inHomeBucket //was the record put in a slot in the home bucket? t/f
 )
{
  bool foundInBucket,
       foundInOverflow;

  int slotNumber,
      prev,
      nodeAddress;

  int key  = record.key;
  int home = hash( key );
  bucketType bucket = GetBucket( home );

  find(
        key, bucket,                                                   //in
	foundInBucket, slotNumber, foundInOverflow, prev, nodeAddress  //out
      );

  if (foundInBucket || foundInOverflow) {
    inserted = false;
    inHomeBucket=false;
    return;
  }

  inserted = true;

  // look for empty slot in home bucket
  for (int s=0; s<NUMBEROFSLOTS; s++)
    if (bucket.slot[s].key == EMPTYKEY) {
      bucket.slot[s]=record;
      bucket.next=NIL;
      PutBucket(home, bucket);
      inHomeBucket=true;
      return;
    }

  // no empty slots;  add to overflow chain

  int originalfront=bucket.next;
  int newspot=newNode();
  bucket.next=newspot;
  nodeType node=GetNode(bucket.next);
  node.next=originalfront;
  node.var.data=record;
  PutNode(newspot, node);
  PutBucket(home, bucket);
  node=GetNode(0);
  node.var.cell0.high++;
  PutNode(0, node);
  inHomeBucket=false;
}

void HashFile::DeleteRecord
   (
	int    key,      //record with this primary key is to be deleted
	bool & deleted   //was the deletion actually done?  t/f
   )
{
  bool foundinbucket, foundinoverflow;
  int slot, prev, address;
  bucketType bucket=GetBucket(hash(key));
  find(key, bucket, foundinbucket, slot, foundinoverflow, prev, address);
  if (foundinbucket) { 
    bucket.slot[slot].key = EMPTYKEY;
    for (int c=0; c<4; c++) bucket.slot[slot].junk[c]='\0';
    deleted=true;
    PutBucket(hash(key), bucket);
  } 
  else if (foundinoverflow) {
    if (prev != NIL) deleteNode(prev); 
    else bucket.next = NIL;
    deleted=true;
    PutBucket(hash(key), bucket);
  } 
  else deleted=false;
}


//==========================================================================
//
//                           STATISTICS / OUTPUT FUNCTIONS
//
//==========================================================================
//                 all functions need to be written


void HashFile::printPrimaryFile ()
{
  cout<<"Primary File\nbucket slot1(key)  slot2(key)  slot3(key)"
      <<"  slot4(key)  slot5(key)    link";
  bucketType bucket;
  for (int countbuckets=0; countbuckets<NUMBEROFBUCKETS; countbuckets++) {
    bucket=GetBucket(countbuckets);
    cout<<endl<<setw(5)<<countbuckets<<" ";
    for (int i=0; i<NUMBEROFSLOTS; i++)
      cout<<setw(11)<<bucket.slot[i].key<<" ";
    cout<<setw(7)<<bucket.next;
  }
  cout<<endl<<endl<<endl;
}

void HashFile::printOverflowFile()
{
  nodeType node=GetNode(FREESPACE);
  int high=node.var.cell0.high;
  int avail;
  for (avail=0; node.next<high && node.next != NIL; avail++)
    node=GetNode(node.next);
  node=GetNode(0);
  cout<<"Overflow File Cell 0"<<endl<<setw(29)<<"high  = "
      <<node.var.cell0.high<<endl<<setw(29)<<"avail = "<<avail<<endl;
  cout<<"Overflow File\nbucket  address of nodes on the chains";
  for (int i=0; i<NUMBEROFBUCKETS; i++) {
    bucketType bucket=GetBucket(i);
    cout<<endl<<setw(6)<<i<<setw(5);
    nodeType cell;
    int next = bucket.next;
    while ( next != NIL ) {
      cout<<setw(5)<<next;
      cell = GetNode( next );
      next=cell.next;
    }
  }
  cout<<endl;
}

void HashFile::printStatistics  ()
{
  bucketType bucket;
  nodeType node;
  int numslots=0;
  int numnodes=0;
  double seeks=0.0;
  for (int i=0; i<NUMBEROFBUCKETS; i++) {
    bucket=GetBucket(i);
    seeks++;
    for (int j=0; j<NUMBEROFSLOTS; j++)
      if (bucket.slot[j].key != 0) numslots++;
    int next=bucket.next;
    while (next !=NIL) {
      node=GetNode(next);
      seeks++;
      numnodes++;
      next=node.next;
    }
  }
  seeks=(seeks*4.0)/(double)(numslots+numnodes);
  cout<<"Program  2: Hash File with Chaining\nWritten by: David Haltinner\n\n"
      <<"Statistics\nnumber of slots in use"<<setw(13)<<"= "<<numslots
      <<"\nnumber of overflow nodes in use"<<setw(4)<<"= "<<numnodes
      <<"\naverage search length of file"<<setw(6)<<"= "
      <<setprecision(3)<<seeks<<endl<<endl<<endl;
}
