// insert.cc

/*
 *  Description
 *  Add records to an Indexed-Sequential File
 *
 *  usage
 *  insert  250
 *
 *  Input
 *  number of records, provided as a command line argument
 *  btree.bin
 *  bfile.bin
 *
 *  Written by
 *  Gordie Howe and Sergei Federov
 */


#include <iostream>
#include <iomanip>
#include <fstream>

#include "btree.h"
#include "random.h"
using namespace std;

void doQuery( btreeType & bt, int key );




int main( int argc, char **argv )
{
  // check usage

  if ( argc != 2 ) {
    cerr<<endl<< "usage: " <<argv[0]<< " #keys(0..300)"<<endl<<endl;
    return 1;
  }

  int n = atoi(argv[1]);  //let's hope there's no problem
  if ( n<0 || n>300 ) {
    cerr <<endl<< argv[0]<< ": #keys out of range"<<endl<<endl;
    return 1;
  }

  btreeType bt( "btree.bin", "bfile.bin" );
  Random    rn;

  logicalRecordType record;
  strcpy(record.name,"aaaaaaa");

  // add records to file

  for (int i=1; i<=n; i++) {
     record.key = rn.intVal();
     if (record.key==60107) strcpy(record.name,"abcdefg");
     if ( !bt.Insert(record) ) {
        cerr << argv[0] << ": record was not inserted; duplicate key "
             << record.key << endl;
     }
  }

  // print Cell0 information

  bt.printIndexFilePage0(); cout<<endl;
  bt.printDataFilePage0();  cout<<endl;

  // make some queries

  cout << endl;

  doQuery( bt, 60000 );
  doQuery( bt, 60107 );
  cout << endl;

  return 0;
}


void doQuery( btreeType & bt, int key )
{
  bool found;
  logicalRecordType record;
  long address;

  cout << "Query: ";

  bt.GetRecord(key, found,record,address);
  if (!found)
	cout << key << " was not found";
  else{
	cout << key << " was found at address " << address
             << "; data = " << record.name;
  }
  cout << endl;
}
