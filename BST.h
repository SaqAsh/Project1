#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include "BST_Node.h"
#include "Node.h"
#include <vector>
class BST {
public:
    BST_Node* root;
    
    BST();
    ~BST();
    
    bool deleteFn(std::string country_name);
    void find(double mean, std::string operation, std::vector<std::string>& countries);
    void Limits(std::string condition);
    void Insert(Node* country, std::string country_name);
    void Range(std::string series_code);
    void printNode();

private:
    void FindHelper(BST_Node* curr, double mean, int operation, std::vector<std::string>& countries);
    void destructorHelper(BST_Node* node);
    BST_Node* leftLeaf(BST_Node* node);
    BST_Node* rightLeaf(BST_Node* node);
    BST_Node* insert_helper(BST_Node* node, Node* country, std::string country_name);
    bool deleteHelper(BST_Node*& node, std::string country_name);
    double findMin(BST_Node* node);
    double findMax(BST_Node* node);
};

#endif
