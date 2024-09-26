#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define infinity 999999999

void optmatrix(const long r[], int N, int M[][N]) {
    int i, j, k, L;
    long thisM;
    for (i = 1; i <=N; i++){
        M[i][i] = 0;
    }
    for(k=1;k<N;k++) {
        for(i=1;i<=N-k;i++){
            j = i+k;
            M[i][j] = infinity;
            for(L=i;L<j;L++){
                thisM = M[i][L] + M[L+1][j] + r[i-1]*r[L]*r[j];
                //M[i][L] is the cost of multiplying the matrices from i to L
                //M[L+1][j] is the cost of multiplying the matrices from L+1 to j
                //r[i-1]*r[L]*r[j] is the cost of multiplying the matrices from i to j
                //More specifically, r[i-1] is the number of rows of the matrix i, r[L] is the number of rows of the matrix L, and r[j] is the number of columns of the matrix j
                if(thisM < M[i][j]){
                    M[i][j] = thisM;
                }
            }
        }
    }
}
int main() {
    long r[] = {30, 35, 15, 5, 10, 20, 25};
    int N = sizeof(r)/sizeof(r[0]);
    int M[N][N];
    optmatrix(r, N, M);
    for(int k=0;k<N;k++){
        for(int l=0;l<N;l++){
            printf("%d ", M[k][l]);
        }
        printf("\n");
    }
    printf("%d\n", M[1][N-1]);
    return 0;
}
