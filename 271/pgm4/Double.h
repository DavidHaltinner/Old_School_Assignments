#ifndef DOUBLE_H
#define DOUBLE_H
#include "HashTb.h"
/**
 * This class holds the HAshDouble object. This object is a child of HashTb, 
 * and it overwrites most of the functions of HashTb. It has sets table as a 
 * pointer array of type E. It also contains an empty and deleted pointer array
 * which tell whether the slof in table is empty or deleted. It has functions 
 * that insert, search and erase elements by hashing them using Double Hashing
 * techniques.
 * @author David Haltinner
 * @date Nov 14, 2002
 * */
template <class E, class K>
class HashDouble : public HashTb<E, K> {
private:
   int limit;
   bool* empty;
   bool* deleted;
   int hash(int key, int i) const;
public:
   HashDouble ( ) : HashTb<E, K> ( ) { }
   HashDouble (int size);
   ~HashDouble ( );
   bool insert (E & element);
   bool search (K key, E & element) const;
   bool erase (K key);
   HashDouble<E, K> & operator=(const HashDouble<E, K> & tb);
   inline ostream & output (ostream & os, int i);
};
#endif
