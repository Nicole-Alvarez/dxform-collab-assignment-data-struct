#include <stdio.h>
#include <stdlib.h>

#define OPEN_TAG '<'
#define CLOSE_TAG '>'
typedef struct node {
    char data;
    struct node* next;
} Stack;

Stack* CreateNode(char data);
void Push(Stack** top, char data);
char Pop(Stack** top);
int IsEmpty(Stack* top);
void evaluateChar(Stack** top, char c);
void getInput(Stack** top);
void printResult(Stack** top);
void FreeStack(Stack* top);
int main()
{
    Stack* top = NULL;
    getInput(&top);
    printResult(&top);
    FreeStack(top);
    return 0;
}
Stack* CreateNode(char data)
{
    Stack* temp = (Stack*)malloc(sizeof(Stack));
    if (temp == NULL) {
        printf("Error: Stack overflow.\n");
        return NULL;
    }
    temp->data = data;
    temp->next = NULL;
    return temp;
}
void Push(Stack** top, char data)
{
    Stack* temp = CreateNode(data);
    if (temp == NULL) {
        return;
    }
    temp->next = *top;
    *top = temp;
}

char Pop(Stack** top)
{
    if (*top == NULL)
        return '\0';

    char data = (*top)->data;
    Stack* temp = *top;
    *top = (*top)->next;
    free(temp);
    return data;
}

int IsEmpty(Stack* top)
{
    return top == NULL;
}
void evaluateChar(Stack** top, char c)
{
    char data;
    if(c == OPEN_TAG)
        Push(top, c);
    if(c == CLOSE_TAG)
    {
        data = Pop(top);
        if(!data)
        {
            printf("Missing pair for %c.\n", c);
            exit(1);
        }
    }
}
void getInput(Stack** top)
{
    char inputChar;
    printf("Input the string to evaluate: ");
    while((inputChar = getchar()) != '\n')
    {
        evaluateChar(top, inputChar);
    }

}
void printResult(Stack** top)
{
    if(IsEmpty(*top))
        printf("Complete pairs");
    else
    {
        char data = Pop(top);
        printf("Missing pair for %c", data);
    }
}
void FreeStack(Stack* top)
{
    Stack* current = top;
    Stack* temp;

    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
}

