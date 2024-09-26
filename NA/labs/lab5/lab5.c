#include <stdio.h>

#define MAX_SIZE 10

int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN);

int main()
{
    int n, MAXN, m, i, j, k;
    double a[MAX_SIZE][MAX_SIZE], v[MAX_SIZE];
    double lambda, TOL;

    scanf("%d", &n);
    for (i=0; i<n; i++) 
        for (j=0; j<n; j++) 
            scanf("%lf", &a[i][j]);
    scanf("%lf %d", &TOL, &MAXN);
    scanf("%d", &m);
    for (i=0; i<m; i++) {
        scanf("%lf", &lambda);
        for (j=0; j<n; j++)
            scanf("%lf", &v[j]);
        switch (EigenV(n, a, &lambda, v, TOL, MAXN)) {
            case -1: 
                printf("%12.8f is an eigenvalue.\n", lambda );
                break;
            case 0:
                printf("Maximum number of iterations exceeded.\n");
                break;
            case 1:
                printf("%12.8f\n", lambda );
                for (k=0; k<n; k++)
                    printf("%12.8f ", v[k]);
                printf("\n");
                break;
        }
    }

    return 0;
}

#include<math.h>

int Getindex(double v[],int n ){
    double max = fabs(v[0]);
    int index = 0;
    for(int i=1;i<n;i++){
        if(fabs(v[i])>max){
            max=fabs(v[i]);
            index = i;
        }
    }
    return index;
}

int LU_factorization(double L[][MAX_SIZE],double U[][MAX_SIZE],int n,double a[][MAX_SIZE]){
    for (int i = 0; i < n; i++){
        L[i][i] = 1;
        for (int j = i; j < n; j++){
            double sum = 0;
            for (int k = 0; k < i; k++){
                sum += L[i][k] * U[k][j];
            }
            U[i][j] = a[i][j] - sum;
        }
        if (U[i][i] == 0){return -1;}
        for (int j = i + 1; j < n; j++){
            double sum = 0;
            for (int k = 0; k <i; k++){
                sum += L[j][k] * U[k][i];
            }
            L[j][i] = (a[j][i] - sum) / U[i][i];
        }
    }
    return 0;
}

int Solve_LU(double L[][MAX_SIZE],double U[][MAX_SIZE],int n,double x[],double b[]){
    double y[MAX_SIZE] = {0};
    y[0] = b[0];
    for (int i = 1; i < n; i++){
        double sum = 0;
        for (int j = 0; j < i; j++)
        {
            sum += L[i][j] * y[j];
        }
        y[i] = b[i] - sum;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (U[i][i] == 0) {return -1;}
        double sum = 0;
        for (int j = i+1; j < n; j++)
        {
            sum += U[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }
    return 0;
}
int EigenV(int n, double a[][MAX_SIZE], double *lambda, double v[], double TOL, int MAXN){
    double y[MAX_SIZE]={0};
    double b[MAX_SIZE][MAX_SIZE]={0};

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j){
                b[i][j]=a[i][j]-*lambda;
            }
            else{
                b[i][j]=a[i][j];
            }
        }
    }
    int index = Getindex(v,n);
    double max = v[index];
    double L[MAX_SIZE][MAX_SIZE]={0};
    double U[MAX_SIZE][MAX_SIZE]={0};
    int flag = LU_factorization(L,U,n,b);

    if(flag==-1){return -1;}
    for(int i=0;i<n;i++){
        v[i]/=max;
    }
    for(int k=1;k<=MAXN;k++){
        int q=Getindex(v,n);
        double z = v[q];
        if(Solve_LU(L,U,n,y,v) == -1){return -1;}
        index = Getindex(y,n);
        double u = y[index];
        double error[MAX_SIZE];
        for(int i=0;i<n;i++){error[i] = v[i]-y[i]/y[index];}
        for(int i=0;i<n;i++) v[i] = y[i]/y[index];

        index = Getindex(error,n);
        if (fabs(error[index]) < TOL)
        {
            *lambda =(z/u) + *lambda;
            return 1;
        }
    }
    return 0;
}