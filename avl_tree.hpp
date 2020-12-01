#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "avl_tree.h"
#include "avl_node.hpp"
#include <stdlib.h>

#include <iostream>

template <class T>
avlTree<T>::avlTree() : root(NULL)
{
}

template <class T>
void print(avlNode<T> *root)
{
    std::cout << root->getValue() << " ";
}

template <class T>
void printBF(avlNode<T> *root)
{
    std::cout << getBF(root) << " ";
}

template <class T>
void printHeight(avlNode<T> *root)
{
    if (root)
        std::cout << root->getHeight() << " ";
}

template <class T>
void printTreeStatus(avlTree<T> tree)
{
    std::cout << tree.getRoot()->getValue() << std::endl;
    std::cout << tree.getRoot()->getRight()->getValue() << std::endl;
    std::cout << tree.getRoot()->getLeft()->getValue() << std::endl;
}

template <class T>
void deleteNode(avlNode<T> *node)
{
    delete node;
}

template <class T>
avlTree<T>::~avlTree()
{
    if (!root)
        return;
    postOrder(root, deleteNode);
}

template <class T>
avlTreeResult_t avlTree<T>::insert(const T &value)
{
    avlNode<T> *new_node = new avlNode<T>(value);

    if (!new_node)
        return AVL_TREE_OUT_OF_MEMORY; // Out of memory

    if (!root)
    { // Special case
        root = new_node;
        root->setHeight();
        // std::cout << "ADDED NEW ROOT: " << new_node->getValue() << std::endl;
        return AVL_TREE_SUCCESS;
    }
    else if (find(root, new_node->getValue()))
    {
        deleteNode(new_node);
        return AVL_TREE_FAILURE;
    }
    else if (insertAvlNode(root, new_node) != AVL_TREE_SUCCESS)
    {
        // std::cout << "COULD NOT ADD: " << new_node->getValue() << std::endl;
        deleteNode(new_node);
        return AVL_TREE_FAILURE;
    }
    // std::cout << "ADDED: " << new_node->getValue() << std::endl;

    treeBalance(new_node);
    return AVL_TREE_SUCCESS;
}

template <class T>
avlTreeResult_t avlTree<T>::remove(const T &value)
{
    // std::cout << "Trying to remove: " << value << std::endl;
    if (!root)
    { //Tree is empty
        // std::cout << "Tree is empty: " << std::endl;
        return AVL_TREE_INVALID_INPUT;
    }

    avlNode<T> *node_to_remove = find(this->root, value);

    if (!node_to_remove)
    {
        // std::cout << "Node isn't in the tree: " << std::endl;
        return AVL_TREE_FAILURE;
    }

    if (!node_to_remove->getParent())
    {
        // std::cout << "Removing The root" << std::endl;
        this->root = createNewSubTree(node_to_remove);
        avlNode<T> *newroot = findNewRoot(this->root);
        // std::cout << "root Removed" << std::endl;
        // if (newroot)
        //     std::cout << "new root is: " << newroot->getValue() << std::endl;
        // else
        // {
        //     std::cout << "now the tree is empty" << std::endl;
        // }
        rootUpdate(newroot);
    }
    else
    {
        removeNodeWithParent(node_to_remove);
    }
    deleteNode(node_to_remove);
    return AVL_TREE_SUCCESS;
}

template <class T>
void avlTree<T>::removeNodeWithParent(avlNode<T> *node_to_remove)
{
    // std::cout << "removing node with parent: " << node_to_remove->getValue() << std::endl;
    avlNode<T> *parent = node_to_remove->getParent();
    // std::cout << "parent: " << node_to_remove->getParent()->getValue() << std::endl;
    if (node_to_remove->isLeftChild())
    {
        // std::cout << "left child" << std::endl;
        parent->setLeft(createNewSubTree(node_to_remove));
    }
    else
    {
        // std::cout << "right child" << std::endl;
        parent->setRight(createNewSubTree(node_to_remove));
    }
    // std::cout << "removing node with parent: " << node_to_remove->getValue() << std::endl;
    recursiveSetHeight(parent);
    treeBalance(parent);
    // std::cout << "removing node with parent: " << node_to_remove->getValue() << std::endl;
}

template <class T>
void printNode(avlNode<T> *node)
{
    std::cout << "=========================" << std::endl;
    std::cout << "left child of: " << node->getValue() << " is: " << (node->getLeft() ? node->getLeft()->getValue() : 0) << std::endl;
    std::cout << "Right child of: " << node->getValue() << " is: " << (node->getRight() ? node->getRight()->getValue() : 0) << std::endl;
    std::cout << "parent of: " << node->getValue() << " is: " << (node->getParent() ? node->getParent()->getValue() : 0) << std::endl;
    if (node->getParent())
    {
        if (node->isLeftChild())
            std::cout << node->getValue() << " is left child" << std::endl;
        else
            std::cout << node->getValue() << " is right child" << std::endl;
    }
    std::cout << "=========================" << std::endl;
}

