//
// File : BST4.h
//

// This implementation requires the client code to include a key( ) member function 
// in the E class, and to overload the assignment operator.

#ifndef BST_H
#define BST_H

#include <stdlib.h>
#include <iostream.h>
#include "BinaryTree4.h"

template <class E, class K>
class BST : public BinaryTree<E> {
public:
   BST ( ) : BinaryTree<E> ( ) { }
   ~BST ( ) { }
   BST ( const E & elm) : BinaryTree<E> (elm) { }
   void error (char * s) const
        { cerr << "\nFatal error in BST : " << s << endl;
          exit (1);
        }
   bool search ( const K & k, E & e ) const;
   BST<E, K> & insert ( const E & e );
   BST<E, K> & erase ( const K & k, E & e );
   bool minimum ( E & e );
   bool maximum ( E & e );
   void aPrint ( );
   bool isEmpty ( ) const { return root == 0; }
};

#endif

