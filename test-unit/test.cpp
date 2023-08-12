#include "../src/main.cpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <unordered_map>
#include "../src/AVLTree.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

// testing accuracy of remove_inorder functionality
TEST_CASE("#1: 1000 nodes, 549 removals", "[flag]"){

    AVLTree tree;   // Create a Tree object
    string name = "ernesto";

    for (int i = 0; i < 1000; i++) {
        tree.insert(name, i);
    }

    for (int i = 0; i < 549; i++) {
        tree.remove_inorder(0);
    }

    int nodes_left = tree.get_node_count();

	REQUIRE(nodes_left == 451);
}

// testing robustness of remove_inorder functionality by clearing the tree only using it
TEST_CASE("#2: 1000 nodes, 1000 removals", "[flag]"){

    AVLTree tree;   // Create a Tree object
    string name = "ernesto";

    for (int i = 0; i < 1000; i++) {
        tree.insert(name, i);
    }

    for (int i = 0; i < 1000; i++) {
        tree.remove_inorder(0);
    }

    int nodes_left = tree.get_node_count();

    REQUIRE(nodes_left == 0);
}

/*
 * testing stability of root node and rotation algorithm with placing and removing a node in the same place,
 * leaving the left subtree untouched
*/
TEST_CASE("#3: 2 nodes, then 1000 insertions and 1000 removals", "[flag]"){

    AVLTree tree;   // Create a Tree object
    string first_name = "first";
    string second_name = "second";
    string name = "ernesto";

    tree.insert(second_name,20);
    tree.insert(first_name, 5);
    tree.insert(name, 30);

    tree.remove_inorder(2);

    for (int i = 0; i < 1000; i++) {
        tree.insert(name, 21+i); // insert a node to right of tree root
        tree.remove_inorder(2); // remove that same node

        /*  visualization:
         *      second
         *      /     \
         *   first    (added and removedInorder 1000 times)
         *
         */
    }

    string inorder_result = tree.print_inorder();

    string inorder_expected = "first, second";

    REQUIRE(inorder_result == inorder_expected);
}

TEST_CASE("#4: Testing postorder traversal", "[flag]"){

    AVLTree tree;   // Create a Tree object
    vector<string> names;
    vector<int> ids;


    names.push_back("do to me"); // ids.push_back(50);
    names.push_back("deep inside"); // ids.push_back(20);
    names.push_back("what you"); // ids.push_back(70);
    names.push_back("i cant stop this feeling"); // ids.push_back(10);
    names.push_back("of me"); // ids.push_back(60);
    names.push_back("realize"); // ids.push_back(90);
    names.push_back("girl you"); // ids.push_back(80);
    names.push_back("just dont"); // ids.push_back(100);

    ids.push_back(50);
    ids.push_back(20);
    ids.push_back(70);
    ids.push_back(10);
    ids.push_back(60);
    ids.push_back(90);
    ids.push_back(80);
    ids.push_back(100);

    for (int i = 0; i < 8; i++) {
        tree.insert(names[i], ids[i]);
    }

    // the lyrics to this hit song won't print out correctly in any other traversal method

    string postorder_result = tree.print_postorder();
    string postorder_expected = "i cant stop this feeling, deep inside, of me, girl you, just dont, realize, what you, do to me";

    REQUIRE(postorder_result == postorder_expected);
}


TEST_CASE("#5: Testing preorder traversal") {

    AVLTree tree;

    vector<string> names;
    vector<int> ids;

    names.push_back("When you"); // ids.push_back(50);
    names.push_back("hold me"); // ids.push_back(20);
    names.push_back("You let me know"); // ids.push_back(70);
    names.push_back("In your arms so tight"); // ids.push_back(10);
    names.push_back("Everythings alright"); // ids.push_back(60);
    names.push_back("Im hooked on a feeling"); // ids.push_back(90);
    names.push_back("Im high on believing"); // ids.push_back(80);
    names.push_back("That youre in love with me"); // ids.push_back(100);

    ids.push_back(50);
    ids.push_back(20);
    ids.push_back(70);
    ids.push_back(10);
    ids.push_back(60);
    ids.push_back(90);
    ids.push_back(80);
    ids.push_back(100);

    for (int i = 0; i < 8; i++) {
        tree.insert(names[i], ids[i]);
    }

    // the lyrics to this hit song won't print out correctly in any other traversal method

    string preorder_result = tree.print_preorder();
    string preorder_expected = "When you, hold me, In your arms so tight, You let me know, Everythings alright, Im hooked on a feeling, Im high on believing, That youre in love with me";

    REQUIRE(preorder_result == preorder_expected);

}


