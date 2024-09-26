/* Author: 张祎迪;  ID:3220102157;  No.01 */
#include <stdio.h>
#include <stdlib.h>

// Define a structure pointer
typedef struct stk *pointer;
// Define a structure （stack）
struct stk {
    int data;      // Data field
    int cnt;       // Count field
    pointer next;  // Pointer to the next node
    pointer prior; // Pointer to the previous node
};

// Initialize the stack (clear)
void clear(pointer p) {
    p->next = NULL;
    p->prior = NULL;
}

// Push operation 
void push_stk1(pointer p0, pointer p) {
    if (p0->next) {
        p0->prior->next = p;
        p->prior = p0->prior;
    } else {
        p0->next = p;
        p->prior = p0;
    }
    p0->prior = p;
    p->next = p0;
    p->cnt = p->prior->cnt + 1;
}

// Create a node
pointer create_node() {
    pointer p = (pointer)malloc(sizeof(struct stk));
    p->cnt = 0;// Initialize the count field
    return p;
}

int main() {
    // Create and initialize the two stacks
    pointer p1 = create_node();
    clear(p1);
    pointer p2 = create_node();
    p2->cnt = 0;
    clear(p2);

    int n;// Number of operations
    int num;// Number to be inserted
    char a;// Operation

    // Input the number of operations
    scanf("%d\n", &n);

    // Loop through the operations
    while (n--) {
        scanf("%c", &a);
        if (a == 'I') {
            // If it's an insert operation
            pointer p = create_node();
            scanf("%d\n", &num);
            p->data = num;
            push_stk1(p1, p);
        }
        
        if (a == 'O') {
            getchar();
            // If it's a pop operation
            if (!p1->next && !p2->next) {
                printf("ERROR\n");
                continue;
            } else if (!p2->next) {
                // Pop from stack 1
                int q = p1->next->data;
                int m = p1->prior->cnt;
                printf("%d %d\n", q, 2 * m + 1);
                if (p1->prior->cnt == 1) {
                    clear(p1);
                    continue;
                }
                p1->prior->prior = p2;
                p2->next = p1->next->next;
                p2->prior = p1->prior;
                clear(p1);
            } else {
                // Pop from stack 2
                int q = p2->next->data;
                printf("%d 1\n", q);
                if (p2->next == p2->prior) {
                    p2->next = NULL;
                    p2->prior = NULL;
                    continue;
                }
                pointer m = p2->next->next;
                p2->next = m;
                m->prior = p2;
            }
        }
    }
    return 0;
}