template <class T>
avlNode<T> *avlTree<T>::createNewSubTree(avlNode<T> *node)
{
    if ((node->getRight()) && (node->getLeft()))
    {
        // std::cout << node->getValue() << "   has two children" << std::endl;
        avlNode<T> *next_node_in_order = firstInOrder(node->getRight());

        // std::cout << "trying to swap: " << node->getValue() << " with: " << next_node_in_order->getValue() << std::endl;
        // printNode(node);
        // printNode(next_node_in_order);
        swap(next_node_in_order, node);
        // printNode(node);
        // printNode(next_node_in_order);

        next_node_in_order->setParent(NULL);
        // std::cout << "set parent (null): " << next_node_in_order->getValue() << std::endl;

        removeNodeWithParent(node);
        // std::cout << "removed node with parent " << std::endl;
        return next_node_in_order;
    }
    if ((!node->getRight()) && (!node->getLeft()))
    {
        // std::cout << "is leaf" << std::endl;
        // deleteNode(node);
        return NULL;
    }
    if (node->getRight())
    {
        // std::cout << "has right child" << std::endl;
        node->getRight()->setParent(NULL);
        avlNode<T> *right_sub_root = node->getRight();
        // deleteNode(node);

        return right_sub_root;
    }
    // std::cout << "has left child" << std::endl;
    avlNode<T> *left_sub_root = node->getLeft();
    node->getLeft()->setParent(NULL);
    // deleteNode(node);
    return left_sub_root;
}

template <class T>
avlNode<T> *avlTree<T>::firstInOrder(avlNode<T> *sub_root)
{
    while (sub_root->getLeft())
    {
        sub_root = sub_root->getLeft();
    }
    return sub_root;
}

template <class T>
void avlTree<T>::swap(avlNode<T> *src, avlNode<T> *dst)
{
    // std::cout << "trying to swap: src = " << src->getValue() << std::endl;
    // std::cout << "asdasd " << src->getParent()->getLeft()->getValue() << std::endl;

    if (src->getRight() == dst) //if dst is right child of src perform parent-child right swap
    {
        // std::cout << "1" << std::endl;
        src->swapWithChild(dst, 1);
    }
    else if (src->getLeft() == dst) //if dst is left child of src perform parent-child left swap
    {
        // std::cout << "2" << std::endl;
        src->swapWithChild(dst, 0);
    }
    else if (dst->getRight() == src) //if src is right child of dst perform parent-child right swap
    {
        // std::cout << "3" << std::endl;
        dst->swapWithChild(src, 1);
    }
    else if (dst->getLeft() == src) //if src is left child of dst perform parent-child left swap
    {
        // std::cout << "4" << std::endl;
        dst->swapWithChild(src, 0);
    }
    else //not connected in the tree
    {
        // std::cout << "5" << std::endl;
        avlNode<T> temp_src = *src;
        avlNode<T> temp_dst = *dst;
        // std::cout << "temp_src: " << std::endl;
        // printNode(&temp_src);
        // std::cout << "temp_dst: " << std::endl;
        // printNode(&temp_dst);
        src->copyFrom(&temp_dst);
        // std::cout << "second" << std::endl;
        dst->copyFrom(&temp_src);
    }
}

template <class T>
void avlTree<T>::rootUpdate(avlNode<T> *newroot)
{
    this->root = newroot;
}

template <class T>
avlNode<T> *avlTree<T>::findNewRoot(avlNode<T> *newroot)
{
    if (!newroot)
        return NULL;
    while (newroot->getParent())
    {
        newroot = newroot->getParent();
    }
    return newroot;
}

template <class T>
avlTreeResult_t avlTree<T>::insertAvlNode(avlNode<T> *root, avlNode<T> *new_node)
{
    // Binary Search Tree insertion algorithm
    if (new_node->getValue() < root->getValue())
    {
        if (root->getLeft())
        { // If there is a left child, keep searching
            avlTreeResult_t result = insertAvlNode(root->getLeft(), new_node);
            root->setHeight();
            return result;
        }
        else
        { // Found the right spot
            // std::cout << "SPOT FOR: " << new_node->getValue() << std::endl;
            root->setLeft(new_node);
            new_node->setParent(root);
            new_node->setHeight();
            // std::cout << "new node height: " << new_node->getHeight() << std::endl;
            root->setHeight();
            return AVL_TREE_SUCCESS;
        }
    }
    else
    {
        if (root->getRight())
        { // If there is a right child, keep searching
            avlTreeResult_t result = insertAvlNode(root->getRight(), new_node);
            root->setHeight();
            // std::cout << "Root is: " << root->getValue() << " and it's height is: " << root->getHeight() << std::endl;
            return result;
        }
        else
        { // Found the right spot
            root->setRight(new_node);
            new_node->setParent(root);
            new_node->setHeight();
            root->setHeight();
            return AVL_TREE_SUCCESS;
        }
    }
}

