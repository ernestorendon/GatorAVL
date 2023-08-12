//
// Created by Ernesto Rendon on 6/1/23.
//

#include "AVLTree.h"

/*
 * AVLTree has public functions which almost always call helper functions with access to internal member variables
 * of nodes within the tree
 *
 * Public functions mostly return strings of either "successful" or "unsuccessful" so that the result can be appended
 * to a vector of strings in main, and after all commmands have been input, the results of each input previously
 * stored are then printed to the user
 *
 * Helper functions are denoted by the underscore prefix (e.g. insert vs. _insert) and return back to the public
 * functions, which ultimately return strings to main
 *
 * Input validation is handled in main; if the parameters make it here, it means that their inputs
 * (name, id, number) have already made it through validation
 */


/* =============================================== INSERTION =============================================== */

/*
 * Function accepts pre-verified name and id parameters, and calls helper function, passing along a result
 * that is modified by reference (either successful or unsuccessful) to return it to main
*/
std::string AVLTree::insert(std::string& _name, const unsigned int _id) {

    std::string result;
    _root = _insert(_root, _name, _id, result);
    return (result);
}

// recursively adds a node in the appropriate place, updating the result string to successful or unsuccessful
AVLTree::TreeNode* AVLTree::_insert(AVLTree::TreeNode* node, std::string& _name_input,
                                    unsigned int _id_input, std::string& result)            {

    if (node == nullptr) {
        nodeCount++;
        result = ("successful");
        return new TreeNode(_name_input, _id_input);
    }

    if (_id_input < node->_gator_ID) {
        node->left = _insert(node->left, _name_input, _id_input, result);
    }

    else if (_id_input > node->_gator_ID){
        node->right = _insert(node->right, _name_input, _id_input, result);
    }

    else if (_id_input == node->_gator_ID) {
        result = ("unsuccessful");
    }

    return (_balance_tree(node));
}


/* ============================================= BALANCE & ROTATIONS ============================================= */

/*
 * recursively rotates tree nodes to maintain a balance factor between -1 and 1, then updates affected nodes' heights
 * accepts an arbitrary node as a parameter and returns the ultimate root node
 */
AVLTree::TreeNode* AVLTree::_balance_tree(AVLTree::TreeNode *node) {

    int left_subtree_height = getHeight(node->left);
    int right_subtree_height = getHeight(node->right);

    int node_balance_factor = left_subtree_height - right_subtree_height;

    if (node_balance_factor < -1) { // tree is right heavy

        // if tree's right subtree is right heavy
        if (getHeight(node->right->right) >= getHeight(node->right->left)) {
            node = _rotateLeft(node);
        }
        else {
            node = _rotateRightLeft(node);
        }
    }

    else if (node_balance_factor > 1) { // tree is left heavy

        // if tree's left subtree is left heavy
        if (getHeight(node->left->left) >= getHeight(node->left->right)) {
            node = _rotateRight(node);
        }
        else {
            node = _rotateLeftRight(node);
        }
    }

    _update_node_height(node);
    return node;
}

AVLTree::TreeNode* AVLTree::_rotateRight(AVLTree::TreeNode* node) {

    AVLTree::TreeNode* grandchild = node->left->right;
    AVLTree::TreeNode* newParent = node->left;
    newParent->right = node;
    node->left = grandchild;
    _update_node_height(node);
    _update_node_height(newParent);
    return newParent;
}

AVLTree::TreeNode* AVLTree::_rotateLeft(AVLTree::TreeNode* node) {

    AVLTree::TreeNode* grandchild = node->right->left;
    AVLTree::TreeNode* newParent = node->right;
    newParent->left = node;
    node->right = grandchild;
    _update_node_height(node);
    _update_node_height(newParent);
    return newParent;
}

AVLTree::TreeNode* AVLTree::_rotateRightLeft(AVLTree::TreeNode* node) {

    node->right = _rotateRight(node->right);
    node = _rotateLeft(node);
    return node;
}

AVLTree::TreeNode* AVLTree::_rotateLeftRight(AVLTree::TreeNode* node) {

    node->left = _rotateLeft(node->left);
    node = _rotateRight(node);
    return node;
}

void AVLTree::_update_node_height(AVLTree::TreeNode* node) {

    node->node_height = 1 + std::max((node->left ? node->left->node_height:0), (node->right ? node->right->node_height:0));
}


