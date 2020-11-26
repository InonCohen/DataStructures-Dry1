#ifndef AVL_NODE_H
#define AVL_NODE_H

#include <iostream>

template <class T>
class avlNode
{
private:
    T data;
    avlNode *left;
    avlNode *right;
    avlNode *parent;
    int height;

public:
    avlNode(const T &value);
    avlNode *avlNode(const avlNode &avlNode);
    ~avlNode() = default;
    avlNode *find(avlNode *node, T data);
    avlNode *getLeft();
    avlNode *getRight();
    avlNode *getParent();
    T &getValue();
    const T getValue() const;
    void setLeft(avlNode *new_left);
    void setRight(avlNode *new_right);
    void setParent(avlNode *new_parent);
    void print() const;
};

template <class T>
class AVLTree
{
private:
    avlNode<T>* root;

public:
    AVLTree() : root_(NULL) {}
    ~AVLTree();

    bool insert(const T &value);
    avlNode<T> *GetRoot() const { return root; }

    avlNode<T> *Find(avlNode<T> *root, const T &value) const;

    int getHeight(avlNode<T> *root) const;
    int balanceFactor(avlNode<T> *root) const;

    void rotateLeft(avlNode<T> *root);
    void rotateRight(avlNode<T> *root);

    void printPreOrder(AVLNode<T> *root) const;  // Parent, Left, Right
    void printInOrder(AVLNode<T> *root) const;   // Left, Parent, Right
    void printPostOrder(AVLNode<T> *root) const; // Left, Right, Parent
};

#endif