#include <stdio.h>
// !!!!! REPEATED ELEMENT!!!!!!!!
void percdown(int arr[], int position) {
    int temp = arr[0];
    int parent, son;
    for (parent=0; parent * 2 + 1 < position; parent = son) {
        son=parent * 2 + 1;
        if(son<position-1&&arr[son+1]>arr[son]){son++;}
        if (temp > arr[son]) {break;}
        else {arr[parent] = arr[son];}
    }
    arr[parent] = temp;
}

int main() {
    int n;
    scanf("%d", &n);
    int original[n];
    int sorting[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &original[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &sorting[i]);
    }
    int posi = 0;
    // If Insertion, find where the last insertion
    while(posi<n-1 && sorting[posi] <= sorting[posi + 1]){posi++;}/**Note!! <=!!!*/
    int posi1 = ++posi;
    while (posi1 < n && sorting[posi1] ==original[posi1]){posi1++;}
    if (posi1 == n) {
        int tmp = sorting[posi];
        int i;
        for (i=posi;i>0&&sorting[i-1]>tmp;i--) {sorting[i]=sorting[i-1];}
        sorting[i] = tmp;
        printf("Insertion Sort\n");
    }
    else{
        printf("Heap Sort\n");
        int posi2 =n-1;
        while (posi2 > 0 && sorting[posi2] > sorting[posi2 - 1]) {posi2--;}
        int tmp = sorting[0];
        sorting[0] = sorting[posi2];
        sorting[posi2] = tmp;
        percdown(sorting, posi2);
    }
    for (int i = 0; i < n; i++) {
        if(i){
            printf(" %d", sorting[i]);
        }
        else{
            printf("%d", sorting[i]);
        }
    }
    printf("\n");
    return 0;
}
