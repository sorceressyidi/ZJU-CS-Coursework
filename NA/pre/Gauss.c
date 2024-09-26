#include<stdio.h>
# define M 100
int main()
{
	int i,j,n,k,s;
	double a[M][M],w,x[M],y[M],c,f;
	printf("输入方程未知数的个数：");
	scanf("%d",&n);
	printf("先输入一行，再输入每行。");
	/*录入数据*/ 
	for(i=0;i<n;i++)
	{
		for(j=0;j<n+1;j++)
		{
			scanf("%lf",&a[i][j]);
		}
	}
	/*处理数据*/
	for(i=1;i<n;i++)
	{
		a[i][0]=a[i][0]/a[0][0];//对第一列数据进行处理
	} 
	for(k=1;k<n;k++)
	{
		for(j=k;j<n+1;j++)
		{   w=0;
			for(s=0;s<k;s++)
			{
				w=w+a[k][s]*a[s][j];
			}
			a[k][j]=a[k][j]-w;//对每一行数据进行更新
		}
		for(i=k+1;i<n;i++)
		{
			w=0;
			for(s=0;s<k;s++)
			{
				w=w+a[i][s]*a[s][k];
			}
			a[i][k]=(a[i][k]-w)/a[k][k];//对每一列数据进行更新
		}
	}
	/*检验结果*/ 
	for(i=0;i<n;i++)
	{
		for(j=0;j<n+1;j++)
		{
			printf("%lf  ",a[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<n;i++)
	{
		y[i]=a[i][n];
	}
	/*回代*/ 
	x[n-1]=1.0*y[n-1]/a[n-1][n-1];
    for(i=n-2;i>=0;i--)
    {   f=0;
    	for(j=i+1;j<n;j++)
    	{
    		c=1.0*a[i][j]*x[j];
    		f=c+f;
		}
		x[i]=1.0*(y[i]-f)/a[i][i];	
	}
	for(i=1;i<n+1;i++)
	{
	printf("x[%d]=%lf\n",i,x[i-1]); 
	}
	return 0;
}