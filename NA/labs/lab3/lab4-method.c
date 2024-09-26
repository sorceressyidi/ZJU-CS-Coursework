#define Max_size 10000 /* max number of dishes */
void Price(int n,double p[]){
    double real[Max_size]={0};
    for(int j=0;j<100;j++){
        for (int i=0;i<n;i++){
            real[i]=(p[i] - (real[(i-1+n)%n]/2 + real[(i+1)%n]/2))/2;
        }
	}
    for(int i=0;i<n;i++){
		p[i]=real[i];
	}
}