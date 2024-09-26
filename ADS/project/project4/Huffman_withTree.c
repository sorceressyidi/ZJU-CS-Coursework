#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 64
#define max_stu 1010
typedef struct lexicon
{
    char letter;
    char code[max];
} Lexicon;

typedef struct Tnode
{
    int weight;
    struct Tnode *left;
    struct Tnode *right;
} *HFnode;

typedef struct Heap *minHeap;
struct Heap
{
    HFnode *h;       // Array to store heap nodes
    int currentsize; // Current size of the heap
};

Lexicon encode[max];
minHeap Mheap;

void MinInsertNode(HFnode node)
{
    Mheap->h[(Mheap->currentsize) + 1] = node;                             // Insert the node at the end of the heap
    Mheap->currentsize++;                                                  // Increment the current size of the heap
    for (int i = Mheap->currentsize, j = (Mheap->currentsize) / 2; j > 0;) // Perform heapify-up
    {
        if (Mheap->h[j]->weight < Mheap->h[i]->weight) // If parent's value is less than child's value
        {
            break; // Heap property satisfied, break out of loop
        }
        else // Otherwise, swap parent and child
        {
            HFnode tmp = Mheap->h[j]; // Swap nodes
            Mheap->h[j] = Mheap->h[i];
            Mheap->h[i] = tmp;
            i /= 2; // Move up the heap
            j = i / 2;
        }
    }
    return;
}

HFnode MinDeleteMin()
{
    HFnode result = Mheap->h[1];
    Mheap->h[1] = Mheap->h[Mheap->currentsize];     // Replace minimum node with last node
    for (int i = 1, j = 2; j < Mheap->currentsize;) // Perform heapify-down
    {
        if (j + 1 < Mheap->currentsize && Mheap->h[j]->weight > Mheap->h[j + 1]->weight) // Choose the smaller child
        {
            j = j + 1;
        }
        if (Mheap->h[j]->weight < Mheap->h[i]->weight) // If child's value is less than parent's value
        {
            HFnode tmp = Mheap->h[j]; // Swap nodes
            Mheap->h[j] = Mheap->h[i];
            Mheap->h[i] = tmp;
            i = j; // Move down the heap
            j = 2 * i;
        }
        else // If heap property is satisfied
        {
            break; // Break out of loop
        }
    }
    Mheap->h[Mheap->currentsize] = NULL; // Remove the last node
    Mheap->currentsize--;                // Decrement the current size of the heap
    return result;
}

void MinInitialHeap(int n, int frequency[])
{
    int maxin = max + 2;                                 // Adding 2 to account for index 0 and to handle 1-based indexing
    Mheap = (struct Heap *)malloc(sizeof(struct Heap));  // Allocate memory for the minHeap structure
    Mheap->h = (HFnode *)malloc(sizeof(HFnode) * maxin); // Allocate memory for the array of heap nodes
    Mheap->h[0] = (HFnode)malloc(sizeof(struct Tnode));  // Allocate memory for the dummy node at index 0
    Mheap->currentsize = 0;                              // Initialize current size of the heap to 0
    Mheap->h[0]->weight = -1;
    Mheap->h[0]->left = NULL;
    Mheap->h[0]->right = NULL;
    for (int i = 0; i < n; i++)
    {
        HFnode newNode = (HFnode)malloc(sizeof(struct Tnode));
        newNode->left = newNode->right = NULL;
        newNode->weight = frequency[i];
        MinInsertNode(newNode);
    }
    return;
}
void Huffman(int n)
{
    for (int i = 1; i < n; i++)
    {
        HFnode newNode = (HFnode)malloc(sizeof(struct Tnode));
        newNode->left = MinDeleteMin();
        newNode->right = MinDeleteMin();
        newNode->weight = newNode->left->weight + newNode->right->weight;
        MinInsertNode(newNode);
    }
    return;
}

int getcost(HFnode T, int depth)
{
    if (T->left == NULL && T->right == NULL)
    {
        return T->weight * depth;
    }
    else
    {
        return getcost(T->left, depth + 1) + getcost(T->right, depth + 1);
    }
}

int cmp(const void *a, const void *b)
{
    return strcmp(((Lexicon *)a)->code, ((Lexicon *)b)->code);
}

int check_prefix(int n)
{
    char *code1, *code2;
    qsort(encode, n, sizeof(Lexicon), cmp);
    for (int i = 1; i < n; i++)
    {
        code1 = encode[i].code;
        code2 = encode[i - 1].code;
        if (strncmp(code1, code2, strlen(code2)) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int num;
    printf("Input case number:\n");
    scanf("%d", &num);
    char input[30];
    int n, m;
    sprintf(input, "test_cases/case%d.txt", num);
    freopen(input, "r", stdin);

    scanf("%d\n", &n);
    char letter;
    int frequency[max];
    int ans[max_stu]={0};
    for (int i = 0; i < n; i++)
    {
        scanf("%c %d ", &letter, &frequency[i]);
    }
    MinInitialHeap(n, frequency);
    Huffman(n);
    int cost = getcost(Mheap->h[1], 0);
    scanf("%d\n", &m);
    for (int i = 0; i < m; i++)
    {
        int cost_submit = 0;
        for (int j = 0; j < n; j++)
        {
            scanf("%c %s", &encode[j].letter, encode[j].code);
            getchar();
            cost_submit += frequency[j] * strlen(encode[j].code);
        }
        if (cost == cost_submit && check_prefix(n))
        {
            ans[i]=1;
        }
        
    }
    fclose(stdin);
    for (int i = 0; i < m-1; i++)
    {
        if (ans[i])
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
    if (ans[m-1])
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
    return 0;
}