#include "FibHeap.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
FibHeap InitialHeap(void)
{
    FibHeap fibheap = (struct FibonacciHeap *)malloc(sizeof(struct FibonacciHeap)); // Allocate memory for the FibonacciHeap structure
    fibheap->min = NULL;
    fibheap->maxDegree = 0;
    fibheap->keyNum = 0;
    fibheap->cons = NULL;
    return fibheap;
}

FibNode InitialFibNode(int value, int vertex)
{
    FibNode newNode = (struct FibonacciNode *)malloc(sizeof(struct FibonacciNode));
    newNode->vertex = vertex;
    newNode->value = value;
    newNode->left = newNode;
    newNode->right = newNode;
    newNode->child = NULL;
    newNode->degree = 0;
    newNode->marked = 0;
    newNode->parent = NULL;
    return newNode;
}

void FibInsertNode(FibHeap fibheap, FibNode fibnode)
{
    if (fibheap->keyNum == 0) // If heap is empty
    {
        fibheap->min = fibnode; // Set the new node as the minimum
    }
    else // If heap is not empty
    {
        // Insert the new node into the circular doubly linked list of roots
        fibheap->min->left->right = fibnode;
        fibnode->left = fibheap->min->left;
        fibnode->right = fibheap->min;
        fibheap->min->left = fibnode;

        // Update the minimum pointer if necessary
        if (fibheap->min->value > fibnode->value)
        {
            fibheap->min = fibnode;
        }
    }
    fibheap->keyNum++; // Increment the number of nodes
    return;
}

FibHeap FibHeapMerge(FibHeap fibheap1, FibHeap fibheap2)
{
    if (fibheap1 == NULL || fibheap1->keyNum == 0) // If heap 1 is empty
    {
        return fibheap2; // Return heap 2
    }
    if (fibheap2 == NULL || fibheap2->keyNum == 0) // If heap 2 is empty
    {
        return fibheap1; // Return heap 1
    }
    FibHeap h = fibheap1;        // Initialize the merged heap as heap 1
    FibNode tmp = h->min->right; // Store the right sibling of the minimum node of heap 1
    // Adjust pointers to merge the circular doubly linked lists of roots
    h->min->right = fibheap2->min->right;
    fibheap2->min->right->left = h->min;
    fibheap2->min->right = tmp;
    tmp->left = fibheap2->min;
    // Update the minimum pointer if necessary
    if (fibheap1->min->value > fibheap2->min->value)
    {
        h->min = fibheap2->min;
    }
    h->keyNum = fibheap1->keyNum + fibheap2->keyNum; // Update the total number of nodes
    return h;
}

void FibDeleteMin(FibHeap fibheap)
{
    FibNode z = fibheap->min; // Store the minimum node
    if (z)                    // If minimum node exists
    {
        if (z->child) // If minimum node has children
        {
            FibNode sibling = z->child->left, next; // Start from the leftmost child
            // Iterate through the children and add them to the list of roots
            while (1)
            {
                next = sibling->left;
                sibling->parent = NULL; // Set the parent pointer to NULL
                // Adjust pointers to add the child to the list of roots
                sibling->right = fibheap->min;
                fibheap->min->left->right = sibling;
                sibling->left = fibheap->min->left;
                fibheap->min->left = sibling;
                if (sibling == z->child) // If all children are processed
                {
                    break;
                }
                sibling = next; // Move to the next child
            }
        }
        // Remove the minimum node from the list of roots
        z->left->right = z->right;
        z->right->left = z->left;
        if (z == z->right) // If only one node in the list of roots
        {
            fibheap->min = NULL; // Set the minimum pointer to NULL
        }
        else // If multiple nodes in the list of roots
        {
            fibheap->min = z->right;  // Update the minimum pointer
            Fib_consolidate(fibheap); // Consolidate the heap
        }
        fibheap->keyNum--; // Decrement the number of nodes
    }
    free(z); // Free memory allocated for the minimum node
    return;
}

