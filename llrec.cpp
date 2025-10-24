#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
    // Base case: empty list
    if (head == NULL) {
        smaller = NULL;
        larger = NULL;
        return;
    }
    
    // Save the current node and advance head
    Node* current = head;
    head = head->next;
    
    // Recursively process the rest of the list
    llpivot(head, smaller, larger, pivot);
    
    // Place current node in appropriate list
    if (current->val <= pivot) {
        current->next = smaller;
        smaller = current;
    } else {
        current->next = larger;
        larger = current;
    }
}