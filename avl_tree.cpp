#include "avl_tree.h"
#include "avl_node.h"


// template <class T>
// // avlNode<T> *avlTree<T>::find(avlNode<T> *root, const T& value) const {

// }

template <class T>
avlNode<T>* avlTree<T>::getRoot() const {
    return this->root;
}

template <class T>
avlNode<T>* avlTree<T>::find(avlNode<T>* root, const T& value) const {
        // Element not found
        if(!root)
            return NULL;

        // Searching for element
        else if(data < root.getData())
            return find(value, root.getLeft()); //search left sub tree
        else if(data > root->get(Data())
            return find(value, root.getRight()); //search right sub tree
        else
            return root; //found
}


template <class T>
int avlTree<T>::getHeight(avlNode<T>* root) const {
  int height = 0;
  if( root ) {
    int left  = getHeight(root->GetLeft());
    int right = getHeight(root->GetRight());
    height = 1 + ((left > right) ? left : right) ;
  }
  return height;
}