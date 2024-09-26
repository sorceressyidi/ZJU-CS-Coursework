/*Import required libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* define processor time (ticks) */
clock_t start, stop;
/* define the interation(K) and number of N */
const int N = 100;
const int K = 10000;
/*Declear needed functions*/
int MaxSubSum1( int (*A)[N], int N );
int MaxSubSum2( int (*A)[N], int N );
int MaxSubSum3( int (*A)[N], int N );
int main ()
{
	int i, j; 
	/* define the 2-dimensional array and max */
    int A[N][N],max1 = 0;
    /* records the duration and runtime of a function */
	double duration , times;
	/* get the Random number */
    srand(time(0));
    /* generate the array elements randomly */
    for (i = 0; i < N; i++) 
	{
        for (j = 0; j < N; j++) 
		{
			/* Assuming the generated random number range is between -50 and 50 */
            A[i][j] = rand()%100-50; 
            /* output the generated array */
            printf("%d ",A[i][j]);
        }
        /* change the line */
        printf("\n");
    }
	/* records the ticks at the start of the function call */
	start = clock();
	/* iterate K times to obtain a more accurate duration*/

	for (i = 0; i < K; i++)
	{
		/* change the function if needed*/
		max1 = MaxSubSum1(A, N);		
	}
	/* records the ticks at the end of the function call */
	stop = clock();
	/* use CLK_TCK to get the total time */
	times = ((double)(stop-start))/CLOCKS_PER_SEC;
	/* times / K is the value of duration */	
	duration = times / K;
	/* output */
	printf("time1=%f\niterations1=%d\nticks1=%d\nduration1=%f\nmax1=%d\n",times,K,stop-start,duration,max1);
	/* records the ticks at the start of the function call */
	start = clock();
	/* iterate K times to obtain a more accurate duration*/
	for (i = 0; i < K; i++)
	{
		/* change the function if needed*/
		max1 = MaxSubSum2(A, N);		
	}
	/* records the ticks at the end of the function call */
	stop = clock();
	/* use CLK_TCK to get the total time */
	times = ((double)(stop-start))/CLOCKS_PER_SEC;
	/* times / K is the value of duration */	
	duration = times / K;
	/* output */
	printf("time2=%f\niterations2=%d\nticks2=%d\nduration2=%f\nmax2=%d\n",times,K,stop-start,duration,max1);
	/* records the ticks at the start of the function call */
	start = clock();
	/* iterate K times to obtain a more accurate duration*/
	for (i = 0; i < K; i++)
	{
		/* change the function if needed*/
		max1 = MaxSubSum3(A, N);		
	}
	/* records the ticks at the end of the function call */
	stop = clock();
	/* use CLK_TCK to get the total time */
	times = ((double)(stop-start))/CLOCKS_PER_SEC;
	/* times / K is the value of duration */	
	duration = times / K;
	/* output */
	printf("time3=%f\niterations3=%d\nticks3=%d\nduration3=%f\nmax3=%d\n",times,K,stop-start,duration,max1);
	system("pause");
	return 0;
}


/* algorithm 1 */
/*simply traverse the matrix */ 
int MaxSubSum1( int (*A)[N], int N )
{
	/* initiate the varibles */
	int ThisSum = 0, MaxSum = 0, i, j, k, l, m, n;
	/* [i] control the row of start position  */
	for( i = 0; i < N; i++ )
	{
		/* [j] control the column of start position */
		for( j = 0; j < N; j++ )
		{
			/* [k] control the row of end position */
			for( k = i; k < N; k++ )
			{
				/* [l] control the column of end position */
				for( l = j; l < N; l++ )
				{
					/* ThisSum is the sum of chosen submatrix */
					ThisSum = 0;
					/* add the member of submatrix to ThisSum */
					/* Traverse submatrix */
					for( m = i; m <= k; m++ )
					{
						for( n = j; n <= l; n++ )
						{
							ThisSum += A[m][n];
						}
					}
					/* compare with the max */
					if( ThisSum > MaxSum )
						MaxSum = ThisSum;
				}
			}
		}
	}
	return MaxSum;
}


/* algorithm 2 */
/* traverse the matrix but with some skill to minimize the procedure of add */ 
int MaxSubSum2( int (*A)[N], int N )
{
	/* initiate the varibles */
	int MaxSum = 0, i, j, k, l;
	/* set a 2 dimensional array to store the sum calculated by former loop */
	int sum[N][N];
	/* [i] control the row of start position  */
	for( i = 0; i < N; i++ )
	{
		/* [j] control the column of start position */
		for( j = 0; j < N; j++ )
		{
			/* [k] control the row of end position */
			for( k = i; k < N; k++ )
			{
				/* [l] control the column of end position */
				for( l = j; l < N; l++ )
				{
					/* sum[k][l] store the sum from [i][j] to [k][l] */
					/* when no former loop start */
					if( k == i && l == j)
					{
						/* sum[k][l] equals A[k][l] */
						sum[k][l] = A[k][l];
					}
					/* when no sum[k-1][l],namely the first row */
					else if ( k == i)
					{
						/* sum[k][l] equals the left sum plus A[k][l] */ 
						sum[k][l] = sum[k][l-1] + A[k][l];
					}
					/* when no sum[k][l-1],namely the first column */
					else if ( l == j)
					{
						/* sum[k][l] equals the upper sum plus A[k][l] */
						sum[k][l] = sum[k-1][l] + A[k][l];
					}
					else
					{
						/* upper sum plus left sum plus minus repeted part and add new part */
						sum[k][l] = sum[k-1][l] + sum[k][l-1] - sum[k-1][l-1] + A[k][l];
					}
					/* compare */
					if( sum[k][l] > MaxSum )
						MaxSum = sum[k][l];
				}
			}
		}
	}
	return MaxSum; 
}


/* algorithm 3 */
/* compress the 2-dimensional array into 1-dimensional array,use algorithm 4 in book to solve */
int MaxSubSum3( int (*A)[N], int N )
{
	/* initiate the varibles */
	int MaxSum = 0, ThisSum = 0, i, j, k, l;
	/* set a 1-dimensional array to store the sum of value in one column */
	int B[N];
	/* [i] control the start line of submatrix */
	for( i = 0; i < N; i++)
	{
		/* initiate the storeage */
		for( l = 0; l < N; l++)
		{
			B[l]=0;
		} 
		/* [j] control the end row of submatrix */
		for( j = i; j < N; j++)
		{
			/* initiate the sum for 1-dimensional array */
			ThisSum = 0;
			/* from the first column to N row */
			/* Traverse the new row */
			for( k = 0; k < N; k++)
			{
				/* since B[k] has already stored the sum of value in one column before line j */
				/* if we wanna get the value of B[k],just add the value of A[j][k] */ 
				B[k] += A[j][k];
				ThisSum += B[k];
				/* compare */
				if( ThisSum > MaxSum)
					MaxSum = ThisSum;
				/* if less than 0,the former part is useless */
				else if(ThisSum < 0 )
					ThisSum = 0;
			}
		}
	}
	return MaxSum;
}
