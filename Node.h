#ifndef NODE_H
#define NODE_H

#include "TimeSeries.h"

class Node {
public:
    TimeSeries* data;
    Node* next;
    Node(TimeSeries* data, Node* next = nullptr);
};

#endif 