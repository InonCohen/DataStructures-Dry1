#include <iostream>
#include "avl_tree.hpp"

int main(int, char **)
{
    avlTree<int> tree;
    tree.insert(10);
    tree.insert(1);

    // tree.insert(1);
    // std::cout << "tree heights inOrder: ";
    // tree.inOrder(tree.getRoot(), printHeight);
    // std::cout << std::endl;

    tree.insert(15);

    // std::cout << "tree heights inOrder: ";
    // tree.inOrder(tree.getRoot(), printHeight);
    // std::cout << std::endl;

    tree.insert(22);
    // std::cout << "tree heights inOrder: ";
    // tree.inOrder(tree.getRoot(), printHeight);
    // std::cout << std::endl;
    tree.insert(21);
    tree.insert(14);
    tree.insert(12);
    tree.insert(13);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    
    tree.remove(13);
    std::cout << std::endl;
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    tree.inOrder(tree.getRoot(), printBF);
    std::cout << std::endl;
    // std::cout << "DONE" << std::endl;
    // std::cout << tree.getRoot()->getValue() << std::endl;
    // std::cout << "HEY1" << std::endl;
    // tree.insert(14);

    // tree.postOrder(tree.getRoot(), print);
    // std::cout << std::endl;
    // tree.inOrder(tree.getRoot(), print);
    // std::cout << std::endl;
    // tree.preOrder(tree.getRoot(), print);
    // std::cout << std::endl;

    // std::cout << "HEY2" << std::endl;
    // tree.postOrder(tree.getRoot(), printBF);
    // std::cout << std::endl;
    // tree.inOrder(tree.getRoot(), printBF);
    // std::cout << std::endl;
    // tree.preOrder(tree.getRoot(), printBF);
    // std::cout << std::endl;

    // std::cout << "HEY3" << std::endl;
    // tree.postOrder(tree.getRoot(), printHeight);
    // std::cout << std::endl;
    // tree.inOrder(tree.getRoot(), printHeight);
    std::cout << std::endl;
    // tree.preOrder(tree.getRoot(), printHeight);
    // std::cout << std::endl;

    std::cout << tree.getRoot()->getValue() << std::endl;
    std::cout << tree.getRoot()->getRight()->getValue() << std::endl;
    std::cout << tree.getRoot()->getLeft()->getValue() << std::endl;

    return 0;
}
