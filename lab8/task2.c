#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define TABLE_SIZE 1024

typedef enum { EMPTY, FILLED, DELETED } SlotStatus;

struct student {
    long long int ID;
    char name[50];
};

struct hash_table_element {
    struct student stud;
    SlotStatus status;
};

int current_collisions = 0;

int mul_hash(long long int key, int m) {
    double A = 0.6180339887;
    double frac = (key * A) - (long long)(key * A);
    return (int)(m * frac);
}

int hash(long long int ID, int m, int i, int mode) {
    int h1, h2;
    switch (mode) {
        case 1:
            return (mul_hash(ID, m) + i) % m;
        case 2:
            return (mul_hash(ID, m) + i * i) % m;
        case 3:
            h1 = mul_hash(ID, m);
            h2 = 1 + (ID % 1023);
            return (h1 + i * h2) % m;
        case 4:
            h1 = (int)(ID % 1024);
            h2 = 1 + (ID % 1023);
            return (h1 + i * h2) % m;
        default: return 0;
    }
}

void insert(struct hash_table_element *table, struct student *stud, int m, int mode) {
    for (int i = 0; i < m; i++) {
        int idx = hash(stud->ID, m, i, mode);
        if (table[idx].status == EMPTY || table[idx].status == DELETED) {
            table[idx].stud = *stud;
            table[idx].status = FILLED;
            return;
        }
        current_collisions++;
    }
}

void delete(struct hash_table_element *table, long long int ID, int m, int mode) {
    for (int i = 0; i < m; i++) {
        int idx = hash(ID, m, i, mode);
        if (table[idx].status == EMPTY) return; // Not found
        if (table[idx].status == FILLED && table[idx].stud.ID == ID) {
            table[idx].status = DELETED;
            return;
        }
        current_collisions++;
    }
}

struct student *search(struct hash_table_element *table, long long int ID, int m, int mode) {
    for (int i = 0; i < m; i++) {
        int idx = hash(ID, m, i, mode);
        if (table[idx].status == EMPTY) return NULL;
        if (table[idx].status == FILLED && table[idx].stud.ID == ID) {
            return &table[idx].stud;
        }
        current_collisions++;
    }
    return NULL;
}

void run(int mode, const char* label) {
    struct hash_table_element table[TABLE_SIZE];
    for(int i = 0; i < TABLE_SIZE; i++) table[i].status = EMPTY;
    
    current_collisions = 0;
    int query_ops = 0;

    FILE *f_data = fopen("t1_data.txt", "r");
    if (f_data) {
        int n_students;
        if (fscanf(f_data, "%d", &n_students) == 1) {
            for (int i = 0; i < n_students; i++) {
                struct student temp;
                if (fscanf(f_data, "%lld,%[^\n]", &temp.ID, temp.name) == 2) {
                    insert(table, &temp, TABLE_SIZE, mode);
                }
            }
        }
        fclose(f_data);
    }

    FILE *f_queries = fopen("t1_queries.txt", "r");
    if (!f_queries) {
        printf("Error opening t1_queries.txt\n");
        return;
    }

    char line[128];
    while (fgets(line, sizeof(line), f_queries)) {
        query_ops++;
        int op;
        long long int id;
        char name[50];

        if (sscanf(line, "%d,%lld,%[^\n]", &op, &id, name) == 3) {
            struct student s;
            s.ID = id;
            strcpy(s.name, name);
            insert(table, &s, TABLE_SIZE, mode);
        } 
        else if (sscanf(line, "%d,%lld", &op, &id) == 2) {
            if (op == 2) delete(table, id, TABLE_SIZE, mode);
            else if (op == 3) search(table, id, TABLE_SIZE, mode);
        }
    }
    fclose(f_queries);

    printf("Method: %s\n", label);
    printf("Total Collisions: %d\n", current_collisions);
    printf("Avg Collisions: %.2f\n\n", (float)current_collisions / query_ops);
}

int main() {
    run(1, "Linear Probing ");
    run(2, "Quadratic Probing ");
    run(3, "Double Hashing1");
    run(4, "Double Hashing2");

    return 0;
}