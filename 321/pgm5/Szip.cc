/*
 *  Description
 *  This is a file compression program that tests the implementation of
 *  the LZ- algorithm.
 *  Input/Output are both through standard IO.
 *
 *  usage
 *  cat L.txt | szip
 *
 *  Input
 *  No arguments. All input is through standard IO and is ASCII text
 *
 *  Written by
 *  David Haltinner
 */

#include <iostream>
#include <map>
using namespace std;

#define MAXPIECES 257

int main() {
	map<char*, short> dictionary;
	char* charValue;
	for (int i=0; i<256; i++) {
		charValue=(char*)i;
		dictionary[charValue]=i;
	}
	short int number=255;
	char tempChar;
	short int lastAscii;
	while (cin>>tempChar) {
		if (number >=MAXPIECES-1) {
			cout<<"compression aborted"<<endl;
			return 0;
		}
		char* tempString=(char*)tempChar;
		do {	
			lastAscii=dictionary[tempString];
			cin>>tempChar;
			if (tempChar==EOF) {
				tempString='\0';
				lastAscii=-lastAscii;
				break;
			}
			tempString+=tempChar;
		} while (dictionary[tempString]!=0);
		dictionary[tempString]=++number;
		cout.write((char *)&lastAscii, sizeof(lastAscii));
		cout<<tempChar;
	}
	return 0;
}
