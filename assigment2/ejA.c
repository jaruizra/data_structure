#include <stdio.h>
#include <stdlib.h>

// Define the Node structure
typedef struct Node {
    int data;
    struct Node* next;
// Name
} Node;

// Global variables
Node* top = NULL;
int length = 0;

// Function to push an element onto the stack
void 
Push (int value) {

    // Allocate memory for new node
    Node* newNode = (Node*)malloc(sizeof(Node));

    // Check for memory allocation failure
    if (newNode == NULL) {
        printf("Error: Memory allocation failed!\n");
        return;
    }

    // Set the data and next pointer
    newNode->data = value;
    newNode->next = top;

    // Update the top pointer
    top = newNode;

    // Increment the length
    length++;

    // Confirmation message
    printf("%d pushed onto the stack\n", value);

}

// Function to pop an element from the stack
int 
Pop () {

    // Check if the stack is empty
    if (top == NULL) {
        printf("Error: Stack Underflow!\n");
        return -1;
    }

    // Get the data from the top node
    int value = top->data;

    // Temporary pointer to the top node
    Node* temp = top;

    // Move the top pointer to the next node
    top = top->next;

    // Free the memory of the popped node
    free(temp);

    // Decrement the length
    length--;

    // Confirmation message
    printf("%d popped from the stack\n", value);

    // Return the popped value
    return value;

}

// Function to get the top element of the stack
int 
Top () {

    // Check if the stack is empty
    if (top == NULL) {
        printf("Error: Stack is empty!\n");
        return -1;
    }

    // Return the data from the top node
    printf("Top element is %d\n", top->data);
    return top->data;

}

// Function to print the length of the stack
void 
printLength () {

    printf("Stack length: %d\n", length);

}

// Function to free the entire stack
void 
freeStack () {

    // Pop elements until the stack is empty
    while (top != NULL) {
        Pop();
    }

}

int 
main (int argc, char *argv[]) {

    // Test the Push function
    printf("Testing Push operation:\n");
    Push(10);
    Push(20);
    Push(30);

    // Print the current top element
    printf("\nTesting Top operation:\n");
    Top();

    // Print the length of the stack
    printf("\nTesting printLength operation:\n");
    printLength();

    // Pop an element
    printf("\nTesting Pop operation:\n");
    Pop();

    // Print the current top element
    printf("\nTesting Top operation after Pop:\n");
    Top();

    // Print the length of the stack
    printf("\nTesting printLength operation after Pop:\n");
    printLength();

    // Pop all elements to empty the stack
    printf("\nPopping remaining elements to empty the stack:\n");
    Pop();
    Pop();

    // Attempt to pop from an empty stack
    printf("\nAttempting to Pop from an empty stack:\n");
    Pop();

    // Free the stack (in case it's not empty)
    freeStack();

    return 0;

}
