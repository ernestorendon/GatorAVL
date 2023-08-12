//
// Created by Ernesto Rendon on 6/1/23.
//
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <unordered_map>
#include <set>

#ifndef PROJECT_1_AVLTREE_H
#define PROJECT_1_AVLTREE_H

class AVLTree {
private:

    struct TreeNode {

        unsigned int _gator_ID; // unique 8 digit number
        std::string _gator_name; // alphanumeric variable (including spaces)

        int node_height;

        TreeNode* left;
        TreeNode* right;

        // node constructor
        TreeNode(std::string& _name_input, unsigned int _id_input) {
            node_height = 1;
            _gator_ID = _id_input;
            _gator_name = _name_input;
            left = nullptr;
            right = nullptr;
        };

    };

    static int getHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        else {
            return node->node_height;
        }
    }

    unsigned int nodeCount;

    TreeNode* _root;

    /* ======= insertion ======= */
    TreeNode* _insert(TreeNode* node, std::string& _name_input, unsigned int _id_input, std::string& result);

    /* ======= removal ======= */
    TreeNode* _remove_id(TreeNode* root, unsigned int _id, std::string& result);
    TreeNode* _remove_inorder(TreeNode* root, int target_num, int& loop_count, std::string& result);
    TreeNode* _inorder_successor(TreeNode* root);

    /* ======= balancing & rotations ======= */
    void _update_node_height(TreeNode* node);
    TreeNode* _balance_tree(AVLTree::TreeNode *node);
    TreeNode* _rotateLeft(TreeNode* node);
    TreeNode* _rotateRight(TreeNode* node);
    TreeNode* _rotateLeftRight(TreeNode* node);
    TreeNode* _rotateRightLeft(TreeNode* node);

    /* ======= searching ======= */
    TreeNode* _search_id(TreeNode* root, unsigned int _id);
    TreeNode* _search_name(AVLTree::TreeNode *root, const std::string& name_query, std::string& final_string);

    /* ======= printing ======= */
    void _print_inorder(TreeNode* root, std::string& name_list);
    void _print_preorder(TreeNode* root, std::string& name_list);
    void _print_postorder(TreeNode* root, std::string& name_list);

public:

    // constructor
    AVLTree() {
        _root = nullptr;
        nodeCount = 0;
    }

    int get_node_count() { return nodeCount;};

    // AVLTree required functionality
    std::string insert(std::string& _name, unsigned int _id);
    std::string remove_id(unsigned int _id);
    std::string remove_inorder(int target_num);
    std::string search_ID(unsigned int _id);
    std::string search_name(const std::string& _name);
    std::string print_inorder();
    std::string print_preorder();
    std::string print_postorder();
    std::string print_level_count();

};

#endif //PROJECT_1_AVLTREE_H