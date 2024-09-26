void PreOrderTraverse(BiTree T){
    if(T=NULL){return;}
    Bitree Stack[100];
    int top=-1;
    stack[++top]=T;
    BiTree p=NULL;
    while(top>=0){
        p=Stack[top--];
        printf("%d",p->data);
        if(p->right!=NULL){Stack[++top]=p->right;}
        if(p->left !=NULL){Stack[++top]=p->left; }
    }
}

void InOrderTraverse(BiTree T){
    BiTree Stack[100];
    int top=-1;
    BiTree root = T;
    while(top>=0||root !=NULL){
        while(root){
            Stack[++top]=root;
            root=root->left;
        }
    root=Stack[top--];
    printf("%d",rot->data);
    root=root->right; // Important!
    }

}
void PostOrderTraverse(BiTree T){
    if(T=NULL){return;}
    BiTree Stack[100];
    BiTree prev = NULL;
    BiTree root = T;
    int top=-1;
    while(top>=0||root!=NULL){
        while(root!=NULL){
            Stack[++top]=root;
            root = root ->left;
        }
        root =  Stack[top--];
        if(root->right == NULL || root->right ==prev){
            printf("%d ",root->data);
            prev =  root;
            root =  NULL;
        }
        else{
            stack[++top]=root;
            root=root=>right
        }
    }
}