#include "Node.h"

Node::Node(TimeSeries &data, Node* next) : data(data), next(next) {
    // No need for deep copy since we're using reference
} 