#include <stdio.h>
#include <stdlib.h> /*Function srand() and rand() are included in <stdlib.h>*/
#include <time.h>
#include "case.c"
clock_t start, stop; /*clock_t is a built-in type ffor processor time(ticks)*/
double duration;     /*records the run time(sec) of a function*/

/*you can change N and K to check the time*/
int N = 10;        /* It means the size of matrix */
int Circle = 7000; /* It means the times of circle, but don't be over 500000, otherwise it can't run.(because it will take lots of space)*/
/* Circle*N*N don't be over 500000*5*5=1250 0000 */

/* The function can generate a matrix randomly, and its size is N*N */
int MaxSubsequenceSum(const int a[], int N);         /* The function is the same as teacher's ppt: it can find a one-dimensional array's maximal subarray and its time complexity is O(N) */
int find_max_N6(int a[N][N], int width, int height); /* A algorithm whose time complexity is O(N^6) */
int find_max_N4(int a[N][N], int width, int height); /* A algorithm whose time complexity is O(N^4) */
int find_max_N3(int a[N][N], int width, int height); /* A algorithm whose time complexity is O(N^3) */

int main() /*It's the main test program's entry*/
{
    int answer;               /* It stores the maximum submatrix's sum */
    int *test_matrix[Circle]; /* Create K new N-SIZE matrixes randomly */
    for (int i = 0; i < Circle; i++)
        test_matrix[i] = (int *)new_matrix(N); /*The function is used to create new matrix*/

    start = clock(); /* record the ticks at the beginning of the unction call */

    for (int i = 0; i < Circle; i++)
        answer = find_max_N3(test_matrix[i], N, N);
    /* You can change the function's name and then run the code to find the difference of algorithm.
    Here are three function you can use:
    find_max_N6(test_matrix[i], N, N);
    find_max_N4(test_matrix[i], N, N);
    find_max_N3(test_matrix[i], N, N);
    */

    stop = clock();                                /* record the ticks at the end of the function call*/
    duration = ((double)(stop - start)) / CLK_TCK; /* Get the sec of the whole process*/
    /* CLK_TCK is a built-in constant = ticks per second*/
    printf("ticks = %d\n", stop - start);
    printf("duration=%f\n", duration);
    return 0;
}

int find_max_N6(int a[N][N], int width, int height)            /*A algorithm whose time complexity is O(N^6)*/
{                                                              /*The algorithm check all submatrix and compare the sum of all submatrix*/
    int ThisSum, MaxSum, begin_x, end_x, begin_y, end_y, x, y; /*Space complexity is O(1)*/
    MaxSum = 0;
    for (begin_x = 0; begin_x < width; begin_x++) /*Determine the begin_width of the submatrix*/
    {
        for (end_x = begin_x; end_x < width; end_x++) /*Determine the end_width of the submatrix*/
        {
            for (begin_y = 0; begin_y < height; begin_y++) /*Determine the begin_height of the submatrix*/
            {
                for (end_y = begin_y; end_y < height; end_y++) /*Determine the end_height of the submatrix*/
                {
                    ThisSum = 0; /*Now we get all information of the submatrix, then get the sum of the submatrix*/
                    for (x = begin_x; x <= end_x; x++)
                    {
                        for (y = begin_y; y <= end_y; y++) /*Check all item of the submatrix and get the sum of the submatrix*/
                        {
                            ThisSum += a[y][x];
                        }
                    }
                    if (ThisSum > MaxSum) /*If the submatrix's sum is larger than MaxSum, renew the MaxSum with ThisSum*/
                    {
                        MaxSum = ThisSum;
                    }
                }
            }
        }
    }
    return MaxSum;
}

int find_max_N4(int a[N][N], int width, int height) /*A algorithm whose time complexity is O(N^4)*/
{
    int LineSum, Sum[width], MaxSum, begin_y, begin_x, y, x; /*Space complexity is O(N)*/
    MaxSum = 0;
    for (begin_y = 0; begin_y < height; begin_y++) /*Determine the beginning y*/
    {
        for (begin_x = 0; begin_x < width; begin_x++) /*Determine the beginning x*/
        {                                             /*Then check all submatrix from (begin_x,begin_y) to (width-1,height-1)*/
            for (int i = 0; i < width; i++)
                Sum[i] = 0;                    /*Reset the array Sum[]*/
            for (y = begin_y; y < height; y++) /*Check all submatrix from (x,y) to (width-1,height-1)*/
            {
                LineSum = 0; /*It records the sum from (beginning x,y) to (x,y): the sum of a line*/
                for (x = begin_x; x < width; x++)
                {
                    LineSum += a[y][x];
                    Sum[x] = LineSum + Sum[x]; /*Sum[x] is equal to the sum of submatrix from (begin_x,begin_y) to (x,y)*/
                    if (Sum[x] > MaxSum)
                        MaxSum = Sum[x]; /*If the sum of submatrix from (begin_x,begin_y) to (x,y) is larger than MaxSum, renew MaxSum with Sum[j2]*/
                }
            }
        }
    }
    return MaxSum;
}

int MaxSubsequenceSum(const int a[], int N) /*The function is the same as teacher's ppt: it's used to find the max subarray of one-dimension array*/
{                                           /*And its time complexity is O(N)*/
    int ThisSum, MaxSum, x;
    ThisSum = MaxSum = 0;
    for (x = 0; x < N; x++)
    {
        ThisSum += a[x];
        if (ThisSum > MaxSum)
            MaxSum = ThisSum;
        else if (ThisSum < 0)
            ThisSum = 0;
    }
    return MaxSum;
}

int find_max_N3(int a[N][N], int width, int height) /* A algorithm whose time complexity is O(N^3) */
{
    int Sum[width], ThisSum, MaxSum, y, y1; /*space complexity is O(N)*/
    MaxSum = 0;
    for (y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
            Sum[x] = 0;                 /*Reset the array Sum[]*/
        for (y1 = y; y1 < height; y1++) /*Find the max-submatrix from a[y][0] to a[height-1][width-1]*/
        {
            for (int x = 0; x < width; x++)
                Sum[x] += a[y1][x];                  /*Sum[x] is equal to the sum of column from a[y][x] to a[y1][x]*/
            ThisSum = MaxSubsequenceSum(Sum, width); /*The function's time complexity is O(N)*/
            /*Get the max subarray of Sum[], it's equal to the sum of the max (y1-y+1)-height submatrix from a[y][0] to a[y1][width-1]*/
            if (ThisSum > MaxSum)
                MaxSum = ThisSum; /*If the sum of submatrix from (beginning x,beginning y) to (j2,j1) is larger than MaxSum, renew MaxSum with ThisSum*/
        }
    }
    return MaxSum;
}
