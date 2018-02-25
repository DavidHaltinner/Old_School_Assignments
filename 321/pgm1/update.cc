// update.cc

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct InventoryRecord {
   int  primaryKey;
   int  onHand;
};


int main( int argc, char **argv )
{
  if ( argc!=2 ) {
    cerr << "\nusage: % update transaction.txt\n\n";
    return 1;
  }

  ifstream oldMasterFile  ,
           transactionFile;
  ofstream newMasterFile;

  InventoryRecord  record;
  int              key,
                   quantity;

  oldMasterFile.open( "old.bin" );
  if(oldMasterFile.fail()){cerr<<"\nupdate: could not open old.bin\n\n";return 1;}
  transactionFile.open( argv[1] );
  if(transactionFile.fail()){cerr<<"\nupdate: could not open tran.t\n\n";return 1;}
  newMasterFile.open( "new.bin" );
  if(newMasterFile.fail()){cerr<<"\nupdate: could not open new.bin\n\n";return 1;}

  oldMasterFile.read( (char *)&record, sizeof(record) );
  if ( oldMasterFile.eof() ) {
    cerr << "\nupdate: empty master file\n\n";
    return 0;
  }
  transactionFile >> key >> quantity;

  while ( !transactionFile.fail() ) {
     if ( record.primaryKey == key ) {
           record.onHand -= quantity;          //update record
           transactionFile >> key >> quantity;
     }else{
           newMasterFile.write( (char *)&record, sizeof(record) );
           oldMasterFile.read ( (char *)&record, sizeof(record) );
     }
  }

  // copy remainder of old master file to new master file
  do{
     newMasterFile.write( (char *)&record, sizeof(record) );
     oldMasterFile.read ( (char *)&record, sizeof(record) );
  }while ( !oldMasterFile.eof() );

  oldMasterFile  .close();
  newMasterFile  .close();
  transactionFile.close();

  return 0;
}
