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

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
//    int height_;

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


/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
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
    void balance_avl(AVLNode<Key, Value>* node);
    void update_avl(AVLNode<Key, Value>* node);
    void rotate_right(AVLNode<Key, Value>* node);
    void rotate_left(AVLNode<Key, Value>* node);

    // redo funcs
    void update_heights(AVLNode<Key, Value>* node);
    void remove_helper(const Key& key);



};

template<typename Key, typename Value>
void AVLTree<Key, Value>::update_heights(AVLNode<Key, Value>* node) {
    if (node == nullptr) return;

    // First, update the height of the children
    if (node->getLeft()) {
        update_heights(node->getLeft());
    }
    if (node->getRight()) {
        update_heights(node->getRight());
    }

    // Now update the height and balance of the current node
    int left_height = (node->getLeft() != nullptr) ? node->getLeft()->get_height() : 0;
    int right_height = (node->getRight() != nullptr) ? node->getRight()->get_height() : 0;

    // Update balance factor (difference between left and right subtrees)
    node->setBalance(left_height - right_height);

    // Update height (1 + max of left and right subtree heights)
    node->set_height(std::max(left_height, right_height) + 1);
}


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
    node->updateBalance(-1);
    n1->updateBalance(1);;
//    if(t1)t1->updateBalance(3);

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

    node->updateBalance(1);
    n1->updateBalance(-1);
//    if(t1)t1->updateBalance(3);
}

// helper function to balance tree
template<typename Key, typename Value>
void AVLTree<Key, Value>::balance_avl(AVLNode<Key, Value> *node) {
    int b_factor = node->getBalance();

    // handle cases
    if (b_factor > 1) {  // left heavy tree
        if (node->getLeft()->getBalance() >= 0) {  // left-left (LL) case
            rotate_right(node);
        } else { // left-right (LR) case
            rotate_left(node->getLeft());
            rotate_right(node);
        }
    } else if (b_factor < -1) { // right heavy
        if (node->getRight()->getBalance() <= 0) {  // right-right (RR) case
            rotate_left(node);
        } else { // right-left (RL) case
            rotate_right(node->getRight());
            rotate_left(node);
        }

    }

}

template<typename Key, typename Value>
void AVLTree<Key, Value>::update_avl(AVLNode<Key, Value>* node) {
    // return;
//    update_heights(static_cast<AVLNode<Key, Value>*>(this->root_));

    // use rotations to balance tree
    while (node != nullptr) {
        int left_height = getSubtreeHeight(node->getLeft());
        int right_height = getSubtreeHeight(node->getRight());
        node->setBalance(left_height - right_height);

        // Update the height of the node
//        update_heights(node);

        // update balance
        balance_avl(node);

        // call again on parent
        node = node->getParent();

    }

//    this->print();

}


/*
 * Recall: If key is already in the tree, you should
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
//    std::cout << "adding: " << new_item.first << std::endl;

    // check to see if exists
    Node<Key, Value>* exists = this->internalFind(new_item.first);

    // convert pair into a node
    AVLNode<Key, Value>* node = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);

    // make a new node if root is null
    if (this->root_ == nullptr) {
        this->root_ = node;
        return;
    }

    // call helper function to insert
    insert_node(this->root_, node);

    // use rotations to balance tree
    if (!exists) update_avl(node);

//    this->print();
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::remove_helper(const Key& key) {

    // first find node
    AVLNode<Key, Value>* node = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    if (!node) return;

//    std::cout << "narrowing" << std::endl;

    // remove if both children
    if (node->getRight() && node->getLeft()) {  // swap with predecessor
        AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(this->predecessor(node));
        Key temp_key = pred->getKey();

        // swap key and value of node
        nodeSwap(node, pred);

        // remove node that now guaranteed to only have one child (predecessor)
        AVLNode<Key, Value>* child = static_cast<AVLNode<Key, Value>*>(node->getLeft());
        AVLNode<Key, Value>* parent = static_cast<AVLNode<Key, Value>*>(node->getParent());

        // promote from root
        if (node == this->root_) {
            this->root_ = child;
        } else if (parent) {
            // update pointers for parent node
            if (parent->getLeft() == node) parent->setLeft(child);
            else parent->setRight(child);
        }

        // update child pointer and delete node
        if (child) child->setParent(parent);
        delete node;

        // rebalance
        update_avl(parent);

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
//    std::cout << "removing: " << key << std::endl;

    // first find node
    AVLNode<Key, Value>* node = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    if (!node) return;

    // get parent
    AVLNode<Key, Value>* parent = node->getParent();

    // check for predecessor
    if (node->getLeft() && node->getRight()) {
        // use bst implementation to remove node
        remove_helper(key);

    } else {
        // use bst implementation to remove node
        BinarySearchTree<Key, Value>::remove(key);

        // rebalance
        update_avl(parent);
    }

//    this->print();

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
