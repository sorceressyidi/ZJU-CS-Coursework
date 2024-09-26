
#ifndef _PairHeap_H
#define _PairHeap_H


typedef struct PairingNode* PairNode;

typedef struct PairingNode* PairHeap;

// The PairingNode structure represents a single node in the pairing heap.
struct PairingNode {
    int vertex;      // The vertex 
    int value;       // The value 
    struct PairingNode* Prev;     // Pointer to the previous node 
    struct PairingNode* child;  // Pointer to the child node, 
    struct PairingNode* sibling; // Pointer to the sibling node, 
    
};

// Function to initialize a new PairNode with the given value and vertex.
PairNode InitialPairHeap(int value, int vertex);
// Function to insert a new PairNode X into the pairing heap H.
PairHeap PairInsert(PairHeap H, PairNode X);
// Function to decrease the value of PairNode X in the pairing heap H to the new value.
PairHeap PairDecrease(PairHeap H, PairNode X, int value);
// Function to remove  the minimum value node from the pairing heap H.
PairHeap PairDeleteMin(PairHeap H);
// Function to merge two pairing heaps H1 and H2 into a single heap.
PairHeap PairMerge(PairHeap H1, PairHeap H2);
// Function to check if the pairing heap H is empty.
int IsPairEmpty(PairHeap H);
// Function to combine  siblings 
PairHeap CombineSiblings(PairHeap H);
#endif