/* =============================================== PRINTING =============================================== */

/*
 * the 3 types of traversal printing each call their respective traversal functions, and a string by reference.
 * The reference string is appended with the nodes in their respective orders, with proper commas separating
 * each node's information.
 */
std::string AVLTree::print_inorder() {

    std::string name_list;

    _print_inorder(_root, name_list);

    return name_list;
}

std::string AVLTree::print_preorder() {

    std::string name_list;

    _print_preorder(_root, name_list);

    return name_list;
}

std::string AVLTree::print_postorder() {

    std::string name_list;

    _print_postorder(_root, name_list);

    return (name_list);
}

void AVLTree::_print_inorder(TreeNode *root, std::string& name_list) {

    if (root == nullptr) {
        return;
    }

    _print_inorder(root->left, name_list);

    if (!name_list.empty()) {
        name_list += ", " + root->_gator_name;
    }
    else {
        name_list += root->_gator_name;
    }

    _print_inorder(root->right, name_list);
}

void AVLTree::_print_preorder(TreeNode *root, std::string& name_list) {

    if (root == nullptr) {
        return;
    }

    if (!name_list.empty()) {
        name_list += ", " + root->_gator_name;
    }
    else {
        name_list += root->_gator_name;
    }

    _print_preorder(root->left, name_list);

    _print_preorder(root->right, name_list);
}

void AVLTree::_print_postorder(TreeNode *root, std::string& name_list) {

    if (root == nullptr) {
        return;
    }

    _print_postorder(root->left, name_list);

    _print_postorder(root->right, name_list);

    if (!name_list.empty()) {
        name_list += ", " + root->_gator_name;
    }
    else {
        name_list += root->_gator_name;
    }
}

// Level count is simply the node height of the root node of the entire tree; returns it as a string to main
std::string AVLTree::print_level_count() {

    if (_root != nullptr) {
        return (std::to_string(_root->node_height));
    }

    else {
        return (std::to_string(0));
    }
}


/* =============================================== SEARCHING =============================================== */

/*
 * calls helper function _search_ID, passing in the root of the tree and the search query; if helper function
 * returns a valid node, this function returns the name as a string to main; if it returns a nullptr,
 * it returns "unsuccessful"
 */
std::string AVLTree::search_ID(const unsigned int _id) {

    TreeNode* result = _search_id(_root, _id);
    if (result != nullptr) {
        return (result->_gator_name);
    }
    else {
        return ("unsuccessful");
    }
}

/*
 * accepts a root of a tree and an id query, recursively searching in post-order until the matching
 * node is found and returned to search_ID for further processing; if no match found, it returns nullptr
 */
AVLTree::TreeNode* AVLTree::_search_id(AVLTree::TreeNode* root, unsigned int _id) {

    if (root == nullptr) {
        return nullptr;
        // match not found
    }

    if (_id < root->_gator_ID) {
        return _search_id(root->left, _id);
    }
    else if (_id > root->_gator_ID){
        return _search_id(root->right, _id);
    }
    else if (_id == root->_gator_ID) {
        return root;
    }

    return root;
}

/*
 * calls helper function _search_name, passing in the root of the tree and the search query; if helper function
 * returns at least one match, this function returns the IDs of matching nodes as a string to main;
 * if helper function returns an empty list, no match was found, and this function returns string "unsuccessful"
 */
std::string AVLTree::search_name(const std::string& _name) {

    std::string final_string;

    _search_name(_root, _name, final_string);

    if (!final_string.empty()) {
        return final_string;
    }
    else {
        return ("unsuccessful");
    }
}

/*
 * accepts a root to a tree, a name query, and a vector of strings containing any nodes that have information
 * matching the name query; the recursive traversal of the tree pushes back each match in preorder, appending
 * newline chars as necessary for proper output
 */
AVLTree::TreeNode* AVLTree::_search_name(AVLTree::TreeNode* root, const std::string& name_query, std::string& final_string) {

    if (root == nullptr) {
        return nullptr;
    }

    if (root->_gator_name == name_query) {
        std::stringstream stream;
        stream << std::setw(8) << std::setfill('0') << root->_gator_ID;
        std::string node_match = stream.str();
        if (!final_string.empty()) {
            final_string += "\n" + node_match;
        }
        else {
            final_string += node_match;
        }
    }

    _search_name(root->left, name_query, final_string);

    _search_name(root->right, name_query, final_string);

    return root;
}


