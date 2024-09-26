#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define MAXN 100

int main(){
    int i, j, N, M;
    char input[30];
/*
//  case 1: --------------------------------------------------
    sprintf(input, "input1.txt");
    FILE* data = fopen(input, "w");
    M = 100;    
    N = M;
    fprintf(data, "%d %d\n", N, M);

    for(i = 0; i < N - 1; i ++) {
        fprintf(data,"%.3d %.3d\n", i + 1, i + 2);
    }
    fprintf(data,"%.3d 001\n", N);

    // price
    srand((unsigned)time(NULL));
    for(i = 0; i < M; i ++) {
        int k=rand()%1000;
        fprintf(data,"%.3d %d\n", i + 1, k);
    }
    fclose(data);

 //case 2: --------------------------------------------------
    sprintf(input, "input2.txt");
    data = fopen(input, "w");
    M = 100;
    N = 0;
    fprintf(data, "%d %d\n", N, M);
    // price
    srand((unsigned)time(NULL));
    for(i = 0; i < M; i ++) {
        int k=rand()%1000;
        fprintf(data,"%.3d %d\n", i + 1, k);
    }
    fclose(data);


//case 3: --------------------------------------------------
    sprintf(input, "input3.txt");
    data = fopen(input, "w");
    M = 100;
    N = M*(M-1)/2;
    fprintf(data, "%d %d\n", N, M);
    // conflict
    for(i = 0; i < M; i ++) {
        for(j = i+1; j < M; j ++) {
            fprintf(data,"%.3d %.3d\n", i + 1, j + 1);
        }
    }
    // price
    srand((unsigned)time(NULL));
    for(i = 0; i < M; i ++) {
        int k=rand()%1000;
        fprintf(data,"%.3d %d\n", i + 1, k);
    }
    fclose(data);
 */
 //case 4: --------------------------------------------------

    sprintf(input, "input4.txt");
    FILE* data = fopen(input, "w");
    M = 100;
    N = M ;
    fprintf(data, "%d %d\n", N, M);
    // conflict
    srand((unsigned)time(NULL));
    int n1[MAXN],n2[MAXN];
    for(i = 0; i < N; i ++) {
        int a = rand() % M + 1;
        int b = rand() % M + 1;
        if(a == b) continue;
        n1[i] = a;
        n2[i] = b;

        //garantee the connection is not duplicated
        for(j = 0;j < i;j ++)
            if(a == n1[j] && b == n2[j]) {
                i--;break;
            }
        fprintf(data,"%.3d %.3d\n", a, b);
    }
    // price
    srand((unsigned)time(NULL));
    for(i = 0; i < M; i ++) {
        int k=rand()%1000;
        fprintf(data,"%.3d %d\n", i + 1, k);
    }
    fclose(data);
/*
//case 5: --------------------------------------------------
    sprintf(input, "input5.txt");
    data = fopen(input, "w");
    M = 0;
    N = 0;
    fprintf(data, "%d %d\n", N, M);
    fclose(data);
*/
    return 0;
}