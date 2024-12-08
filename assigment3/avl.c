#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, int key) {
    if (root == NULL)
        return createNode(key);
    if (key < root->key)
        root->left = insertNode(root->left, key);
    else if (key > root->key)
        root->right = insertNode(root->right, key);
    // If equal keys are not allowed, we usually do nothing or handle duplicates separately
    return root;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Compute the height of the tree
int height(Node* root) {
    if (root == NULL)
        return -1; // height of an empty tree can be considered -1
    return 1 + max(height(root->left), height(root->right));
}

int main() {
    Node* root = NULL;
    int keys[] = {10, 20, 30, 25, 15, 5};
    int n = sizeof(keys)/sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        root = insertNode(root, keys[i]);
        int h = height(root);
        printf("Inserted %d, Height after insertion: %d\n", keys[i], h);
    }

    return 0;
}
