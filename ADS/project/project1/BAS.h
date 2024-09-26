#ifndef __BAS_HEAD__
#define __BAS_HEAD__

typedef struct Treenode* node;
struct Treenode{
    int key;
    node left;
    node right;
    int height;
};


int max(int a,int b);               // return the max value of a and b
int height(node root);              // get height
node FindMin(node root);            // return the node with minimal value of the tree
node FindMax(node root);            // return the node with minimal value of the tree
node createnode(int value);         // create a node of given value
node Find(node root, int key);      // return the node of the given key, NULL for not found
node insert_unBST(node root, int key);    // Insert a node with given value, return the root. Can be used in empty tree
node delete_unBST(node root, int key);    // return the tree with the given node deleted.
node rightRotate(node root);        // input the root before rotate, return the root after rRot
node leftRotate(node root);         // input the root before rotate, return the root after lRot
node insert_AVL(node root, int key);// insert for AVL
node delete_AVL(node root, int key);// delete for AVL
node insert_splay(node root,int key);// insert for splay
node splay(node root,int key);
node delete_splay(node root,int key);     // delete for splay
node find(node root,int key);        // find for splay
node findMaxleft(node root);            // used by splay
void PrintTree(node tree,  int level, int i);
#endif