#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "avl_tree.h"
#include "avl_node.hpp"
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
        std::cout << "ADDED NEW ROOT: " << new_node->getValue() << std::endl;
        return AVL_TREE_SUCCESS;
    }
    else if (find(root, new_node->getValue()))
    {
        deleteNode(new_node);
        return AVL_TREE_FAILURE;
    }
    else if (insertAvlNode(root, new_node) != AVL_TREE_SUCCESS)
    {
        std::cout << "COULD NOT ADD: " << new_node->getValue() << std::endl;
        deleteNode(new_node);
        return AVL_TREE_FAILURE;
    }
    std::cout << "ADDED: " << new_node->getValue() << std::endl;

    treeBalance(new_node);
    return AVL_TREE_SUCCESS;
}

template <class T>
avlTreeResult_t avlTree<T>::remove(const T &value)
{

    if (!root)
    { //Tree is empty
        return AVL_TREE_INVALID_INPUT;
    }

    avlNode<T> *node_to_remove = find(this->root, value);

    if (!node_to_remove)
    {
        return AVL_TREE_FAILURE;
    }

    if (node_to_remove->isLeftChild())
    {
        node_to_remove->getParent()->setLeft(createNewSubTree(node_to_remove));
        return AVL_TREE_SUCCESS;
    }
    node_to_remove->getParent()->setRight(createNewSubTree(node_to_remove));

    return AVL_TREE_SUCCESS;
}

// template <class T>
// void avlTree<T>::removeNodeOneChild(avlNode<T> *node, bool is_right_child)
// {
//     if (node_to_remove->isLeftChild())
//     {
//         if (is_right_child)
//             node_to_remove->getParent()->setLeft(node_to_remove->getRight());
//         else
//             node_to_remove->getParent()->setLeft(node_to_remove->getLeft());
//     }
//     else
//     {
//         node_to_remove->getParent()->setRight(node_to_remove->getRight());
//     }
//     this->eraseAndBalance(node);
// }

template <class T>
avlNode<T> *avlTree<T>::createNewSubTree(avlNode<T> *node)
{
    if ((!node->getRight()) && (!node->getLeft()))
    {
        return NULL;
    }
    if ((node->getRight()) && (!node->getLeft()))
    {
        return node->getRight();
    }
    if ((!node->getRight()) && (node->getLeft()))
    {
        return node->getLeft();
    }
    avlNode<T> *new_parent = node->getRight();
    while (new_parent->getLeft())
    {
        new_parent = new_parent->getLeft();
    }
    new_parent->setLeft(node->getLeft());
    avlNode<T> *height_calc_node = new_parent;
    while (height_calc_node->getParent() != node->getRight())
    {
        height_calc_node->setHeight();
        height_calc_node = height_calc_node->getParent();
    }
    height_calc_node->setParent(NULL);
    deleteNode(node);
    treeBalance(new_parent);
    return height_calc_node;
}

// template <class T>
// void avlTree<T>::eraseAndBalance(avlNode<T> *node)
// {
//     avlNode<T> *node_parent = node->getParent();
//     deleteNode(node);
//     treeBalance(node_parent);
// }

// template <class T>
// void avlTree<T>::removeLeaf(avlNode<T> *node)
// {
//     if (node->getParent() == NULL)
//     {
//         deleteNode(node);
//         this->root = NULL;
//     }
//     if (node->isLeftChild())
//     {
//         node->getParent()->setLeft(NULL);
//     }
//     else
//     {
//         node->getParent()->setRight(NULL);
//     }
//     this->eraseAndBalance(node);
// }

template <class T>
void avlTree<T>::rootUpdate(avlNode<T> *newroot)
{
    this->root = newroot;
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
    std::cout << "balance is: " << balance << " of node: " << root->getValue() << std::endl;
    if (balance > 1)
    {                                    // left tree unbalanced
        if (getBF(root->getLeft()) < 0)  // right child of left tree is the cause
            rotateLeft(root->getLeft()); // double rotation required
        rotateRight(root);
    }
    else if (balance < -1)
    {
        // std::cout << "222balance is: " << getBF(root->getRight()) << " of node: " << root->getRight()->getValue() << std::endl;
        // right tree unbalanced
        if (getBF(root->getRight()) > 0)
        { // left child of right tree is the cause
            std::cout << "ap" << std::endl;
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
    std::cout << "Rotating: " << sub_root->getValue() << " left" << std::endl;
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
    std::cout << sub_root->getValue() << "'s new parent is: " << newroot->getValue() << std::endl;
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
    std::cout << "Rotating: " << sub_root->getValue() << " right" << std::endl;
    avlNode<T> *newroot = sub_root->getLeft();
    sub_root->setLeft(newroot->getRight());

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
    newroot->setRight(sub_root);
    this->recursiveSetHeight(sub_root);
    std::cout << sub_root->getValue() << "'s new parent is: " << newroot->getValue() << std::endl;
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

    std::cout << "left height: " << left << "     right height: " << right << std::endl;
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