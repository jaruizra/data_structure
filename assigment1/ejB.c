#include <stdio.h>



unsigned long
ackermann (unsigned long m, unsigned long n) {

    // Ackerman function
    // m, n are the resoult of
    // A(m, n) = n +1, if m=0;
    // A(m, n) = A(m - 1, 1) if m and n = 0
    // A(m, n) = A(m-1, A(m, n-1)) if m or n not 0

    if (m == 0) {
        return n + 1;
    }

    else if (m > 0 && n == 0) {
        return ackermann(m - 1, 1);
    }

    else {
        return ackermann(m - 1, ackermann(m, n - 1));
    }

}

int main (int argc, char *argv[]) {



    // variables
    unsigned long m = 4;
    unsigned long n = 3;

    unsigned long result;

    // evaluate Ackerman function
    result = ackermann(m, n);

    // print the result
    printf("Ackermann(%lu, %lu) = %lu\n", m, n, result);

}