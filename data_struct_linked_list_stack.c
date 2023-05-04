#include<stdio.h>
#include<stdlib.h>
 
typedef struct node
{
    int num;
    struct node *next;
} LINKED_LIST;

LINKED_LIST* createNode(int data) {
    LINKED_LIST* newNode = (LINKED_LIST*)malloc(sizeof(LINKED_LIST));
    newNode->num = data;
    newNode->next = NULL;
    return newNode;
}
 
void InsertFront(LINKED_LIST** head, int data); 
void DisplayList(LINKED_LIST* head);

int main()
{ 
    LINKED_LIST* head = NULL;
 
}  

void InsertFront(LINKED_LIST** head, int data)
{
    LINKED_LIST* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
} 

void DisplayList(LINKED_LIST* head)
{ 
    
} 