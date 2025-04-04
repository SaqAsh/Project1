#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "TimeSeries.h"
#include "Node.h"

class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    void handle_insert(TimeSeries* time_series);
    Node* head;

private:
    void Destroy(Node* n);
};

#endif 
