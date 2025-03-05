#include "BST_Node.h"
#include <iostream>

BST_Node::BST_Node()
    : left(nullptr), right(nullptr)
{
    array_of_time_series = new TimeSeries*[512]{nullptr};
    countries = new std::string[512]{""};
    num_countries = 0;
}

BST_Node::~BST_Node() {
    // for(int i = 0; i < 512; i++) {
    //     delete array_of_time_series[i];
    // }
    delete [] array_of_time_series;
    array_of_time_series = nullptr;
    delete [] countries;
    countries = nullptr;
}