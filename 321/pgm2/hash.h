// hash.h

#ifndef HASH_H
#define HASH_H 1

#include <fstream>
#include <string>
#include "typedefs.h"
using std::string;
using std::fstream;

class HashFile {

  private:
	char primaryFile [25];
	char overflowFile[25];

	void deleteNode( int cellNumber );
	int  newNode();      // done

	int hash( int key ); // done

	void find   // called by InsertRecord and DeleteRecord;    // done
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
	    );

	fstream pf;
	void       PutBucket( int cellNumber, bucketType bucket );
	bucketType GetBucket( int cellNumber );

	fstream of;
	void     PutNode( int cellNumber, nodeType record );
	nodeType GetNode( int cellNumber );

  public:
	HashFile( char primary[], char overflow[] );              // done
	HashFile( string flag, char primary[], char overflow[] ); // done

	void InsertRecord
	( slotType   record,      // record to be added to the file
          bool     & inserted,    // was the record actually inserted? t/f
	  bool     & inHomeBucket // is the record in the home bucket? t/f
	);
	void DeleteRecord
	( int key,        // primary key of record to be removed
	  bool & deleted  // was the record actually deleted? t/f
	);

	void printPrimaryFile ();
	void printOverflowFile();
	void printStatistics  ();
};

#endif
