<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><center><font size = 7>Project 1: Performance Measurment Of POW</font></center>



<center><font size = 6>Author : 张祎迪</font></center> 

<br>

<center><font size = 4.5>Date:2023-10-03</center></font>

<div STYLE="page-break-after: always;"></div>

## $Chapter 1: Introduction$
Designed to analyze and contrast the efficiency of different algorithms for the computation of exponential values,this project assesses how each algorithm performs according to execution time when computing exponentiation for various values of n,which will offer valuable insights into the effectiveness and efficiency of these algorithms.
## $Chapter 2:  Algorithm Specification$
* Full code is presented at the end of this PDF document and also submitted in the code directory.
### Algorithm 1 :brute-force approach
* pseudo-code
	
	<font size =1>
	
	```C
	function Pow_brute(x, n)
	    temp = 1
	    for i from 1 to n 
	        temp = temp * x//in every iteration,temp is multipled by x,thus after n iterations we can get x^n
	    end for
	    return temp
	end function
	```

</font>

* code in C:
	
	<font size =1>
	
	```C
	double Pow_brute(double x,int n){ 
	    double temp = 1;
	    for(int i = 0;i<n;i++){
	        temp = temp*x;//in every iteration,temp is multipled by x,thus after n iterations we can get x^n
	    }
	    return temp;
	}
	```

</font>

> This function takes the input 'x' as base ,and the input n as the exponent. It creates a temporary variable temp, repeatedly  performs `temp = temp * x` n times, and temp gets the value of x raised to the power of n when the loop ends. 

> Straightforward as it is ,this algorithm may not be efficient for large exponents and can take quite a long time running.
#### time complexity：

In every loop,`temp = temp*x` is calculated ,and there are n loops , so the algorithm has a time complexity of `O(n)`, with its running time increasing linearly when calculating large exponents.
#### space complexity:

The function requires constant space regardless of the value of n, thus space complexity is`O(1)`.

<div STYLE="page-break-after: always;"></div>

### Algorithm 2.1:calculating recursively

* pseudo-code
	
	<font size = 1>
	
	```C
	function Pow_recursive(x, n)
	    if n == 0 then
	        return 1
	    else if n % 2 == 0 then
	        return Pow_recursive(x * x, n >> 1) // if n is even, we have x^n = (x^(n/2)) * (x^(n/2))
	    else
	        return Pow_recursive(x * x, n >> 1) * x // if n is odd, we have x^n = (x^(n/2)) * (x^(n/2)) * x
	    end if
	end function
	```
	
	</font>
	
* code in C
	
	<font size = 1>
  
  ```C
  double Pow_recursive(double x,int n){ 
        if(n==0){return 1;}
        else if (n%2==0){
            return Pow_recursive(x*x,n>>1);//if n is even,we have x^n = (x^(n/2))*(x^(n/2))
        }
        else{
            return Pow_recursive(x*x,n>>1)*x;//if n is odd,we have x^n = (x^(n/2))*(x^(n/2))*x 
	      }
	  }
	```

</font>

> This function takes the input 'x' as base ,and the input n as the exponent. 

> If n is 0, the function returns 1 in that any random number raised to the power of 0 is 1.

> If n is even, n will be divided by 2 and the function recursively calls itself with the input x squared and the halved n according to the principle $x^{2n}=(x^{2})^{n}$.

> If n is odd, n will be divided by 2 and the function recursively calls itself with the input x squared and the halved n, at the same time the result is multiplied by x according to the principle $x^{2n+1}=(x^{2})^{n}*x$.

> This algorithm exploits recursion and the divide-and-conquer strategy to calculate more efficiently.
#### time complexity：
In each recursive call ,n is halved, until finally calling Pow\_recursive($x*x$, 1) before returning the result.Thus, the height of the recursive tree is $log_{2}n$.

The overall time complexity can be written as:`T(n) = T(n/2) + O(1)`and according to the $Master$ $Theorem$, the algorithm's time complexity is `O(log n)`. Therefore, it is highly efficient, especially when dealing with large exponents.

#### space complexity:
In each recursive call, certain memory space is allocated.Since recursive calls form a recursive tree, the space complexity of the algorithm can be expressed as `O(logn)` as analyzed above.

<div STYLE="page-break-after: always;"></div>

### Algorithm 2.2:calculating iteratively

* pseudo-code
	
	<font size = 1>
	
	```C
	function Pow_iterative(x, n)
	    re = 1 // Initialize the result to 1
	    while n is not zero
	        // Check if the lowest bit of 'n' is set,which is,if 'n' is odd.
	        if n is odd
	            re = re * x
	        end if
	        x = x * x // Square 'x' for the next iteration to effectively reduce 'n' by half
	        n = n >> 1 // Right-shift 'n' by 1 bit, effectively dividing it by 2
	    end while
	    return re // Return the final result, which is x raised to the power of n
	end function
	```
	
	</font>
	
* code in C
	
	<font size = 1>
	
	```C
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
	```

</font>

