#include "BST_Node.h"
#include <iostream>

BST_Node::BST_Node()
    : left(nullptr), right(nullptr)
{
    array_of_time_series = new TimeSeries*[512]{nullptr};
}

BST_Node::~BST_Node() {
    // for(int i = 0; i < 512; i++) {
    //     delete array_of_time_series[i];
    // }
    delete [] array_of_time_series;
    array_of_time_series = nullptr;
}