// AVL balancing algorithm
template <class T>
void avlTree<T>::treeBalance(avlNode<T> *root)
{
    if (!root)
        return;

    int balance = getBF(root);
    // std::cout << "balance is: " << balance << " of node: " << root->getValue() << std::endl;
    if (balance > 1)
    { // left tree unbalanced
        if (getBF(root->getLeft()) < 0)
        { // right child of left tree is the cause
            // std::cout << "Double rotate" << std::endl;
            rotateLeft(root->getLeft()); // double rotation required
        }
        rotateRight(root);
    }
    else if (balance < -1)
    {
        // std::cout << "222balance is: " << getBF(root->getRight()) << " of node: " << root->getRight()->getValue() << std::endl;
        // right tree unbalanced
        if (getBF(root->getRight()) > 0)
        { // left child of right tree is the cause
            // std::cout << "ap" << std::endl;
            rotateRight(root->getRight());
        }
        rotateLeft(root);
    }
    if (root->getParent())
    {
        // std::cout << "parent is: " << root->getParent()->getValue() << std::endl;
        treeBalance(root->getParent());
    }
}

template <class T>
void avlTree<T>::rotateLeft(avlNode<T> *sub_root)
{
    // std::cout << "Rotating: " << sub_root->getValue() << " left" << std::endl;
    avlNode<T> *newroot = sub_root->getRight();
    sub_root->setRight(newroot->getLeft());

    if (sub_root->getParent() == NULL)
    {
        this->root = newroot;
        newroot->setParent(NULL);
    }
    else
    {
        if (sub_root->isLeftChild())
        {
            sub_root->getParent()->setLeft(newroot);
        }
        else
        {
            sub_root->getParent()->setRight(newroot);
        }
    }
    newroot->setLeft(sub_root);
    this->recursiveSetHeight(sub_root);
    // std::cout << sub_root->getValue() << "'s new parent is: " << newroot->getValue() << std::endl;
}

template <class T>
void avlTree<T>::recursiveSetHeight(avlNode<T> *node)
{
    while (node)
    {
        node->setHeight();
        node = node->getParent();
    }
}

template <class T>
void avlTree<T>::rotateRight(avlNode<T> *sub_root)
{
    // std::cout << "Rotating: " << sub_root->getValue() << " right" << std::endl;
    avlNode<T> *newroot = sub_root->getLeft();
    sub_root->setLeft(newroot->getRight());

    if (sub_root->getParent() == NULL)
    {
        this->root = newroot;
        newroot->setParent(NULL);
    }
    else
    {
        // std::cout << "sub_root's parent is: " << sub_root->getParent()->getValue() << std::endl;
        if (sub_root->isLeftChild())
        {
            // std::cout << "sub_root is left child" << std::endl;
            sub_root->getParent()->setLeft(newroot);
        }
        else
        {
            // std::cout << "sub_root is right child" << std::endl;
            sub_root->getParent()->setRight(newroot);
        }
    }
    newroot->setRight(sub_root);
    this->recursiveSetHeight(sub_root);

    // std::cout << sub_root->getValue() << "'s new parent is: " << newroot->getValue() << std::endl;
}

template <class T>
avlNode<T> *find(avlNode<T> *root, const T &value)
{
    // Element not found
    if (!root)
        return NULL;

    if (root->getValue() == value)
    {
        return root;
    }
    else if (value < root->getValue())
    {
        return find(root->getLeft(), value); //search left sub tree
    }
    else
    {
        return find(root->getRight(), value); //search right sub tree
    }
}

template <class T>
int getBF(avlNode<T> *root)
{
    if (!root)
    {
        return 0;
    }
    int balance;
    int left = root->getLeft() ? root->getLeft()->getHeight() : -1;
    int right = root->getRight() ? root->getRight()->getHeight() : -1;

    // std::cout << "left height: " << left << "     right height: " << right << std::endl;
    balance = left - right;
    return balance;
}

template <class T>
void avlTree<T>::inOrder(avlNode<T> *root, void (*function)(avlNode<T> *)) const
{
    if (!root)
        return;
    inOrder(root->getLeft(), function);
    function(root);
    inOrder(root->getRight(), function);
}

template <class T>
void avlTree<T>::postOrder(avlNode<T> *root, void (*function)(avlNode<T> *)) const
{
    if (!root)
        return;
    postOrder(root->getLeft(), function);
    postOrder(root->getRight(), function);
    function(root);
}

// template <class T>
// void avlTree<T>::postOrder(avlNode<T> *root, void (*function)(avlNode<T> *, int* )) const
// {
//     if (!root)
//         return;
//     postOrder(root->getLeft(), function);
//     postOrder(root->getRight(), function);
//     function(root);
// }

template <class T>
void avlTree<T>::preOrder(avlNode<T> *root, void (*function)(avlNode<T> *)) const
{
    if (!root)
        return;
    function(root);
    preOrder(root->getLeft(), function);
    preOrder(root->getRight(), function);
}

#endif