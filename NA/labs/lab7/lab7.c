#include <stdio.h>
#include <math.h>
#include<string.h>
#define MAX_m 200
#define MAX_n 5

double f1(double x)
{
    return sin(x);
}

double f2(double x)
{
    return exp(x);
}

int OPA( double (*f)(double t), int m, double x[], double w[], double c[], double *eps );

void print_results( int n, double c[], double eps)
{    
    int i;

    printf("%d\n", n);
    for (i=0; i<=n; i++)
        printf("%12.4e ", c[i]);
    printf("\n");
    printf("error = %9.2e\n", eps);
    printf("\n");
}

int main()
{
    int m, i, n;
    double x[MAX_m], w[MAX_m], c[MAX_n+1], eps;

    m = 90;
    for (i=0; i<m; i++) {
        x[i] = 3.1415926535897932 * (double)(i+1) / 180.0;
        w[i] = 1.0;
    }
    eps = 0.001;
    n = OPA(f1, m, x, w, c, &eps);
    print_results(n, c, eps);

    m = 200;
    for (i=0; i<m; i++) {
        x[i] = 0.01*(double)i;
        w[i] = 1.0;
    }
    eps = 0.001;
    n = OPA(f2, m, x, w, c, &eps);
    print_results(n, c, eps);

    return 0;
}

double xi[MAX_m];
double yi[MAX_m];
double wi[MAX_m];
int size;
double PolySum(double* f,int F, double* g,int G){
    double mul=0;
    for (int i=0;i<size;i++){   
        double Fsum = 0;
        double Gsum = 0;
        for (int j=0;j<=MAX_n;j++){
            Fsum+=f[j]*pow(xi[i],j);
            Gsum+=g[j]*pow(xi[i],j);
        }   
        if(F==1){Fsum=yi[i];}
        if(G==1){Gsum=yi[i];}
         mul+= Fsum*Gsum*wi[i];
    }
    return mul;
}
int OPA( double (*f)(double t), int m, double x[], double w[], double c[], double *eps ){
    size=m;
    for(int i=0;i<m;i++){
        xi[i] = x[i];
        yi[i] = f(x[i]);
        wi[i] = w[i];
    }
    double p0[MAX_n+1]={0};
    double p1[MAX_n+1]={0};
    double p2[MAX_n+1]={0};
    double unused[MAX_n+1]={0};
    p0[0]=1;
    unused[0]=1;
    double a0=PolySum(p0,0,unused,1)/PolySum(p0,0,p0,0);
    for(int i=0;i<=MAX_n;i++){c[i]=a0*p0[i];}
    double error = PolySum(unused,1,unused,1)-a0*PolySum(p0,0,unused,1);
    double p0x[MAX_n+1]={0};
    memcpy(p0x+1,p0,MAX_n*sizeof(double));
    double B1=PolySum(p0x,0,p0,0)/PolySum(p0,0,p0,0);
    p1[0]=-B1;
    p1[1]=1;
    double a1=PolySum(p1,0,unused,1)/PolySum(p1,0,p1,0);
    c[0]+=a1*p1[0];
    c[1]+=a1*p1[1];
    error -= a1*PolySum(p1,0,unused,1);
    int cnt = 1;
    while(fabs(error)>=*eps&&cnt<MAX_n){
        cnt++;
        if(p1[MAX_n]!=0){*eps=error;return cnt;}
        p0x[0]=0;
        memcpy(p0x+1,p1,MAX_n*sizeof(double));
        double Bk=PolySum(p0x,0,p1,0)/PolySum(p1,0,p1,0);
        double Ck=PolySum(p0x,0,p0,0)/PolySum(p0,0,p0,0);
        p2[0]=0;
        memcpy(p2+1,p1,MAX_n*sizeof(double));
        for(int i=0;i<=MAX_n;i++){
            p2[i]=p2[i]-Bk*p1[i]-Ck*p0[i];
        }
        double a2 = PolySum(p2,0,unused,1)/PolySum(p2,0,p2,0);
        for(int i=0;i<=MAX_m;i++){
            c[i]+=a2*p2[i];
        }
        error -= a2*PolySum(p2,0,unused,1);
        memcpy(p0,p1,(MAX_n+1)*sizeof(double));
        memcpy(p1,p2,(MAX_n+1)*sizeof(double));
        
    }
    *eps=error;
    return cnt;
    
}
