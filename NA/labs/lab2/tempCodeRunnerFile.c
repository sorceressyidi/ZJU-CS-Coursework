double bisection(int n,double c[],double a,double b){
    double mid;
    double left = cal(n,c,a);
    double right = cal(n,c,b);
    for(int i=0;i<16;i++){
        mid = a+(b-a)/2;
        printf("%f\n",mid);
        double middle = cal(n,c,mid);
        if( (left*middle-0)>1e-10){
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