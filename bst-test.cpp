#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{



    BinarySearchTree<uint16_t, uint16_t> testTree;

//    testTree.insert(std::make_pair(5, 8));
//    testTree.insert(std::make_pair(3, 159));
//    testTree.insert(std::make_pair(1, 9));
//    testTree.insert(std::make_pair(10, 0x5a));
//
//    testTree.insert(std::make_pair(15, 0xb));
//    testTree.insert(std::make_pair(4, 4));
//    testTree.insert(std::make_pair(17, 159));

    testTree.print();
    std::cout << "checking balance: " << testTree.isBalanced() << std::endl;

    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));

    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

    // Binary Search Tree tests
    BinarySearchTree<int,int> bt2;
    bt2.insert(std::make_pair(4,4));
    bt2.insert(std::make_pair(5,2));
    bt2.insert(std::make_pair(6,2));
    bt2.insert(std::make_pair(6,5));
//    bt2.insert(std::make_pair(3,6));
//    bt2.insert(std::make_pair(6,1));
//    bt2.insert(std::make_pair(3,3));
//    bt2.insert(std::make_pair(5,5));
//    bt2.insert(std::make_pair(7,7));
//    bt2.insert(std::make_pair(12,7));
//    bt2.insert(std::make_pair(-3,7));

    for (auto it = bt2.begin(); it != bt2.end(); ++it) {
        std::cout << it->first << " ";
    }
    std::cout << std::endl;

    bt2.print();

    // check internal find
    if (bt2.find(10) != bt2.end()) {
        std::cout << "found value" << std::endl;
    } else {
        std::cout << "did not find value" << std::endl;
    }

    std::cout << "balanced: " << bt2.isBalanced() << std::endl;

    // check remove
    bt2.remove(3);
    bt2.remove(5);
    bt2.remove(6);
    bt2.remove(4);

    std::cout << "after remove: ";
    for (auto it = bt2.begin(); it != bt2.end(); ++it) {
        std::cout << it->first << " ";
    }
    std::cout << std::endl;


//    // AVL Tree Tests
//    AVLTree<char,int> at;
//    at.insert(std::make_pair('a',1));
//    at.insert(std::make_pair('b',2));
//
//    cout << "\nAVLTree contents:" << endl;
//    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
//        cout << it->first << " " << it->second << endl;
//    }
//    if(at.find('b') != at.end()) {
//        cout << "Found b" << endl;
//    }
//    else {
//        cout << "Did not find b" << endl;
//    }
//    cout << "Erasing b" << endl;
//    at.remove('b');

    return 0;
}
