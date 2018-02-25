// print.cc

/*
 * Description
 * This program will print a large number of records from the hash table
 * and/or the overflow list. It only calls three functions that are in hash.cc.
 * This program tests the implementation of the hash and overflow files.
 *
 * Usage
 * % ./print
 *
 * Input
 * There is no input
 *
 * Written By
 * David Haltinner      Sep '03
 */

#include <fstream>
using namespace std;
#include "hash.h"

int main()
{
  HashFile hf( "primary.bin", "overflow.bin" );
  hf.printStatistics();
  hf.printPrimaryFile();
  hf.printOverflowFile();
  return 0;
}
