#include "BST_Node.h"
#include <iostream>

// This is the constructor for the BST_Node class
BST_Node::BST_Node(std::string country_name, TimeSeries* time_series, double min, double max) : left(nullptr), right(nullptr)
{
    this->max = max;
    this->min = min;
    array_of_time_series = new TimeSeries*[512]{nullptr};
    countries = new std::string[512]{""};
    countries[0] = country_name;
    array_of_time_series[0] = time_series;
    num_countries = 1;
}
// This is the destructor for the BST_Node class
BST_Node::~BST_Node() {
    // for(int i = 0; i < 512; i++) {
    //     delete array_of_time_series[i];
    // }
    delete [] array_of_time_series;
    array_of_time_series = nullptr;
    delete [] countries;
    countries = nullptr;
}