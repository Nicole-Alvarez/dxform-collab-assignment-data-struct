#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node* next;
} Stack;
Stack* CreateNode(char data);
void Push(Stack** top, char data);
char Pop(Stack** top);
int IsEmpty(Stack* top);
void FreeStack(Stack* top);

int main() {
    char c, data;
    Stack* top = NULL;

    printf("Input the string to evaluate: ");

    while ((c = getchar()) != '\n')
    {
        if(c == '<')
            Push(&top, c);
        else if(c == '>')
        {
            data = Pop(&top);
            if(!data)
                printf("Missing pair for %c.\n", c);
        }
    }

    printf("\n");
    if(IsEmpty(top))
        printf("Complete pairs");
    else
    {
        char data = Pop(&top);
        printf("Missing pair for %c", data);
    }

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
