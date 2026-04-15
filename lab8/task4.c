#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


int *create4bitarray(int size) {
    int numIntsRequired = (size + 7) / 8; 
    int *arr = (int *)calloc(numIntsRequired, sizeof(int));
    return arr;
}

int getCount(int *array, int index) {
    int i = index / 8; 
    int j = index % 8; 
    return (array[i] >> (j * 4)) & 0xF;
}

void incrementIndex(int *array, int index) {
    int i = index / 8;
    int j = index % 8;
    int currentVal = getCount(array, index);

    if (currentVal < 15) {
        unsigned int mask = ~(0xF << (j * 4));
        array[i] = (array[i] & mask) | ((currentVal + 1) << (j * 4));
    }
}

void decrementIndex(int *array, int index) {
    int i = index / 8;
    int j = index % 8;
    int currentVal = getCount(array, index);

    if (currentVal > 0) {
        unsigned int mask = ~(0xF << (j * 4));
        array[i] = (array[i] & mask) | ((currentVal - 1) << (j * 4));
    }
}

int main() {
    int size = 10;
    int *array = create4bitarray(size); 

    printf("Initial array: "); 
    for (int i = 0; i < size; i++) { 
        printf("%d ", getCount(array, i)); 
    } 
    printf("\n"); 

    incrementIndex(array, 0); 
    incrementIndex(array, 5); 
    incrementIndex(array, 5); 
    incrementIndex(array, 0); 
    incrementIndex(array, 9); 

    printf("After some increments: "); 
    for (int i = 0; i < size; i++) { 
        printf("%d ", getCount(array, i)); 
    } 
    printf("\n"); 

    decrementIndex(array, 0); 
    decrementIndex(array, 5); 
    decrementIndex(array, 9); 

    printf("After some decrements: "); 
    for (int i = 0; i < size; i++) { 
        printf("%d ", getCount(array, i)); 
    } 
    printf("\n"); 

    incrementIndex(array, 3); 
    incrementIndex(array, 3); 
    incrementIndex(array, 0); 
    incrementIndex(array, 0); 
    incrementIndex(array, 0); 
    incrementIndex(array, 0); 
    incrementIndex(array, 0); 
    incrementIndex(array, 1); 
    incrementIndex(array, 2); 

    for (int i = 0; i < 20; i++) { 
        incrementIndex(array, 8); 
    } 

    for (int i = 0; i < 20; i++) { 
        decrementIndex(array, 1); 
    } 

    printf("Final array : "); 
    for (int i = 0; i < size; i++) { 
        printf("%d ", getCount(array, i)); 
    } 
    printf("\n"); 

    free(array);
    return 0; 
}