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
void GoToChoice(int choice, struct Node **root);
void PrintNodes(struct Node *root);
int IsFullBinaryTree(struct Node *root);
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
    printf("\n[3] Determine if Full Binary Tre"); 
    printf("\n[4] Determine if Complete Binary Tree");  
    printf("\n[5] Print Nodes");
    printf("\n[6] Exit\n");
    printf("\nChoice: "); 
}

void GoToChoice(int choice, struct Node **root) {
    int i, data, isFull;
	switch (choice) {
        case 1:
			data = InputData();
			*root = InsertNode(*root, data);
		break;
        case 2:
            
        break;
        case 3:
            
        break;
        case 4:
            
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
    if (root == NULL)
        return 1;
    
    if (root->left == NULL && root->right == NULL)
        return 1;
    
    if ((root->left != NULL && root->right != NULL) && 
        IsFullBinaryTree(root->left) && IsFullBinaryTree(root->right))
        return 1;
    
    return 0;
}

void PrintNodes(struct Node *root) {
    if (root == NULL)
        return;

    printf("%d ", root->data);
    PrintNodes(root->left);
    PrintNodes(root->right);
}