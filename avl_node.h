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
    avlNode() = default;
    avlNode(const T &value);
    ~avlNode() = default;
    avlNode *getLeft();
    avlNode *getRight();
    avlNode *getParent();
    T &getValue();
    const T getValue() const;
    void setLeft(avlNode<T> *new_left);
    void setRight(avlNode<T> *new_right);
    void setParent(avlNode<T> *new_parent);
    void setHeight();
    void print() const;
    int getHeight();
    bool isLeftChild();
};


#endif