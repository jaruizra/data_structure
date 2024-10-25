#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure of a tree node
typedef struct TreeNode {
    char* data;              // Changed from 'char' to 'char*' to support multi-character labels
    struct TreeNode** children;
    int childCount;
} TreeNode;

// Function to create a new tree node
TreeNode* createNode(const char* data, int childCount) {
    // Allocate memory for the new node
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for new node!\n");
        return NULL;
    }

    // Copy the data string into the node
    newNode->data = strdup(data);
    if (newNode->data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for node data!\n");
        free(newNode);
        return NULL;
    }

    newNode->childCount = childCount;
    newNode->children = NULL;

    // Allocate memory for children pointers and initialize them to NULL
    if (childCount > 0) {
        newNode->children = (TreeNode**)calloc(childCount, sizeof(TreeNode*));
        if (newNode->children == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for children of node %s!\n", data);
            free(newNode->data);
            free(newNode);
            return NULL;
        }
    }

    return newNode;
}

// Function to add children to a node
void addChildren(TreeNode* parent, TreeNode** children, int childCount) {
    if (parent == NULL) {
        fprintf(stderr, "Error: Parent node is NULL!\n");
        return;
    }

    if (childCount != parent->childCount) {
        fprintf(stderr, "Error: Mismatch in child count for node %s!\n", parent->data);
        return;
    }

    for (int i = 0; i < childCount; i++) {
        if (children[i] == NULL) {
            fprintf(stderr, "Error: Child at index %d is NULL!\n", i);
            return;
        }
        parent->children[i] = children[i];
    }
}

// Function to print the tree (preorder traversal)
void printTree(const TreeNode* root) {
    if (root == NULL)
        return;

    printf("%s ", root->data);

    for (int i = 0; i < root->childCount; i++) {
        printTree(root->children[i]);
    }
}

// Function to free the memory allocated for the tree
void freeTree(TreeNode* root) {
    if (root == NULL)
        return;

    for (int i = 0; i < root->childCount; i++) {
        freeTree(root->children[i]);
    }

    free(root->data);
    free(root->children);
    free(root);
}

int main(void) {
    // Create nodes for each element in the tree
    TreeNode* A = createNode("A", 4);
    TreeNode* B = createNode("B", 2);
    TreeNode* B_prime = createNode("B'", 1);
    TreeNode* C = createNode("C", 3);
    TreeNode* D = createNode("D", 0);
    TreeNode* E = createNode("E", 0);
    TreeNode* F = createNode("F", 0);
    TreeNode* F_prime = createNode("F'", 0);
    TreeNode* G = createNode("G", 0);
    TreeNode* H = createNode("H", 0);
    TreeNode* I = createNode("I", 0);

    // Check for memory allocation failures
    if (!A || !B || !B_prime || !C || !D || !E || !F || !F_prime || !G || !H || !I) {
        fprintf(stderr, "Error: Memory allocation failed during node creation.\n");
        // Free any allocated nodes
        freeTree(A); freeTree(B); freeTree(B_prime); freeTree(C); freeTree(D);
        freeTree(E); freeTree(F); freeTree(F_prime); freeTree(G); freeTree(H); freeTree(I);
        return EXIT_FAILURE;
    }

    // Set up children arrays for B, B', C, and A
    TreeNode* B_children[] = { E, F };
    TreeNode* B_prime_children[] = { F_prime };
    TreeNode* C_children[] = { G, H, I };
    TreeNode* A_children[] = { B, B_prime, C, D };

    // Add children to nodes
    addChildren(B, B_children, 2);
    addChildren(B_prime, B_prime_children, 1);
    addChildren(C, C_children, 3);
    addChildren(A, A_children, 4);

    // Print the tree (preorder traversal)
    printf("Tree Structure (Preorder Traversal):\n");
    printTree(A);
    printf("\n");

    // Free the memory allocated for the tree
    freeTree(A);

    return EXIT_SUCCESS;
}
