#include "AVLTree.h"
using namespace std;

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

void initialize_command_list(set<string>& tree_commands) {

    tree_commands.emplace("insert");
    tree_commands.emplace("remove");
    tree_commands.emplace("search");
    tree_commands.emplace("removeInorder");
    tree_commands.emplace("printInorder");
    tree_commands.emplace("printPreorder");
    tree_commands.emplace("printPostorder");
    tree_commands.emplace("printLevelCount");
}

void get_input(unordered_map<string, string>& command_args) { // parsing the input as necessary

    vector<string> map_keys;
    map_keys.push_back("command");
    map_keys.push_back("arg1");
    map_keys.push_back("arg2");
    int index = 0;

    string input_line;
    getline(cin >> ws, input_line);
    istringstream in_stream(input_line);

    while (in_stream >> quoted(input_line)) {
        command_args.emplace(map_keys[index], input_line);
        index++;
    }
}

bool validate_id(const string& input_id) { // ensuring a valid gator id input

    if (input_id.length() == 8) {
        for (int i = 0; i < input_id.length(); i++) {
            if(isdigit(input_id[i])==0) {
                return false; // gator_id contains invalid digits
            }
        }
        return true; // gator_id given is a valid 8 digit input
    }
    else {
        return false; // case: gator_id provided not 8 digits long
    }
}

bool validate_name(const string& input_name) { // ensuring gator name is only alphabeticals and spaces

    for (int i = 0; i < input_name.length(); i++) {
        if(isalpha(input_name[i])==0 && !(isspace(input_name[i]))) {
            return false; // gator_name contains invalid chars (not alphabetical or spaces)
        }
    }

    return true;
}

bool validate_number(const string& input_number, const int& node_count) { // validating number for use in removeInorder

    try { // if input string doesn't fit into an int nicely, will trigger a conversion fault
        int result = stoi(input_number);

        if ((0 <= result) && (result < node_count) ) { // ensure that in-order node requested is a valid index
            return true;
        }
        else {
            return false; // input was a valid number, but out of range of the tree node indices
        }
    }

    catch(...) {
        return false; // input was something other than numbers
    }
}

void print_user_results(vector<string>& results) { // printing final results of all commands to user
    for (int i = 0; i < results.size(); i++) {
        cout << results[i] << endl;
    }
}

/*
 * User first enters the number of commands. Program will then accept one command at a time.
 * Each command is executed as its entered, and its results are pushed back to a vector.
 *
 * After all commands have been entered, the vector of results is then printed to the user. The vector's elements will
 * either be "successful", "unsuccessful", or in the case of searches, the results of that search.
 *
 * As per spec, search(NAME) will be returning matching node IDs with a newline char at the end of each,
 * while search(ID) will print out a comma seperated list.
 *
 * In the case of mistyped commands, result will be "unsuccessful"; in the case of a correctly typed command, but
 * invalid parameters, result will be "unsuccessful".
 *
 * In the case of searching for a name/id that doesn't exist, result will be "unsuccessful".
 *
 * In the case of printing an empty list, result will be an empty string.
 */
int main(){

    AVLTree tree;

    set<string> tree_commands;
    initialize_command_list(tree_commands);

    vector<string> user_command_results;

    int num_user_commands = 0;
    cin >> num_user_commands;

    unordered_map<string, string> command_args;

    for (int i = 0; i < num_user_commands; i++) {

        command_args.clear();
        get_input(command_args);

        if (command_args["command"] == "insert") {
            if (validate_name(command_args["arg1"]) && validate_id(command_args["arg2"])) {
                // execute insert
                string result = tree.insert(command_args["arg1"], stoi(command_args["arg2"]));
                user_command_results.push_back(result);

            }

            else {
                user_command_results.push_back("unsuccessful"); // name or id parameter was invalid
            }
        }

        else if (command_args["command"] == "remove") {
            if (validate_id(command_args["arg1"])) { // execute remove
                string result = tree.remove_id(stoi(command_args["arg1"]));
                user_command_results.push_back(result);
            }

            else {
                user_command_results.push_back("unsuccessful"); // input name or id parameter was invalid
            }
        }

        else if (command_args["command"] == "search") {
            if (validate_name(command_args["arg1"])) { // execute search by name
                string result = tree.search_name(command_args["arg1"]);
                user_command_results.push_back(result);
            }

            else if (validate_id(command_args["arg1"])) { // execute search by gator id
                string result = tree.search_ID(stoi(command_args["arg1"]));
                user_command_results.push_back(result);
            }

            else {
                user_command_results.push_back("unsuccessful"); // input name or id parameter was invalid
            }
        }

        else if (command_args["command"] == "removeInorder") {

            int current_node_count = tree.get_node_count();

            if (validate_number(command_args["arg1"], current_node_count)) {
                string removal_num = tree.remove_inorder(stoi(command_args["arg1"]));
                user_command_results.push_back(removal_num);
            }

            else {
                user_command_results.push_back("unsuccessful");
            }
        }

        else if (command_args["command"] == "printInorder") {
            string list_inorder = tree.print_inorder();
            user_command_results.push_back(list_inorder);
        }

        else if (command_args["command"] == "printPreorder") {
            string list_preorder = tree.print_preorder();
            user_command_results.push_back(list_preorder);
        }

        else if (command_args["command"] == "printPostorder") {
            string list_postorder = tree.print_postorder();
            user_command_results.push_back(list_postorder);
        }

        else if (command_args["command"] == "printLevelCount") {
            string tree_level_count = tree.print_level_count();
            user_command_results.push_back(tree_level_count);
        }

        else {
            user_command_results.push_back("unsuccessful"); // command was incorrect (typo or invalid command given)
        }
    }

    print_user_results(user_command_results);

	return 0;
}