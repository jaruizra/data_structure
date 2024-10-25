#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure of a tree node
typedef struct TreeNode {
    char* data;
    struct TreeNode** children;
    int childCount;
} TreeNode;

// Queue node for level order traversal
typedef struct QueueNode {
    const TreeNode* data;
    struct QueueNode* next;
} QueueNode;

// Queue structure
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Function to create a new tree node
TreeNode* createNode(const char* data, int childCount) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for new node!\n");
        return NULL;
    }

    newNode->data = strdup(data);
    if (newNode->data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for node data!\n");
        free(newNode);
        return NULL;
    }

    newNode->childCount = childCount;
    newNode->children = NULL;

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

// Function to print the tree in preorder traversal
void printPreorder(const TreeNode* root) {
    if (root == NULL)
        return;

    printf("%s ", root->data);
    for (int i = 0; i < root->childCount; i++) {
        printPreorder(root->children[i]);
    }
}

// Function to print the tree in postorder traversal
void printPostorder(const TreeNode* root) {
    if (root == NULL)
        return;

    for (int i = 0; i < root->childCount; i++) {
        printPostorder(root->children[i]);
    }
    printf("%s ", root->data);
}

// Function to print the tree in inorder traversal (generalized for n-ary trees)
void printInorder(const TreeNode* root) {
    if (root == NULL)
        return;

    int mid = root->childCount / 2;
    for (int i = 0; i < mid; i++) {
        printInorder(root->children[i]);
    }

    printf("%s ", root->data);

    for (int i = mid; i < root->childCount; i++) {
        printInorder(root->children[i]);
    }
}

// Function to initialize a queue
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

// Function to enqueue a node
void enqueue(Queue* q, const TreeNode* node) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    if (temp == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for queue node!\n");
        exit(EXIT_FAILURE);
    }
    temp->data = node;
    temp->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

// Function to dequeue a node
const TreeNode* dequeue(Queue* q) {
    if (isQueueEmpty(q))
        return NULL;

    QueueNode* temp = q->front;
    const TreeNode* node = temp->data;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return node;
}

// Function to print the tree in level order traversal
void printLevelOrder(const TreeNode* root) {
    if (root == NULL)
        return;

    Queue q;
    initQueue(&q);
    enqueue(&q, root);

    while (!isQueueEmpty(&q)) {
        const TreeNode* current = dequeue(&q);
        printf("%s ", current->data);

        for (int i = 0; i < current->childCount; i++) {
            enqueue(&q, current->children[i]);
        }
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

    // Print the tree in different traversal orders
    printf("Preorder Traversal:\n");
    printPreorder(A);
    printf("\n\n");

    printf("Postorder Traversal:\n");
    printPostorder(A);
    printf("\n\n");

    printf("Inorder Traversal (Generalized for N-ary Tree):\n");
    printInorder(A);
    printf("\n\n");

    printf("Level Order Traversal:\n");
    printLevelOrder(A);
    printf("\n");

    // Free the memory allocated for the tree
    freeTree(A);

    return EXIT_SUCCESS;
}
