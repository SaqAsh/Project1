#include "LinkedList.h"


LinkedList::LinkedList() : head(NULL) {}

LinkedList::~LinkedList() {
    Destroy(head);
}

void LinkedList::Destroy(Node *n) {
    if (n != nullptr) {
        Destroy(n->next);
        delete n;
    }
}

void LinkedList::HandleInsertIntoLinkedList(TimeSeries& time_series) {
    Node* newNode = new Node(time_series);
    newNode->next = nullptr;  // Ensure new node points to null
    
    if (!head) {
        head = newNode;
        return;
    }
    
    Node* temp = head;
    while (temp->next != nullptr) {  // Stop at last node, not after it
        temp = temp->next;
    }
    temp->next = newNode;
}
