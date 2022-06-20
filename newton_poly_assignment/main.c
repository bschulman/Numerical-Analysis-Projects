#include <stdio.h>
#include <complex.h>
#include <stdlib.h>

struct Node {
    double complex coef;
    struct Node *next;
} Node_t;

double complex evaluate(struct Node *poly, double complex x, int degree) {
    double complex coeff[degree + 1];
    struct Node *current_node = NULL;
    current_node = poly;
    for (int i = 0; i < degree + 1; i++) {
        coeff[i] = current_node->coef;
        current_node = current_node->next;
    }

    double complex result = coeff[0];  // Initialize result
    double complex derivative = coeff[0] * degree;
    // Evaluate value of polynomial
    for (int i = 1; i < degree + 1; i++) {
        result = result * x + coeff[i];
        if (i != degree) {
            derivative = derivative * x + coeff[i] * (degree - i);
        }
    }
    if (derivative != 0) {
        double complex r = result / derivative;
        //printf("%lf + %lfI", creal(r), cimag(r));
        return r;
    }
    return result / (derivative - 0.01 + 0.01 * I);
}


double complex newton(struct Node *poley, int degree) {

    double complex guess = 0.1 + 0.1 * I;
    for (int i = 0; i < 50; ++i) {
        //printf("%lf + %lfI - ", creal(guess),cimag(guess));
        guess = guess - evaluate(poley, guess, degree);
        //printf(" = %lf + %lf*I\n",creal(guess), cimag(guess));
    }
    return guess;
}

int main() {
    int deg;
    scanf("%i", &deg);
    int arraysize = deg + 1;
    double complex po1y[arraysize];
    double rp;
    rp = 0;
    for (int i = 0; i <= deg; ++i) {
        scanf("%lf", &rp);
        po1y[i] = rp + 0 * I;
    }
    struct Node *polee = NULL;
    polee = malloc(sizeof(Node_t));
    struct Node *current_node = NULL;
    double complex roots[deg];
    int permadeg = deg;
    for (int i = 0; i < permadeg; i++) {
        current_node = NULL;
        current_node = polee;
        for (int a = 0; a < deg + 1; a++) {
            current_node->coef=po1y[a];
            current_node->next = malloc(sizeof(Node_t));
            current_node = current_node->next;
        }
        roots[i] = newton(polee, deg);
        printf("%lf + %lfI\n", creal(roots[i]), cimag(roots[i]));
        printf("***************************\n");
        if (deg != 0) {
            double complex po2y[deg];
            po2y[0] = po1y[0];
            for (int k = 1; k <= deg; k++) {
                po2y[k] = (po2y[k - 1] * roots[i]) + po1y[k];
            }
            deg--;
            for (int l = 0; l <= deg; l++) {
                po1y[l] = po2y[l];
                //printf("(%lf + %lfI)x^%i", creal(po1y[l]), cimag(po1y[l]), deg - l);
            }
        }
    }
    return 0;
}