#include<stdio.h>
#include<math.h>

char filename[256];
FILE *InFile = NULL;
double a[20][20];
int N;

// Solves an arbitrary system of equations

// function to print matrix content at any stage
void print() {
    for (int i = 0; i < N; i++, printf("\n"))
        for (int j = 0; j <= N; j++)
            printf("%lf ", a[i][j]);

    printf("\n");
}

//print result as rational approximation fraction
void rat_approx(double f, int64_t md) {
//    if(fabs(f)<0.000001){
//        //printf("%lf\n",fabs(f));
//        printf("0\n");
//        return;
//    }

    //printf("%20.16lf\n",f);
    int64_t num, denom;
    /*  q: continued fraction coefficients. */
    int64_t q, h[3] = {0, 1, 0}, k[3] = {1, 0, 0};
    int64_t x, d, n = 1;
    int i, neg = 0;


    if (f < 0) {
        neg = 1;
        f = -f;
    }

    while (f != floor(f)) {
        n <<= 1;
        f *= 2;
    }
    d = f;

    /* continued fraction and check denominator each step */
    for (i = 0; i < 64; i++) {
        q = n ? d / n : 0;
        if (i && !q) { break; }

        x = d;
        d = n;
        n = x % n;

        x = q;
        if (k[1] * q + k[0] >= md) {
            x = (md - k[0]) / k[1];
            if (x * 2 >= q || k[1] >= md) {
                i = 65;
            } else {
                break;
            }
        }

        h[2] = x * h[1] + h[0];
        h[0] = h[1];
        h[1] = h[2];
        k[2] = x * k[1] + k[0];
        k[0] = k[1];
        k[1] = k[2];
    }
    denom = k[1];
    num = neg ? -h[1] : h[1];
    printf("%lld/%lld\n", num, denom);
}

// swapping
void swap_row(int i, int j) {
    printf("Swapped rows %d and %d\n", i, j);
    for (int k = 0; k <= N; k++) {
        double temp = a[i][k];
        a[i][k] = a[j][k];
        a[j][k] = temp;
    }
    print();
}

// get matrix content
int forwardElim() {
    print();
    for (int k = 0; k < N; k++) {
        //print();
        // Initialize maximum value and index for pivot
        int i_max = k;
        double v_max = fabs(a[i_max][k]);

        /* find greater magnitude for pivot if any */
        for (int i = k + 1; i < N; i++) {
            if (fabs(a[i][k]) > v_max) {
                v_max = fabs(a[i][k]);
                i_max = i;
            }
        }
        printf("max=%lf\n", v_max);


        /* Swap the greatest value row with current row */
        if (i_max != k) {
            swap_row(k, i_max);
        }

        /* if a diagonal element  is zero,
         * it denotes that matrix is bad, and
         * will lead to a division-by-zero later. */
        if (a[k][k]==0) {//only trigger this if diagonal is zero after swapping
            //print();
            printf("max value=%lf\nbad element at %d, %d\n", v_max, k, i_max);
            return k; // Boo!!!
        }


        for (int i = k + 1; i < N; i++) {
            /* factor f to set current row kth element to 0,
             * and subsequently remaining kth column to 0 */
            double f = a[i][k] / a[k][k];

            /* subtract fth multiple of corresponding kth
               row element*/
            for (int j = k + 1; j <= N; j++)
                a[i][j] -= a[k][j] * f;

            /* filling lower triangular matrix with zeros*/
            a[i][k] = 0;
        }

        // print();        //for matrix state
    }
    //print();            //for matrix state
    return -1;
}

// calculate values of unknowns
void backSub() {
    double x[N];  // An array to store solution

    /* Start calculating from last equation up to the
       first */
    for (int i = N - 1; i >= 0; i--) {
        /* start with the RHS of the equation */
        x[i] = a[i][N];

        /* Initialize j to i+1 since matrix is upper
           triangular*/
        for (int j = i + 1; j < N; j++) {
            /* subtract all the lhs values
             * except the coefficient of the variable
             * whose value is being calculated */
            x[i] -= a[i][j] * x[j];
        }

        /* divide the RHS by the coefficient of the
           unknown being calculated */
        x[i] = x[i] / a[i][i];

    }

    printf("\nSolution for the system:\n");
    for (int i = 0; i < N; i++) {
        //double r=round(x[i]);
        //double f=fabs(round(x[i]) - x[i]);
        if (fabs(x[i]) < 0.00001) {
            printf("0\n");
        } else if (fabs(round(x[i]) - x[i]) > 0.0000000001) {
            //printf("%20.16lf\n", round(x[i]));
            rat_approx(x[i], 2000);
            continue;
        } else {
            printf("%d\n", (int) (round(x[i])));
        }
        //printf("%lf\n", x[i]);
    }
}


// row reduce
void gaussianElimination() {
    /* reduction into r.e.f. */
    int singular_flag = forwardElim();

    /* if matrix is singular */
    if (singular_flag != -1) {
        //printf("Singular Matrix.\n");

        /* if the RHS of equation corresponding to
           zero row  is 0, * system has infinitely
           many solutions, else inconsistent*/
        if (a[singular_flag][N]) {
            printf("Inconsistent.\n");

        } else {
            printf("Underdetermined.\n");
        }

        return;

    }
    /* get solution to system and print it using
       backward substitution */
    backSub();
}


// Main method
int main() {
    /* open file */
    do {
        printf("\nInput filename: ");
        scanf("%s", filename);
        InFile = fopen(filename, "r");
    } while (InFile == NULL);
    fscanf(InFile, "%d", &N);
/**
 * first dim. is row and second is column
 * **/
    /* Reading Matrix */
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++) {
            fscanf(InFile, "%lf", &a[i][j]);
        }
    }
    gaussianElimination();

    return 0;
}
