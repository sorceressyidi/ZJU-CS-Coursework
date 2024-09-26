
#include <stdio.h>
#include <math.h>

#define MAX_SIZE 10
#define bound pow(2, 127)
#define ZERO 1e-9 /* X is considered to be 0 if |X|<ZERO */

int Jacobi( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );

int Gauss_Seidel( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN );

int main()
{
    int n, MAXN, i, j, k;
    double a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE], x[MAX_SIZE];
    double TOL;

    scanf("%d", &n);
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++)
            scanf("%lf", &a[i][j]);
        scanf("%lf", &b[i]);
    }
    scanf("%lf %d", &TOL, &MAXN);

    printf("Result of Jacobi method:\n");
    for ( i=0; i<n; i++ )
        x[i] = 0.0;
    k = Jacobi( n, a, b, x, TOL, MAXN );
    switch ( k ) {
        case -2:
            printf("No convergence.\n");
            break;
        case -1: 
            printf("Matrix has a zero column.  No unique solution exists.\n");
            break;
        case 0:
            printf("Maximum number of iterations exceeded.\n");
            break;
        default:
            printf("no_iteration = %d\n", k);
            for ( j=0; j<n; j++ )
                printf("%.8f\n", x[j]);
            break;
    }
    printf("Result of Gauss-Seidel method:\n");
    for ( i=0; i<n; i++ )
        x[i] = 0.0;
    k = Gauss_Seidel( n, a, b, x, TOL, MAXN );
    switch ( k ) {
        case -2:
            printf("No convergence.\n");
            break;
        case -1: 
            printf("Matrix has a zero column.  No unique solution exists.\n");
            break;
        case 0:
            printf("Maximum number of iterations exceeded.\n");
            break;
        default:
            printf("no_iteration = %d\n", k);
            for ( j=0; j<n; j++ )
                printf("%.8f\n", x[j]);
            break;
    }

    return 0;
}

/* Your function will be put here */




int change(double a[][MAX_SIZE] ,double b[],int n){
    for(int j=0;j<n;j++){
        double MAX = fabs(a[j][j]);
        int num = j;
        for(int i=j;i<n;i++){
            if(fabs(a[i][j])>MAX){
                MAX=a[i][j];
                num = i;
            }
        }
        int num2=0;
        if (MAX==0){
            for(int i =0;i<j;i++){
                if(fabs(a[i][j])>MAX){
                    MAX = fabs(a[i][j]);
                    num2 = j;
                }
            }
            if (MAX==0){return 0;}
            for(int q=0;q<n;q++){
                a[j][q] += a[num2][q];
                b[j]+=b[num2];
            }
        }
        else{
            if(num==j){continue;}
            for(int q=0;q<n;q++){
                double tmp = a[j][q];
                a[j][q]=a[num][q];
                a[num][q]= tmp;
            }
            double tmp = b[j];
            b[j] = b[num];
            b[num] = tmp;
        }
    }
    return 1;
}

int Jacobi( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN ){
    if(!change(a,b,n)){return -1;}
    double x1[MAX_SIZE];
    int k = 1;
    double ERROR;
    while(k<=MAXN){
        for(int i=0;i<n;i++){
            double sum = 0.0;
            for(int j=0;j<n;j++){
                if(j==i){continue;}
                sum -=x[j]*a[i][j];
            }
            x1[i]=(b[i]+sum)/a[i][i];
        }
        ERROR = fabs(x1[0]-x[0]);
        for(int i=0;i<n;i++){
            if(fabs(x1[i]-x[i])>ERROR){ERROR=fabs(x1[i]-x[i]);}
            else if(fabs(x1[i])>bound){return -2;}
            x[i]=x1[i];
        }
       if (ERROR < TOL){return k;}
       k++;
    }
   return 0;
}

int Gauss_Seidel( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN ){
    if(!change(a,b,n)){return -1;}
    int k = 1;
    double x1[MAX_SIZE];
    double ERROR;
    while(k<=MAXN){
        for(int i=0;i<n;i++){
            double sum = 0.0;
            for(int j=0;j<i;j++){
                sum -= a[i][j] * x1[j];
            }
            for(int j=i+1;j<n;j++){
                sum -= a[i][j] * x[j];
            }
            x1[i]=(sum+b[i])/a[i][i];
        }
        ERROR = fabs(x1[0]-x[0]);
        for(int i=0;i<n;i++){
            if(fabs(x1[i]-x[i])>ERROR){ERROR=fabs(x1[i]-x[i]);}
            else if(fabs(x1[i])>bound){return -2;}
            x[i]=x1[i];
        }
       if (ERROR < TOL){return k;}
       k++;
    }
    return 0;
}



