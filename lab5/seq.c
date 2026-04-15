#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#define int long long int

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
        printf(" %lld ->", temp->ele);
        temp = temp->next;
    }
    printf(" [NULL]\n");
}


int main()
{
    LIST myList = createNewList();
    int n = 100000;
    int arr[n];
    int i;
    for(i=0; i<n; i++)
    {
        arr[i] = i;
    }
    for(i=0; i<n; i++)
    {
        NODE myNode = createNewNode(arr[i]);
        insertAfter(i-1, myNode, myList);
    }
    struct timeval start, end;
    int temp1;
    gettimeofday(&start, NULL);
    for(i=0; i<n; i++)
        temp1 = arr[i];
    gettimeofday(&end, NULL);
    printf("Time taken for sequential scan on array: %ld microseconds\n",
        ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 +
        start.tv_usec)));
    gettimeofday(&start, NULL);


    NODE temp = myList->head;
    while(temp != NULL)
        temp = temp->next;
    gettimeofday(&end, NULL);
    printf("Time taken for sequential scan on linked list: %ld microseconds\n",
        ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 +
        start.tv_usec)));
}