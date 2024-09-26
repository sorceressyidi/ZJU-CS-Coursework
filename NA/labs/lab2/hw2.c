#include<stdio.h>
#include<math.h>
double cal(int n,double c[],double x){
    double result=0.0;
    for(int i=0;i<=n;i++){
        result += c[i]*pow(x,i);
    }
    return result;
}


double bisection(int n,double c[],double a,double b){
    double mid;
    double left = cal(n,c,a);
    double right = cal(n,c,b);
    for(int i=0;i<16;i++){
        mid = a+(b-a)/2;
        printf("%f\n",mid);
        double middle = cal(n,c,mid);
        if( left*middle >0){
            a=mid;
            left = middle;
        }
        else{
            b = mid;
            right = middle;
        }
    }
    return mid;
}
int main(){
    double c[4] ;
    c[0]=-1;
    c[1]=-1;
    c[2]=0;
    c[3]=1;
    double re = bisection(3,c,1,2);
   
}