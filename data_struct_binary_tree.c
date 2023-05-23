#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include "./error.h"

#define SUCCESS 1
#define FAILURE 0
jmp_buf jump_buffer; //For error handling

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
void FullBinaryResult(int);
void GoToChoice(int choice, struct Node **root);
void PrintNodes(struct Node *root);
int IsFullBinaryTree(struct Node *root);
//Ivan Flag
int IsCompleteBinaryTree(struct Node *root);
struct Node** CreateNodeArr();
struct Node** FillNodeArray(struct NodeArrParams);
void PrintResult(int status);
void CatchNullParam(struct Node* node);
//End Flag
int Max(int, int);
int GetHeight(struct Node* root);
struct Node *CreateNode(int data);
struct Node *InsertNode(struct Node *root, int data);

int main()
{
	struct Node *root = NULL;
	int choice = 0;

	do{
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
    printf("\n[2] Determine Heigh");
    printf("\n[3] Determine if Full Binary Tree");
    printf("\n[4] Determine if Complete Binary Tree");
    printf("\n[5] Print Nodes");
    printf("\n[6] Exit\n");
    printf("\nChoice: ");
}

void GoToChoice(int choice, struct Node **root) {
    int i, data, isFull, height;
	switch (choice) {
        case 1:
			data = InputData();
			*root = InsertNode(*root, data);
		break;
        case 2:
            height = GetHeight(*root);
            printf("Height of the binary tree: %d\n", height);
        break;

        case 3:
            isFull = IsFullBinaryTree(*root);
            FullBinaryResult(isFull);
        break;
        case 4:
            if (setjmp(jump_buffer) == 0) {
                PrintResult(IsCompleteBinaryTree(*root));
            } else {
                // Handle the error condition
                printf("Returning to menu due to error\n");
            }
        break;
       	case 5:
            PrintNodes(*root);
        break;
  		case 6:
            printf("Exiting...\n");
    	break;
        default:
            printf("\nChoice Invalid.\n");
        break;
    }
}

struct Node *CreateNode(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node *InsertNode(struct Node *root, int data) {
    if (root == NULL){
    	return CreateNode(data);
    }

    struct Node* currentNode = root;
    struct Node* parentNode = NULL;

    while (currentNode != NULL) {
        parentNode = currentNode;
        if (data <= currentNode->data){
        	currentNode = currentNode->left;
        }
        else{
        	currentNode = currentNode->right;
        }
    }

    if (data <= parentNode->data){
    	parentNode->left = CreateNode(data);
    }
    else{
    	parentNode->right = CreateNode(data);
    }

    return root;
}

int IsFullBinaryTree(struct Node *root) {
    if (root == NULL){
    	return 1;
    }

    if (root->left == NULL && root->right == NULL){
    	return 1;
    }

    if ((root->left != NULL && root->right != NULL) && IsFullBinaryTree(root->left) && IsFullBinaryTree(root->right)){
    	return 1;
    }

    return 0;
}

//Ivan Flag
struct Node** CreateNodeArr()
{
    int queueSize = 1000;
    struct Node** nodeArr = (struct Node**)malloc(sizeof(struct Node*) * queueSize);
    if(!nodeArr)
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
    CatchNullParam(root);
    int rear = 0;
    struct NodeArrParams initialParam = {root, CreateNodeArr(), &rear};
    struct Node** nodeArr = FillNodeArray(initialParam);

    int flag = 0;
    int count = 0;
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
void CatchNullParam(struct Node* node)
{
    if (!node)
    {
        printerr_null_param();
        longjmp(jump_buffer, 1);
    }
}
void PrintResult(int status)
{
    printf("The binary tree is %s\n", status ? "a Complete Binary Tree" : "not a Complete Binary Tree");
}
//End Flag

int GetHeight(struct Node* node) {
    if (node == NULL) {
        return -1; // An empty tree has a depth of 0
    }

    int leftDepth = GetHeight(node->left);
    int rightDepth = GetHeight(node->right);
    printf("leftDepth: %d\n", leftDepth);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}
void FullBinaryResult(int isFull){
	if (isFull){
		printf("The binary tree is a Full Binary Tree.\n");
	} else{
		printf("The binary tree is not a Full Binary Tree.\n");
	}
}
void PrintNodes(struct Node *root) {
    if (root == NULL){
    	return;
    }

    printf("%d ", root->data);
    PrintNodes(root->left);
    PrintNodes(root->right);
}
