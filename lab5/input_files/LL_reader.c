#include <stdio.h>
#include <stdlib.h>

#include<sys/time.h>

typedef struct node * NODE;
struct node{
    int ele;
    NODE next;
};


typedef struct linked_list * LIST;
struct linked_list{
    int count;
    NODE head;
};


LIST createNewList()
{
    LIST myList;
    myList = (LIST) malloc(sizeof(struct linked_list));
    myList->count=0;
    myList->head=NULL;
    return myList;
}


NODE createNewNode(int value)
{
    NODE myNode;
    myNode = (NODE) malloc(sizeof(struct node));
    myNode->ele=value;
    myNode->next=NULL;
    return myNode;
}
void insertAfter(int searchEle, NODE n1, LIST l1)
{
    if(l1->head==NULL)
    {
        l1->head = n1;
        n1->next = NULL;
        l1->count++;
    }
    else
    {
        NODE temp = l1->head;
        NODE prev = temp;
        while(temp!=NULL)
        {
            if (temp->ele == searchEle)
            break;
            prev = temp;
            temp = temp->next;
        }
        if(temp==NULL)
        {
            printf("Element not found\n");
            return;
        }
        else
        {
        if(temp->next == NULL)
        {
            temp->next = n1;
            n1->next = NULL;
            l1->count++;
        }
        else
        {
            prev = temp;
            temp = temp->next;
            prev->next = n1;
            n1->next = temp;
            l1->count++;
        }
        return;
        }
    }
    return;
}
void printList(LIST l1)
{
    NODE temp = l1->head;
    printf("[HEAD] ->");
    while(temp != NULL)
    {
        printf(" %d ->", temp->ele);
        temp = temp->next;
    }
    printf(" [NULL]\n");
}

// Recursive function to compute sum of integers in a linked list
int llSumNTR(NODE head)
{
    if (head == NULL)
        return 0;
    return head->ele + llSumNTR(head->next); // Pay close attention here
}
int llSumTR(NODE head, int acc)
{
    if (head == NULL)
        return acc;
    return llSumTR(head->next, head->ele + acc); // Pay close attention here
}
int llSumI(NODE head)
{
    int acc =0;

    while(head != NULL){
        acc += head->ele;
        head = head->next;
    }
    return acc; // Pay close attention here
}

// This is just a wrapper function to take LIST as input, but run the recursive sum function on its NODEs starting from the head
int llSumNTRWrapper(LIST list)
{
    return llSumNTR(list->head);
}
int llSumTRWrapper(LIST list)
{
    return llSumTR(list->head, 0);
}
int llSumIWrapper(LIST list)
{
    return llSumI(list->head);
}

// Driver code
int main()
{
    // Reads the file numbers1000.txt and creates a linked list with those integers
    FILE *fp;
    fp = fopen("numbers1000.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    int num;
    LIST myList = createNewList();
    while (fscanf(fp, "%d", &num) != EOF)
    {
        NODE myNode = createNewNode(num);
        myNode->next = myList->head;
        myList->head = myNode;
        myList->count++;
    }
    fclose(fp);
    struct timeval t1, t2;
    double time_taken;

    // Perform some operations on the linked list
    // ...
    gettimeofday(&t1, NULL);
    int sum = llSumIWrapper(myList);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) * 1e6;
    time_taken = (time_taken + (t2.tv_usec - t1.tv_usec)) * 1e-6;
    printf("I LL SUM took %f seconds to execute\nsum: %d\n", time_taken, sum);

    // Example operation: Print the elements of the linked list
    // NODE temp = myList->head;
    // while (temp != NULL)
    // {
    //     printf("%d ", temp->ele);
    //     temp = temp->next;
    // }
}/*  */