void Fib_consolidate(FibHeap h)
{
    if (h == NULL || h->min == NULL) // If heap is empty
    {
        return;
    }
    // Calculate the maximum possible degree of a node in the heap
    h->maxDegree = (int)(log2((double)(h->keyNum)) + 1);
    h->cons = (FibNode *)malloc(sizeof(FibNode) * (h->maxDegree + 1)); // Allocate memory for consolidation array
    for (int i = 0; i < h->maxDegree + 1; i++)                         // Initialize consolidation array to NULL
    {
        h->cons[i] = NULL;
    }
    FibNode w = h->min, x, y; // Initialize variables for consolidation
    int d;
    while (h->min) // Iterate through the roots
    {
        x = w;             // Store the current root
        if (x->right == x) // If only one root
        {
            h->min = NULL; // Set the minimum pointer to NULL
        }
        else // If multiple roots
        {
            h->min = x->right; // Update the minimum pointer
            // Remove the root from the list of roots
            x->right->left = x->left;
            x->left->right = x->right;
            // Make the root a singleton circular doubly linked list
            x->left = x;
            x->right = x;
        }
        d = x->degree;     // Get the degree of the root
        while (h->cons[d]) // If another root with the same degree exists
        {
            y = h->cons[d];          // Get the root with the same degree
            if (x->value > y->value) // Compare values of the roots
            {
                FibNode tmp = x; // Swap roots if necessary
                x = y;
                y = tmp;
            }
            FibHeapLink(h, y, x); // Link the roots
            h->cons[d] = NULL;    // Clear the slot in the consolidation array
            d++;                  // Increment the degree
        }
        h->cons[d] = x; // Store the root in the consolidation array
        w = h->min;     // Move to the next root
    }
    h->min = NULL;                         // Reset the minimum pointer
    for (d = 0; d < h->maxDegree + 1; d++) // Iterate through the consolidation array
    {
        if (h->cons[d]) // If a root exists in the slot
        {
            if (h->min == NULL)
            {
                h->min = h->cons[d];
            }
            else
            {
                // Insert the root into the list of roots
                h->min->left->right = h->cons[d];
                h->cons[d]->left = h->min->left;
                h->min->left = h->cons[d];
                h->cons[d]->right = h->min;
                if (h->cons[d]->value < h->min->value) // Update the minimum pointer if necessary
                {
                    h->min = h->cons[d];
                }
            }
        }
    }
    free(h->cons); // Free memory allocated for the consolidation array
    return;
}

void FibHeapLink(FibHeap h, FibNode y, FibNode x)
{
    y->parent = x;        // Set parent pointer of y to x
    if (x->child == NULL) // If x has no children
    {
        x->child = y; // Set y as the first child of x
        y->left = y;  // Make y a singleton circular doubly linked list
        y->right = y;
    }
    else // If x already has children
    {
        // Insert y into the list of children of x
        x->child->left->right = y;
        y->left = x->child->left;
        y->right = x->child;
        x->child->left = y;
    }
    y->marked = 0; // Clear the mark flag of y
    x->degree++;   // Increment the degree of x
    return;
}

void FibDecrease(FibHeap fibheap, FibNode fibnode, int value)
{
    fibnode->value = value;             // Update the value of the node
    FibNode y = fibnode->parent;        // Get the parent of the node
    if (y && fibnode->value < y->value) // If the new value is less than the value of the parent
    {
        FibCut(fibheap, fibnode, y);  // Cut the node from its parent
        FibCascading_Cut(fibheap, y); // Perform cascading cut operation
    }
    if (fibnode->value < fibheap->min->value) // If the new value is less than the minimum value
    {
        fibheap->min = fibnode; // Update the minimum pointer
    }
    return;
}

void FibCut(FibHeap h, FibNode x, FibNode y)
{
    y->degree--;      // Decrease the degree of y
    if (x->left == x) // If x is the only child of y
    {
        y->child = NULL; // Set the child pointer of y to NULL
    }
    else // If there are other children of y
    {
        // Remove x from the list of children of y
        x->left->right = x->right;
        x->right->left = x->left;
        if (y->child == x) // If x is the first child of y
        {
            y->child = x->right; // Update the child pointer of y
        }
    }
    x->parent = NULL; // Set the parent pointer of x to NULL
    // Insert x into the list of roots
    h->min->left->right = x;
    x->left = h->min->left;
    h->min->left = x;
    x->right = h->min;
    x->marked = 0; // Clear the mark flag of x
    return;
}

void FibCascading_Cut(FibHeap h, FibNode y)
{
    FibNode z = y->parent; // Get the parent of y
    if (z)                 // If y has a parent
    {
        if (y->marked == 0) // If y is unmarked
        {
            y->marked = 1; // Mark y
        }
        else // If y is marked
        {
            FibCut(h, y, z);        // Cut y from its parent
            FibCascading_Cut(h, z); // Perform cascading cut operation on the parent
        }
    }
    return;
}
