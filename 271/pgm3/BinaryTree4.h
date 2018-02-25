//
// File : BinaryTree4.h 
//

#ifndef BINARYT_H
#define BINARYT_H

template <class T>
class BNode {
public:
   T data;
   BNode<T> * parent;   // rarely needed
   BNode<T> * leftChild;
   BNode<T> * rightChild;

   BNode ( ) : leftChild(0), rightChild(0), parent(0) { }
   BNode (const T & elm) : data(elm), parent(0), leftChild(0), rightChild(0) { }
   T getData( BNode<T> * t ) const;
   void setData( BNode<T> * t, T & elm );
};

template <class T>
class BinaryTree {
protected:
   BNode<T> * root;

   void preorder (void (*Visit)(BNode<T> * u), BNode<T> * t);
   void inorder (void (*Visit)(BNode<T> * u), BNode<T> * t);
   void postorder (void (*Visit)(BNode<T> * u), BNode<T> * t);
   static void tFree(BNode<T> * t) { if (t) delete t; }
   static void output (BNode<T> * p) { cout << p -> data << endl; } 
public:
   BinaryTree ( ) : root (0) { }
   BinaryTree (const T & elm)
      { root = new BNode<T>;
        root -> data = elm; root -> parent = 0; root -> leftChild = 0; root -> rightChild = 0; }
   virtual ~BinaryTree ( ) { postorder(tFree, root); root = 0; }
   bool Root (T & elm) const;
   bool isEmpty ( ) const
      { return ((root) ? false : true); }
   void makeTree (const T & elm, BinaryTree<T> & left, BinaryTree<T> & right);
   void preorder (void (*Visit)(BNode<T> * u))
      { preorder (Visit, root); }
   void inorder (void (*Visit)(BNode<T> * u))
      { inorder (Visit, root); }
   void postorder (void (*Visit)(BNode<T> * u))
      { postorder (Visit, root); }
   void inOutput ( );
};

#endif

