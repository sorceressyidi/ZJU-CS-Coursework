#include <stdio.h>
#include <math.h>

#define ZERO 1e-13 /* X is considered to be 0 if |X|<ZERO */
#define MAXN 11    /* Max Polynomial Degree + 1 */


double cal(int n,double c[],double x){
    double result=0.0;
    for(int i=0;i<=n;i++){
        result += c[i]*pow(x,i);
    }
    return result;
}

double bisection(int n,double c[],double a,double b,double EPS){
    double mid;
    double left = cal(n,c,a);
    double right = cal(n,c,b);
    while(1){
        mid = a+(b-a)/2;
        double middle = cal(n,c,mid);
        if( (middle == 0)||fabs((b-a)/2)<EPS){return mid;}
        if( left*middle >0){
            a=mid;
            left = middle;
        }
        if(left*middle<0){
            b = mid;
            right = middle;
        }
    }
}

double Polynomial_Root(int n, double c[], double a, double b, double EPS){
    if (n==0||c[0]==0){
        double x0=0;
        return x0;
    }
    if(a>b){
        double t = a;
        a=b;
        b=t;
    }
    double c1[n];
    for(int i=0;i<n;i++){
        c1[i]=(i+1)*c[i+1];
    }
    double c2[n-1];
    for(int i=0;i<n-1;i++){
        c2[i]=(i+1)*c1[i+1];
    }
    double x0=a;
    if(cal(n,c,x0)==0){return x0;}
    double p0;
    double p;
    for(double j=0;j<2;j++){
        double b0 = a+(b-a)*j/2;
        p0 =bisection(n,c,a,b0,EPS);
        for(int q=0;q<200;q++){
        double re1=cal(n,c,p0);
        double re2=cal(n-1,c1,p0);
        double re3=cal(n-2,c2,p0);
        if(fabs(re2*re2-re1*re3)<ZERO){
            p0= p0+0.002;
            continue;
        }
        p =p0-(re1*re2)/(re2*re2-re1*re3);
        if(p>b||p<a){break;}
        if(fabs(p-p0)<EPS){return p;}
        p0=p;
        }
    }
    return p;
}



int main()
{
    int n;
    double c[MAXN], a, b;
    double EPS = 0.00005;
    int i;

    scanf("%d", &n);
    for (i=n; i>=0; i--) 
    scanf("%lf", &c[i]);
    scanf("%lf %lf", &a, &b);
    printf("%.4f\n", Polynomial_Root(n, c, a, b, EPS));

    return 0;
}

