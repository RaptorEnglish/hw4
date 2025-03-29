#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    int getBalance2 () const;
    void setBalance2 (int balance);
    void updateBalance2(int diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
    int bal_;  // balance is giving me strange behavior
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}
template<class Key, class Value>
int AVLNode<Key, Value>::getBalance2() const
{
    return bal_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance2(int balance)
{
    bal_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance2(int diff)
{
    bal_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void balance(AVLNode<Key, Value>* node);
    void rotate_right(AVLNode<Key, Value>* node);
    void rotate_left(AVLNode<Key, Value>* node);


};

// helper function to rotate a node left
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotate_left(AVLNode<Key, Value> *node) {
    // exit if rotation not possible
    if (!node || !node->getRight()) return;

    // get elements to use in rotation
    AVLNode<Key, Value>* parent = node->getParent();
    AVLNode<Key, Value>* n1 = node->getRight();
    AVLNode<Key, Value>* t1 = n1->getLeft();

    // point at grandchild
    node->setRight(t1);
    if (t1) t1->setParent(node);

    // swap node with left child
    n1->setParent(parent);
    n1->setLeft(node);

    // update parent pointer
    if (parent) {
        if (parent->getLeft() == node) parent->setLeft(n1);
        else parent->setRight(n1);
    } else {
        this->root_ = n1;
    }

    // update node's parent
    node->setParent(n1);

    // update balance factors
    node->updateBalance2(1);
    n1->updateBalance2(-1);;

}

// helper function to balance tree
template<typename Key, typename Value>
void AVLTree<Key, Value>::balance(AVLNode<Key, Value> *node) {
    int b_factor = node->getBalance2();

    // handle cases
    if (b_factor > 1) {  // left heavy tree
        if (node->getLeft()->getBalance2() >= 0) {  // left-left (LL) case
            rotate_right(node);
        } else { // left-right (LR) case
            rotate_left(node->getLeft());
            rotate_right(node);
        }
    } else if (b_factor < -1) {
        if (node->getRight()->getBalance2() <= 0) {  // right-right (RR) case
            rotate_left(node);
        } else { // right-left (RL) case
            rotate_right(node->getRight());
            rotate_left(node);
        }

    }

}

// helper function to rotate a node left
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotate_right(AVLNode<Key, Value> *node) {
    // exit if rotation not possible
    if (!node || !node->getLeft()) return;

    // get elements to use in rotation
    AVLNode<Key, Value>* parent = node->getParent();
    AVLNode<Key, Value>* n1 = node->getLeft();
    AVLNode<Key, Value>* t1 = n1->getRight();

    // point at grandchild
    node->setLeft(t1);
    if (t1) t1->setParent(node);

    // swap node with left child
    n1->setParent(parent);
    n1->setRight(node);

    // update parent pointer
    if (parent) {
        if (parent->getLeft() == node) parent->setLeft(n1);
        else parent->setRight(n1);
    } else {
        this->root_ = n1;
    }

    // update node's parent
    node->setParent(n1);

    node->updateBalance2(-1);
    n1->updateBalance2(1);
}

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO

    // use bst implementation to add node
    BinarySearchTree<Key, Value>::insert(new_item);



    // find node that was inserted
    AVLNode<Key, Value>* inserted = static_cast<AVLNode<Key, Value>*>(this->internalFind(new_item.first));
    std::cout << "top" << std::endl;


    // use rotations to balance tree
    while (inserted) {
        // Update the height of the node
        int left_height = getSubtreeHeight(inserted->getLeft());
        int right_height = getSubtreeHeight(inserted->getRight());

        // Update balance factor
//        inserted->setBalance2(left_height - right_height);
//
//        // update balance
//        balance(inserted);

        // call again on parent
        inserted = inserted->getParent();

    }

}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO

    // use bst implementation to remove node
    BinarySearchTree<Key, Value>::remove(key);

    // use rebalancing functions

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
