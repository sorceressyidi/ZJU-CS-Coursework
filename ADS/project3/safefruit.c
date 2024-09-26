#include<stdio.h>
#include<string.h>
#define MAX 1000
/*
    The struct to store the fruit information
*/
typedef struct {
    int price;
    int id;
}Fruit;

int final_price = 0;        // The final price of the selected fruits
int final_sel[MAX] = {0};   // The final selected fruits
int current_sel[MAX] = {0};         // The current selected fruits
int max_num = 0;            // The maximum number of fruits that can be selected
int res[MAX] = {0};               // The maximum number of fruits that can be selected from subset which index from i to m
int m,n;                    // m kinds of fruits, n kinds of conflicts
int conflict[MAX][MAX] ={0};// conflict matrix
Fruit fruit[MAX];

/*
 Compare function for qsort
*/
int cmp(const void *a, const void *b){
    return *(int*)a - *(int*)b;
}

/*
    The recursive function to find the maximum number of fruits that can be selected
    cur: the current fruit index
    num: the number of fruits that have been selected
    price: the total price of the selected fruits
*/

void BronKerbosch(int cur, int num, int price){
    for(int i = cur; i>=0; i--){
        /*
            cut branches:
            1. Adding all the fruit that can be eaten together is still smaller than the current best choice
            2. Adding all the fruit remained can't produce better cost
            3. Adding all the fruit that can be eaten together can't produce better cost
            4. Adding all the fruit remained is still smaller than the current best choice
        */
        if(num + res[i] < max_num||(num + i+1 < max_num)|| (num + i == max_num && price >= final_price) || (num + res[i] == max_num && price >= final_price)){
            return;
        }
        for(int j = 0; j < m; j++){
            if(current_sel[j] && conflict[fruit[j].id][fruit[i].id]){
                goto next;
            }
        }
        current_sel[i] = 1;
        BronKerbosch(i-1, num+1, price+fruit[i].price);
        current_sel[i] = 0;
        next:;
    }
    if(num > max_num){
        max_num = num;
        final_price = price;
        memset(final_sel, 0, sizeof(final_sel));
        int count = 0;
        for(int i = 0; i < m; i++){
            if(current_sel[i]){
                final_sel[count++] = fruit[i].id;
            }
        }
    }else if(num == max_num && price < final_price){
        final_price = price;
        memset(final_sel, 0, sizeof(final_sel));
        int count = 0;
        for(int i = 0; i < m; i++){
            if(current_sel[i]){
                final_sel[count++] = fruit[i].id;
            }
        }
    }
}
int main(){
    scanf("%d %d", &n, &m);
    /* Read the conflict matrix */
    for(int i = 0; i < n; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        conflict[a][b] = 1;
        conflict[b][a] = 1;
    }
    /* Read the fruit information */
    for (int i = 0; i < m; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        fruit[i].id = a;
        fruit[i].price = b;
    }
    /*
        Enumerate all the fruits as the starting fruit and find the maximum number of fruits that can be selected.
    */
    for(int i = 0; i < m; i++){
        max_num = 0;
        final_price = 1e9;
        // Find the maximum number of fruits that can be selected from subset which index from 0 to i
        BronKerbosch(i,0,0);
        // Save the maximum number of fruits that can be selected from subset which index from 0 to i
        res[i] = max_num;
    }
    printf("%d\n", max_num);
    qsort(final_sel, max_num, sizeof(int), cmp);
    for(int i = 0; i < max_num-1; i++){
        printf("%03d ", final_sel[i]);
    }
    printf("%03d\n", final_sel[max_num-1]);
    printf("%d\n", final_price);
    return 0;
}

