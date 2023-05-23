#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include "./error.h"

#define SUCCESS 1
#define FAILURE 0
#define INVALID_CHOICE_MSG() printf("\nChoice Invalid.\n")
#define EXIT_MSG() printf("Exiting...\n")

jmp_buf jump_buffer;

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct NodeArrParams {
    struct Node* root;
    struct Node** nodeArr;
    int* rear;
};

int InputChoice();
int InputData();
void DisplayMenu();
void GoToChoice(int choice, struct Node **root);
struct Node *CreateNode(int data);
struct Node *InsertNode(struct Node *root, int data);

int IsFullBinaryTree(struct Node *root);

int IsCompleteBinaryTree(struct Node *root);
struct Node** CreateNodeArr();
struct Node** FillNodeArray(struct NodeArrParams);

int GetHeight(struct Node* root);
void PrintHeight(int height);

void PrintResult(int status, int choice);
void PrintNodes(struct Node *root);

int main()
{
	struct Node *root = NULL;
	int choice = 0;

	do
    {
        DisplayMenu();
        choice = InputChoice();
        GoToChoice(choice, &root);
    }while(choice!=6);

    return 0;
}

int InputChoice() {
    int choice;
    scanf("%d", &choice);
    fflush(stdin);

    return choice;
}

int InputData() {
	int data;

	printf("Enter the value to insert: ");
 	scanf("%d", &data);

	return data;
}

void DisplayMenu()
{
    printf("\n[1] Insert Node");
    printf("\n[2] Determine Height");
    printf("\n[3] Determine if Full Binary Tree");
    printf("\n[4] Determine if Complete Binary Tree");
    printf("\n[5] Print Nodes");
    printf("\n[6] Exit\n");
    printf("\nChoice: ");
}

void GoToChoice(int choice, struct Node **root)
{
    int data;
	switch (choice)
	{
        case 1:
			data = InputData();
			if (setjmp(jump_buffer) == 0)
            {
                *root = InsertNode(*root, data);
			}
		break;
        case 2:
            PrintHeight(GetHeight(*root));
        break;

        case 3:
            PrintResult(IsFullBinaryTree(*root), choice);
        break;
        case 4:
            if (setjmp(jump_buffer) == 0)
            {
                PrintResult(IsCompleteBinaryTree(*root), choice);
            }
        break;
       	case 5:
                if(*root)
                    PrintNodes(*root);
                else
                    printerr_null_param();
        break;
  		case 6:
            EXIT_MSG();
    	break;
        default:
            INVALID_CHOICE_MSG();
        break;
    }
}

struct Node *CreateNode(int data)
{
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode)
    {
        printerr_allocation();
        longjmp(jump_buffer, 1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node *InsertNode(struct Node *root, int data)
{
    if (!root){
    	return CreateNode(data);
    }

    struct Node* currentNode = root;
    struct Node* parentNode = NULL;

    while (currentNode != NULL)
    {
        parentNode = currentNode;
        if (data <= currentNode->data)
        {
        	currentNode = currentNode->left;
        }
        else
        {
        	currentNode = currentNode->right;
        }
    }

    if (data <= parentNode->data)
    {
    	parentNode->left = CreateNode(data);
    }else
    {
    	parentNode->right = CreateNode(data);
    }

    return root;
}

int IsFullBinaryTree(struct Node *root) {
    if (root == NULL)
    {
    	return SUCCESS;
    }

    if (root->left == NULL && root->right == NULL)
    {
    	return SUCCESS;
    }

    if ((root->left != NULL && root->right != NULL) && IsFullBinaryTree(root->left) && IsFullBinaryTree(root->right))
    {
    	return SUCCESS;
    }

    return FAILURE;
}

//Ivan Flag
struct Node** CreateNodeArr()
{
    int queueSize = 1000;
    struct Node** nodeArr = (struct Node**)malloc(sizeof(struct Node*) * queueSize);
    if (!nodeArr)
    {
        printerr_allocation();
        longjmp(jump_buffer, 1);
    }
    return nodeArr;
};
struct Node** FillNodeArray(struct NodeArrParams param)
{
    int front = 0;
    param.nodeArr[(*param.rear)++] = param.root;

    while (front < *param.rear) {
        struct Node* current = param.nodeArr[front++];

        if (current->left != NULL) {
            param.nodeArr[(*param.rear)++] = current->left;
        }

        if (current->right != NULL) {
            param.nodeArr[(*param.rear)++] = current->right;;
        }
    }
    return param.nodeArr;
}
int IsCompleteBinaryTree(struct Node* root)
{
     if (!root)
        return 1;

    int rear = 0;
    struct NodeArrParams initialParam = {root, CreateNodeArr(), &rear};
    struct Node** nodeArr = FillNodeArray(initialParam);

    int flag = 0;
    for (int i = 0; i < rear; i++)
    {
        struct Node* current = nodeArr[i];
        if(rear == 2 && current->right != NULL)
        {
            free(nodeArr);
            return FAILURE;
        }
        if (flag && (current->left != NULL || current->right != NULL))
        {
            free(nodeArr);
            return FAILURE;
        }
        if (current->left == NULL || current->right == NULL)
        {
            flag = 1;
        }
    }

    free(nodeArr);
    return SUCCESS;
}
//End Flag
int GetHeight(struct Node* node) {
    if (node == NULL) {
        return -1; // An empty tree has a depth of -1
    }

    int leftDepth = GetHeight(node->left);
    int rightDepth = GetHeight(node->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}
//Print Functions
void PrintResult(int status, int choice)
{
    if (choice == 3)
        printf("The binary tree is %s\n", status ? "a Full Binary Tree" : "not a Full Binary Tree");
    if(choice == 4)
        printf("The binary tree is %s\n", status ? "a Complete Binary Tree" : "not a Complete Binary Tree");
}

void PrintHeight(int height)
{
    printf("Height of the binary tree: %d\n", height);
}

void PrintNodes(struct Node *root) {
    if (root == NULL){
    	return;
    }

    printf("%d ", root->data);
    PrintNodes(root->left);
    PrintNodes(root->right);
}
