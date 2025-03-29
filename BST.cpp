#include "BST.h"
#include <iostream>
#include <cmath>
#include <vector>
//this is the constructor for the binary search tree
BST::BST() {
    root = nullptr;
}

// this is the destructor for the binary search tree
BST::~BST() {
    if(root) {
        destructorHelper(root);
        root = nullptr;
    } 
}
//this is the helper function for the destructor of the binary search tree
//utilizes the post order traversal to delete the nodes
void BST::destructorHelper(BST_Node* node) {
    if (!node) return;
    destructorHelper(node->left);
    destructorHelper(node->right);
    delete node;
}
// this is the delete function, it is the one that calls the delete helper function to delete the certain country, which recursively deletes the country
bool BST::deleteFn(std::string country_name) {
    return deleteHelper(root, country_name);
}

// Helper function for deletion pre-order traversal 
/*
    CITATION: 

    [1] A small part of this function was generated with the help of chat.openai.com with the prompt 
    I think there might be an indexing issue with the countries in the node of the BST, when removing, can you point to me where the issue might be?
    where chatgpt responses with the suggestion to make the bound from j to node->num_countries -1 instead of node->num_countries, which was the issue
*/
bool BST::deleteHelper(BST_Node*& node, std::string country_name) {
    if (!node) return false;

    // Check if the country is in this node
    for (int i = 0; i < node->num_countries; i++) {
        if (node->countries[i] == country_name) {
            // Remove country from node and shift the rest of the countries 
            for (int j = i; j < node->num_countries - 1; j++) {
                node->countries[j] = node->countries[j + 1];
                node->array_of_time_series[j] = node->array_of_time_series[j + 1];
            }
            node->num_countries--;

            // This is the empty case, when we have emptied out the node 
            if (node->num_countries == 0) {
                delete node;
                node = nullptr;
            }
            return true;
        }
    }

    // recursively delete the country from the subtree, essentially cleaning up the rest of the tree if either one of these 
    // return true we know that we have cleaned up the rest of the tree for that country
    if (deleteHelper(node->left, country_name) || deleteHelper(node->right, country_name))
        return true;
    //side note, the returning true and false is super important for this function since it allows for the output to be printed according to the specs 
    return false;
}

// this is the find function that calls the find helper function, it decodes the operation into an integer value
/*
    CITATION: 

    [2] A small part of this function was generated with the help of chat.openai.com with the prompt 
    Give me the outline for a 3 case ternary in c++ since I wanted to use ternary operator but I had forgotten how to use it for 
    three operations where chatgpt responded with the outline of the ternary operator which is what I am using in this function
*/
void BST::find(double mean, std::string operation, std::vector<std::string>& countries) {   
    // encode the string operation into numbers for ease of debugging since I do not know how to spell
    int operation_decoded= (operation == "less") ? 0 : (operation == "equal") ? 1 : (operation == "greater") ? 2 : -1; 
    FindHelper(root, mean, operation_decoded, countries);
}
/*
    CITATION: 

    [3] A small part of this function was generated with the help of chat.openai.com with the prompt 
    what is the floating point counterpart for the absolute value function in c++ where chatgpt responded with 
    fabs() which is what I am usin for the tolerance and it told me that it is using the cmath library which is what I am using
*/
//this is the helper function for the find function is using in order traversal to find the countries that match the mean
void BST::FindHelper(BST_Node* curr, double mean, int operation_decoded, std::vector<std::string>& countries) {
    if (!curr) return;
    FindHelper(curr->left, mean, operation_decoded, countries);

    // goes through all the countries in the array and checks if the mean is less, equal or greater than the mean

    for (int i = 0; i < curr->num_countries; i++) {
        double time_series_mean = curr->array_of_time_series[i]->mean();
        if ((operation_decoded == 0 && time_series_mean < mean) || (operation_decoded == 1 && fabs(time_series_mean - mean) < 1e-3) || (operation_decoded == 2 && time_series_mean > mean)) 
            countries.push_back(curr->countries[i]);
            // std::cout << curr->countries[i] << " ";
    }

    FindHelper(curr->right, mean, operation_decoded, countries);
}

//Helper function to find the left most node in the tree for the limits
BST_Node* BST::leftLeaf(BST_Node* node) {
    return (node->left) ? leftLeaf(node->left) : node;
}

