#include<stdio.h>
#include<stdlib.h>
#define MAXNUM 100000
typedef struct node *TreeNode;
int front,rear = 0;
int data[MAXNUM][MAXNUM];
struct node{
    int data;
    TreeNode left ;
    TreeNode right;
};

TreeNode In_Post_Order(int post[],int inorder[],int n){
    if(n<=0){return NULL;}
    int i=0;
    for(i=0;i<n;i++){
        if(inorder[i] == post[n-1]){break;}
    }
    TreeNode root = (TreeNode)malloc(sizeof(struct node));
    root -> data = post[n-1];
    root -> left = In_Post_Order(post,inorder,i);
    root -> right= In_Post_Order(post+i,inorder+i+1,n-1-i);
    return root;
}

void enqueue(TreeNode *a,TreeNode node){
    a[rear++]=node;
}
TreeNode dequeue(TreeNode* a){
    return a[front++];
}

void ZigZag(TreeNode root) {
    if(!root){return;}
    int layer = 0;
    int last = 1;
    TreeNode queue[MAXNUM];
    enqueue(queue,root);    
    int i=0;

    while(front < rear){
        TreeNode p = dequeue(queue);
        data[layer][i++]=p->data;
        if(p->left){enqueue(queue,p->left);}
        if(p->right){enqueue(queue,p->right);}
        if(front==last){
            if (!(layer&1)){
                for(int j = i-1;j>=0;j--){
                    printf("%d ",data[layer][j]);
                }
            }
            else{
                for (int j=0;j<i;j++){
                    printf("%d ",data[layer][j]);
                }
            }
            layer++;
            last = rear;
            i = 0;
        }

    }
}

int main(){
    int n ;
    scanf("%d",&n);
    int post[n];
    int inorder[n];
    
    for(int i=0;i<n;i++){
        scanf("%d",&inorder[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&post[i]);
    }
    TreeNode root = In_Post_Order(post,inorder,n);
    ZigZag(root);
    return 0;
}