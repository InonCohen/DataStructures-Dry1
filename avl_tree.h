#ifndef AVL_NODE_H
#define AVL_NODE_H

#include "\avl_node.h"

template <class T>
class avlTree
{
private:
    avlNode<T>* root;

public:
    avlTree() = default;
    ~avlTree();

    bool insert(const T &value);
    avlNode<T>*GetRoot() const;

    avlNode<T>* find(avlNode<T>* root, const T& value) const;

    int getHeight(avlNode<T> *root) const;
    int balanceFactor(avlNode<T> *root) const;

    void rotateLeft(avlNode<T> *root);
    void rotateRight(avlNode<T> *root);

    void printPreOrder(AVLNode<T> *root) const;  // Parent, Left, Right
    void printInOrder(AVLNode<T> *root) const;   // Left, Parent, Right
    void printPostOrder(AVLNode<T> *root) const; // Left, Right, Parent
};

#endif