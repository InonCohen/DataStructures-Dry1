#include <iostream>
#include "avl_tree.hpp"

int main(int, char **)
{  
    avlTree<int> tree;
    tree.insert(10);
    tree.insert(13);
    tree.insert(14);
    tree.insert(15);
    tree.insert(16);
    tree.insert(17);
    tree.insert(18);
    tree.insert(19);
    printTreeStatus(&tree);


    std::cout << tree.getLargest()->getValue() << std::endl;

    tree.reverseInOrder(5, print);
    std::cout << std::endl;

    tree.reverseInOrder(20, print);
    std::cout << std::endl;

    tree.insert(15);

    return 0;

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
    tree.insert(13);
    tree.insert(13);
    tree.insert(1666);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    tree.remove(13);
    std::cout << std::endl;
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    tree.remove(13);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    tree.inOrder(tree.getRoot(), printHeight);
    std::cout << std::endl;

    tree.inOrder(tree.getRoot(), printBF);
    std::cout << std::endl;

    printTreeStatus(&tree);

    tree.remove(15);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    return 0;
    tree.remove(14);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    tree.inOrder(tree.getRoot(), printHeight);
    std::cout << std::endl;
    tree.remove(15);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    tree.remove(12);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    tree.inOrder(tree.getRoot(), printHeight);
    std::cout << std::endl;
    tree.remove(10);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    tree.remove(1);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    tree.remove(21);
    tree.inOrder(tree.getRoot(), print);
    std::cout << "removed 21" << std::endl;
    tree.remove(22);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    tree.insert(13);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    tree.remove(13);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    tree.insert(13);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    tree.remove(13);
    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    return 0;
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

    printTreeStatus(&tree);


    return 0;
}
