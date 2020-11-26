#include "avl_tree.h"
#include "avl_node.h"

template <class T>
void deleteNode(avlNode<T> *root)
{
    delete root;
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
        return AVL_TREE_SUCCESS;
    }
    else if (insertAvlNode(root, new_node) != AVL_TREE_SUCCESS)
    {
        deleteNode(new_node);
        return AVL_TREE_FAILURE;
    }
}

template <class T>
avlTreeResult_t avlTree<T>::insertAvlNode(avlNode<T> *root, avlNode<T> *new_node)
{
    if (find(root, new_node->getValue))
        return AVL_TREE_FAILURE;
    // Binary Search Tree insertion algorithm
    if (new_node->getValue() == root->getValue())
        return AVL_TREE_FAILURE;
    if (new_node->getValue() < root->getValue())
    {
        if (root->getLeft()) // If there is a left child, keep searching
            return insertAvlNode(root->getLeft(), new_node);
        else
        { // Found the right spot
            root->setLeft(new_node);
            new_node->setParent(root);
            return AVL_TREE_SUCCESS;
        }
    }
    else
    {
        if (root->getRight()) // If there is a right child, keep searching
            return insertAvlNode(root->getRight(), new_node);
        else
        { // Found the right spot
            root->setRight(new_node);
            new_node->setParent(root);
            return AVL_TREE_SUCCESS;
        }
    }
}

// AVL balancing algorithm
template <class T>
void avlTree<T>::treeBalance(avlNode<T>* root) {
    if (!root)
        return;
        
    int balance = getBF(root);
    if (balance > 1)
    {                                           // left tree unbalanced
        if (BalanceFactor(root->GetLeft()) < 0) // right child of left tree is the cause
            RotateLeft(root->GetLeft());        // double rotation required
        RotateRight(root);
    }
    else if (balance < -1)
    {                                            // right tree unbalanced
        if (BalanceFactor(root->GetRight()) > 0) // left child of right tree is the cause
            RotateRight(root->GetRight());
        RotateLeft(root);
    }
    if (root->getParent())
        treeBalance(root->getParent());
}

template <class T>
avlTree<T>::~avlTree()
{
    if (!root)
        return;
    postOrder(root, deleteNode);
}

template <class T>
avlNode<T> *find(avlNode<T> *root, const T &value)
{
    // Element not found
    if (!root)
        return NULL;

    T root_value = root->getValue();

    if (root_value == value)
    {
        return root;
    }
    else if (value < root_value)
    {
        return find(root->getLeft(), value); //search left sub tree
    }
    else if (value > root_value)
    {
        return find(root->getRight(), value); //search right sub tree
    }
}

template <class T>
int getHeight(avlNode<T> *root)
{
    if (!root)
        return -1;

    int left = getHeight(root->getLeft());
    int right = getHeight(root->getRight());
    return 1 + ((left > right) ? left : right);
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