> This function takes the input *x* as base ,and the input *n* as the exponent.
> After initializing the temporary variable *re* to 1, the function enters the *while loop* which iteratively calculate the desired result.

> According to the law :
> > $$n(decimal)=b[k]b[k-1]...b[2]b[1]b[0](binary)$$
> > $x^{n}=x^{2^{0}*b[0]}$ x $x^{2^{1}*b[1]}$ x $x^{2^{2}*b[2]}$ x …… x$x^{2^{k}*b[k]}$

> In each loop:
> > we check if the lowest bit of 'n' is set, which is, if 'n' is odd by performing a bitwise AND operation with 1 and if 'n' is odd, we multiply 're' by 'x'.
> > Then, square 'x' to get $x^{2^{n+1}}$(suppose in the nth loop)and right-shift 'n' by 1 bit to divide it by 2.

> Continue the loop until 'n' is zero, getting the result of $x^{n}$.

#### time complexity:
In each loop, processing time for each bit of exponent n is constant and does not depend on the size of n.

For the integer exponent n, (as analyzed above) $O(log_{2}n)$ bits are needed to represent it in binary form,which is the counts for the while loops,thus making the time complexity $O(log$ $n)$.
#### space complexity:
The algorithm exploits  iteration to calculate more effectively with variables occupying fixed memory , which means that the space they occupy does not depend on the magnitude of the input exponent n,thus making the space complexity O(1).
### testing function

<font size =1>

```C
void testing_program(int n,double x) {
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
```
</font>

> This function uses C's standard library `time.h`. 
> It takes the input 'x' as base , the input n as the exponent and evaluates three algorithms in terms of runtime for calculating x raised to the power of n.
>
> For  algorithm1 and algorithm2 (recursive version), it records the start time using the clock() function before executing a loop that performs the calculations **one hundred thousand** times.
>
> For algorithm2(iterative version),it records the start time using the clock() function before executing a loop that performs the calculations **a million** times.
>
> After the loop, it records the end time and calculates the duration of the execution in seconds.
> Finally, it prints the calculated result, the run time in seconds, and the tick count for each algorithm.

<div STYLE="page-break-after: always;"></div>

## $Chapter 3:  Testing Results$

* The results are tested on  MacBook Air M2 Sonoma 14.0 , Apple clang version 15.0.0(arm64-apple-darwin23.0.0)

<font size= 0.001> 

