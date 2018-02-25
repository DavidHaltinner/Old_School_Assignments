//
// File: Chain.cc
//

#include <assert.h>
#include "Chain.h"

template <class E, class K>
HashChain<E, K>::HashChain(int size) : HashTb<E, K>( size )
{
   assert (size > 0);
   B = size;
   table = (LList<E> *) new LList<E> [B];
}
/**
 * This is the erase function I wrote. It hashes to the correct LList, and 
 * then finds the specific element in the LLIst. Once found it removes it.
 * @param key, which matches the element i need to fins
 * @return true if i find it, false otherwise
 * */
template <class E, class K>
bool HashChain<E, K>::erase (K key)
{
   E temp;
   static  LList<E>  p;
   int idx = hash(key);
   p = *((LList<E> *) table +idx);
   p.first( );
   while (! p.end( )) {
      temp = p.getData( );
      if (temp.key( ) == key) {
         p.extractPosition();
         return true;
         }
      else
         p.next( );
   }
   return false;
}

template <class E, class K>
bool HashChain<E, K>::insert (E & element)
{
   bool found;
//   E item;
   int idx = hash (element.key( ));
   
   // check for duplicates
   found = search (element.key( ), element);
   if (found) return false;
   ((LList<E> *)table + idx) -> append (element);

   return true;
}

template <class E, class K>
bool HashChain<E, K>::search(K key, E & element) const
{
   E temp;
   static  LList<E>  p;
   int idx = hash(key);

   p = *((LList<E> *) table +idx);
   p.first( );
   while (! p.end( )) {
      temp = p.getData( );
      if (temp.key( ) == key) {
         element = temp;
         return true;
         }
      else
         p.next( );
   }
   return false;
}

