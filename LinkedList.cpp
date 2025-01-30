#include "LinkedList.h"


LinkedList::LinkedList() : head(NULL) {}

LinkedList::~LinkedList() {
    Destroy(head);
}

void LinkedList::Destroy(Node *n) {
    if (n != nullptr) {
        Destroy(n->next);
        delete n->data;
        delete n;
    }
}

void LinkedList::HandleInsertIntoLinkedList(TimeSeries* time_series) {
    Node* newNode = new Node(time_series);
    newNode->next = nullptr;  
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
