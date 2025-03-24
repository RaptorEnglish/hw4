#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool check_leaf_depth(Node* root, int depth, int& global_depth) {
    // accomplish by logging first leaf node's depth, then compare all other leaf nodes to see if they match
    if (root == nullptr) return true;

    // check if leaf node
    if (root->left == nullptr && root->right == nullptr) {
        // update global depth if not already updated
        if (global_depth == -1) global_depth = depth;

        // return comparison of curr depth to global depth (assume either triggered by other leaf or by curr)
        return depth == global_depth;
    }

    // check all leaf nodes in both branches
    bool check_left = check_leaf_depth(root->left, depth + 1, global_depth);
    bool check_right = check_leaf_depth(root->right, depth + 1, global_depth);
    return check_left && check_right;
}


bool equalPaths(Node * root)
{
    int global_depth = -1;  // initialize flag value that will be updated by first leaf node
    return check_leaf_depth(root, 0, global_depth);
}

