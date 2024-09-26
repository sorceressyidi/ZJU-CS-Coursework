double calculate(double x){
    double sum = 0;
    for(double i=1;i<=10000;i++){
        sum += 1/(i*(i+1)*(i+2)*(i+x));
    }
    return sum;
}

void Series_Sum( double sum[] ){
    for(int i=0;i<300;i++){
        
    }
    for(int i = 0;i<3001;i++){
        sum[i]=0;
        double p = 0.1*(double)i;
        double fraction = calculate(p);
        sum[i]=(1-p)*(2-p)*fraction + 1+0.25*(1-p);
    }
}
