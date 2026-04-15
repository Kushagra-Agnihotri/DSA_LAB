#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


int hash1(long long int key) {
    return key % 256;
}

int hash2(long long int key) {
    double A = 0.6180339887;
    double frac = (key * A) - (long long)(key * A);
    return (int)(256 * frac);
}

int hash3(long long int key) {
    return key % 256; 
}

int hash4(long long int key) {
    return (key ^ (key >> 3)) % 256;
}

int hash5(long long int key) {
    int val = 255 - (key % 197);
    return val % 256;
}


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
    int size = 256;
    int *array = create4bitarray(size);

    FILE *file = fopen("bloom_numbers.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    long long int num;
    printf("Reading numbers and adding to Bloom Filter...\n");
    
    while (fscanf(file, "%lld\n", &num) == 1) {
        //printf("%lld\n", num);
        
        incrementIndex(array, hash1(num));
        incrementIndex(array, hash2(num));
        incrementIndex(array, hash3(num));
        incrementIndex(array, hash4(num));
        incrementIndex(array, hash5(num));
    }
    fclose(file);

    printf("Initial array: "); 
    for (int i = 0; i < size; i++) { 
        printf("%d ", getCount(array, i)); 
    } 
    printf("\n"); 

    FILE *qfile =  fopen("count_bloom_queries.txt", "r");
    if (!qfile) {
        perror("Error opening file");
        return 1;
    }
    long long int queryID;
    int positive = 0;
    int negative = 0;

    printf("\nTesting Membership:\n");
    int op = 0;
    while(fscanf(qfile, "%d,", &op)==1){
        printf("%d\n", op);

        long long int key;
        fscanf(qfile, "%lld\n", &key);

        switch(op){
            case 1: 
                printf("Increment\n");

                incrementIndex(array, hash1(key));
                incrementIndex(array, hash2(key));
                incrementIndex(array, hash3(key));
                incrementIndex(array, hash4(key));
                incrementIndex(array, hash5(key));
                continue;
            case 2 :
                printf("DECREMENT\n");

                decrementIndex(array, hash1(key)); 
                decrementIndex(array, hash2(key)); 
                decrementIndex(array, hash3(key)); 
                decrementIndex(array, hash4(key)); 
                decrementIndex(array, hash5(key));
                continue;
            case 3 :
                printf("QUERY\n");

                bool count = getCount(array, hash1(key)) && 
                getCount(array, hash2(key)) &&
                getCount(array, hash3(key)) &&
                getCount(array, hash4(key)) &&
                getCount(array, hash5(key));

                if(count)
                {
                    printf("ID %lld: PROBABLY PRESENT\n", key);
                    positive++;
                }
                else{
                    printf("ID %lld: DEFINITELY NOT PRESENT\n", key);
                    negative++;
                }
                continue;
            default: return 0;

        }
    }
    printf("Final array : "); 
    for (int i = 0; i < size; i++) { 
        printf("%d ", getCount(array, i)); 
    } 
    printf("\n"); 

    printf("Number of positives : %d , Number of negatives : %d\n", positive, negative);
    printf("False Positivity %f\n", 1.0f/(1.0f+19.0f));

    free(array);
    return 0; 
}