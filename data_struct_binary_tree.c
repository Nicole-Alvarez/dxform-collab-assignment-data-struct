#include <stdio.h>
#include <stdlib.h>

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
int IsCompleteBinaryTree(struct Node *root);
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
    printf("\n[2] Determine Height");
    printf("\n[3] Determine if Full Binary Tree");
    printf("\n[4] Determine if Complete Binary Tree");
    printf("\n[5] Print Nodes");
    printf("\n[6] Exit\n");
    printf("\nChoice: ");
}

void GoToChoice(int choice, struct Node **root) {
    int i, data, isFull, isComplete, height;
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
            isComplete = IsCompleteBinaryTree(*root);
            if(isComplete)
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

void FullBinaryResult(int isFull){
	if (isFull){
		printf("The binary tree is a Full Binary Tree.\n");
	} else{
		printf("The binary tree is not a Full Binary Tree.\n");
	}
}

int IsCompleteBinaryTree(struct Node* root) {
    if (root == NULL)
        return 1;
    int flag = 0; // Flag to track if we have encountered a non-full node

    // Create a queue for level order traversal
    struct Node** queue = (struct Node**)malloc(sizeof(struct Node*) * 1000);
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct Node* current = queue[front++];

        // If we have encountered a non-full node before, but the current node has any child, it is not a complete binary tree
        if (flag && (current->left != NULL || current->right != NULL)) {
            free(queue);
            return 0;
        }

        // If the current node has no left child, mark the flag to indicate a non-full node
        if (current->left == NULL) {
            flag = 1;
        }
        // If the current node has a left child, enqueue it
        else {
            queue[rear++] = current->left;
        }

        // If the current node has no right child, mark the flag to indicate a non-full node
        if (current->right == NULL) {
            flag = 1;
        }
        // If the current node has a right child, enqueue it
        else {
            queue[rear++] = current->right;
        }
    }

    free(queue);
    return 1;
}

int GetHeight(struct Node* node) {
    if (node == NULL) {
        return -1; // An empty tree has a depth of -1
    }

    int leftDepth = GetHeight(node->left);
    int rightDepth = GetHeight(node->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

void PrintNodes(struct Node *root) {
    if (root == NULL){
    	return;
    }

    printf("%d ", root->data);
    PrintNodes(root->left);
    PrintNodes(root->right);
}
