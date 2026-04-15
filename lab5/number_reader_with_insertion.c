#include <stdio.h>
#include<sys/time.h>
void insertionSortR(int *arr, int n)
{
    if (n <= 1) return;
    insertionSortR(arr, n-1);
    int last = arr[n-1];
    int j = n-2;
    while (j >= 0 && arr[j] > last)
    {
        arr[j+1] = arr[j];
        j--;
    }
    arr[j+1] = last;
}
// iterative insertion sort
void insertionSortI(int *arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        int last = arr[i];
        int j = i-1;
        while (j >= 0 && arr[j] > last)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = last;
    }
}
int main()
{
    // Reads the numbers stored in numbers1000.txt and stores them into an integer array
    FILE *fp = fopen("input_files/numbers.txt", "r");
    int n = 100000;
    int numbers[n];
    int i = 0;
    if (fp == NULL) {
        printf("Error: Could not open file numbers10000.txt\n");
        return 1; 
    }
    while (fscanf(fp, "%d", &numbers[i]) != EOF)
    {
        i++;
    }
    fclose(fp);

    struct timeval t1, t2;
    double time_taken;
    gettimeofday(&t1, NULL);

    // Perform some operation on the numbers
    // ...    
    insertionSortR(numbers,n);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    printf("Iterative Rsort took %f seconds to execute\n", time_taken);


    

    // Example operation: Print the numbers stored in the array
    for (int i = 0; i < 100; i++)
    {
        printf("%d \n", numbers[i]);
    }
}