/* =============================================== REMOVAL =============================================== */

/*
 * accepts an id query for removal of the node from the tree; first checks if the node exists by calling
 * _search_id helper function; if it doesn't exist, returns string "unsuccessful" to main;
 *
 * if node does exist, this function calls helper function _remove_id for recursive removal and
 * rebalancing of tree, then returns "successful" to main
 */
std::string AVLTree::remove_id(const unsigned int _id) {

    std::string result = "unsuccessful";

    _root = _remove_id(_root, _id, result);

    return result;
}


/*
 * this helper function accepts a tree root and an id query, removes the matching node based on a set of 4
 * possibilities, updates the node heights and rebalances the tree's affected nodes recursively;
 *
 * eventually returns the main root of the tree to remove_id if successful, and returns a nullptr if removal fails to
 * find a match
 */
AVLTree::TreeNode* AVLTree::_remove_id(TreeNode* root, unsigned int _id, std::string& result) {

    if (root == nullptr) {
        return nullptr;
    }

    if (_id < root->_gator_ID) {
        root->left = _remove_id(root->left, _id, result);
    }

    else if (_id > root->_gator_ID) {
        root->right = _remove_id(root->right, _id, result);
    }

    else {
        if (root->left == nullptr && root->right == nullptr) { // if removing a leaf node
            delete root;
            result = "successful";
            nodeCount--;
            return nullptr;
        }

        else if (root->left == nullptr) { // removing a node with only a right child
            TreeNode* temp = root->right;
            delete root;
            result = "successful";
            nodeCount--;
            return temp;
        }

        else if (root->right == nullptr) { //removing a node with only a left child
            TreeNode* temp = root->left;
            delete root;
            result = "successful";
            nodeCount--;
            return temp;
        }

        else { // removing a node with 2 children
            TreeNode* successor = _inorder_successor(root->right);
            root->_gator_name = successor->_gator_name;
            root->_gator_ID = successor->_gator_ID;
            root->right = _remove_id(root->right, successor->_gator_ID,result);
        }
    }

    return _balance_tree(root);
}

/*
 * this function is called by the case of removal of a node with 2 children
 *
 * it accepts a node and returns the node designated as its inorder successor, a/k/a the left-most node of the
 * root's right subtree
 */
AVLTree::TreeNode* AVLTree::_inorder_successor(AVLTree::TreeNode* root) {

    if (root == nullptr || root->left == nullptr) {
        return root;
    }
    return _inorder_successor(root->left);
}

/*
 * function accepts a target number, of which the matching node in a tree traversed inorder is then removed from the
 * tree; if the target num is
 *
 * it calls helper function _remove_inorder, passing in the same target number as well as an int by reference to track
 * recursion depth, and string that captures result
 */
std::string AVLTree::remove_inorder(const int target_num) {

    std::string result = "";
    int loop_count = 0;

    _remove_inorder(_root, target_num, loop_count, result);

    if (result == "successful") {
        return result;
    }
    else {
        return ("unsuccessful");
    }
}

/*
 * function accepts the tree's root, a target number, and an int by reference that tracks recursion depth, or
 * in other words which node (starting from 0) we're on, while traversing in order
 *
 * once the target node is reached, this function calls _remove_id to handle removal of the node, while
 * dealing with the case of recursively removing the root node;
 */
AVLTree::TreeNode* AVLTree::_remove_inorder(TreeNode* root, const int target_num, int& loop_count, std::string& result) {

    if (root == nullptr) {
        return nullptr;
    }

    root->left = _remove_inorder(root->left, target_num, loop_count, result);

    if (target_num == loop_count) {

        // if removing the TreeRoot via this function, make the internal TreeRoot the successor returned
        if (root == _root) {
            _root = _remove_id(root, root->_gator_ID, result);
        }
        else { // else, remove, rebalance, and return the non-TreeRoot node
            root = _remove_id(root, root->_gator_ID, result);
            loop_count++;
            return root;
        }
    }

    loop_count++;
    root ->right = _remove_inorder(root->right, target_num, loop_count, result);

    return root;
}