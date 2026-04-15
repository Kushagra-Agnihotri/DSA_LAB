#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
int arr[10000] = {0};
int rec(long long int n){
    if(n == 0){
        return 0;
    }
    if(n == 1){
        return 1;
    }
    if(arr[n]!=0){
        return arr[n];
    }
    // printf("currently at : %lld\n",n);
    arr[n] = rec(n-1) + rec(n-2);
    return arr[n];
}

int itr(int n){
    if (n <= 1) {
        return n; // Base cases: F(0) = 0, F(1) = 1
    }

    long long first = 0;
    long long second = 1;
    long long next;

    // Loop from the 2nd term up to the nth term
    for (int i = 2; i <= n; i++) {
        next = first + second; // Calculate the next term
        first = second;       // Update 'first' to the previous 'second'
        second = next;        // Update 'second' to the new 'next'
    }

    return second; // 'second' now holds the nth Fibonacci number
}

void main(){
    struct timeval t1, t2;
    double time_taken;
    int n =5;
    gettimeofday(&t1, NULL);

    int val = itr(n);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    printf("Iterative fib took %f seconds to execute\n val:%d\n", time_taken, val);

    gettimeofday(&t1, NULL);
    val = rec(n);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    printf("REccursive fib took %f seconds to execute\n val:%d\n", time_taken, val);
    
    

}