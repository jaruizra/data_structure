#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100  // Maximum size of the queue

// Global variables for the queue
int queue[MAX_SIZE];
// Index of the front element
int front = 0;
// Index of the rear element
int rear = -1;
// Current length of the queue
int length = 0;     

// Function to add an element to the queue
void 
Enqueue (int value) {

    // Check if the queue is full
    if (length == MAX_SIZE) {
        printf("Error: Queue Overflow!\n");
        return;
    }

    // Move rear pointer in a circular fashion
    rear = (rear + 1) % MAX_SIZE;

    // Insert the new element
    queue[rear] = value;

    // Increment the length
    length++;

    // Confirmation message
    printf("%d enqueued into the queue\n", value);

}

// Function to remove and return the front element from the queue
int 
Dequeue () {

    // Check if the queue is empty
    if (length == 0) {
        printf("Error: Queue Underflow!\n");
        return -1;
    }

    // Get the front element
    int value = queue[front];

    // Move front pointer in a circular fashion
    front = (front + 1) % MAX_SIZE;

    // Decrement the length
    length--;

    // Confirmation message
    printf("%d dequeued from the queue\n", value);

    // Return the dequeued value
    return value;

}

// Function to get the front element without removing it
int 
Front () {

    // Check if the queue is empty
    if (length == 0) {
        printf("Error: Queue is empty!\n");
        return -1;
    }

    // Return the front element
    printf("Front element is %d\n", queue[front]);
    return queue[front];

}

// Function to print the length of the queue
void 
printLength () {

    printf("Queue length: %d\n", length);

}

int 
main (int argc, char *argv[]) {

    // Test the Enqueue function
    printf("Testing Enqueue operation:\n");
    Enqueue(10);
    Enqueue(20);
    Enqueue(30);

    // Print the current front element
    printf("\nTesting Front operation:\n");
    Front();

    // Print the length of the queue
    printf("\nTesting printLength operation:\n");
    printLength();

    // Dequeue an element
    printf("\nTesting Dequeue operation:\n");
    Dequeue();

    // Print the current front element
    printf("\nTesting Front operation after Dequeue:\n");
    Front();

    // Print the length of the queue
    printf("\nTesting printLength operation after Dequeue:\n");
    printLength();

    // Dequeue all elements to empty the queue
    printf("\nDequeuing remaining elements to empty the queue:\n");
    Dequeue();
    Dequeue();

    // Attempt to dequeue from an empty queue
    printf("\nAttempting to Dequeue from an empty queue:\n");
    Dequeue();

    return 0;

}
