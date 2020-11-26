#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "avl_node.h"

template <class T>
class avlTree
{
private:
    avlNode<T> *root;

public:
    avlTree() = default;
    ~avlTree();

    bool insert(const T &value);
    avlNode<T> *GetRoot() const;

    // void rotateLeft(avlNode<T> *root);
    // void rotateRight(avlNode<T> *root);

    avlNode<T> *getRoot() const { return this->root; }

    template <class Func>
    void inOrder(avlNode<T> *root, Func function) const; // Left, this, Right

    template <class Func>
    void preOrder(avlNode<T> *root, Func function) const; // this, Left, Right

    template <class Func>
    void postOrder(avlNode<T> *root, Func function) const; // Left, Right, this

    // friend class avlNode<T>;
};


template <class T>
avlNode<T> find(avlNode<T> *root, const T &value);

template <class T>
int getHeight(avlNode<T> *root);

template <class T>
int getBF(avlNode<T> *root);

#endif