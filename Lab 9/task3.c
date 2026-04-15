#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} Node;

typedef struct bst {
    Node *root;
} BST;

typedef struct {
    int *data;
    int size;
} IntArray;

BST *new_bst() {
    BST *bst = malloc(sizeof(BST));
    bst->root = NULL;
    return bst;
}

Node *new_node(int value) {
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert(BST *bst, int value) {
    Node *node = new_node(value);
    if (bst->root == NULL) {
        bst->root = node;
        return;
    }
    Node *current = bst->root;
    while (current != NULL) {
        if (value < current->value) {
            if (current->left == NULL) {
                current->left = node;
                return;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = node;
                return;
            }
            current = current->right;
        }
    }
}

BST *constructBst(int *array, int size) {
    BST *newBST = new_bst();
    for (int i = 0; i < size; i++) {
        insert(newBST, array[i]);
    }
    return newBST;
}

int isBSTRecursive(Node *node, long min, long max) {
    if (node == NULL) return 1;
    if (node->value <= min || node->value >= max) return 0;
    return isBSTRecursive(node->left, min, node->value) && 
           isBSTRecursive(node->right, node->value, max);
}

int isBSTIterative(Node *root) {
    if (root == NULL) return 1;
    
    typedef struct stackNode {
        Node *node;
        long min;
        long max;
    } StackNode;

    StackNode stack[1000]; 
    int top = -1;

    stack[++top] = (StackNode){root, LONG_MIN, LONG_MAX};

    while (top >= 0) {
        StackNode curr = stack[top--];
        Node *n = curr.node;

        if (n->value <= curr.min || n->value >= curr.max) return 0;

        if (n->right) {
            stack[++top] = (StackNode){n->right, n->value, curr.max};
        }
        if (n->left) {
            stack[++top] = (StackNode){n->left, curr.min, n->value};
        }
    }
    return 1;
}

IntArray* fetchIntArrays(int *count) {
    FILE *file = fopen("n_integers.txt", "r");
    if (file == NULL) return NULL;

    IntArray *results = malloc(1000 * sizeof(IntArray));
    int header;
    int i = 0;

    while (fscanf(file, "%d ,", &header) == 1) {
        results[i].size = header;
        results[i].data = malloc(header * sizeof(int));
        
        int ch;
        while ((ch = fgetc(file)) != EOF && ch != '[');

        for (int j = 0; j < header; j++) {
            fscanf(file, "%d", &results[i].data[j]);
        }
        
        while ((ch = fgetc(file)) != EOF && ch != ']');
        i++;
    }
    fclose(file);
    *count = i;
    return results;
}

int main() {
    int arrayCount = 0;
    IntArray *dataArrays = fetchIntArrays(&arrayCount);

    if (dataArrays == NULL) return 1;

    BST **bstList = malloc(arrayCount * sizeof(BST *));

    for (int i = 0; i < arrayCount; i++) {
        bstList[i] = constructBst(dataArrays[i].data, dataArrays[i].size);
        
        int resRec = isBSTRecursive(bstList[i]->root, LONG_MIN, LONG_MAX);
        int resIter = isBSTIterative(bstList[i]->root);

        printf("BST %d: Recursive Check = %s, Iterative Check = %s\n", 
                i, resRec ? "Valid" : "Invalid", resIter ? "Valid" : "Invalid");
    }

    return 0;
}