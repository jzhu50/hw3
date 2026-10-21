#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) {
  // base case
  if (head == NULL) {
    smaller = NULL;
    larger = NULL;
    return;
  }

  // recursive
  Node* curr = head;
  head = head->next;

  // saved all nodes
  llpivot(head, smaller, larger, pivot);

  // process nodes
  if (curr->val <= pivot) {
    curr->next = smaller;
    smaller = curr;
  } else {
    curr->next = larger;
    larger = curr;
  }
}

