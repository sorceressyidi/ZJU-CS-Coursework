#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct node *TreeNode;

// Use "struct" to represent a tree node
struct node{
    int data;
    TreeNode left ;
    TreeNode right;
};

// This function constructs a binary tree node and inserts a new node with the given data.
// It returns the modified binary tree's root.
TreeNode construct(TreeNode root, int num) {
    // If the root is NULL, create a new node and assign it the given data.
    if (!root) {
        root = (TreeNode)malloc(sizeof(struct node));
        root->data = num;
        root->left = NULL;
        root->right = NULL;
    }
    else {
        // If the root is not NULL, compare the absolute value of 'num' with the absolute
        // value of the data in the current root node to determine the insertion location.
        if (abs(num) < abs(root->data)) {
            // If 'num' is smaller, recursively insert it into the left subtree.
            root->left = construct(root->left, num);
        }
        else {
            // If 'num' is larger or equal, recursively insert it into the right subtree.
            root->right = construct(root->right, num);
        }
    }
    // Return the modified binary tree's root.
    return root;
}

// This function checks for red-red violations within a binary tree.
// It returns 1 if there are no violations and 0 if any red-red violations are found.
int rednode(TreeNode root) {
    // Base case: If the current node is NULL, there are no violations.
    if (!root) {
        return 1;
    }
    // Check if the data of the current node is negative (indicating a red node).
    if (root->data < 0) {
        // Check if the child is also a red node, indicating a red-red violation.
        if ((root->left && root->left->data < 0)||(root->right && root->right->data < 0)) {
            return 0;
        }
    }
    // Recursively check for red violations in the left and right subtrees.
    return rednode(root->left) && rednode(root->right);
}


// This function checks if all paths from the root to leaves in a binary tree
// have the same number of black nodes, updating a flag to indicate the result.
int paths(TreeNode root, int* flag) {
    // Base case: If the current node is NULL (a leaf), return 1 (black node count).
    if (root == NULL) return 1;
    // Recursively calculate the count of black nodes in the left subtree.
    int left = paths(root->left, flag);
    // Recursively calculate the count of black nodes in the right subtree.
    int right = paths(root->right, flag);
    // Compare the black node counts in the left and right subtrees.
    // If they are not equal, update the flag to 0, indicating an inconsistency.
    if (left != right) {
        *flag = 0;
    }
    // Determine the total count of black nodes in the current subtree.
    // Increment by 1 if the current node is a black node (data > 0).
    // If the current node is a red node (data < 0), the count is not incremented.
    return (root->data > 0) ? left + 1 : left;
}
//This is a function to "print" to binary search tree.
void printTree(TreeNode n, int type, int level) {
    if (!n) {
        return; // If the node is empty, no operation is performed, just return
    }
    printTree(n->right, 2, level + 1); // Recursively traverse the right subtree, set type to 2, indicating the right subtree
    
    if (type != 0) {
        for (int i = 0; i < level; i++) {
            printf("     "); // Print a certain number of spaces to create a hierarchical structure
        }
    }
    if (type == 1) {
        printf("\\%d\n", n->data); // Print the node value with a backslash, indicating the right subtree
    } else if (type == 2) {
        printf("/%d\n", n->data); // Print the node value with a forward slash, indicating the left subtree
    } else {
        printf("%d\n", n->data); // By default, only print the node value
    }
    printTree(n->left, 1, level + 1);  // Recursively traverse the left subtree, set type to 1, indicating the left subtree
}
int main() {
    int n;
    scanf("%d", &n);

    // Process 'n' test cases
    while (n--) {
        int cnt;
        scanf("%d", &cnt);
        TreeNode root = NULL;

        // Create the binary tree with 'cnt' nodes
        while (cnt--) {
            int num;
            scanf("%d", &num);

            // Construct the binary tree using 'construct' function
            root = construct(root, num);
        }
      //Uncomment it if you want to see to printed tree.
      /*
        printf("\n");
        printTree(root, 0,  0);	
      */
        // Check if the binary tree is a valid red-black tree
        if (root->data < 0) {
            // If the root data is negative, it's not a valid red-black tree
            printf("No\n");
        } else {
            int flag = 1;
            // Call 'paths' function to check properties of red-black tree
            paths(root, &flag);

            if (rednode(root) == 0) {
                // If there's a red-red violation, it's not a valid red-black tree
                printf("No\n");
            } else if (!(flag)) {
                // If not all paths have the same number of black nodes, it's not a valid red-black tree
                printf("No\n");
            } else {
                // If all checks pass, it's a valid red-black tree
                printf("Yes\n");
            }
        }
    }
    return 0;
}