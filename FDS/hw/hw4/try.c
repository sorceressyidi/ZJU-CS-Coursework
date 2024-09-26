#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义二叉树结点
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 创建一个二叉树结点
struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 结构体模拟栈
struct TreeNodeStack {
    struct TreeNode* data;
    struct TreeNodeStack* next;
};

struct TreeNodeStack* createStackNode(struct TreeNode* node) {
    struct TreeNodeStack* stackNode = (struct TreeNodeStack*)malloc(sizeof(struct TreeNodeStack));
    stackNode->data = node;
    stackNode->next = NULL;
    return stackNode;
}

void push(struct TreeNodeStack** stack, struct TreeNode* node) {
    struct TreeNodeStack* stackNode = createStackNode(node);
    stackNode->next = *stack;
    *stack = stackNode;
}

struct TreeNode* pop(struct TreeNodeStack** stack) {
    if (*stack == NULL) {
        return NULL;
    }
    struct TreeNodeStack* temp = *stack;
    *stack = (*stack)->next;
    struct TreeNode* node = temp->data;
    free(temp);
    return node;
}

bool isEmpty(struct TreeNodeStack* stack) {
    return stack == NULL;
}

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

// 主函数
int main() {
    struct TreeNode* root = createNode(1);
    root->right = createNode(2);
    root->right->left = createNode(3);
    
    printf("Inorder Traversal: ");
    int resultSize;
    int* result = inorderTraversal(root, &resultSize);
    for (int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    free(result);
    return 0;
}
