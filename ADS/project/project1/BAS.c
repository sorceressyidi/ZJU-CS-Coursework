#include "BAS.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int max(int a,int b){
return a>b?a:b;
}

int height(node root) {
    if (root == NULL) {
        return -1;
    } else {
        return root->height;
    }
}

node createnode(int value){
    node temp = (node)malloc(sizeof(struct Treenode));
    temp -> key = value;
    temp ->left = NULL;
    temp ->right = NULL;
    temp -> height = 0;
    return temp;
}

node rightRotate(node root){
    node rotate = root ->left;
    root ->left = rotate ->right;
    rotate -> right = root;

    root->height = max(height(root->left), height(root->right)) + 1;
    rotate->height = max(height(rotate->left), height(rotate->right)) + 1;
    return rotate;
}

node leftRotate(node root){
    node rotate = root ->right;
    root ->right = rotate ->left;
    rotate -> left = root;

    root->height = max(height(root->left), height(root->right)) + 1;
    rotate->height = max(height(rotate->left), height(rotate->right)) + 1;
    return rotate;
}


node Find(node root, int key){
    node ptr = root;
    while(ptr && ptr->key != key){
        if(key > ptr->key){
            ptr = ptr->right;
        }else{
            ptr = ptr->left;
        }
    }
    return ptr;
}

node insert_unBST(node root, int key){
    if(root == NULL){
        root = createnode(key);
    }else if(root->key > key){
        root->left = insert_unBST(root->left, key);
    }else if(root->key < key){
        root->right = insert_unBST(root->right, key);
    }
    root->height = max(height(root->left), height(root->right)) + 1;
    return root;
}

node insert_AVL(node root, int key){
    if(root == NULL){
        root = createnode(key);
    }else if(root->key > key){
        root->left = insert_AVL(root->left, key);
        if(abs(height(root->left) - height(root->right)) > 1){
            if(root->left->key > key){      // LL
                root = rightRotate(root);
            }else if(root->left->key < key){    // LR
                root->left = leftRotate(root->left);
                root = rightRotate(root);
            }
        }
    }else if(root->key < key){
        root->right = insert_AVL(root->right, key);
        if(abs(height(root->left) - height(root->right)) > 1){
            if(root->right->key < key){      // RR
                root = leftRotate(root);
            }else if(root->right->key > key){    // RL
                root->right = rightRotate(root->right);
                root = leftRotate(root);
            }
        }
    }


    root->height = max(height(root->left), height(root->right)) + 1;
    return root;
}


