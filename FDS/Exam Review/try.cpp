// 中序遍历二叉树并返回结果作为数组
int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    struct TreeNodeStack* stack = NULL;
    int* result = (int*)malloc(sizeof(int));
    int resultSize = 0;
    struct TreeNode* current = root;
    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        result = (int*)realloc(result, (resultSize + 1) * sizeof(int));
        result[resultSize] = current->val;
        resultSize++;
        current = current->right;
    }

    *returnSize = resultSize;
    return result;
}

void PostOrderTraverse(BiTree T) {
	if (T == NULL)	return;
	BiTree Stack[100];
	int top = 0;
	BiTree prev = NULL;//用来标记，被标记的结点及其子树都是已经遍历完了的。
	BiTree root = T;//根节点指针
	while (top > 0 || root != NULL) {
		//把当前根节点入栈以及非空左子树入栈
		while (root != NULL) {
			Stack[top++] = root;
			root = root->left;
		}
 
		root = Stack[--top];//弹出左子树被完全遍历的结点
 
		//root->right==NULL当前根节点右子树为空,root->right==prev当前根节点右子树被完全遍历过
		if (root->right == NULL || root->right == prev) {
			printf("%d ", root->data);//左右子树都被遍历完，打印当前根节点值。
			prev = root;//标记当前根节点，用来判断后续结点的右子树是否被完全遍历。
			root = NULL;//根节点指针置空，为了回溯到父节点。
		}
		//将当前根节点入栈，遍历右子树
		else {
			Stack[top++] = root;
			root = root->right;
		}
	}
 
}