//Helper function to find the right most node in the tree for the limits
BST_Node* BST::rightLeaf(BST_Node* node) {
    return (node->right) ? rightLeaf(node->right) : node;
}

//This function is used to print the countries with the lowest or highest mean
//uses ternary operator to determine which leaf to use and then prints the countries in the leaf using the helper
void BST::Limits(std::string condition) {
    if (!root) return;
    BST_Node* leaf = (condition == "lowest") ? leftLeaf(root) : rightLeaf(root);
    for (int i = 0; i < leaf->num_countries; i++) {
        std::cout << leaf->countries[i] << " ";
    }
    std::cout << "\n";
}

//This function is used to calculate the range of the means of the time series, uses the findMin and findMax helper functions
void BST::Range(std::string series_code) {
    if (!root) return;
    double minMean = findMin(root);
    double maxMean = findMax(root);
    std::cout << minMean << " " << maxMean << "\n";
}

//Helper function to recurse through tree and find the minimum mean
double BST::findMin(BST_Node* node) {
    if (!node) return 0;
    return (node->left) ? findMin(node->left) : node->array_of_time_series[0]->mean();
}

//helper function to recurse through tree and find the maximum mean
double BST::findMax(BST_Node* node) {
    if (!node) return 0;
    return (node->right) ? findMax(node->right) : node->array_of_time_series[0]->mean();
}

//This is the insert function that is called by the other functions to insert nodes 
void BST::Insert(Node* country, std::string country_name) {
    root = insert_helper(root, country, country_name);
}

/*
    CITATION: 

    [5] A small part of this function was generated with the help of chat.openai.com with the prompt 
    what is the floating point counterpart for the absolute value function in c++ where chatgpt responded with 
    fabs() which is what I am usin for the tolerance and it told me that it is using the cmath library which is what I am using
    Another part of this function was generated with the help of chat.openai.com with the prompt
    ChatGPT helped frame the logic for initially grouping multiple countries in a single BST node and then splitting them up based on their values. 
    My nodes aren't splitting correctly, can you give me a frame on how you can do this certain thing, I need to group them initially then split them based off of values, I can take 
    care of accessing the values just give me pseudocode/some c++ code as a frame, since you don't know anything about the data acessing 
*/
BST_Node* BST::insert_helper(BST_Node* node, Node* country, std::string country_name) {
    double mean = country->data->mean();
    
    // if we don't got a node, in the sense no root then we create a new bst node and insert the country into it
    if (!node) {
        BST_Node* newNode = new BST_Node(country_name, country->data, mean, mean);
        newNode->num_countries = 1;
        return newNode;
    }
    
    // If the node has not yet split (i.e. no children), insert into its  list.
    if (!node->left && !node->right) {
        node->countries[node->num_countries] = country_name;
        node->array_of_time_series[node->num_countries++] = country->data;
        
        if (mean < node->min) node->min = mean;
        if (mean > node->max) node->max = mean;
        // if we don't have equal values and we have more than one country we gotta do some splitting
        if (node->num_countries > 1 && fabs(node->max - node->min) > 1e-3) {
            double threshold = node->min + (node->max - node->min) / 2.0;
            BST_Node* leftChild = nullptr;
            BST_Node* rightChild = nullptr;
            
            // Redistribute each country into the left or right child based on the threshold.
            for (int i = 0; i < node->num_countries; i++) {
                double currMean = node->array_of_time_series[i]->mean();
                Node* temp = new Node( node->array_of_time_series[i]);
                if (currMean < threshold)
                    leftChild = insert_helper(leftChild, temp, node->countries[i]);
                else
                    rightChild = insert_helper(rightChild, temp, node->countries[i]);
                delete temp;
            }
            // Clear the parent's list so countries are stored only in the children.
            node->num_countries = 0;
            node->left = leftChild;
            node->right = rightChild;
        }
        return node;
    }
    else {
        //insert the new country directly into the proper child.
        double threshold = node->min + (node->max - node->min) / 2.0;
        (mean < threshold)? node->left = insert_helper(node->left, country, country_name) : node->right = insert_helper(node->right, country, country_name);
        if (mean < node->min) node->min = mean;
        if (mean > node->max) node->max = mean;
        return node;
    }
}
