#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_char 64
#define max_stu 1010
// Define lexicon struct to store character and its corresponding code
typedef struct lexicon
{
    char letter;
    char code[max_char];
} Lexicon;
// Define Heap struct for minimum heap operation
struct Heap
{
    int a[max_char];       // Array to store heap nodes
    int currentsize; // Current size of the heap
};
typedef struct Heap *minHeap;

Lexicon encode[max_char];
minHeap Mheap;
// Swap method for reordering heap
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
// Insert method for heap operation
void insert(int X)
{
    Mheap->a[++Mheap->currentsize] = X;
    for (int i = Mheap->currentsize; Mheap->a[i / 2] > Mheap->a[i]; i /= 2)
    {
        swap(&Mheap->a[i], &Mheap->a[i / 2]);
    }
}
// Delete the minimum node in the heap
int deletemin(){
    int minnode = Mheap->a[1];
    Mheap->a[1] = Mheap->a[Mheap->currentsize];
    (Mheap->currentsize)--;
    // Percolate Down
    int kid = 1;
    for (int i = 1; i * 2 <= Mheap->currentsize; i = kid)
    {
        kid = i * 2;
        if (kid < Mheap->currentsize && Mheap->a[kid + 1] < Mheap->a[kid])
            kid++;
        if (Mheap->a[i] > Mheap->a[kid])
        {
            swap(&Mheap->a[i], &Mheap->a[kid]);
        }
        else
            break;
    }
    return minnode;

}
// Comparator function for qsort
int cmp(const void *a, const void *b)
{
    return strcmp(((Lexicon *)a)->code, ((Lexicon *)b)->code);
}

// Check if there is prefix issue among the codes
int check_prefix(int n)
{
    char *Huffcode1, *Huffcode2;
    qsort(encode, n, sizeof(Lexicon), cmp);
    for (int i = 1; i < n; i++)
    {
        Huffcode1 = encode[i].code;
        Huffcode2 = encode[i - 1].code;
        if (strncmp(Huffcode1, Huffcode2, strlen(Huffcode2)) == 0)
        {
            return 0;
        }
    }
    return 1;
}
// compute the cost of Huffman Code
int Huffman(int n){
    int cost = 0;
    for (int i = 1; i < n; i++)
    {

        int newNode = deletemin();
        newNode += deletemin();
        insert(newNode);
        cost += newNode;
    }
    return cost;
}

// Main function
int main(){
    int num;
    printf("Input case number:\n");
    scanf("%d", &num);
    char input[30];
    sprintf(input, "test_cases/case%d.txt", num);
    freopen(input, "r", stdin);

    int n,m;
    scanf("%d\n", &n);
    char letter;
    int frequency[max_char];
    // Allocate memory for Mheap
    Mheap = malloc(sizeof(struct Heap));
    Mheap->currentsize=0;
    int ans[max_stu]={0};
    for (int i = 0; i < n; i++)
    {
        scanf("%c %d", &letter, &frequency[i]);
        getchar();
        insert(frequency[i]);
    }
    // Compute the cost of optimal Huffman Code
    int cost=Huffman(n);
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
        // Check if the prefix issue exists and whether the submitted cost is the same with the optimal cost

        if (cost == cost_submit && check_prefix(n))
        {
            ans[i]=1;
        }
    }
    // Free memory when it is no longer needed
    free(Mheap);
    // Print result
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

