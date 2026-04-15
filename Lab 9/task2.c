#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} Node;

typedef struct bst {
    Node *root;
} BST;

BST *new_bst() 
{
    BST *bst = malloc(sizeof(BST));
    bst->root = NULL;
    return bst;
}

Node *new_node(int value) 
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void traverse_in_order(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    traverse_in_order(node->left);
    printf("%d ", node->value);
    traverse_in_order(node->right);
}

void insert(BST *bst, int value)
{
    Node *node = new_node(value);
    if (bst->root == NULL) 
    {
        bst->root = node;
        return;
    }
    Node *current = bst->root;
    while (current != NULL) 
    {
        if (value < current->value) 
        {
            if (current->left == NULL) 
            {
                current->left = node;
                return;
            }
            current = current->left;
        } 
        else 
        {
            if (current->right == NULL) 
            {
                current->right = node;
                return;
            }
            current = current->right;
        }
    }
}

int search(BST *bst, int key)
{
    Node *current = bst->root;
    while (current != NULL) 
    {
        if (key == current->value) 
        {
            return 1;
        } 
        else if (key < current->value) 
        {
            current = current->left;
        } 
        else 
        {
            current = current->right;
        }
    }
    return 0;
}

int find_min(BST *bst)
{
    Node *current = bst->root;
    while (current->left != NULL) 
    {
        current = current->left;
    }
    return current->value;
}

int find_max(BST *bst)
{
    Node *current = bst->root;
    while (current->right != NULL) 
    {
        current = current->right;
    }
    return current->value;
}

Node *predecessor(Node *node)
{
    if (node->left == NULL)
    {
        return NULL;
    }
    Node *current = node->left;
    while (current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

Node *successor(Node *node)
{
    if (node->right == NULL)
    {
        return NULL;
    }
    Node *current = node->right;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

void delete(BST *bst, Node *node)
{
    if (node == NULL)
        return;
    if (node->left == NULL && node->right == NULL)
    {
        // Node is a leaf
        Node* current = bst->root;
        while (current != NULL)
        {
            if (current->left == node)
            {
                current->left = NULL;
                break;
            }
            if (current->right == node)
            {
                current->right = NULL;
                break;
            }
            if (node->value < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        free(node);
        return;
    }
    
    if (node->left == NULL)
    {
        // Node only has right child
        Node* current = bst->root;
        if (current == node)
        {
            bst->root = node->right;
            free(node);
            return;
        }
        while (current != NULL)
        {
            if (current->left == node)
            {
                current->left = node->right;
                break;
            }
            if (current->right == node)
            {
                current->right = node->right;
                break;
            }
            if (node->value < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        free(node);
        return;
    }

    if (node->right == NULL)
    {
        // Node only has left child
        Node* current = bst->root;
        if (current == node)
        {
            bst->root = node->left;
            free(node);
            return;
        }
        while (current != NULL)
        {
            if (current->left == node)
            {
                current->left = node->left;
                break;
            }
            if (current->right == node)
            {
                current->right = node->left;
                break;
            }
            if (node->value < current->value)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        free(node);
        return;
    }

    // Node has both children
    Node *temp = successor(node);
    node->value = temp->value;
    delete(bst, temp);
    return;
}



// Pre-order traversal: Root -> Left -> Right
void preOrderTraversal( Node* node) {
    if (node == NULL) {
            printf("NUll \t");

        return;
    }
    // Visit the root node first
    printf("%d ", node->value);
    // Traverse the left subtree
    preOrderTraversal(node->left);
    // Traverse the right subtree
    preOrderTraversal(node->right);
}

// Post-order traversal: Left -> Right -> Root
void postOrderTraversal( Node* node) {
    if (node == NULL) {
                    printf("NUll \t");

        return;
    }
    // Traverse the left subtree
    postOrderTraversal(node->left);
    // Traverse the right subtree
    postOrderTraversal(node->right);
    // Visit the root node last
    printf("%d ", node->value);
}


BST *  constructBst(int * array){
    int size = 600;
    printf("size - %d ", size);
    BST * newBST = new_bst();
    for  ( int i=0 ;i<size;i++){
        insert(newBST, array[i]);

    }
    return newBST;
}


int * fetchIntarray (){
    FILE *file = fopen("n_integers.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }
    int target_count = 1000;
    int header;
    int *results = (int *)malloc(target_count * sizeof(int));
    int found_count = 0;

    // if (results == NULL) {
    //     printf("Memory allocation error.\n");
    //     fclose(file);
    //     return 0;
    // }


    if (fscanf(file, "%d ,", &header) != 1) {
        printf("Could not find initial header.\n");
        free(results);
        fclose(file);
        return 0;
    }

    printf("Processing Block ID: %d\n", header);

    int ch;
    while ((ch = fgetc(file)) != EOF && ch != '[');

    while (found_count < header) {
        if (fscanf(file, "%d", &results[found_count]) == 1) {
            found_count++;
        } else {
            break;
        }
    }

    printf("Successfully retrieved %d integers:\n", found_count);
    // for (int i = 0; i < found_count; i++) {
    //     printf("%d ", results[i]);
    //     if ((i + 1) % 10 == 0) printf("\n");
    // }
    fclose(file);
    printf("\n");
    return results;
}
int main()
{
    int * numbers = fetchIntarray();
    for(int i=0;i<100;i++){
        printf("\n %d ", numbers[i]);
    }
    BST * bst = constructBst(numbers);
    traverse_in_order(bst->root);


}