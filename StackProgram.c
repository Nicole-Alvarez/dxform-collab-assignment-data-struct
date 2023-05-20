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
void EvaluateChar(Stack** top, char c, int* underFlowFlag, int* tagFlag);
void GetInput(Stack** top, int* underFlowFlag, int* tagFlag);
void PrintResult(Stack** top, int underFlowFlag, int tagFlag);
void FreeStack(Stack* top);
int main()
{
    Stack* top = NULL;
    int underFlowFlag = 0;
    int tagFlag = 0;
    GetInput(&top, &underFlowFlag, &tagFlag);
    PrintResult(&top, underFlowFlag, tagFlag);
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
void EvaluateChar(Stack** top, char c, int* underFlowFlag, int* tagFlag)
{
    char data;
    if(c == OPEN_TAG)
    {
        Push(top, c);
        if(*tagFlag <= 0)
            *tagFlag = 1;
    }
    if(c == CLOSE_TAG)
    {
        data = Pop(top);
        if(!data)
        {
            *underFlowFlag = 1;
            PrintResult(top, *underFlowFlag, *tagFlag);
            FreeStack(*top);
            exit(1);
        }
    }
}
void GetInput(Stack** top, int* underFlowFlag, int* tagFlag)
{
    char inputChar;
    printf("Input the string to evaluate: ");
    while((inputChar = getchar()) != '\n')
    {
        EvaluateChar(top, inputChar, underFlowFlag, tagFlag);
    }

}
void PrintResult(Stack** top, int underFlowFlag, int tagFlag)
{
    if(underFlowFlag > 0)
    {
        printf("Stack underflow: missing pair for >");
        return;
    }
    if(tagFlag < 1)
    {
        printf("String expression is valid, but no tags were inputted");
        return;
    }
    if(IsEmpty(*top))
        printf("Complete '<' and '>' pairs");
    else
    {
        char res = Pop(top);
        printf("Missing pair for %c", res);
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
