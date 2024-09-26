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

double gx[MAX_m];
double gy[MAX_m];
double gw[MAX_m];
int gm;

double Polynomials_Sum(double* f,int flagf, double* g,int flagg)/*计算f(x)，g(y)的求和,flg表示后一个变量*/
{
    double ret = 0;
    for (int i = 0; i < gm; i++)
    {   
        double sumf = 0;
        double sumg = 0;
        for (int j = 0; j <= MAX_n; j++)
        {
            sumf +=  f[j] * pow(gx[i], j);
            sumg +=  g[j] * pow(gx[i], j);
        }   
        sumf = (flagf == 0) ? sumf : gy[i];
        sumg = (flagg == 0) ? sumg : gy[i];
        ret += gw[i] * sumg * sumf;
    }
    return ret;
}

int OPA(double (*f)(double t), int m, double x[], double w[], double c[], double* eps)
{
     gm = m;
    for (int i = 0; i < m; i++)
    {
        gx[i] = x[i];
        gw[i] = w[i];
        gy[i] = f(x[i]);
    }
    
    double phi0[MAX_n+1] = { 0 };
    double phi1[MAX_n+1] = { 0 };
    double phi2[MAX_n+1] = { 0 };
    phi0[0] = 1;

    double y[MAX_n+1] = {0};
    //y[1] = 1;

    double a0=Polynomials_Sum(phi0, 0,y,1) / Polynomials_Sum(phi0,0, phi0, 0);
    c[0] = a0;
    double error = Polynomials_Sum(y,1, y, 1) - a0*Polynomials_Sum(phi0,0, y,1 );
    
    double xphi0[MAX_n+1] = {0};
    xphi0[1]=1;

    double B1 = Polynomials_Sum(xphi0,0, phi0, 0) / Polynomials_Sum(phi0,0, phi0, 0);
    
    phi1[0] = -B1;
    phi1[1] = 1;

    a0 = Polynomials_Sum(phi1, 0, y, 1) / Polynomials_Sum(phi1,0, phi1, 0);
    c[0]+=a0*phi1[0];
    c[1]+=a0*phi1[1];
    double a = Polynomials_Sum(phi0,0,y,0)-Polynomials_Sum(y,1,y,0);

    error -= a0 * Polynomials_Sum(phi1,0, y, 1);
    int k = 1;
    
    while (k < MAX_n && fabs(error) >= *eps)
    {
        k++;
                if (phi1[MAX_n] != 0) {
            *eps = error;
            return k;
        }
        xphi0[0] = 0;
        memcpy(xphi0 + 1, phi1, MAX_n * sizeof(double));

        
        B1 = Polynomials_Sum(xphi0,0, phi1,0) / Polynomials_Sum(phi1,0, phi1, 0);
        
        double C1 = Polynomials_Sum(xphi0,0, phi0, 0) / Polynomials_Sum(phi0,0, phi0, 0);
        
        phi2[0] = 0;
        memcpy(phi2+1,phi1,MAX_n*sizeof(double));

        for (int i = 0; i <= MAX_n; i++)
            phi2[i] = phi2[i] - B1 * phi1[i] - C1 * phi0[i];
       
        double t1 = Polynomials_Sum(phi2, 0, y, 1);
        double t2 = Polynomials_Sum(phi2, 0, phi2, 0);
        a0 =  t1/t2 ;
        
        for (int i = 0; i <= MAX_n; i++)
            c[i] += a0 * phi2[i];
        
        error -= a0 * Polynomials_Sum(phi2,0, y, 1);
        for (int i = 0; i <= MAX_n; i++)
        {
            phi0[i] = phi1[i];
            phi1[i] = phi2[i];
        }    
    }
    *eps = error;
    return k;
}



double gx[MAX_m];
double gy[MAX_m];
double gw[MAX_m];
int gm;

double Polynomials_Sum(double* f,int flagf, double* g,int flagg)/*计算f(x)，g(y)的求和,flg表示后一个变量*/
{
    double ret = 0;
    for (int i = 0; i < gm; i++)
    {   
        double sumf = 0;
        double sumg = 0;
        for (int j = 0; j <= MAX_n; j++)
        {
            sumf +=  f[j] * pow(gx[i], j);
            sumg +=  g[j] * pow(gx[i], j);
        }   
        sumf = (flagf == 0) ? sumf : gy[i];
        sumg = (flagg == 0) ? sumg : gy[i];
        ret += gw[i] * sumg * sumf;
    }
    return ret;
}

int OPA(double (*f)(double t), int m, double x[], double w[], double c[], double* eps)
{
    for (int i = 0; i < m; i++)
    {
        gx[i] = x[i];
        gw[i] = w[i];
        gy[i] = f(x[i]);
        gm = m;
    }
    
    double phi0[MAX_n+1] = { 0 };
    double phi1[MAX_n+1] = { 0 };
    double phi2[MAX_n+1] = { 0 };
    phi0[0] = 1;

    double y[MAX_n+1] = {0};
    y[1] = 1;

    double a0=Polynomials_Sum(phi0, 0,y,1) / Polynomials_Sum(phi0,0, phi0, 0);
    
    for (int i = 0; i <= MAX_n; i++)
    {
        c[i] = phi0[i] * a0;
    }
    
    double error = Polynomials_Sum(y,1, y, 1) - a0 * Polynomials_Sum(phi0,0, y,1 );
    
    double xphi0[MAX_n+1] = {0};
    for (int i = 0; i < MAX_n; i++)
        xphi0[i+1] = phi0[i];

    double B1 = Polynomials_Sum(xphi0,0, phi0, 0) / Polynomials_Sum(phi0,0, phi0, 0);
    
    phi1[0] = -B1;
    phi1[1] = 1;

    a0 = Polynomials_Sum(phi1, 0, y, 1) / Polynomials_Sum(phi1,0, phi1, 0);
    for (int i = 0; i <= MAX_n; i++)
    {
        c[i] += a0 * phi1[i];
    }
    
    error -= a0 * Polynomials_Sum(phi1,0, y, 1);
    int k = 1;
    
    while (k < MAX_n && fabs(error) >= *eps)
    {
        k++;
        xphi0[0] = 0;
        for (int i = 0; i < MAX_n; i++)
            xphi0[i+1] = phi1[i];
        
        B1 = Polynomials_Sum(xphi0,0, phi1,0) / Polynomials_Sum(phi1,0, phi1, 0);
        
        double C1 = Polynomials_Sum(xphi0,0, phi0, 0) / Polynomials_Sum(phi0,0, phi0, 0);
        
        phi2[0] = 0;
        if (phi1[MAX_n] != 0) {
            *eps = error;
            return k;
        }
        for (int i = 0; i < MAX_n; i++)
            phi2[i + 1] = phi1[i];

        for (int i = 0; i <= MAX_n; i++)
            phi2[i] = phi2[i] - B1 * phi1[i] - C1 * phi0[i];
       
        double t1 = Polynomials_Sum(phi2, 0, y, 1);
        double t2 = Polynomials_Sum(phi2, 0, phi2, 0);
        a0 =  t1/t2 ;
        
        for (int i = 0; i <= MAX_n; i++)
            c[i] += a0 * phi2[i];
        
        error -= a0 * Polynomials_Sum(phi2,0, y, 1);
        for (int i = 0; i <= MAX_n; i++)
        {
            phi0[i] = phi1[i];
            phi1[i] = phi2[i];
        }    
    }
    *eps = error;
    return k;
}
