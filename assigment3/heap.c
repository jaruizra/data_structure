#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int capacity;
    int size;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(sizeof(int) * (capacity+1)); // index 0 unused
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// "Bubble up" the element at index i
void bubbleUp(MinHeap *heap, int i) {
    int parent = i / 2;
    while (parent > 0 && heap->data[i] < heap->data[parent]) {
        swap(&heap->data[i], &heap->data[parent]);
        i = parent;
        parent = i / 2;
    }
}

// Insert a new element x into the heap
void insert(MinHeap *heap, int x) {
    if (heap->size == heap->capacity) {
        fprintf(stderr, "Heap is full. Cannot insert.\n");
        return;
    }
    heap->size++;
    heap->data[heap->size] = x;
    bubbleUp(heap, heap->size);
}

// "Bubble down" the element at index i
void bubbleDown(MinHeap *heap, int i) {
    while (1) {
        int left = 2*i;
        int right = 2*i + 1;
        int smallest = i;
        
        if (left <= heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right <= heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        
        if (smallest != i) {
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
}

// Extract the root (minimum) element
int extract(MinHeap *heap) {
    if (heap->size == 0) {
        fprintf(stderr, "Heap is empty. Cannot extract.\n");
        return -1; // or some error code
    }
    int rootValue = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;
    bubbleDown(heap, 1);
    return rootValue;
}

// Peek at the root element without removing it
int peek(MinHeap *heap) {
    if (heap->size == 0) {
        fprintf(stderr, "Heap is empty.\n");
        return -1; // or some error code
    }
    return heap->data[1];
}

// Utility function to print the heap
void printHeap(MinHeap *heap) {
    if (heap->size == 0) {
        printf("Heap is empty.\n");
        return;
    }
    printf("Heap elements: ");
    for (int i = 1; i <= heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main() {
    // Create a heap with sufficient capacity
    MinHeap *heap = createHeap(50);

    // Insert the given elements: [15,10,20,17,25,8,12]
    int elements[] = {15, 10, 20, 17, 25, 8, 12};
    int n = sizeof(elements)/sizeof(elements[0]);
    for (int i = 0; i < n; i++) {
        insert(heap, elements[i]);
    }
    
    printf("Heap after insertions:\n");
    printHeap(heap);

    // Extract twice and display after each extraction
    int extracted = extract(heap);
    printf("\nExtracted: %d\n", extracted);
    printf("Heap after first extract:\n");
    printHeap(heap);

    extracted = extract(heap);
    printf("\nExtracted: %d\n", extracted);
    printf("Heap after second extract:\n");
    printHeap(heap);

    // Cleanup
    free(heap->data);
    free(heap);

    return 0;
}