node FindMin(node root){
    if(root == NULL){
        printf("Can't find the minimal of an empty tree! \n");
        return NULL;
    }
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

node FindMax(node root){
    if(root == NULL){
        printf("Can't find the maximal of an empty tree! \n");
        return NULL;
    }
    while(root->right != NULL){
        root = root->right;
    }
    return root;
}

node delete_unBST(node root, int key){
    node temp = NULL;
    if(root == NULL){
        return NULL;
    }
    if(root->key > key){
        root->left = delete_unBST(root->left, key);
    }else if(root->key < key){
        root->right = delete_unBST(root->right, key);
    }else{
        if(root->right && root->left ){
            temp = FindMax(root->left);
            root->key = temp->key;
            root->left = delete_unBST(root->left, temp->key);
        }else{
            temp = root;
            if(root->right == NULL){
                root = root->left;
            }else{
                root = root->right;
            }
            free(temp);
        }
    }
    if (root) root->height = max(height(root->left), height(root->right)) + 1;
    return root;
}

node delete_AVL(node root, int key){
    node temp = NULL;
    if(root == NULL){
        return NULL;
    }
    if(root->key > key){
        root->left = delete_AVL(root->left, key);
        if((height(root->right) - height(root->left)) > 1){
            if(height(root->right->right) < height(root->right->left)){     //RL
                root->right = rightRotate(root->right);
                root = leftRotate(root);
            }else{                                                      // RR
                root = leftRotate(root);
            }
        }
    }else if(root->key < key){
        root->right = delete_AVL(root->right, key);
        if((height(root->left) - height(root->right)) > 1){
            if(height(root->left->right) > height(root->left->left)){     //LR
                root->left = leftRotate(root->left);
                root = rightRotate(root);
            }else{                                                      // RR
                root = rightRotate(root);
            }
        }
    }else{
        if(root->right && root->left ){
            temp = FindMax(root->left);
            root->key = temp->key;
            root->left = delete_AVL(root->left, temp->key);
            if((height(root->right) - height(root->left)) > 1){
                if(height(root->right->right) < height(root->right->left)){     //RL
                    root->right = rightRotate(root->right);
                    root = leftRotate(root);
                }else{                                                      // RR
                    root = leftRotate(root);
                }
            }
        }else{
            temp = root;
            if(root->right == NULL){
                root = root->left;
            }else{
                root = root->right;
            }
            free(temp);
        }
    }

    if(root != NULL) root->height = max(height(root->left), height(root->right)) + 1;
    return root;
}

void PrintTree(node tree,  int level, int i){
    if(tree == NULL){
        return;
    }
    
    if(tree->right != NULL){
        PrintTree(tree->right,level+1,1);
    }
    for(int i =  0;i<level;i++){
        printf("    ");
    }
    if(i == 1){
        printf("/");
    }else if(i == -1){
        printf("\\");
    }
    printf("%d\n",tree->key);
    if(tree->left != NULL){
        PrintTree(tree->left,level+1,-1);
    }
}

node insert_splay(node root, int key) {
    node parent = NULL;
    node temp = root;
    while (temp != NULL) {
        parent = temp;
        if (temp->key < key) {
            temp = temp->right;
        } 
        else if (temp->key > key){
            temp = temp->left;
        }
        else{
            return splay(root,key);
        }
    }
    node insertNode = createnode(key);
    if (!parent) {
        root = insertNode;
    } else if (parent->key < key) {
        parent->right = insertNode;
    } else {
        parent->left = insertNode;
    }
    //return root;
    return splay(root, key);
}

// Top-down splay
node splay(node root, int key) {
    int key_value = key;
    if (!root || root->key == key_value) {
        return root;
    }
    if(root->key > key_value){
        if(!root->left){
            return root;
        }
        if(root->left->key > key_value){
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }else if(root->left->key < key_value){
            root->left->right = splay(root->left->right, key);
            if(root->left->right){
                root->left = leftRotate(root->left);
            }
        }
        return (root->left)?rightRotate(root):root;
    }
    else{
        if(!root->right){
            return root;
        }
        if(root->right->key > key_value){
            root->right->left = splay(root->right->left, key);
            if(root->right->left){
                root->right = rightRotate(root->right);
            }
        }else if(root->right->key < key_value){
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right)?leftRotate(root):root;
    }
}
node find(node root,int key){
    node temp = root;
    while(temp!=NULL){
        if(temp->key < key){
            temp = temp->right;
        }
        else if(temp->key > key){
            temp = temp->left;
        }
        else{
            break;
        }
    }
    if(!temp){
        printf("Not found\n");
        return root;
    }
    return splay(root,key);
}

node findMaxleft(node root){
    node temp = root->left;
    node P = NULL;
    while(temp->right){
        P = temp;
        temp = temp->right;
    }
    if(!P){
        root -> left = temp -> left;
        return temp;
    }
    P->right = temp->left;
    return temp;
}


node delete_splay(node root,int key){
    node temp = find(root,key);
    if(!temp){
        return root;
    }
    
    if(!temp->left){
        root = temp->right;
        free(temp);
    }
    else if(!temp->right){
        root = temp->left;
        free(temp);
    }
    else{
        node maxleft = findMaxleft(temp);
        maxleft->right = temp->right;
        maxleft->left = temp->left;
        root = maxleft;
        free(temp);
    }
    return root;
}