#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include "./error.h"
jmp_buf jump_buffer; //For error handling

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

int InputChoice();
int InputData();
void DisplayMenu();
void FullBinaryResult(int);
void GoToChoice(int choice, struct Node **root);
void PrintNodes(struct Node *root);
int IsFullBinaryTree(struct Node *root);
int CalculateMaxDepth(struct Node* node);
int IsCompleteBinaryTree(struct Node *root);
void FillQueueArray(struct Node* root, struct Node** queue, int* front, int* rear);
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
    printf("\n[2] Determine Height");
    printf("\n[3] Determine if Full Binary Tree");
    printf("\n[4] Determine if Complete Binary Tree");
    printf("\n[5] Print Nodes");
    printf("\n[6] Exit\n");
    printf("\nChoice: ");
}

void GoToChoice(int choice, struct Node **root) {
    int i, data, isFull, res;
	switch (choice) {
        case 1:
			data = InputData();
			*root = InsertNode(*root, data);
		break;
        case 2:
            res = CalculateMaxDepth(*root);
            printf("Height is %d", res);
        break;

        case 3:
            isFull = IsFullBinaryTree(*root);
            FullBinaryResult(isFull);
        break;
        case 4:
            if (setjmp(jump_buffer) == 0) {
                res = IsCompleteBinaryTree(*root);
                if(res)
                    printf("success");
                else
                    printf("Dead");
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
int CalculateMaxDepth(struct Node* node) {
    if (node == NULL) {
        return 0; // An empty tree has a depth of 0
    }

    int leftDepth = CalculateMaxDepth(node->left);
    int rightDepth = CalculateMaxDepth(node->right);
    printf("leftDepth: %d\n", leftDepth);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}
void FillQueueArray(struct Node* root, struct Node** queueArr, int* front, int* rear) {
    if(root == NULL)
    {
        printerr_null_param();
        longjmp(jump_buffer, 1);
    }
    queueArr[*rear] = root;
    (*rear)++;

    while (*front < *rear) {
        struct Node* current = queueArr[(*front)++];

        if (current->left != NULL) {
            queueArr[*rear] = current->left;
            (*rear)++;
        }

        if (current->right != NULL) {
            queueArr[*rear] = current->right;
            (*rear)++;
        }
    }
}

int IsCompleteBinaryTree(struct Node* root) {
    if (root == NULL)
        return 1;
    //Create array of pointers
    int queueSize = 1000;
    struct Node** queueArr = (struct Node**)malloc(sizeof(struct Node*) * queueSize);
    if(queueArr == NULL)
    {
        printerr_allocation();
        longjmp(jump_buffer, 1);
    }
    int front = 0, rear = 0;

    FillQueueArray(root, queueArr, &front, &rear);

    int flag = 0;
    for (int i = 0; i < rear; i++) {
        struct Node* current = queueArr[i];
        if (flag && (current->left != NULL || current->right != NULL)) {
            free(queueArr);
            return 0;
        }
        if (current->left == NULL || current->right == NULL) {
            flag = 1;
        }
    }

    free(queueArr);
    return 1;
}
//End Flag
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
