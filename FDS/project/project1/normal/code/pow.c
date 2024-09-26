#include<stdio.h>
#include<time.h>/*implement C's standard library time.h*/
clock_t start,stop;/*clock_t is a built-in type for processing time in ticks*/
double duration;/*duration is to keep record of run time of a funciton in seconds*/

//implement a function that calculate x^n using the given algorithm 2 recursively
double Pow_recursive(double x,int n){ 
    if(n==0){return 1;}
    else if (n%2==0){
        return Pow_recursive(x*x,n>>1);//if n is even,we have x^n = (x^(n/2))*(x^(n/2))
    }
    else{
        return Pow_recursive(x*x,n>>1)*x;//if n is odd,we have x^n = (x^(n/2))*(x^(n/2))*x 
    }
}

//implement a function that calculate x^n using the given algorithm 2 iteratively
double Pow_iterative(double x,int n){ 
    double re = 1;// Initialize the result to 1.
    while(n){
        // Check if the lowest bit of 'n' is set by performing a bitwise AND operation with 1.
        if(n&1){
            re *= x;
        }
        x=x*x;// Square 'x' for the next iteration to effectively reduce 'n' by half.
        n = n >> 1; // Right-shift 'n' by 1 bit, effectively dividing it by 2.
    }
    return re;// Return the final result, which is x raised to the power of n.
}

//implement a function that calculate x^n using bruteforce method
double Pow_brute(double x,int n){ 
    double temp = 1;
    for(int i = 0;i<n;i++){
        temp = temp*x;//in every iteration,temp is multipled by x,thus after n iterations we can get x^n
    }
    return temp;
}

// Testing program to test different values of 'n'
void testing_program(int n,double x) {
    //double x = 1.0001 ;
    double re;
    //Testing of algorithm 1
    start = clock();/*records the tick count at the start of the function*/
    for(int i=0;i<100000;i++){
        re = Pow_brute(x,n);
    }
    stop = clock();/*records the tick count at the end of the function*/
    duration =( (double)(stop-start))/CLOCKS_PER_SEC;/*calculate time duration and transforms it to be in seconds*/
    printf("The result is %lf,run time of algorithm 1 is %lf,tick is %lu\n",re,duration,stop-start);


    //Testing of algorithm2 recursively
    start = clock();
    for(int i=0;i<100000;i++){
        re = Pow_recursive(x,n);
    }
    stop = clock();
    duration =( (double)(stop-start))/CLOCKS_PER_SEC;
    printf("The result is %lf,run time of algorithm 2 recursively is %lf,tick is %lu\n",re,duration,stop-start);


    //Testing of algorithm2 iteratively;
    start = clock();
    for(int i=0;i<1000000;i++){
        re = Pow_iterative(x,n);
    }
    stop = clock();
    duration =( (double)(stop-start))/CLOCKS_PER_SEC;
    printf("The result is %lf,run time of algorithm 2 iteratively is %lf,tick is %lu\n",re,duration,stop-start);
}
int main() {
    int n;
    int b[8]= {1000, 5000, 10000, 20000, 40000, 60000, 80000, 100000};//Initialize test cases
    double x;
    printf("The value of x is ");
    scanf("%lf",&x);
    for (int i = 0;i<8;i++){
        n = b[i];
        printf("the value of n is %d \n",n);/*n = 1000, 5000, 10000, 20000, 40000, 60000, 80000, 100000*/
        testing_program(n,x);
    }
    return 0;
}