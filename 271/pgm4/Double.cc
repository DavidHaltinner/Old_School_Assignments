/**
 * This is one of the Constructors for HashDouble that takes the size as the 
 * only parameter. It then sets the pointer arrays to that length give.
 * @param size, which is the length for the data arrays
 * */
template <class E, class K>
HashDouble<E, K>::HashDouble(int size)
{
   assert (size > 0);
   B = size;
   table = (E *) new E[B];
   empty = new bool[B];
   deleted = new bool[B];
   for (int i=0; i<B; i++)
   {
      empty[i]=true;
      deleted[i]=false;
   }
}
/**
 * This is the destructor for HashDouble. It deletes the table (pointer to E),
 * the deleted, and empty pointer as well.
 * */
template <class E, class K>
HashDouble<E, K>::~HashDouble ( )
{
   delete [] deleted;
   delete [] empty;
   delete [] (E*)table;
}
/**
 * This function erases the element with the given key from the table, and 
 * sets it as deleted.
 * @param key, the matching key of the element to remove
 * @return true if we removed it, false if we couldnt
 * */
template <class E, class K>
bool HashDouble<E, K>::erase (K key)
{
   int idx, i=0;   
   do
   {
      idx=hash(key, i);
      if ((*((E*) table+idx)).key()==key)
      {
         deleted[idx]=true;
         return true;
      }
      i++;
   }
   while (i<B && empty[idx]==false);
   return false;
}
/**
 * This is the overwritten hash function, that does the hasing accordning to 
 * the rules of the Double Hashing function.
 * @param key, which is the number we will be hasing
 * @param i, which is the next spot to hash, since we hashed the same spot.
 * @return the index for the hashed key
 * */
template <class E, class K>
int HashDouble<E, K>::hash (int key, int i) const
{ 
   return (((key%B)+i*(key%(B-2)+1))%B); 
}
/**
 * This function inserts the given element into the table. It hashes the key 
 * to find the next available slot, and sets the corresponding deleted and 
 * empty markers to false.
 * @param element, which is the thing to insert
 * @return true if we could delete it, false if we couldnt
 * */
template <class E, class K>
bool HashDouble<E,K>::insert (E & element)
{
   E temp;
   int idx, i=0;
   if(search(element.key(), temp)) return true;
   do
   {
      idx=hash(element.key(), i);
      i++;
   }
   while (i<B && empty[idx]==false && deleted[idx]==false);
   if (i>=B) return false;
   (*((E*) table+idx))=element;
   empty[idx]=deleted[idx]=false;
   return true;
}
/**
 * This is the overloaded assignment operator. 
 * @param tb, which is the HashDouble to copy to myself
 * */
template <class E, class K>
HashDouble<E, K> & HashDouble<E, K>::operator=( const HashDouble<E, K> & tb)
{
   B = tb.B;
   for (int i = 0; i < B; i++)
      (*((E *)table + i)) = (*((E *)tb.table + i));
   return *this;
}
/**
 * This is an output function to display the table's data. 
 * @param os, the stream to throw myself into
 * @param i, which doesnt do anything here, but it does in HashTb.
 * @return the stream with my data
 * */
template <class E, class K>
inline ostream & HashDouble<E, K>::output (ostream & os, int i)
{  
   for (int i = 0; i < B; i++)
      if (deleted[i]==false && empty[i]==false)
         os<<(*((E *)table+i))<<endl;
   return os;
}
/**
 * This is the search function which looks for an element with the given key.
 * @param key, which is the key to search for.
 * @param element, to assign the found object to.
 * @return true if we found it, false if we didnt.
 * */
template <class E, class K>
bool HashDouble<E, K>::search (K key, E & element) const
{
   int idx, i=0;
   do
   {
      idx=hash(key, i);
      if ((*((E*) table+idx)).key()==key && deleted[idx]==false)
      {
         element=(*((E*) table+idx));
         return true;
      }
      i++;
   }
   while (i<B && empty[idx]==false);
   return false;
}
