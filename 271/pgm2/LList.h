//
// File: LList.h    
//

#ifndef LLIST_H
#define LLIST_H

#include <iostream>
#include <string>
#include <stdlib.h>

template <class T>        // Forward reference
class LList;

template <class T>
class Node {
friend class LList<T>;
protected:
   T * data; 
   Node<T> * next;
public:
   Node ( ) { data = 0; }              // avoid seg fault when list head deleted      
   ~Node( ) { if (data) delete data; }
};

template <class T>
class LList {
protected:
   Node<T> * head;
   Node<T> * cur;
public:
   LList( ) { head = new Node<T>; head -> next = head; cur = head; }
   ~LList( );
   LList(const LList<T> &);
   LList<T> & operator=(const LList<T> &);
   void append ( const T & );
   bool end( ) const;
   void error (char * s)
        { cerr << "\nFatal error in LList : " << endl; exit(1); }
   void extractPosition( );
   bool find( const T & );
   void first( );
   void front( );
   T &  getData( ) const;
   void last( );
   void insert( const T & );
   bool isEmpty ( ) const;
   void next( );
   void previous( );
   void purge( );
   void setData ( const T & );
   int  size( ) const;
};

#endif

