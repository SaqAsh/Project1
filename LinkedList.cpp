#include "LinkedList.h"

//Constructor for the linked list
LinkedList::LinkedList() : head(NULL) {}
//Destructor for the linked list`
LinkedList::~LinkedList() {
    Destroy(head);
}
//Destructor helper for the linked list
void LinkedList::Destroy(Node *n) {
    if (n != nullptr) {
        Destroy(n->next);
        delete n->data;
        delete n;
    }
}
// This function is used to insert a new TimeSeries object into the linked list
void LinkedList::handle_insert(TimeSeries* time_series) {
    Node* newNode = new Node(time_series);
    if (!head) {
        head = newNode;
        return;
    }
    
    Node* temp = head;
    while (temp->next != nullptr) {  
        temp = temp->next;
    }
    temp->next = newNode;
}
