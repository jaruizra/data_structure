#include <stdio.h>

// a structure for complex numbers
typedef struct {
    double real;
    double imaginary;
// Name
} ComplexNumber;

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

// subb of two numbers
ComplexNumber 
Sub(ComplexNumber cn1, ComplexNumber cn2) {
    // variable
    ComplexNumber result;
    // perform rest
    result.real = cn1.real - cn2.real;
    result.imaginary = cn1.imaginary - cn2.imaginary;
    // return
    return result;
}

// Addition of two complex numbers
ComplexNumber 
Add(ComplexNumber cn1, ComplexNumber cn2) {
    // variable new number
    ComplexNumber result;
    //sum
    result.real = cn1.real + cn2.real;
    result.imaginary = cn1.imaginary + cn2.imaginary;
    // return value
    return result;
}

// Multiplication of two complex numbers
ComplexNumber 
Multiply(ComplexNumber cn1, ComplexNumber cn2) {
    // return variable
    ComplexNumber result;
    // multiply
    result.real = (cn1.real * cn2.real) - (cn1.imaginary * cn2.imaginary);
    result.imaginary = (cn1.real * cn2.imaginary) + (cn1.imaginary * cn2.real);
    // return
    return result;
}

// division of two icomples numbers
ComplexNumber 
Divide(ComplexNumber cn1, ComplexNumber cn2) {

    // return variable
    ComplexNumber result;

    // Calculate the denominator
    double denominator = (cn2.real * cn2.real) + (cn2.imaginary * cn2.imaginary);
    
    // Check if the denominator is 0 to avoid division by 0
    if (denominator == 0) {
        // error message
        printf("Error: Division by zero!\n");
        // Set result to 0 for both real and imaginary
        result.real = 0;
        result.imaginary = 0;
        // return 0
        return result; 
    }

    // Calculate the real part of the result using the formula
    result.real = ((cn1.real * cn2.real) + (cn1.imaginary * cn2.imaginary)) / denominator;

    // Calculate the imaginary part
    result.imaginary = ((cn1.imaginary * cn2.real) - (cn1.real * cn2.imaginary)) / denominator;

    // Return the result
    return result;
}


int main(int argc, char *argv[]) {

    // Declare a complex number
    ComplexNumber cn1, cn2;
    
    // Set real and imaginary parts
    setRealPart(&cn1, 3.5);
    setImaginaryPart(&cn1, -4.7);

    // Set values for the second complex number
    setRealPart(&cn2, 1.0);
    setImaginaryPart(&cn2, 2.0);

    // Print the complex number
    // Print the complex numbers
    printf("Complex Number 1: \n");
    Print(cn1);
    
    printf("Complex Number 2: \n");
    Print(cn2);

    // Perform add
    ComplexNumber sum = Add(cn1, cn2);
    // Print
    printf("Sum: ");
    Print(sum);

    // Perform subb
    ComplexNumber difference = Sub(cn1, cn2);
    // result
    printf("Difference: ");
    Print(difference);
    
    // perform multiply
    ComplexNumber product = Multiply(cn1, cn2);
    printf("Product: ");
    Print(product);

    // perform Divide
    ComplexNumber div = Divide(cn1, cn2);
    printf("Division: ");
    Print(div);

    return 0;

}
