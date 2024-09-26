#include "MinHeap.h"
#include <stdio.h>
#include <stdlib.h>
minHeap MinInitialHeap(int max)
{
    int maxin = max + 2;                                              // Adding 2 to account for index 0 and to handle 1-based indexing
    minHeap Mheap = (struct MinHeap *)malloc(sizeof(struct MinHeap)); // Allocate memory for the minHeap structure
    Mheap->h = (MNode *)malloc(sizeof(MNode) * maxin);                // Allocate memory for the array of heap nodes
    Mheap->h[0] = (MNode)malloc(sizeof(struct MinHeapNode));          // Allocate memory for the dummy node at index 0
    Mheap->currentsize = 0;                                           // Initialize current size of the heap to 0
    Mheap->h[0]->value = -100;
    Mheap->h[0]->vertex = -1;
    Mheap->h[0]->index = 0;
    return Mheap;
}

MNode InitialMinNode(minHeap Mheap, int value, int vertex)
{
    MNode node = (MNode)malloc(sizeof(struct MinHeapNode));
    node->value = value;
    node->vertex = vertex;
    node->index = Mheap->currentsize + 1; // Set the index of the node
    return node;
}

void MinInsertNode(minHeap Mheap, MNode node)
{
    Mheap->h[(Mheap->currentsize) + 1] = node;                             // Insert the node at the end of the heap
    Mheap->currentsize++;                                                  // Increment the current size of the heap
    for (int i = Mheap->currentsize, j = (Mheap->currentsize) / 2; j > 0;) // Perform heapify-up
    {
        if (Mheap->h[j]->value < Mheap->h[i]->value) // If parent's value is less than child's value
        {
            break; // Heap property satisfied, break out of loop
        }
        else // Otherwise, swap parent and child
        {
            MNode tmp = Mheap->h[j]; // Swap nodes
            Mheap->h[j] = Mheap->h[i];
            Mheap->h[i] = tmp;
            Mheap->h[i]->index = i; // Update indices
            Mheap->h[j]->index = j;
            i /= 2; // Move up the heap
            j = i / 2;
        }
    }
    return;
}

void MinDecrease(minHeap Mheap, MNode Mnode, int value)
{
    Mheap->h[Mnode->index]->value = value;                     // Update the value of the node
    for (int i = Mnode->index, j = (Mnode->index) / 2; j > 0;) // Perform heapify-up
    {
        if (Mheap->h[j]->value < Mheap->h[i]->value) // If parent's value is less than child's value
        {
            break; // Heap property satisfied, break out of loop
        }
        else // Otherwise, swap parent and child
        {
            MNode tmp = Mheap->h[j]; // Swap nodes
            Mheap->h[j] = Mheap->h[i];
            Mheap->h[i] = tmp;
            Mheap->h[i]->index = i; // Update indices
            Mheap->h[j]->index = j;
            i /= 2; // Move up the heap
            j = i / 2;
        }
    }
    return;
}

void MinDeleteMin(minHeap Mheap)
{
    free(Mheap->h[1]);                              // Free memory allocated for the minimum node
    Mheap->h[1] = Mheap->h[Mheap->currentsize];     // Replace minimum node with last node
    Mheap->h[1]->index = 1;                         // Update index of the new root node
    for (int i = 1, j = 2; j < Mheap->currentsize;) // Perform heapify-down
    {
        if (j + 1 < Mheap->currentsize && Mheap->h[j]->value > Mheap->h[j + 1]->value) // Choose the smaller child
        {
            j = j + 1;
        }
        if (Mheap->h[j]->value < Mheap->h[i]->value) // If child's value is less than parent's value
        {
            MNode tmp = Mheap->h[j]; // Swap nodes
            Mheap->h[j] = Mheap->h[i];
            Mheap->h[i] = tmp;
            Mheap->h[i]->index = i; // Update indices
            Mheap->h[j]->index = j;
            i = j; // Move down the heap
            j = 2 * i;
        }
        else // If heap property is satisfied
        {
            break; // Break out of loop
        }
    }
    Mheap->h[Mheap->currentsize] = NULL; // Remove the last node
    Mheap->currentsize--;                // Decrement the current size of the heap
}