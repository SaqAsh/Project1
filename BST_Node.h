#ifndef BST_NODE_H
#define BST_NODE_H

#include <string>

class BST_Node {
public:
    BST_Node(double minMean, double maxMean);  
    ~BST_Node();  // Destructor

    bool isLeaf() const;  
    void increaseSize(std::string*& arr, int size, int& capacity);  
    void increaseSize(double*& arr, int size, int& capacity);  
    void Push(std::string value, std::string*& arr, int& size, int& capacity);
    void Push(double value, double*& arr, int& size, int& capacity);

    double minMean, maxMean;  
    std::string* countries;  
    double* means;  
    int countryCount, countryCapacity;
    int meanCount, meanCapacity;
    BST_Node* left;
    BST_Node* right;
};

#endif
