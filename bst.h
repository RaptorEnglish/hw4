#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

    // height functions
    void set_height(int height) { height_ = height; }
    int get_height() { return height_; }

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
    int height_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL),
    height_(0)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value>* current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
//    int tree_height(Node<Key, Value>* node);


public:
    void print_tree() const;


protected:
    Node<Key, Value>* root_ = nullptr;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator()
{
    // TODO

    current_ = nullptr;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ != rhs.current_;
}

// helper to find successor of current node
template<typename Key, typename Value>
Node<Key, Value>* successor(Node<Key, Value>* current) {
    if (!current) return current;

    // init subtree to use to search
    Node<Key, Value>* next;

    // left most node of right subtree
    if (current->getRight()) {
        next = current->getRight();
        while (next->getLeft()) {
            next = next->getLeft();
        }
        return next;
    }

    // otherwise find first ancestor with curr node in left
    next = current->getParent();
    while (next && next->getRight() == current) {
        current = next;
        next = next->getParent();
    }

    return next;

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    if (current_) current_ = successor(current_);
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
    // TODO
    root_ = nullptr;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO

    this->clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

template<class Key, class Value>
Node<Key, Value>* get_leaf(Node<Key, Value>* root) {
    if (root == nullptr) return nullptr;

    // check children
    if (root->getLeft() == nullptr && root->getRight() == nullptr) {
        return root;
    } else if (root->getLeft() == nullptr) {
        return get_leaf(root->getRight());
    } else {
        return get_leaf(root->getLeft());
    }
}

// helper function to recursively traverse to insert a node
template<class Key, class Value>
void insert_node(Node<Key, Value>* parent, Node<Key, Value>* n) {
    if (!parent) return;

    // over write if exists
    if (parent->getKey() == n->getKey()) {
        parent->setValue(n->getValue());
        delete n;  // newly allocated node not needed anymore
    }

    // check left if inserted val is less than curr node
    else if (n->getKey() < parent->getKey()) {
        if (parent->getLeft()) {
            return insert_node(parent->getLeft(), n);
        } else {
            parent->setLeft(n);
            n->setParent(parent);
        }
    }

    // check right if inserted val is greater than curr node
    else if (n->getKey() > parent->getKey()) {
        if (parent->getRight()) {
            return insert_node(parent->getRight(), n);
        } else {
            parent->setRight(n);
            n->setParent(parent);
        }
    }

    // Update the height of the current node after insertion
    int left_height = (parent->getLeft()) ? parent->getLeft()->get_height() : 0;
    int right_height = (parent->getRight()) ? parent->getRight()->get_height() : 0;
    parent->set_height(1 + std::max(left_height, right_height));
}



/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO

    // convert pair into a node
    Node<Key, Value>* node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);

    // make a new node if root is null
    if (this->root_ == nullptr) {
        root_ = node;
        return;
    }

    // overwrite if parent equals value
    insert_node(root_, node);

}



/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO

    // first find node
    Node<Key, Value>* node = internalFind(key);
    if (!node) return;

    // remove if no children
    if (node->getRight() == nullptr && node->getLeft() == nullptr) {
        if (node == root_) {  // remove root with no children
            root_ = nullptr;
        } else {
            Node<Key, Value>* parent = node->getParent();
            if (parent->getRight() == node) parent->setRight(nullptr);
            else parent->setLeft(nullptr);

            // Update the height of the current node after removal
            int left_height = (parent->getLeft()) ? parent->getLeft()->get_height() : 0;
            int right_height = (parent->getRight()) ? parent->getRight()->get_height() : 0;
            parent->set_height(1 + std::max(left_height, right_height));

        }
        delete node;

    } else if (node->getRight() == nullptr || node->getLeft() == nullptr) {  // only one child
        Node<Key, Value>* child;
        if (node->getRight()) child = node->getRight();
        else child = node->getLeft();

        // promote from root
        if (node == root_) {
            root_ = child;
            child->setParent(nullptr);
        } else {
            Node<Key, Value>* parent = node->getParent();

            // update pointers for parent node
            if (parent->getLeft() == node) {
                parent->setLeft(child);
            } else {
                parent->setRight(child);
            }

            // update child parent pointer
            child->setParent(parent);
        }
        delete node;

    } else {  // swap with predecessor
        Node<Key, Value>* pred = predecessor(node);
        Key temp_key = pred->getKey();

        // swap key and value of node
        nodeSwap(node, pred);

        // remove node that now guaranteed to only have one child (predecessor)
        Node<Key, Value>* child = node->getLeft();
        Node<Key, Value>* parent = node->getParent();

        // promote from root
        if (node == root_) {
            root_ = child;
        } else if (parent) {
            // update pointers for parent node
            if (parent->getLeft() == node) parent->setLeft(child);
            else parent->setRight(child);
        }

        // update child pointer and delete node
        if (child) child->setParent(parent);
        delete node;

    }

}


