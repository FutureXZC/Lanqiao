#include<stdio.h>
double fibo(long n)
{
    if(n < 1) 
		return -1;
    long F[n + 1];
    F[1] = 1;
    F[2] = 1;
    for (int i = 3; i <= n; ++i) 
		F[i] = F[i - 1] + F[i - 2];
    return F[n];
}
int main()
{
    long num;
	scanf("%lld",&num);
    	if (num < 20) 
			  printf("%.8lf", (fibo(num) / fibo(num + 1)) );
    	else 
			  printf("0.61803399");
    return 0;
}
