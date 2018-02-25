/**
 * This file contains the definition for a Stack using an array. It has methods
 * to return the top data with or without deleting it, adding another data 
 * member, checking to see if its empty, and increasing the size of it. It 
 * also has a default constructor, and one that takes in a specified capacity;
 * it also has a destructor. data is the array, capacity is how much the 
 * stack will hold, top is top slot where we add/remove from.
 * @authors Peter Worland, David Haltinner
 * @date Oct 4 2002
 * */
#ifndef ASTK_H
#define ASTK_H

#include <iostream.h>
#include <stdlib.h>

template <class T>
class AStack {
protected:
   T * data;
   int capacity;
   int top;
   void AddCapacity( int );   // not needed for pgm #2
public:
   AStack( ) : data ( new T[100] ), capacity ( 100 ), top ( 0 ) { } 
   AStack( int n ) : data ( new T[n] ), capacity ( n ), top ( 0 ) { }
   ~AStack( ) {/* cout << "destructor" << endl;*/ delete [ ] data; capacity = 0; top = 0; }
   void Error( char * s ) const
   { cerr << "\nFatal error in AStack: " << s << endl;
     exit(1);
   }
   T Top( ) const;
   T Pop( );
   void Push( const T & );
   bool IsEmpty( ) const;
}; //class AStack<T>

#endif
