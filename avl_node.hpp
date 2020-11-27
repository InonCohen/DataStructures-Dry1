#ifndef AVL_NODE_HPP
#define AVL_NODE_HPP

#include "avl_node.h"


template <class T>
avlNode<T>::avlNode(const T &value) : data(value), left(NULL), right(NULL), parent(NULL) {
}


template <class T>
avlNode<T>* avlNode<T>::getLeft() {
    return this->left;
}

template <class T>
avlNode<T>* avlNode<T>::getRight() {
    return this->right;
}

template <class T>
avlNode<T>* avlNode<T>::getParent() {
    return this->parent;
}

template <class T>
T& avlNode<T>::getValue() {
    return this->data;
}

template <class T>
const T avlNode<T>::getValue() const {
    return this->data;
}


template <class T>
void avlNode<T>::setLeft(avlNode<T>* new_left) {
    if (new_left)
        new_left->setParent(this);
    this->left = new_left;
}

template <class T>
void avlNode<T>::setRight(avlNode<T>* new_right) {
    if (new_right)
        new_right->setParent(this);
    this->right = new_right;
}

template <class T>
void avlNode<T>::setParent(avlNode<T>* new_parent) {
    this->parent = new_parent;
}

template <class T>
bool avlNode<T>::isLeftChild() {
    return this->getParent()->getLeft() == this;
}

template <class T>
void avlNode<T>::setHeight() {
    int left = this->getLeft() ? this->getLeft()->getHeight() : -1;
    int right = this->getRight() ? this->getRight()->getHeight() : -1;
    this->height = 1 + ((left > right) ? left : right);
}

template <class T>
void avlNode<T>::print() const {
    std::cout << data << std::endl;
}

template <class T>
int avlNode<T>::getHeight()
{
    return this->height;
}

#endif
