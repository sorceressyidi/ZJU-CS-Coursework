#include <stdio.h>

#define MAX_N 10

void Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[]);

double S( double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[] );

int main()
{
    int n, Type, m, i;
    double x[MAX_N], f[MAX_N], a[MAX_N], b[MAX_N], c[MAX_N], d[MAX_N];
    double s0, sn, Fmax, t0, tm, h, t;

    scanf("%d", &n);
    for (i=0; i<=n; i++) 
        scanf("%lf", &x[i]);
    for (i=0; i<=n; i++) 
        scanf("%lf", &f[i]);
    scanf("%d %lf %lf %lf", &Type, &s0, &sn, &Fmax);

    Cubic_Spline(n, x, f, Type, s0, sn, a, b, c, d);
    for (i=1; i<=n; i++)
        printf("%12.8e %12.8e %12.8e %12.8e \n", a[i], b[i], c[i], d[i]);

    scanf("%lf %lf %d", &t0, &tm, &m);
    h = (tm-t0)/(double)m;
    for (i=0; i<=m; i++) {
        t = t0+h*(double)i;
        printf("f(%12.8e) = %12.8e\n", t, S(t, Fmax, n, x, a, b, c, d));
    }

    return 0;
}

/* Your functions will be put here */

void Cubic_Spline(int n, double x[], double f[], int Type, double s0, double sn, double a[], double b[], double c[], double d[]){
    double h[MAX_N];
    double alpha[MAX_N];
    double l[MAX_N];
    double u[MAX_N];
    double z[MAX_N];
    for(int i=0;i<=n;i++){
        a[i+1]=f[i];
    }
    for(int i=0;i<n;i++){
        h[i]=x[i+1]-x[i];
    }    
    if(Type==1){
        alpha[0]=3*(f[1]-f[0])/h[0]-3*s0;
        alpha[n]=3*sn-3*(f[n]-f[n-1])/h[n-1];
    }
    for(int i=1;i<n;i++){
        alpha[i]=3/h[i]*(f[i+1]-f[i])-3/h[i-1]*(f[i]-f[i-1]);
    }
    l[0] = (Type == 1) ? 2 * h[0] : 1;
    u[0] = (Type == 1) ? 0.5 : 0;
    z[0] = (Type == 1) ? alpha[0] / l[0] : s0 / 2;
    for(int i=1;i<n;i++){
        l[i]=2*(x[i+1]-x[i-1])-h[i-1]*u[i-1];
        u[i]=h[i]/l[i];
        z[i]=(alpha[i]-h[i-1]*z[i-1])/l[i];
    }
    l[n] = (Type == 1) ? h[n - 1] * (2 - u[n - 1]) : 1;
    z[n] = (Type == 1) ? (alpha[n] - h[n - 1] * z[n - 1]) / l[n] : sn / 2;
    c[n + 1] = (Type == 1) ? z[n] : sn / 2;
    for(int j=n-1;j>=0;j--){
        c[j+1] =z[j]-u[j]*c[j+2];
        b[j+1] =(a[j+2]-a[j+1])/h[j]-h[j]*(c[j+2]+2*c[j+1])/3;
        d[j+1] =(c[j+2]-c[j+1])/(3*h[j]);
    }
}

double S( double t, double Fmax, int n, double x[], double a[], double b[], double c[], double d[] ){
    if(x[0]>t || x[n]<t){return Fmax;}
    int i=0;
    if(t==x[0]){i++;}
    for(;x[i]<t;i++);
    return a[i]+b[i]*(t-x[i-1])+c[i]*(t-x[i-1])*(t-x[i-1])+d[i]*(t-x[i-1])*(t-x[i-1])*(t-x[i-1]);
}