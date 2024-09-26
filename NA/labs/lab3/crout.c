
#include <stdio.h>

#define Max_size 10000 /* max number of dishes */

void Price( int n, double p[] );

int main()
{
    int n, i;
    double p[Max_size];

    scanf("%d", &n);
    for (i=0; i<n; i++) 
        scanf("%lf", &p[i]);
    Price(n, p);
    for (i=0; i<n; i++)
        printf("%.2f ", p[i]);
    printf("\n");

    return 0;
}

void crout(double* b, int n,double* x){
    //只需记录u非对角元素
	double z[Max_size]; 
    double u[Max_size];
    u[0]= 0.25;
    z[0]=b[0]/2;
    
    //Lz=b
    double lii;//l的对角元
    for(int i=1;i<n-1;i++){
        lii = 2-0.5*u[i-1];
        u[i]= 0.5/lii;
        z[i]=(b[i]-0.5*z[i-1])/lii;
    }
    lii=2-0.5*u[n-2];
    z[n-1]=(b[n-1]-0.5*z[n-2])/lii;
    x[n-1]=z[n-1];
    for(int i=n-2;i>=0;i--){
        x[i]=z[i]-u[i]*x[i+1];
    }
}


void Price( int n, double p[] ){
	double c[Max_size]={0};
	c[0]=c[n-2]=-0.5;
    double u[Max_size],v[Max_size],x[Max_size];;
    crout(p,n-1,v);
	crout(c,n-1,u);
	x[n-1]=(p[n-1]-0.5*v[0]-0.5*v[n-2])/(2+0.5*u[0]+0.5*u[n-2]);
    p[n-1]=x[n-1];
	for(int j=0;j<n-1;j++){
		x[j]=u[j]*x[n-1]+v[j];
        p[j]=x[j];
	}
}
