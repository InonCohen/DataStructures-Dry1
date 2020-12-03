#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "avl_node.h"

typedef enum avlTreeResult_t
{
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
    avlTreeResult_t insertAvlNode(avlNode<T> *root, avlNode<T> *new_node);
    avlTreeResult_t removeAvlNode(avlNode<T> *root, avlNode<T> *new_node);

public:
    avlTree();
    ~avlTree();
    avlTreeResult_t insert(const T &value);
    avlTreeResult_t remove(const T &value);
    void treeBalance(avlNode<T> *root);
    void rotateLeft(avlNode<T> *root);
    void rotateRight(avlNode<T> *root);
    avlNode<T> *getRoot() const { return this->root; }
    void inOrder(avlNode<T> *root, void (*function)(avlNode<T> *)) const; // Left, this, Right
    void preOrder(avlNode<T> *root, void (*function)(avlNode<T> *)) const; // this, Left, Right
    void postOrder(avlNode<T> *root, void (*function)(avlNode<T> *)) const; // Left, Right, this
    // void postOrder(avlNode<T> *root, void (*function)(avlNode<T> *, int* ));
    
    avlNode<T>* findNewRoot(avlNode<T> *newroot);
    void rootUpdate(avlNode<T>* newroot);

    void recursiveSetHeight(avlNode<T> *node);
    void removeLeaf(avlNode<T> *node);
    void removeNodeOneChild(avlNode<T> *node, bool is_right_child);
    void eraseAndBalance(avlNode<T> *node);
    avlNode<T>* createNewSubTree(avlNode<T>* node);
    void swap(avlNode<T> *src, avlNode<T> *dst);
    avlNode<T>* firstInOrder(avlNode<T> *sub_root);
    void removeNodeWithParent(avlNode<T> *node_to_remove);
};

template <class T>
avlNode<T> *find(avlNode<T> *root, const T &value);

template <class T>
int getBF(avlNode<T> *root);

#endif