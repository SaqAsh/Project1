#include "BST.h"
#include <iostream>
#include <cmath>

BST::BST() {
    root = nullptr;
}

BST::~BST() {
    destructorHelper(root);
}

void BST::destructorHelper(BST_Node* node) {
    if (!node) return;
    destructorHelper(node->left);
    destructorHelper(node->right);
    delete node;
}

bool BST::deleteFn(std::string country_name) {
    return deleteHelper(root, country_name);
}

// Helper function for deletion
bool BST::deleteHelper(BST_Node*& node, std::string country_name) {
    if (!node) return false;

    // Check if the country is in this node
    for (int i = 0; i < node->num_countries; i++) {
        if (node->countries[i] == country_name) {
            // Remove country from node (just shift elements)
            for (int j = i; j < node->num_countries - 1; j++) {
                node->countries[j] = node->countries[j + 1];
                node->array_of_time_series[j] = node->array_of_time_series[j + 1];
            }
            node->num_countries--;

            // If the node is empty, delete it
            if (node->num_countries == 0) {
                delete node;
                node = nullptr;
            }
            return true;
        }
    }

    // Recur left or right
    if (deleteHelper(node->left, country_name) || deleteHelper(node->right, country_name))
        return true;

    return false;
}

void BST::find(double mean, std::string operation) {
    int op = (operation == "less") ? 0 : (operation == "equal") ? 1 : (operation == "greater") ? 2 : -1;
    FindHelper(root, mean, op);
    std::cout << std::endl;
}

void BST::FindHelper(BST_Node* curr, double mean, int op) {
    if (!curr) return;

    FindHelper(curr->left, mean, op);

    for (int i = 0; i < curr->num_countries; i++) {
        double tsMean = curr->array_of_time_series[i]->mean();
        if ((op == 0 && tsMean < mean) || 
            (op == 1 && fabs(tsMean - mean) < 1e-3) || 
            (op == 2 && tsMean > mean)) {
            std::cout << curr->countries[i] << " ";
        }
    }

    FindHelper(curr->right, mean, op);
}

BST_Node* BST::leftLeaf(BST_Node* node) {
    return (node->left) ? leftLeaf(node->left) : node;
}

BST_Node* BST::rightLeaf(BST_Node* node) {
    return (node->right) ? rightLeaf(node->right) : node;
}

void BST::Limits(std::string condition) {
    if (!root) return;
    BST_Node* leaf = (condition == "lowest") ? leftLeaf(root) : rightLeaf(root);
    for (int i = 0; i < leaf->num_countries; i++) {
        std::cout << leaf->countries[i] << " ";
    }
    std::cout << "\n";
}

void BST::Range(std::string series_code) {
    if (!root) return;
    double minMean = findMin(root);
    double maxMean = findMax(root);
    std::cout << minMean << " " << maxMean << std::endl;
}

double BST::findMin(BST_Node* node) {
    if (!node) return 0;
    return (node->left) ? findMin(node->left) : node->array_of_time_series[0]->mean();
}

double BST::findMax(BST_Node* node) {
    if (!node) return 0;
    return (node->right) ? findMax(node->right) : node->array_of_time_series[0]->mean();
}

void BST::Insert(Node* country, std::string country_name) {
    root = insertHelper(root, country, country_name);
}

BST_Node* BST::insertHelper(BST_Node* node, Node* country, std::string country_name) {
    double mean = country->data->mean();
    const double tol = 1e-3;
    
    if (!node) {
        BST_Node* newNode = new BST_Node();
        // We assume the node was constructed with capacity >= 2.
        newNode->num_countries = 1;
        newNode->countries[0] = country_name;
        newNode->array_of_time_series[0] = country->data;
        return newNode;
    }
    
    double nodeMean = node->array_of_time_series[0]->mean();
    
    // If the means are equal within tolerance, add the country to the current node.
    if (fabs(mean - nodeMean) < tol) {
        node->countries[node->num_countries] = country_name;
        node->array_of_time_series[node->num_countries] = country->data;
        node->num_countries++;
        return node;
    }
    else if (mean < nodeMean) {
        node->left = insertHelper(node->left, country, country_name);
    }
    else {
        node->right = insertHelper(node->right, country, country_name);
    }
    
    return node;
}


void BST::printNode() {
    printHelper(root);
    std::cout << std::endl;
}

void BST::printHelper(BST_Node* node) {
    if (!node) return;
    printHelper(node->left);
    for (int i = 0; i < node->num_countries; i++) {
        std::cout << node->countries[i] << " ";
    }
    printHelper(node->right);
}
