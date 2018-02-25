// insert.cc

/*
 * Description
 * This program will insert a large number of records into the hash table
 * and/or the overflow list. The record's keys are randomly generated.
 * This program tests the implementation of the hash and overflow files.
 *
 * Usage
 * % ./insert
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
using namespace std;
#include "hash.h"
#include "random.h"

// 5 slots per bucket & 119 buckets & 566 : load factor is approx 95%
const int SLOTSLOADED = 566;  //number of slots to be filled

int main()
{
  cerr << "insert: begin" << endl;

  HashFile hf( "primary.bin", "overflow.bin" );
  slotType record;
  bool inserted, inhome;
  Random random(888777);  //everyone MUST use this seed!!
  record.junk[0] = 'a';  //{use for all records!}
  int putinbucket=0;
  while (inserted && putinbucket<SLOTSLOADED) {
    record.key = random.intVal();
    hf.InsertRecord(record,inserted,inhome);
    if (inhome) putinbucket++;
  }
  random.setSeed(888777);
  record.key = random.intVal();
  hf.InsertRecord(record,inserted,inhome);
  if (!inserted) cout<<"Record with key = "<<record.key
                     <<" could not be inserted\n";
  cerr << "insert: end" << endl;
  return 0;
}
