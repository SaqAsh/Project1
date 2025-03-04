#include "BST_Node.h"
#include <iostream>

BST_Node::BST_Node(double minMean, double maxMean)
    : minMean(minMean), maxMean(maxMean), countryCount(0), meanCount(0), left(nullptr), right(nullptr)
{
    countryCapacity = 2;
    countries = new std::string[countryCapacity];
    
    meanCapacity = 2;
    means = new double[meanCapacity];
}

BST_Node::~BST_Node() {
    delete[] countries;
    delete[] means;
}

bool BST_Node::isLeaf() const {
    return (left == nullptr && right == nullptr);
}

void BST_Node::Push(std::string value, std::string*& arr, int& size, int& capacity) {
    increaseSize(arr, size, capacity);  // Resize if needed
    arr[size++] = value;  // Add to the array and increment size
}

void BST_Node::Push(double value, double*& arr, int& size, int& capacity) {
    increaseSize(arr, size, capacity);  // Resize if needed
    arr[size++] = value;  // Add to the array and increment size
}

void BST_Node::increaseSize(std::string*& arr, int size, int& capacity) {
    if (size != capacity) return;
    int newCapacity = capacity * 2;
    std::string* newArr = new std::string[newCapacity];
    for (int i = 0; i < capacity; i++) {
        newArr[i] = arr[i];
    }
    capacity = newCapacity;
    delete[] arr;
    arr = newArr;
}

void BST_Node::increaseSize(double*& arr, int size, int& capacity) {
    if (size != capacity) return;
    int newCapacity = capacity * 2;
    double* newArr = new double[newCapacity];
    for (int i = 0; i < capacity; i++) {
        newArr[i] = arr[i];
    }
    capacity = newCapacity;
    delete[] arr;
    arr = newArr;
}
