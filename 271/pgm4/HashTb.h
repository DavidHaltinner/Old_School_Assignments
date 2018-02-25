//
// File: HashTb.h
//

#ifndef HASHTB_H
#define HASHTB_H

#include <iostream.h>

template <class E, class K>
class HashTb {
protected:
   int B;                                              // no. of buckets
   void * table;                                       // enable different implementations
   int hash (int key, int i = 0) const;                // hash ints
   int hash (char * key, int = 0) const;               // hash cstrings
   virtual ostream & output(ostream & os, int i) = 0;
public:
   HashTb ( ) { B = 11; }
   HashTb (int size) { B = size; }
   inline virtual ~HashTb ( ) { }
   virtual bool insert (E & element) = 0;
   virtual bool search (K key, E & element) const = 0;
   virtual bool erase (K key) = 0;
   virtual HashTb<E, K> & operator=(const HashTb<E, K> & tb);
//   friend ostream & operator<<(ostream & os, const HashTb<E, K> & tb);
};

//template <class T>
//inline HashTb<T>::~HashTb ( ) { /* delete [ ] table;*/ }

template <class E, class K>
HashTb<E, K> & HashTb<E, K>::operator=( const HashTb<E, K> & h )
{
   B = h.B;
//   for (int i = 0; i < B; i++)
//      (*((LList<E> *)table +i)) = (*((LList<E> *)h.table + i));
   return *this;
}

template <class E, class K>
int HashTb<E, K>::hash (int key, int i) const
    { return (key % B); }

template <class E, class K>
int HashTb<E, K>::hash (char * key, int i) const
    { int hv = 0;
      while (*key != '\0') hv += *key++;
      return (hv % B);
    }

#endif

