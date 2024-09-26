#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *input;
int *wolves;
int *identities;

int check(int N, int M, int L) {
    int *liers = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        identities[i] = 1;
    }
    for (int i = 0; i < M; i++) {
        identities[wolves[i]] = -1;
    }
    for (int i = 0; i < N; i++) {
        int identity = identities[abs(input[i])] * input[i];
        identities[abs(input[i])] = identity;
    }
    int liers_count = 0;
    for (int i = 0; i < N; i++) {
        int claim = input[i] / abs(input[i]);
        int identity = identities[abs(claim)];
        if (claim != identity) {
            liers[liers_count++] = i + 1;
        }
    }
    if (liers_count == L) {
        int w = 0;
        for (int i = 0; i < liers_count; i++) {
            if (identities[liers[i]] < 0) {
                w++;
            }
        }
        if (w > 0 && w < M) {
            return 1;
        }
    }
    free(liers);
    return 0;
}

int BT(int N, int M, int L, int last) {
    if (M == 0) {
        if (check(N, M, L)) {return 1;}
        return 0;
    }
    else {
        while (last) {
            wolves[M - 1] = last;
            if (BT(N, M - 1, L, last - 1)) {
                return 1;
            }
            else {
                wolves[M - 1] = 0;
            }
            last--;
        }
    }
    return 0;
}

int main() {
    int M, N, L;
    scanf("%d %d %d", &N, &M, &L);
    input = (int *)malloc(N * sizeof(int));
    wolves = (int *)malloc(M * sizeof(int));
    identities = (int *)malloc((N + 1) * sizeof(int));

    for (int i = 0; i < N; i++) {
        scanf("%d", &input[i]);
    }

    if (BT(N, M, L, N)) {
        for (int i = 0; i < M; i++) {
            printf("%d ", wolves[i]);
        }
        printf("\n");
    }

    else {
        printf("No Solution\n");
    }
    free(input);
    free(wolves);
    free(identities);
    return 0;
}
