// viewZip.cc

// display (view) the contents of a compressed(Zipped) file
// read (i,c) pairs and print a readable report

#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char **argv)
{
  short int i;  // sizeof(short) = 2
  char      c;  // (i,c) pair

  while ( cin.read((char*)&i, sizeof(i)) )
  {
    cout << setw(3)<<i << " ";  // print i

    if ( !cin.get(c) ) {
      cout<<endl<<argv[0]
          <<": unexpected end of file"<<endl<<endl;
      return 1;
    }

    if ( ' ' < c && c <= '~' )
         cout<< "  " << c << endl; // printable: e.g.  a
    else{
         // unprintable: print ascii_code(c) e.g.  10
         unsigned short int x = (unsigned char)c;
         cout << setw(4) << x <<endl;
    }
  }

  return 0;
}