// helper to get node farthest right in subtree
template<typename Key, typename Value>
Node<Key, Value>* recursive_find_largest(Node<Key, Value>* parent) {
    if (parent == nullptr) return nullptr;

    // base case check if left child is null (assuming lowest on left)
    if (parent->getRight() == nullptr) return parent;

    return recursive_find_largest(parent->getRight());
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO

    // base if current is null
    if (!current) return nullptr;

    // case 1: left subtree exists
    if (current->getLeft()) {
        return recursive_find_largest(current->getLeft());
    }

    // case 2: no left subtree, move up to find predecessor
    Node<Key, Value>* parent = current->getParent();
    while (parent != nullptr && current == parent->getLeft()) {
        current = parent;
        parent = parent->getParent();
    }

    // if we found a parent where the curr node is the right child, this is the predecessor
    if (parent == nullptr) {
        return parent;
    }

    return parent;
}


// helper function to recursively delete nodes
template<typename Key, typename Value>
void recursive_clear(Node<Key, Value>* parent) {
    // check if parent is null
    if (parent == nullptr) return;

    // head recursion to find leaf nodes
    recursive_clear(parent->getLeft());
    recursive_clear(parent->getRight());

    // delete after recursing
    delete parent;


}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO

    recursive_clear(root_);  // call helper function to recursively clear

    // set root to nullptr
    root_ = nullptr;

}

template<typename Key, typename Value>
Node<Key, Value>* recursive_find_smallest(Node<Key, Value>* parent) {
    if (parent == nullptr) return nullptr;

    // base case check if left child is null (assuming lowest on left)
    if (parent->getLeft() == nullptr) return parent;

    return recursive_find_smallest(parent->getLeft());
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO

    // if root is null, return
    return recursive_find_smallest(root_);

}

// helper function to recursively find node based on key
template<typename Key, typename Value>
Node<Key, Value>* recursive_find(const Key& key, Node<Key, Value>* parent) {
    // return if no parent
    if (parent == nullptr) return nullptr;

    // check if parent has correct val
    if (parent->getKey() == key) {
        return parent;
    }

    // search left subtree if value less than parent
    if (key < parent->getKey()) {
        return recursive_find(key, parent->getLeft());
    }

    // search right subtree if value greater than parent
    if (key > parent->getKey()) {
        return recursive_find(key, parent->getRight());
    }

}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO

    // base case if root i
    Node<Key, Value>* n = recursive_find(key, root_);  // use helper to recurse tree
    return n;

}

// helper function to calculate height of subtree
template<typename Key, typename Value>
int tree_height(Node<Key, Value>* node) {
    if (!node) {
        return 0;
    }

    // calc height of left and right sub trees
    int l_height = tree_height(node->getLeft());
    int r_height = tree_height(node->getRight());

    // return max height + 1
    if (l_height > r_height) {
        return l_height + 1;
    }
    return r_height + 1;

}


// helper function to recursively check if is balanced
template<typename Key, typename Value>
bool is_balanced_helper(Node<Key, Value>* node) {
    // null root is balanced
    if (!node) return true;

    // get heights of root sub trees
    int l_height = tree_height(node->getLeft());
    int r_height = tree_height(node->getRight());

    // get diff by subtracting larger from smaller
    int diff = std::abs(r_height - l_height);
    if (diff > 1) return false;

    return is_balanced_helper(node->getLeft()) && is_balanced_helper(node->getRight());
}


/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO

    // use recursive helper function to determine if tree is balanced
    return is_balanced_helper(root_);
}

template<typename Key, typename Value>
void recursive_print(Node<Key, Value>* n, int depth) {
    if (!n) return;

    for (size_t i = 0; i < depth; i++) {
        std::cout << " ";
    }
    std::cout << n->getValue() << std::endl;

    recursive_print(n->getLeft(), depth + 1);
    recursive_print(n->getRight(), depth + 1);
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print_tree() const {
    recursive_print(root_, 0);
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
