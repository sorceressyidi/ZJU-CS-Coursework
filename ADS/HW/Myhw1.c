#include<stdio.h>
#include<stdlib.h>
typedef struct Treenode* node;
int max(int a,int b){
return a>b?a:b;
}
struct Treenode{
    int value;
    node left;
    node right;
    int height;
};

int height(node root) {
    if (root == NULL) {
        return -1;
    } else {
        return root->height;
    }
}

node RRotation(node root){
    node rotate = root ->left;
    root -> left = rotate ->right;
    rotate -> right = root;
    root->height = max(height(root->left), height(root->right)) + 1;
    rotate->height = max(height(rotate->left), height(rotate->right)) + 1;
    return rotate;
}

node LRotation(node root){
    node rotate = root -> right;
    root ->right = rotate -> left;
    rotate->left = root;
    root->height = max(height(root->left), height(root->right)) + 1;
    rotate->height = max(height(rotate->left), height(rotate->right)) + 1;
    return rotate;
}

node RLRotation(node root){
    root->right = RRotation(root->right);
    return LRotation(root);
}

node LRRotation(node root){
    root->left = LRotation(root->left);
    return RRotation(root);
}

node addnode(int value,node root){
    if(!root){
        root = (node)malloc(sizeof(struct Treenode));
        root -> value = value;
        root -> left = NULL;
        root -> right = NULL;
        root ->height = 0;
    }
    else{
        if(value<(root->value)){
            root -> left = addnode(value,root->left);
            if(height(root->left) - height(root->right) > 1){
                if(value < root->left->value){root = RRotation(root);}
                else{root = LRRotation(root);}
            }
        }
        else{
            root -> right = addnode(value,root->right);
            if(height(root->left) - height(root->right) < -1){
                if(value>root->right->value){root = LRotation(root);}
                else{root = RLRotation(root);}
            }
        }
    }
    root->height = max(height(root->left), height(root->right)) + 1;
    return root;
}

int main(){
    int n;
    scanf("%d",&n);
    node root = NULL;
    while(n--){
        int value;
        scanf("%d",&value);
        root = addnode(value,root);
    }
    printf("%d", root->value);
    return 0;
}