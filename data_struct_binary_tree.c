#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};
struct Parameter {
    struct Node* node;
    int level;
    int maxDepth;
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
int IsCompleteRecursive(struct Parameter);
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
            res = IsCompleteBinaryTree(*root);
            if(res)
                printf("success");
            else
                printf("Dead");
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

    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}
int IsCompleteRecursive(struct Parameter param)
{
    if (param.node == NULL) {
        return 1;
    }
    if (param.level > param.maxDepth) {
        return 0;
    }
    int leftComplete = IsCompleteRecursive((struct Parameter){param.node->left, param.level + 1, param.maxDepth});
    int rightComplete = IsCompleteRecursive((struct Parameter){param.node->right, param.level + 1, param.maxDepth});

    return leftComplete && rightComplete;
}
int IsCompleteBinaryTree(struct Node* root) {
    int maxDepth = CalculateMaxDepth(root); // Calculate the maximum depth of the tree
    struct Parameter initialParam = {root, 0, maxDepth};
    return IsCompleteRecursive(initialParam);

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
