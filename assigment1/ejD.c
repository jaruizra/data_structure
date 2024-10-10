#include <stdio.h>
#include <stdlib.h>

// a structure for complex numbers
typedef struct {
    double real;
    double imaginary;
// Name
} ComplexNumber;

// Define a structure for array list of complex numbers
typedef struct {
    
    // Pointer to the array
    ComplexNumber* array; 
    // Current number of complex numbers
    int size;             
    // Total capacity of the array
    int capacity; 

// Name        
} ComplexNumberList;

// Sett the real part
void 
setRealPart (ComplexNumber* cn, double real) {
    cn->real = real;
}

// Sett the imaginary part
void 
setImaginaryPart (ComplexNumber* cn, double imaginary) {
    cn->imaginary = imaginary;
}

// Print the complex number in the good form (getter)
void 
Print(ComplexNumber cn) {

    // Not print - 2 times
    if (cn.imaginary >= 0) {
        printf("%lf + %lfi\n", cn.real, cn.imaginary);
    } else {
        // I do the imaginary number into positive
        printf("%lf - %lfi\n", cn.real, -cn.imaginary);
    }
}

// Function to create a new complex number list
ComplexNumberList* 
createList(int capacity) {
    ComplexNumberList* list = (ComplexNumberList*)malloc(sizeof(ComplexNumberList));
    list->capacity = capacity;
    list->size = 0;
    list->array = (ComplexNumber*)malloc(capacity * sizeof(ComplexNumber));
    return list;
}

// Function to print the list
void 
printList(ComplexNumberList* list) {
    // looop
    for (int i = 0; i < list->size; i++) {
        // call my built in print function
        Print(list->array[i]); 
    }
}

// Function to insert a complex number at a given index
void 
insert(ComplexNumberList* list, ComplexNumber cn, int index) {
    
    // check where to put it
    if (index < 0 || index > list->size) {
        printf("Error: Index out of bounds!\n");
        return;
    }

    // Check if the array needs to be resized
    if (list->size == list->capacity) {
        // increase capacity
        list->capacity += 1;
        // dynamic memory realloc
        list->array = (ComplexNumber*)realloc(list->array, list->capacity * sizeof(ComplexNumber));
    }

    // Shift elements to the right to make space for the new element
    for (int i = list->size; i > index; i--) {
        list->array[i] = list->array[i - 1];
    }

    // Insert the new complex number at the specified index
    list->array[index] = cn;
    list->size++;
}

// Function to delete a complex number from a given index
void 
delete(ComplexNumberList* list, int index) {
    // check where to put it = error
    if (index < 0 || index >= list->size) {
        printf("Error: Index out of bounds!\n");
        return;
    }

    // Shift elements to the left to fill the gap created by deletion
    for (int i = index; i < list->size - 1; i++) {
        list->array[i] = list->array[i + 1];
    }

    // Decrease the size of the list
    list->size--;
}

// Function to add all complex numbers in the list
ComplexNumber 
Add(ComplexNumberList* list) {
    // Initialize sum as 0 + 0i
    ComplexNumber sum = {0.0, 0.0};

    // loop
    for (int i = 0; i < list->size; i++) {
        sum.real += list->array[i].real;          
        sum.imaginary += list->array[i].imaginary;
    }
    // Return the sum
    return sum;
}

// Function to subtract all complex numbers in the list
ComplexNumber 
Sub(ComplexNumberList* list) {
    // case of no elements
    if (list->size == 0) {
        printf("Error: No complex numbers to subtract!\n");
        // Return 0 if list is empty
        return (ComplexNumber){0.0, 0.0};
    }

    // Initialize the result with the first complex number in the list
    ComplexNumber result = list->array[0];

    // Subtract each subsequent complex number from the result
    for (int i = 1; i < list->size; i++) {
        result.real -= list->array[i].real;            
        result.imaginary -= list->array[i].imaginary; 
    }

    // Return final number
    return result; 
}

