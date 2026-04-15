#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
// Recursive binary search
int binarySearchRecursive(int arr[], int l, int r, int x)
{
if (r >= l)
{
int mid = l + (r - l) / 2;
if (arr[mid] == x)
return mid;
if (arr[mid] > x)
return binarySearchRecursive(arr, l, mid - 1, x);
return binarySearchRecursive(arr, mid + 1, r, x);
}
return -1;
}
// Iterative binary search
int binarySearchIterative(int arr[], int l, int r, int x)
{
while (l <= r)
{
int m = l + (r - l) / 2;
if (arr[m] == x)
return m;
if (arr[m] < x)
l = m + 1;
else
r = m - 1;
}
return -1;
}
// Driver code
int main(void)
{
int arr[500000];
for(int i = 0; i < 500000; i++)
arr[i] = i*2;
int n = sizeof(arr) / sizeof(arr[0]);
int result[5000];
struct timeval t1, t2;
double time_taken;
gettimeofday(&t1, NULL);
for(int j = 0; j < 5000; j++)
result[j] = binarySearchIterative(arr, 0, n - 1, j*8);
gettimeofday(&t2, NULL);
time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
printf("Iterative binary search took %f seconds to execute\n", time_taken);
gettimeofday(&t1, NULL);
for(int j = 0; j < 5000; j++)
result[j] = binarySearchRecursive(arr, 0, n - 1, j*8);
gettimeofday(&t2, NULL);
time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
printf("Recursive binary search took %f seconds to execute\n", time_taken);
return 0;
}