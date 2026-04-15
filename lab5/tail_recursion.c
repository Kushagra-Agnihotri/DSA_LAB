#include <stdio.h>
#include<sys/time.h>
typedef long long ll;
int factNTR(int n) {
    if (n == 0)
    {
    return 1;
    }
    else
    {
    return n * factNTR(n - 1);
    }
}


int factTR(int n, int acc) {
    if (n == 0)
    {
    return acc;
    }
    else
    {
    return factTR(n - 1, n * acc);
    }
}


int factI(int n)
{
    int acc = 1;
    while (n > 0)
    {
    acc = acc * n;
    n = n - 1;
    }
    return acc;
}

int main(){
    struct timeval start, end;

    ll n = 2000; 
    int iterations = 1000000;
    // Perform some operation on the numbers
    // ...        
    gettimeofday(&start, NULL);
    for(int i = 0; i < iterations; i++) factNTR(n);    
    gettimeofday(&end, NULL);
    long double seconds = end.tv_sec - start.tv_sec;
    long double micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("FactNTR took %Lf seconds to execute\n", micros/1e6);

    gettimeofday(&start, NULL);
    factTR(10,1);
    for(int i = 0; i < iterations; i++) gettimeofday(&end, NULL);
    seconds = end.tv_sec - start.tv_sec;
     micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("FactTR took %Lf seconds to execute\n", micros/1e6);

    gettimeofday(&start, NULL);
    for(int i = 0; i < iterations; i++) factI(10);
    gettimeofday(&end, NULL);
     seconds = end.tv_sec - start.tv_sec;
    micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("FactI took %Lf seconds to execute\n", micros/1e6);


}    