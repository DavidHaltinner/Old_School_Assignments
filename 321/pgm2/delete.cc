//delete.cc

/*
 * Description
 * This program will delete a large number of records from the hash table
 * and/or the overflow list. It will skip the first few hundred records, and
 * Only deletes the last couple hundred.
 * This program tests the implementation of the hash and overflow files.
 *
 * Usage
 * % ./delete
 *
 * Input
 * There is no input
 *
 * Written By
 * David Haltinner      Sep '03
 */

#include <iostream>
#include <iomanip>
#include <fstream>

#include "hash.h"
#include "random.h"
using namespace std;

int main()
{
  cerr << "delete: begin" << endl;

  HashFile hf( "primary.bin", "overflow.bin" );
  Random random(888777);  //everyone MUST use this seed!!
  int key;
  bool deleted;
  for (int i=1; i<300; i++) 
    key = random.intVal();
  for (int i=1; i<250; i++) {
    key = random.intVal();
    hf.DeleteRecord(key, deleted);
  }
  random.setSeed(888777);
  for (int i=1; i<300; i++)
    key = random.intVal();  // skip past 300 keys
  key = random.intVal(); // get the next random number
  hf.DeleteRecord(key, deleted);
  if (!deleted)     // to verify that we can't
    cout<<"Record with key = "<<key<<" could not be deleted\n";
  cerr << "delete: end" << endl;
  return 0;
}
