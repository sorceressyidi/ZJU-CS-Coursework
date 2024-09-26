#ifndef _Fib_HEAD_
#define _Fib_HEAD_

typedef struct FibonacciNode* FibNode;
struct FibonacciNode
{
    int vertex;                // Vertex value
    int value;                 // Value associated with the vertex
    int degree;                // Degree of the node
    struct FibonacciNode *left;    // Pointer to the left sibling
    struct FibonacciNode *right;   // Pointer to the right sibling
    struct FibonacciNode *child;   // Pointer to the first child
    struct FibonacciNode *parent;  // Pointer to the parent
    int marked;                // Mark flag for child cut operation
};

typedef struct FibonacciHeap *FibHeap;
struct FibonacciHeap{
    FibNode min;               // Pointer to the minimum node in the heap
    int maxDegree;             // Maximum degree of nodes in the heap
    int keyNum;                // Number of nodes in the heap
    FibNode *cons;             // Consolidation array
};

// Function to initialize a Fibonacci Heap
FibHeap InitialHeap(void);
// Function to initialize a Fibonacci Heap Node with given value and vertex
FibNode InitialFibNode(int value, int vertex);
// Function to insert a node into the Fibonacci Heap
void FibInsertNode(FibHeap fibheap, FibNode fibnode);
// Function to link two Fibonacci Heap trees
void FibHeapLink(FibHeap h, FibNode y, FibNode x);
// Function to merge two Fibonacci Heaps
FibHeap FibHeapMerge(FibHeap fibheap1, FibHeap fibheap2);
// Function to consolidate the trees in the Fibonacci Heap
void Fib_consolidate(FibHeap h);
// Function to decrease the value of a node in the Fibonacci Heap
void FibDecrease(FibHeap fibheap, FibNode fibnode, int value);
// Function to delete the minimum value node from the Fibonacci Heap
void FibDeleteMin(FibHeap fibheap);
// Function to cut a node from its parent in the Fibonacci Heap
void FibCut(FibHeap h, FibNode x, FibNode y);
// Function to perform cascading cut operation in the Fibonacci Heap
void FibCascading_Cut(FibHeap h, FibNode y);

#endif
