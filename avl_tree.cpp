#include "avl_tree.h"
#include "avl_node.h"

template <class T>
avlNode<T> *find(avlNode<T> *root, const T &value)
{
    // Element not found
    if (!root)
        return NULL;

    // Searching for element
    else if (value < root.getData())
        return find(value, root.getLeft()); //search left sub tree
    else if (value > root->getData())
        return find(value, root.getRight()); //search right sub tree
    else
        return root; //found
}

template <class T>
int getHeight(avlNode<T> *root)
{
    if (!root)
        return -1;

    int height;
    if (root)
    {
        int left = getHeight(root->getLeft());
        int right = getHeight(root->getRight());
        height = 1 + ((left > right) ? left : right);
    }
    return height;
}

template <class T>
int getBF(avlNode<T> *root)
{
    if (!root)
    {
        return 0;
    }
    int balance;
    balance = getHeight(root->getLeft()) - getHeight(root->getRight());

    return balance;
}

template <class T>
template <class Func>
void avlTree<T>::inOrder(avlNode<T> *root, Func function) const
{
    if (!root)
        return;
    inOrder(root->getLeft(), function);
    function(root);
    inOrder(root->getRight(), function);
}

template <class T>
template <class Func>
void avlTree<T>::postOrder(avlNode<T> *root, Func function) const
{
    if (!root)
        return;
    postOrder(root->getLeft(), function);
    postOrder(root->getRight(), function);
    function(root);
}

template <class T>
template <class Func>
void avlTree<T>::preOrder(avlNode<T> *root, Func function) const
{
    if (!root)
        return;
    function(root);
    preOrder(root->getLeft(), function);
    preOrder(root->getRight(), function);
}