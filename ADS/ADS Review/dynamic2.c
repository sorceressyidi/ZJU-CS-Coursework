#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define infinity 999999999
/**
 * All pairs shortest path using dynamic programming
*/

void AllPairsShortestPath(int N, int A[][N],int M[][N]) {
    int i, j, k;
    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            M[i][j] = A[i][j];
        }
    }
    for (k = 0; k < N; k++){
        for (i = 0; i < N; i++){
            for (j = 0; j < N; j++){
                if (M[i][k] + M[k][j] < M[i][j]){
                    M[i][j] = M[i][k] + M[k][j];
                }
            }
        }
    }
}

int main() {
    int N = 4;
    int A[4][4] = {
        {0, 3, infinity, 7},
        {8, 0, 2, infinity},
        {5, infinity, 0, 1},
        {2, infinity, infinity, 0}
    };
    int M[N][N];
    AllPairsShortestPath(N, A, M);
    for(int k=0;k<N;k++){
        for(int l=0;l<N;l++){
            printf("%d ", M[k][l]);
        }
        printf("\n");
    }
    return 0;
}