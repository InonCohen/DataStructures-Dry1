#include <iostream>
#include "avl_tree.hpp"

int main(int, char **)
{
        twList<int> check;
    std::cout<<check<<std::endl;
    check.addFirst(9);
    std::cout<<check<<std::endl;
    check.addFirst(8);
    std::cout<<check<<std::endl;
    check.addLast(1);
    std::cout<<check<<std::endl;
    check.addLast(2);
    std::cout<<check<<std::endl;
    check.addLast(0);
    std::cout<<check<<std::endl;
    check.addFirst(0);
    std::cout<<check<<std::endl;
    check.addFirst(10);
    std::cout<<check<<std::endl;
    twListNode<int> *h,*t;
    h=(check.getHead());
    check.remove(h->getNext());
    std::cout<<check<<std::endl;
    t=(check.getTail());
    check.remove(t->getPrev());
    std::cout<<check<<std::endl;
//    twListNode<int> five(5);
//    check.addLast(five);
//    std::cout<<check<<std::endl;
//    twListNode<int> ten(10);
//    check.addFirst(ten);
//    std::cout<<check<<std::endl;
//    twListNode<int> ele(11);
//    check.addLast(ele);
//    std::cout<<check<<std::endl;
//    twListNode<int> zero(0);
//    check.addFirst(zero);
//    std::cout<<check<<std::endl;
    return 0;
}

 /*   avlTree<int> tree;
    for (int i = 3; i < 13; i++)
    {
        tree.insert(i);
    }
    // tree.inOrder(tree.getRoot(), printNode);

    // printTreeStatus(&tree);
    // std::cout << "largest: " << tree.getLargest()->getValue() << std::endl;
    // std::cout << "first: " << tree.getFirst()->getValue() << std::endl;
    // tree.reverseInOrder(14, print);
    // for (int i = 3; i < 13; i++)
    // {
    //     tree.remove(i);
    //     // printNode(tree.getLargest());
    //     // std::cout << "removed: " << i << std::endl;
    // }

    tree.inOrder(tree.getRoot(), print);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    tree.inOrder(tree.getRoot(), printBF);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    tree.inOrder(tree.getRoot(), printHeight);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    // std::cout << tree.getRoot() << std::endl;
    // printTreeStatus(&tree);
    // std::cout << "largest: " << tree.getLargest()->getValue() << std::endl;
    // std::cout << "first: " << tree.getFirst()->getValue() << std::endl;
    // tree.reverseInOrder(14, print);

    return 0;
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

    int z = tree.reverseInOrder(20, print);
    std::cout << std::endl;
    std::cout << z << std::endl;
    tree.insert(12);
    z = tree.reverseInOrder(20, print);
    std::cout << std::endl;
    std::cout << z << std::endl;

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

    return 0;*/
}
