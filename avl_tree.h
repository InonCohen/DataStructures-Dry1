#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "avl_node.h"


typedef enum avlTreeResult_t {
    AVL_TREE_OUT_OF_MEMORY,
    AVL_TREE_INVALID_INPUT,
    AVL_TREE_SUCCESS,
    AVL_TREE_FAILURE
} avlTreeResult_t;


template <class T>
class avlTree
{
private:
    avlNode<T> *root;

    avlTreeResult_t insertAvlNode(avlNode<T>* root, avlNode<T>* new_node);

public:
    avlTree() = default;
    ~avlTree();

    avlTreeResult_t insert(const T &value);
    void treeBalance(avlNode<T>* root);

    void rotateLeft(avlNode<T> *root);
    void rotateRight(avlNode<T> *root);

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
avlNode<T>* find(avlNode<T> *root, const T &value);

template <class T>
int getHeight(avlNode<T> *root);

template <class T>
int getBF(avlNode<T> *root);

#endif