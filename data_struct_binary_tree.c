#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
  int data;
  struct TreeNode* left;
  struct TreeNode* right;
};

int InputChoice(); 
void DisplayMenu(); 
void GoToChoice();
int InputData();
struct TreeNode* insertNode(struct TreeNode* root, int val);
int max(int a, int b);
int getHeight(struct TreeNode* root);

int main()
{
	int choice = 0;
	
	do{  
        DisplayMenu();
        choice = InputChoice();
        GoToChoice(choice);
    }while(choice!=6);
    
    return 0;
}

int InputChoice() {
    int choice;
    scanf("%d", &choice);
    fflush(stdin);

    return choice;
} 

void DisplayMenu()
{
    printf("\n[1] Insert Node"); 
    printf("\n[2] Determine Height"); 
    printf("\n[3] Determine if Full Binary Tre"); 
    printf("\n[4] Determine if Complete Binary Tree");  
    printf("\n[5] Print Nodes");
    printf("\n[6] Exit\n");
    printf("\nChoice: "); 
}

void GoToChoice(int choice) {
  struct TreeNode* root;
  int data, height;

	switch (choice) {
        case 1:
            data=InputData();
            root=insertNode(root, data);
            break;
        case 2:
            height = getHeight(root);
            printf("Height of the binary tree: %d\n", height);
            break;
        case 3:
            
            break;
        case 4:
            
            break;
         case 5:
            
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("\nChoice Invalid.\n");
            break;
    }
}

struct TreeNode* insertNode(struct TreeNode* root, int val) {
  if (root == NULL) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
  } else if (val < root->data) {
    root->left = insertNode(root->left, val);
  } else if (val > root->data) {
    root->right = insertNode(root->right, val);
  }
  return root;
}

int InputData() {
    int data;

    printf("Enter data: ");
    scanf("%d", &data);
    
    return data;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(struct TreeNode* root) {
    if (root == NULL) {
        return -1;  // height of an empty tree is -1
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    return max(leftHeight, rightHeight) + 1;
}


void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

void printLevel(struct TreeNode* root, int level, int height) {
    if (root == NULL) {
        return;
    }

    if (level == 1) {
        int spaces = height - 1;
        printSpaces(spaces);
        printf("%d", root->data);
        printSpaces(spaces);
    } else if (level > 1) {
        printLevel(root->left, level - 1, height);
        printLevel(root->right, level - 1, height);
    }
}

void displayBinaryTree(struct TreeNode* root) {
    int height = getHeight(root);

    for (int i = 1; i <= height; i++) {
        printLevel(root, i, height);
        printf("\n");
    }
}