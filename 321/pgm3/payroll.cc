// payroll.cc

/*
 *  Description
 *  Print (send to standard output) a list of the primary key values of
 *  the logical records in an indexed-sequential file.  The values are
 *  printed in order from smallest to largest.
 *
 *  usage
 *  payroll
 *
 *  Input
 *  btree.bin (Index File)
 *  bfile.bin is opened but not used (Data File)
 *
 *  Written by
 *  Gordie Howe and Jaromir Jagr
 *
 */


#include <iostream>

#include "btree.h"


int main( void )
{

  btreeType bt( "btree.bin", "bfile.bin" );

  cout << "\nSequential List of Keys" << endl;
  bt.Sequential();

  return 0;
}
