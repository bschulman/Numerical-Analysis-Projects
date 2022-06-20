#include<stdio.h>
#include<math.h>

/*******
 Function that performs Gauss-Elimination on a Tridiagonal system and returns the Upper triangular matrix and solution of equations:
There are two options to do this in C.
1. Pass the augmented matrix (a) as the parameter, and calculate and store the upperTriangular(Gauss-Eliminated Matrix) in it.
2. Use malloc and make the function of pointer type and return the pointer.
This program uses the first option.
********/
char filename[256];
FILE *InFile = NULL;
int n;
double L[20], D[20], R[20], Q[20], X[20];

void tridiagonal() {

// Create temporary vectors
    double c[n];
    double d[n];

// This updates the coefficients in the first row
// Note that we should be checking for division by zero here
    c[0] = R[0] / D[0];
    d[0] = Q[0] / D[0];

// Create the c and d coefficients in the forward sweep
    for (int i = 1; i < n; i++) {
        double m = 1.0 / (D[i] - L[i] * c[i - 1]);
        c[i] = c[i] * m;
        d[i] = (Q[i] - L[i] * d[i - 1]) * m;
    }

// This is the reverse sweep, used to update the solution vector X
    for (int i = n - 1; i-- > 0;) {
        X[i] = d[i] - c[i] * Q[i + 1];
    }
}



int main() {
    printf("Input number of points\n");
    scanf("%i",&n);
    printf("\nInput left diagonal values\n");
    for (int i = 0; i < n-1; ++i) {
        scanf("%lf",&L[i]);
    }
    printf("\nInput diagonal values\n");
    for (int i = 0; i < n-1; ++i) {
        scanf("%lf",&D[i]);
    }
    printf("\nInput right diagonal values\n");
    for (int i = 0; i < n-1; ++i) {
        scanf("%lf",&R[i]);
    }
    printf("\nInput right column values\n");
    for (int i = 0; i < n-1; ++i) {
        scanf("%lf",&Q[i]);
    }
    tridiagonal();

    printf("\nThe solution of linear equations is:\n\n");
    for (int i = 0; i < n - 1; i++) {
        printf("x[%d]=\t%lf\n", i + 1, X[i]);
    }
}