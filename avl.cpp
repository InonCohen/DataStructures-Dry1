#include "avl.h"


template <class T>
avlNode<T>::avlNode(const T &value) : data(value), left(NULL), right(NULL), parent(NULL) {
}




template <class T>
avlNode<T>* avlNode<T>::find(avlNode* node, T data) {
        // Element not found
        if(node == NULL)
            return NULL;

        // Searching for element
        else if(data < node->data)
            node->left = find(x, node->left); //search left sub tree
        else if(data > node->data)
            node->right = find(x, node->right); //search right sub tree
        else
            return node; //found
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
void avlNode<T>::setLeft(avlNode* new_left) {
    this->left = new_left;
}

template <class T>
void avlNode<T>::setRight(avlNode* new_right) {
    this->right = new_right;
}

template <class T>
void avlNode<T>::setParent(avlNode* new_parent) {
    this->parent = new_parent;
}

template <class T>
void avlNode<T>::print() const {
    std::cout << data_ << std::endl;
}