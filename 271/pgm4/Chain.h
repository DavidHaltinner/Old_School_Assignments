//
// File: Chain.h
//

#ifndef CHAIN_H
#define CHAIN_H

#include "HashTb.h"
#include "LList.h"

template <class E, class K>
class HashChain : public HashTb<E, K> {
public:
   HashChain ( ) : HashTb<E, K> ( ) { }
   HashChain (int size);
   ~HashChain ( );
   bool insert (E & element);
   bool search (K key, E & element) const;
   bool erase (K key);
   void purgeAll ( );
   HashChain<E, K> & operator=(const HashChain<E, K> & tb);
   inline ostream & output (ostream & os, int i);
};

template <class E, class K>
HashChain<E, K>::~HashChain ( )
{
   delete [ ] (LList<E> *)table;
}


template <class E, class K>
 void HashChain<E, K>::purgeAll ( )
{
LList<E> temp;

for (int i = 0; i < B; i++) {
   temp = *((LList<E> *)table + i);
   temp.purge( );
   }
}

template <class E, class K>
HashChain<E, K> & HashChain<E, K>::operator=( const HashChain<E, K> & tb)
{
   B = tb.B;
   for (int i = 0; i < B; i++)
      (*((LList<E> *)table + i)) = (*((LList<E> *)tb.table + i));
   return *this;
}

template <class E, class K>
inline ostream & HashChain<E, K>::output (ostream & os, int i)
{
   static LList<E> p;
   p = *((LList<E> *)table + i);                       // pointer arithmetic
   p.first( );

   while (! p.end( )){
      os << p.getData( ) << endl;
      p.next( );
   }
   return os;
}

#endif

