#ifndef BST_NODE_H
#define BST_NODE_H

#include <string>
#include "TimeSeries.h"
class BST_Node {
public:
    BST_Node();  
    ~BST_Node();  
    BST_Node* left;
    BST_Node* right;
    TimeSeries** array_of_time_series;
    std::string* countries;
    int num_countries;
};

#endif
