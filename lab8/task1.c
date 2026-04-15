#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct student { 
    long long int ID; 
    char name[30];
    struct student* next; 
};

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int hash1(long long int key, int size) {
    return key % size;
}

int hash2(long long int key, int size) {
    int p = 1;
    while (p * 2 < size) p *= 2;
    return key % p;
}

int hash3(long long int key, int size) {
    int p = size - 1;
    while (p > 1 && !is_prime(p)) p--;
    return key % p;
}

int hash4(long long int key, int size) {
    double A = 0.6180339887; 
    double frac = (key * A) - (long long)(key * A); 
    return (int)(size * frac);
}

int hash5(long long int key, int size) {
    int limit = (int)(0.9 * size);
    int p = limit;
    while (p > 1 && !is_prime(p)) p--;
    return key % p;
}

int hash6(long long int key, int size) {
    int p = size - 1;
    while (p > 1 && !is_prime(p)) p--;
    return (int)(((unsigned long long)key * p) % size);
}

void reset_table(struct student** table, int size) {
    for (int i = 0; i < size; i++) {
        struct student* curr = table[i];
        while (curr) {
            struct student* temp = curr;
            curr = curr->next;
            free(temp);
        }
        table[i] = NULL;
    }
}

int main() {
    FILE *file = fopen("t1_data.txt", "r");
    if (!file) return 1;

    int N;
    if (fscanf(file, "%d", &N) != 1) {
        fclose(file);
        return 1;
    }

    struct student *input_list = malloc(N * sizeof(struct student));
    for (int i = 0; i < N; i++) {
        if (fscanf(file, "%lld,%[^\n]", &input_list[i].ID, input_list[i].name) != 2) {
            break;
        }
    }
    fclose(file);

    int table_size = 2 * N;
    struct student** hash_table = calloc(table_size, sizeof(struct student*));

    for (int func_num = 1; func_num <= 6; func_num++) {
        int collisions = 0;
        reset_table(hash_table, table_size);

        for (int i = 0; i < N; i++) {
            int index;
            long long id = input_list[i].ID;

            if (func_num == 1) index = hash1(id, table_size);
            else if (func_num == 2) index = hash2(id, table_size);
            else if (func_num == 3) index = hash3(id, table_size);
            else if (func_num == 4) index = hash4(id, table_size);
            else if (func_num == 5) index = hash5(id, table_size);
            else index = hash6(id, table_size);

            if (hash_table[index] != NULL) {
                collisions++;
            }

            struct student* newNode = malloc(sizeof(struct student));
            newNode->ID = id;
            strcpy(newNode->name, input_list[i].name);
            newNode->next = hash_table[index];
            hash_table[index] = newNode;
        }

        printf("Hash Function %d: %d collisions\n", func_num, collisions);
    }

    reset_table(hash_table, table_size);
    free(hash_table);
    free(input_list);

    return 0;
}