#include <stdio.h>
#include <stdlib.h>
#include "pairheap.h"

// Function to initialize and create a new PairNode with the given value and vertex.
PairNode InitialPairHeap(int value, int vertex){
    PairNode pairnode = (PairNode)malloc(sizeof(struct PairingNode));
    // Check if the memory allocation was successful.
    if(pairnode == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }
    // Initialize the PairNode with the given value and vertex.
    pairnode->value = value;
    pairnode->vertex = vertex;
    pairnode->Prev = NULL;
    pairnode->child = NULL;
    pairnode->sibling = NULL;
    
    return pairnode;
}

// Function to insert a new PairNode X into the pairing heap H.
PairHeap PairInsert(PairHeap H, PairNode X){
    if (H == NULL)
        return X;
    else
        return PairMerge(H, X);

}

// Function to decrease the value of a specific node in a PairHeap and restructure the heap accordingly.
PairHeap PairDecrease(PairHeap H, PairNode X, int value) {
    // Decrease the value of the node X to the given value.
    X->value = value;

    // If X is the root node, no restructure is needed, simply return the heap.
    if (X == H) {
        return H;
    } else {
        // If X has a sibling (i.e., it is not the only child of its parent), restructure the sibling connections.
        if (X->sibling != NULL) {
            // Update the sibling's previous pointer to bypass X.
            X->sibling->Prev = X->Prev;
            // If X was the child of its previous node, update the child pointer.
            if (X->Prev->child == X) {
                X->Prev->child = X->sibling;
            }
            // If X was the sibling of its previous node, update the sibling pointer.
            else if (X->Prev->sibling == X) {
                X->Prev->sibling = X->sibling;
            }
        } else {
            // If X does not have a sibling, update the previous node's pointers accordingly.
            if (X->Prev->child == X) {
                // If X was the child of its previous node, set the child pointer to NULL.
                X->Prev->child = NULL;
            } else if (X->Prev->sibling == X) {
                // If X was the sibling of its previous node, set the sibling pointer to NULL.
                X->Prev->sibling = NULL;
            }
        }
        // Remove X from its previous position by setting its sibling and previous pointers to NULL.
        X->sibling = NULL;
        X->Prev = NULL;
        
        // Merge X (now treated as a new node) back into the heap using PairMerge function.
        return PairMerge(H, X);
    }
}

// Function to delete the minimum value node (the root node) from a PairHeap.
PairHeap PairDeleteMin(PairHeap H) {
    // If the heap is empty, return NULL.
    if (H == NULL) {
        return NULL;
    }

    // If the root node does not have any children, there is nothing to delete, return NULL.
    if (H->child == NULL) {
        free(H);            // +
        return NULL;
    }
    //set the previous pointer of the root node's children to NULL.
    H->child->Prev = NULL;
    PairNode child = H->child;
    free(H);
    // Call the CombineSiblings function to combine the siblings of the root node's children.
    H = CombineSiblings(child);
   
    // Return the new root node of the restructured heap.
    return H;
}


// Function to check if the pairing heap H is empty.
int IsPairEmpty(PairHeap H){
    return H == NULL;
}

// Function to merge two PairHeaps, H1 and H2, into a single PairHeap.
PairHeap PairMerge(PairHeap H1, PairHeap H2) {
    // If H1 is NULL, there is no need to merge, return H2 as the result.
    if (H1 == NULL) {
        return H2;
    }
    // If H2 is NULL, there is no need to merge, return H1 as the result.
    if (H2 == NULL) {
        return H1;
    }
    else {
        // If the value of H1 is greater than the value of H2, H2 becomes the new root.
        if(H1->value > H2->value) {
            // Set the previous pointer of H2 to the previous pointer of H1.
            H2->Prev = H1->Prev;
            // If H1 was the child of its previous node, update the child pointer.
            if(H1->Prev != NULL) {
                if(H1->Prev->child == H1) {
                    H1->Prev->child = H2;
                } else if(H1->Prev->sibling == H1){
                    H1->Prev->sibling = H2;
                }
            }
            // Swap the child and sibling pointers of H1 and H2.
            PairNode temp = H2->child;
            H1->Prev = H2;
            H2->child = H1;
            H1->sibling = temp;
            // If H1 had children, update their previous pointers to point to H1.
            if(temp != NULL) {
                temp->Prev = H1;
            }
            // Return H2 as the new root of the merged heap.
            return H2;
        }
        // If the value of H1 is less than or equal to the value of H2, H1 becomes the new root.
        else {
            // Append H2's sibling list to H1's sibling list.
            H1->sibling = H2->sibling;
            
            // If H1 now has a sibling list, update their previous pointers to point to H1.
            if (H1->sibling != NULL) {
                H1->sibling->Prev = H1;
            }
            // Swap the child pointers of H1 and H2, making H2 a child of H1.
            PairNode temp = H1->child;
            H2->Prev = H1;
            H1->child = H2;
            H2->sibling = temp;
            // If H2 had children, update their previous pointers to point to H2.
            if(temp != NULL) {
                temp->Prev = H2;
            }
            // Return H1 as the new root of the merged heap.
            return H1;
        }
    }
}

// Function to combine all sibling nodes in a PairHeap, starting from the given node H.
PairHeap CombineSiblings(PairHeap H) {
    // If the given node H is NULL or does not have any siblings, return H as the result.
    if (H == NULL || H->sibling == NULL) {
        return H;
    }
    // Initialize H11 and H12 to the starting pair of sibling nodes.
    PairNode H11 = H;
    PairNode H12 = H->sibling;
    // Initialize H21 to be used for merging.
    PairNode H21;
    // Loop through the sibling nodes, merging them in pairs until there are no more pair siblings to merge.
    // printf("combine1\n");
    while(H11 || H12){
        // Merge the current pair of siblings (H11 and H12) into a new node H21.
        H21 = PairMerge(H11, H12);
        // Update H11 to be the next sibling after the merged pair.
        H11 = H21->sibling;
        // Move H12 to the next pair of siblings by checking if H11 has a sibling.
        H12 = (H11) ? H11->sibling : NULL;
    }
    // If there are any remaining sibling nodes after the loop, set H21 to the last merged sibling.
    if (H11 != NULL) {
        H21 = H11;
    }
    // Continue merging the previous nodes until H21 is the root of the heap.
    while (H21->Prev) {
        // Merge the previous node with the current node (H21) to form a new root.
        H21 = PairMerge(H21->Prev, H21);
    }
    

    // Return H21 as the new root of the combined heap.
    return H21;
}


