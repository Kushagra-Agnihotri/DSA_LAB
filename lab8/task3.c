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


int *createBloomFilter(int size) {
    int bitsPerInt = sizeof(int) * 8;
    int numIntsRequired = (size + bitsPerInt - 1) / bitsPerInt;
    
    int *filter = (int *)calloc(numIntsRequired, sizeof(int));
    return filter;
}

void setBit(int *filter, int index) {
    int i = index / (sizeof(int) * 8); 
    int j = index % (sizeof(int) * 8); 
    filter[i] = filter[i] | (1 << j); 
}

int checkBit(int *filter, int index) {
    int i = index / (sizeof(int) * 8); 
    int j = index % (sizeof(int) * 8); 
    return (filter[i] >> j) & 1;
}

void addToFilter(int *filter, long long int key) {
    setBit(filter, hash1(key));
    setBit(filter, hash2(key));
    setBit(filter, hash3(key));
    setBit(filter, hash4(key));
    setBit(filter, hash5(key));
}

bool isPresent(int *filter, long long int key) {
    if (!checkBit(filter, hash1(key))) return false;
    if (!checkBit(filter, hash2(key))) return false;
    if (!checkBit(filter, hash3(key))) return false;
    if (!checkBit(filter, hash4(key))) return false;
    if (!checkBit(filter, hash5(key))) return false;
    return true; 
}

int main() {
    int filterSize = 256;
    int *filter = createBloomFilter(filterSize);

    FILE *file = fopen("bloom_numbers.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    long long int num;
    printf("Reading numbers and adding to Bloom Filter...\n");
    
    while (fscanf(file, "%lld\n", &num) == 1) {
        //printf("%lld\n", num);
        
        addToFilter(filter, num);
    }
    fclose(file);

    long long int testNumbers[] = {123456789, 987654321, 555555555}; // Example numbers
    int testSize = sizeof(testNumbers) / sizeof(testNumbers[0]);

    FILE *qfile =  fopen("bloom_queries.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
    long long int num1;


    printf("\nTesting Membership:\n");
    while (fscanf(file, "%lld\n", &num1) == 1) {
        if (isPresent(filter, num1)) {
            printf("ID %lld: PROBABLY PRESENT\n", num1);
        } else {
            printf("ID %lld: DEFINITELY NOT PRESENT\n", num1);
        }
    }

    free(filter);
    return 0;
}