<table>
    <tr>
        <td></td>
        <td>N</td>
        <td>1000</td>
        <td>5000</td>
        <td>10000</td>
        <td>20000</td>
        <td>40000</td>
        <td>60000</td>
        <td>80000</td>
        <td>100000</td>
    </tr>
    <tr>
      	<font size= 0.001> 
        <th rowspan="5"><div style = "width:1.5cm">Algorithm 1</div></th>
         </font>
    </tr>
    <tr>
        <td>Iterations</td>
        <td>100000</td>
        <td>100000</td>
        <td>100000</td>
        <td>100000</td>
        <td>100000</td>
        <td>100000</td>
        <td>100000</td>
        <td>100000</td>
    </tr>
    <tr>
        <td>Ticks</td>
        <td>361811</td>
        <td>1726246</td>
        <td>3436671</td>
        <td>6885644</td>
        <td>13782837</td>
        <td>20743694</td>
        <td>28000420</td>
        <td>35234169</td>
    </tr>
    <tr>
        <td>Total time<br>(sec)</td>
        <td>0.361811</td>
        <td>1.726246</td>
        <td>3.436671</td>
        <td>6.885644</td>
        <td>13.782837</td>
        <td>20.743694</td>
        <td>28.000420</td>
        <td>35.234169</td>
    </tr>
        <td>Duration<br>(1/100000<br>sec)</td>
        <td>0.361811</td>
        <td>1.726246</td>
        <td>3.436671</td>
        <td>6.885644</td>
        <td>13.782837</td>
        <td>20.743694</td>
        <td>28.000420</td>
        <td>35.234169</td>
    </tr>
    <tr>
        <font size= 0.001>
        <th rowspan="5"><div style = "width:1.5cm">Algorithm 2（iterative version）</div></th>
        </font>
    </tr>
    <tr>
        <td>Iterations</td>
        <td>1000000</td>
        <td>1000000</td>
        <td>1000000</td>
        <td>1000000</td>
        <td>1000000</td>
        <td>1000000</td>
        <td>1000000</td>
        <td>1000000</td>
    </tr>
    </tr>
        <td>Ticks</td>
        <td>17925</td>
        <td>23136</td>
        <td>25108</td>
        <td>27400</td>
        <td>30768</td>
        <td>31599</td>
        <td>32268</td>
        <td>34458</td>
    </tr>
    </tr>
        <td>Total time<br>(sec)</td>
        <td>0.017925</td>
        <td>0.023136</td>
        <td>0.025108</td>
        <td>0.027400</td>
        <td>0.030768</td>
        <td>0.031599</td>
        <td>0.032268</td>
        <td>0.034458</td>
    </tr>
    </tr>
        <td>Duration<br>(1/100000<br>sec)</td>
        <td>0.0017925</td>
        <td>0.0023136</td>
        <td>0.0025108</td>
        <td>0.0027400</td>
        <td>0.0030768</td>
        <td>0.0031599</td>
        <td>0.0032268</td>
        <td>0.0034458</td>
    </tr>
    <tr>
        <th rowspan="5"><div style = "width:1.5cm">Algorithm 2(recursive version）</div></th>
    </tr>
    <tr>
        <td>Iterations</td>
        <td>100000</td>
        <td>100000</td>
        <td>100000</td>
        <td>100000</td>
        <td>100000</td>
        <td>100000</td>
        <td>100000</td>
        <td>100000</td>
    </tr>
    </tr>
        <td>Ticks</td>
        <td>2879</td>
        <td>4090</td>
        <td>4438</td>
        <td>4766</td>
        <td>5177</td>
        <td>5405</td>
        <td>5869</td>
        <td>6360</td>
    </tr>
    </tr>
        <td>Total time<br>(sec)</td>
        <td>0.002879</td>
        <td>0.004090</td>
        <td>0.004438</td>
        <td>0.004766</td>
        <td>0.005177</td>
        <td>0.005405</td>
        <td>0.005869</td>
        <td>0.006360</td>
    </tr>
    </tr>
        <td>Duration<br>(1/100000<br>sec)</td>
        <td>0.002879</td>
        <td>0.004090</td>
        <td>0.004438</td>
        <td>0.004766</td>
        <td>0.005177</td>
        <td>0.005405</td>
        <td>0.005869</td>
        <td>0.006360</td>
    </tr>
</table>
</font>

* From the N-runtime graph of algorithm 1 below,we can clearly see that the function's run time increases linearly(with respect to N)when calculating,which means it can take a rather long time running when the exponent increases tremendously.

  <img src="/Users/lily/Desktop/cszju/fds/project/project1/normal/1.jpg" alt="1" style="zoom:35%;" />

  

* From the N-runtime graph of algorithm 2(iterative version) below,we can clearly see that the function's run time has a logarithmic growth(with respect to N)when calculating,which means  when the exponent   increases tremendously,the algorithm can still be rather effective.

  <img src="/Users/lily/Desktop/cszju/fds/project/project1/normal/3.jpg" alt="3" style="zoom:15%;" />

* From the N-runtime graph of algorithm 2(recursive version) below,we can clearly see that the function's run time has a logarithmic growth(with respect to N)when calculating,which means  when the exponent   increases tremendously,the algorithm can still be rather effective.

  <img src="/Users/lily/Desktop/cszju/fds/project/project1/normal/2.jpg" alt="2" style="zoom:15%;" />

* Form the N-runtime graph of algorithms comparison below,we can clearly see that when the exponent experiences a tremendous growth,algorithm2 performs much better than algorithm1.

<img src="/Users/lily/Desktop/cszju/fds/project/project1/normal/123.jpg" alt="123" style="zoom:35%;" />

## $Chapter 4:  Analysis$ $and$ $Comments$

### Analysis for algorithm 1(brute-force approach)
#### time complexity：
* In every loop,`temp = temp*x` is calculated ,and there are n loops ,so the algorithm has a time complexity of`O(n)`, with its running time increasing linearly when calculating large exponents.
#### space complexity:
* The function requires constant space regardless of the value of n, thus space complexity is `O(1)`.
### Analysis for algorithm 2.1(calculating recursively)
#### time complexity：
* In each recursive call ,n is halved ,until finally calling Pow\_recursive($x*x$, 1) before returning the result.Thus, the height of the recursive tree is $log_{2}n$.
* The overall time complexity can be written as:`T(n) = T(n/2) + O(1)`and according to the $Master$ $Theorem$, the algorithm's time complexity is `O(log n)`. Therefore, it is highly efficient, especially when dealing with large exponents.
#### space complexity:
* In each recursive call, certain memory space is allocated.Since recursive calls form a recursive tree, the space complexity of the algorithm can be expressed as `O(logn)`as analyzed above.
### Analysis for algorithm 2.2(calculating iteratively)

#### time complexity:
* In each loop, processing time for each bit of exponent n is constant and does not depend on the size of n.

* For the integer exponent n, (as analyzed above) $O(log_{2}n)$ bits are needed to represent it in binary form,which is the counts for the while loops,thus making the time complexity $O(log n)$.
#### space complexity:
* The algorithm exploits  iteration to calculate more effectively with variables occupying fixed memory , which means that the space they occupy does not depend on the magnitude of the input exponent n,thus making the space complexity O(1).
### Comparisons

As analyzed above (also illustrated  in $Chapter 3:  Testing Results$).When it comes to large exponents, algorithm 2 performs much better that algorithm 1,thus making it a better choice when doing the calculation.

## $Appendix:$  $Source$ $Code$ 

```C
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
```



## $Declaration$

*I hereby declare that all the work done in this project titled "Performance Measurment Of POW" is of my independent effort.*
