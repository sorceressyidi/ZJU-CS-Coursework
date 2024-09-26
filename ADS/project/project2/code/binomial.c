#include<stdio.h>
#include<stdlib.h>
#include"binomial.h"
/*
Function: newBinNode
--------------------
Create a new node.
*/
BinNode newBinNode(int value, int vertex){
    BinNode node = (BinNode)malloc(sizeof(struct BinomialNode));
    node->value = value;
    node->vertex = vertex;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}
/*
Function: BinomialLink
--------------------
Link child node with binomial heap.
*/

BinNode BinomialLink(BinNode node, BinNode child){
    if(node == NULL){return child;}
    if(child == NULL){return node;}
    if(node->degree < child->degree){return BinomialLink(child, node);}
    child->parent = node;
    child->sibling = node->child;
    node->child = child;
    node->degree++;
    return node;
}
/*
Function: BinomialMerge
--------------------
Merge two lists and combine subtrees with same degrees.
*/
BinNode BinomialMerge(BinNode node1, BinNode node2){
    //First step, merge them in increase order.
    BinNode pointer1 = node1, pointer2 = node2;
    BinNode begin = NULL;
    BinNode *node = &begin;
    while(pointer1&& pointer2){
        if(pointer1->degree <= pointer2->degree){
            *node = pointer1;
            pointer1 = pointer1->sibling;
        }else{
            *node = pointer2;
            pointer2 = pointer2->sibling;
        }
        node = &((*node)->sibling);
    }
    if(pointer1 == NULL){*node = pointer2;}
    else{*node = pointer1;}
    if(!begin){return begin;}
    //Second step, combine subtrees with same degrees.
    BinNode prev = NULL;    //Previous node.
    BinNode current = begin;//Current node.
    BinNode next = current->sibling; //Next node.
    while(next){
        //If the degrees of current and next are different, move to next pair.
        //If degrees of current == next == next.sibling, tackle the last two nodes.
        if(current->degree != next->degree || (next->sibling && next->sibling->degree == current->degree)){
            prev = current;
            current = next;
        }
        //If the degree of current == next, combine them.
        else{
            //If the value of current <= next, link next to current.
            if(current->value <= next->value)
            {
                current->sibling = next->sibling;
                BinNode temp = BinomialLink(current, next);
            }else{
                //If the value of current > next, link current to next.

                if(prev == NULL){begin = next;}
                else{prev->sibling = next;}
                BinomialLink(next, current);
                current = next;
            }
        }
        next = current->sibling;
    }
    return begin;
}
/*
Function: BinGetMin2
--------------------
Get the min node and its previous node.
*/

BinNode* BinGetMin2(BinNode node) {
    if (node == NULL){return NULL;}
    BinNode *min2 = (BinNode*)malloc(2 * sizeof(BinNode));
    if (min2 == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    min2[0] = NULL;
    min2[1] = node;
    BinNode prev = NULL;
    BinNode current = node;
    while (current) {
        if (current->value < min2[1]->value) {
            // Update the min node and its previous node
            min2[0] = prev;
            min2[1] = current;
        }
        prev = current;
        current = current->sibling;
    }
    return min2;
}
/*
Function: BinDeleteMin
--------------------
Delete min node.
*/
BinNode BinDeleteMin(BinNode node){
    if(node == NULL){return NULL;}
    //Get the min node and its previous node.
    BinNode *min2 = BinGetMin2(node);
    BinNode prev = min2[0];
    BinNode min = min2[1];
    //Remove the min node from the list.
    if(prev == NULL){node = min->sibling;}
    else{prev->sibling = min->sibling;}
    //Reverse the child list of min node.
    BinNode childlist = NULL;
    BinNode child = min->child;
    while(child){
        BinNode temp = child->sibling;
        if(!childlist){
            //If childlist is empty, create a new list.
            childlist = child;
            childlist->sibling = NULL;
            childlist->parent = NULL;
        }
        else{
            //If childlist is not empty, insert the new node to the head of the list.
            childlist->parent = NULL;
            child->sibling = childlist;
            childlist = child;
        }
        child = temp;
    }
    free(min2);
    return BinomialMerge(node, childlist);
}
/*
Function: BinInsert
--------------------
Insert a new node to heap.
*/
BinNode BinInsert(BinNode node, BinNode binnode){
    return BinomialMerge(node, binnode);
}
/*
Function: BinDecrease
--------------------
Decrease the value of one certain node.
*/
void BinDecrease(BinNode binnode, int value, BinNode* NodeArray)
{
	binnode->value = value;
	BinNode parent, child;
	parent = binnode->parent;
	child = binnode;
	while (parent != NULL && parent->value > child->value) //Exchange the position between child and parent.
	{
		int temp_value, temp_vertex;
		BinNode temp = NodeArray[child->vertex];   //Change the Distance array.
		NodeArray[child->vertex] = NodeArray[parent->vertex];
		NodeArray[parent->vertex] = temp;

		temp_value = child->value;
		temp_vertex = child->vertex;
		child->value = parent->value;
		child->vertex = parent->vertex;
		parent->value = temp_value;
		parent->vertex = temp_vertex;

		child = parent;
		parent = parent->parent;
	}
}
int IsBinEmpty(BinNode node)
{
	return node == NULL;
}
