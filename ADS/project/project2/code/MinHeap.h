#ifndef _MinHeap_HEAD_
#define _MinHeap_HEAD_

typedef struct MinHeapNode *MNode;
struct MinHeapNode
{
    int vertex; // Vertex value
    int value;  // Value associated with the vertex
    int index;  // Index of the node in the heap
};

// Define a structure for MinHeap
typedef struct MinHeap *minHeap;
struct MinHeap
{
    MNode *h;        // Array to store heap nodes
    int currentsize; // Current size of the heap
};

// Function to initialize a min heap with maximum size 'max'
minHeap MinInitialHeap(int max);
// Function to initialize a min heap node with given value and vertex
MNode InitialMinNode(minHeap Mheap, int value, int vertex);
// Function to insert a node into the min heap
void MinInsertNode(minHeap Mheap, MNode node);
// Function to decrease value of a node in min heap
void MinDecrease(minHeap Mheap, MNode Mnode, int value);
// Function to delete minimum value node from the min heap
void MinDeleteMin(minHeap Mheap);
#endif