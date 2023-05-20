#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
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

int main() {
    struct TreeNode* root = createNode(5);
    root->left = createNode(2);
    root->right = createNode(8);
    root->left->left = createNode(1);
    root->left->right = createNode(4);
    root->right->right = createNode(9);

    int height = getHeight(root);
    printf("Height of the binary tree: %d\n", height);

    return 0;
}
