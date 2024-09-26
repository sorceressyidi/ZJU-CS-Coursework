#include <stdio.h>

void Series_Sum( double sum[] );

int main()
{
    int i;
    double x, sum[3001];
    
    Series_Sum( sum );

    x = 0.0;
    for (i=0; i<3001; i++)
        printf("%6.2f %16.12f\n", x + (double)i * 0.10, sum[i]);

    return 0;
}

double integer(int x){
    double sum = 0.00;
    for(int i=1;i<=x;i++){
        sum += 1.00/i;
    }
    return sum/(double)x;
}
double calculate(double x,int p){
    double sum = 0.0;
    for(int i=1;i<=1500;i++){
        sum += 1.0/(i*(i+p)*(i+p+1)*(i+x)*(i+p+2));
    }
    return sum;
}
void Series_Sum( double sum[] ){
    int fra;
    for(int i=1;i<=300;i++){
        sum[i*10]=integer(i);
    }
    sum[0]= 1.644934066848;
    for (int i=1;i <= 3000;i++){
        double x = i*0.1;
        if(i%10==0){
            continue;
        }
        if(i<2980){ 
            fra = i/10+1;
        }
        else{fra = i/10-1;}
        double sum_index = calculate(x,fra);
        sum[i]=(fra-x)*((fra- x+ 1)*(sum_index*(fra-x+2)+(sum[fra*10]+sum[fra*10+20]-2*sum[fra*10+10])/2) + sum[fra*10] - sum[fra*10 + 10]) + sum[fra*10];
    }
}