// Function to multiply all complex numbers in the list
ComplexNumber 
Multiply(ComplexNumberList* list) {
    // Case of no elements
    if (list->size == 0) {
        printf("Error: No complex numbers to multiply!\n");
        // Return 0 if list is empty
        return (ComplexNumber){0.0, 0.0}; 
    }

    // Initialize the result with the first complex number in the list
    ComplexNumber result = list->array[0];

    // Multiply each subsequent complex number to the result
    for (int i = 1; i < list->size; i++) {
        // Calculate the real part using the formula
        double real = (result.real * list->array[i].real) - (result.imaginary * list->array[i].imaginary);
        // Calculate the imaginary part using the formula
        double imaginary = (result.real * list->array[i].imaginary) + (result.imaginary * list->array[i].real);
        // Update result
        result.real = real;
        result.imaginary = imaginary;
    }

    // Return final number
    return result; 
}

// Function to divide all complex numbers in the list
ComplexNumber 
Divide(ComplexNumberList* list) {
    // Case of no elements
    if (list->size == 0) {
        printf("Error: No complex numbers to divide!\n");
        // Return 0 if list is empty
        return (ComplexNumber){0.0, 0.0}; 
    }

    // Initialize the result with the first complex number in the list
    ComplexNumber result = list->array[0];

    // Iterate through the list to divide by each subsequent complex number
    for (int i = 1; i < list->size; i++) {
        ComplexNumber cn = list->array[i];

        // Calculate the denominator to avoid division by zero
        double denominator = (cn.real * cn.real) + (cn.imaginary * cn.imaginary);

        // Check for division by zero
        if (denominator == 0) {
            printf("Error: Division by zero with complex number at index %d!\n", i);
            // Return 0 if division by zero occurs
            return (ComplexNumber){0.0, 0.0}; 
        }

        // Calculate the real part of the result
        double real = (result.real * cn.real + result.imaginary * cn.imaginary) / denominator;

        // Calculate the imaginary part of the result
        double imaginary = (result.imaginary * cn.real - result.real * cn.imaginary) / denominator;

        // Update the result
        result.real = real;
        result.imaginary = imaginary;
    }

    // Return final number
    return result; 
}

int main(int argc, char *argv[]) {

    // Create a complex number list with a size of 2 list[2]
    ComplexNumberList* list = createList(2);

    // Declare a complex number
    ComplexNumber cn1, cn2, cn3;
    
    // Set values for the first number
    setRealPart(&cn1, 3.5);
    setImaginaryPart(&cn1, -4.7);

    // Set values for the second number
    setRealPart(&cn2, 1.0);
    setImaginaryPart(&cn2, 2.0);

    // Set values for the third number
    setRealPart(&cn3, 2.5);
    setImaginaryPart(&cn3, 3.5);

    // Print the complex number
    printf("Complex Number 1: \n");
    Print(cn1);
    
    printf("Complex Number 2: \n");
    Print(cn2);

    printf("Complex Number 3: \n");
    Print(cn3);
    
    // Insert complex numbers into the list
    insert(list, cn1, 0);
    insert(list, cn2, 1);

    // Print the list
    printf("Complex Numbers in the List:\n");
    printList(list);

    // perform a shift, in this case I move cn2
    insert(list, cn3, 1);
    printf("List after cn2 shift:\n");
    printList(list);
    
    // delete a number, in this case the cn1
    delete(list, 0);
    printf("List after element 0 deletion: \n");
    printList(list);
    
    // Perform add
    ComplexNumber sum = Add(list);
    printf("Sum of Complex Numbers: \n");
    Print(sum);

    // Perform subtraction 
    ComplexNumber difference = Sub(list);
    printf("Difference of Complex Numbers: \n");
    Print(difference);

    // Perform multiplication of all complex numbers in the list
    ComplexNumber product = Multiply(list);
    printf("Product of Complex Numbers: \n");
    Print(product); // Print the product

    // Perform division of all complex numbers in the list
    ComplexNumber quotient = Divide(list);
    printf("Quotient of Complex Numbers: \n");
    Print(quotient); // Print the quotient

    // Free allocated memory
    free(list->array);
    free(list);

    return 0;

}