// main.cc

/*
 *  Description
 *  This is a Database Query program that tests the implementation of a
 *  buffer manager
 *  The calls to the data base are specified in a script file
 *  A history of the commands and their effect is written to a log file
 *
 *  usage
 *  bman  dataBaseFileName  scriptFileName  logFileName
 *
 *  Input
 *  data base file (name given as command line argument)
 *  script file    (name given as command line argument)
 * 
 *  Written by
 *  andrew perrie
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <assert.h>

#include "pool.h"

using namespace std;

int whichCommand(string);
const string showIndent("     ");


int main( int argc, char** argv )
{
  if ( argc != 4 ) {
    cerr << endl << "usage:  " << argv[0] << "  "
         << "dataBaseFileName  scriptFileName  logFileName" <<endl<<endl;
    return 1;
  }

	// database file
  fstream * db;
  db = new fstream;
  db->open( argv[1], ios::in|ios::out );
  if ( db->fail() ) {
    cerr<<endl<<argv[0]<<": unable to open input file "<<argv[1]<<endl<<endl;
    return 1;
  }

	// script file
  ifstream cfin;
  cfin.open( argv[2] );
  if ( cfin.fail() ) {
    cerr<<endl<<argv[0]<<": unable to open input file "<<argv[2]<<endl<<endl;
    return 1;
  }

	// log file
  ofstream logf;
  logf.open( argv[3] );
  if ( logf.fail() ) {
    cerr<<endl<<argv[0]<<": unable to open output file "<<argv[3]<<endl<<endl;
    return 1;
  }


  logf << "Assignment: buffer pool ; LRU Replacement" <<  endl;
  logf << "Written by: David Haltinner" << endl << endl;


  logf << "database file:\t" << argv[1] << endl;
  logf << "command file:\t"  << argv[2] << endl;
  logf << "log file:\t"      << argv[3] << endl;


  struct record {
	short primaryKey;
	char  chars[6];
	int   int1;
	int   int2;
  };

  union overlay {
	record logicalRecord;
	char   binary[sizeof(record)];  // 16
  };

  overlay data;


  LRUBufferPool *bp;
  string        command;


  while (true) {

     cfin >> command;

     switch ( whichCommand(command) ) {

        case 1:
			// ';' : comment line; throw it away
		{
		  char newline;
		  do newline=cfin.get(); while (!(newline == '\n'));
		}
		break;

        case 2:
			// buffer : create buffer pool
		{
		  int     pageSize ,  numberOfPages;
		  cfin >> pageSize >> numberOfPages;
		  logf << endl << "buffer\t"
		       << pageSize << "  " << numberOfPages << endl;

			// create buffer pool
		  bp = new LRUBufferPool(pageSize,numberOfPages,db);
		}
		break;

        case 3:
			// show : display contents of logical record
		{
		  int     primaryKey;
		  cfin >> primaryKey;
		  logf<< endl << "show\t" << primaryKey << endl;

		//===================================================
		  char * chars = bp -> get( primaryKey*16, logf );
		  for (int i=0; i<16; i++) data.binary[i] = chars[i];
		//===================================================

		  logf << showIndent;
		  logf << data.logicalRecord.primaryKey << "  ";
		  for (int i=0; i<6; i++) logf<< data.logicalRecord.chars[i];
		  logf << "  " << data.logicalRecord.int1;
		  logf << "  " << data.logicalRecord.int2;
		  logf << endl;
		}
		break;

        case 4:
			// update : modify contents of logical record
		{
		  string string6;
		  cfin >> data.logicalRecord.primaryKey >> string6
		       >> data.logicalRecord.int1 >> data.logicalRecord.int2;
		  for(int i=0;i<6;i++) data.logicalRecord.chars[i]=string6[i];

		  logf<< endl << "update\t"
		      << data.logicalRecord.primaryKey << '\t';
		  for (int i=0; i<6; i++) logf<< data.logicalRecord.chars[i];
		  logf<< '\t' << data.logicalRecord.int1
		      << '\t' << data.logicalRecord.int2 << endl;

		//===================================================
		  int fileOffset = data.logicalRecord.primaryKey*16;
		  bp->put(data.binary, fileOffset, 16, logf);
		//===================================================
		}
		break;

	case 5:
			// debug : display buffer pool in hex
		logf<< endl << "debug" << endl;
//		bp->showPoolInHex(logf);
		break;

        case 6:
			// exit
		logf << endl << "exit" << endl;
		bp->flushToDisk(logf);

		int hits,misses,writeBacks;
		bp -> getStats( hits,misses,writeBacks );

		logf<< endl;
		logf<< "Statistics"<<endl;
		logf<< "     hits:"        << setw(15) << hits       << endl;
		logf<< "     misses:"      << setw(13) << misses     << endl;
		logf<< "     write backs:" << setw( 8) << writeBacks << endl;

		cfin.close();
		logf.close();
		return 0;

        default:
		assert(false);
     }
  }

  return 0; // successful
}


int whichCommand(string cmd)
{
  if      ( cmd == ";"      )	return 1;
  else if ( cmd == "buffer" )	return 2;
  else if ( cmd == "show"   )	return 3;
  else if ( cmd == "update" )	return 4;
  else if ( cmd == "debug"  )	return 5;
  else if ( cmd == "exit"   )	return 6;
  else 				return 0;
}
