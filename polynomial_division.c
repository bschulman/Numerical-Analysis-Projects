#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>

//data type for terms
struct Node {
    double complex coef;
    struct Node *next;
} Node_t;

static struct Node *remaind;

//define polynomial data type
typedef struct {
    int power;
    //first term is highest power
    struct Node *first_term;
} poly_t, *poly;


/* pass in negative power to have a zeroed polynomial */
poly create_polynomial(int power) {
    int zeroed = 0;
    if (power <= 0) {
        power = -power;
        zeroed = 1;
    }
    //p points to our polynomial
    poly p_local = NULL;
    p_local = malloc(sizeof(poly_t));
    p_local->first_term = malloc(sizeof(Node_t));
    if (power > 0) {
        p_local->first_term->next = malloc(sizeof(Node_t));
        p_local->first_term->next = NULL;
    }
    //define polynomial
    p_local->power = power;
    struct Node *current_term;
    current_term = p_local->first_term;
    if (zeroed == 1) {
        for (int i = 0; i <= power; i++) {
            current_term->coef = 0;
            current_term->next = malloc(sizeof(Node_t));
            if (i == power) {
                current_term->next = NULL;
            } else {
                current_term = current_term->next;
            }
        }
    } else {
        double rp, ip;
        rp = ip = 0;
        for (int j = p_local->power; j >= 0; j--) {
            printf(" %i'th coefficient real part, please, followed by imaginary part, input! \n", j);
            scanf("%lf %lf", &rp, &ip);
            current_term->coef = rp + ip * I;
            if (j != 0) {
                current_term->next = malloc(sizeof(Node_t));
                current_term = current_term->next;
            } else {
                current_term->next = NULL;
            }
        }
    }
    return p_local;
}

void print_polynomial(poly p) {
    double real, imag;
    struct Node *current_term;
    current_term = p->first_term;
    for (int i = 0; i <= p->power; i++) {
        imag = cimag(current_term->coef);
        real = creal(current_term->coef);
        current_term = current_term->next;
        printf("(%lf + %lf*I)*x^%i ", real, imag, p->power - i);
        if (i < p->power) {
            printf("+ ");
        }
    }
    printf("\n");
}


/* p: dividend;  d: divisor;  r: remainder; returns quotient */
poly divide(poly p, poly d) {

    poly q; //quotient
    int power = p->power - d->power;

    double complex ratio, r[p->power + 1];

    if (power < 0) {
        return 0;
    }

    struct Node *current_p_term;
    current_p_term = p->first_term;
    //initialize quotient polynomial with all zero terms and same degree as dividend
    q = create_polynomial(-power);
    //load remainder array
    for (int i = 0; i <= p->power; ++i) {
        r[i] = current_p_term->coef;
        current_p_term = current_p_term->next;
    }

    //declare and initialize quotient chain
    struct Node *current_q_term = NULL;
    //iterate through from dividend degree down to divisor degree
    for (int i = p->power; i >= d->power; i--) {
        //obtain i-d->power'th term of quotient
        current_q_term = q->first_term;
        for (int k = 0; k <= d->power - i; ++k) {
            if (current_q_term->next != NULL) {
                current_q_term = current_q_term->next;
            }
        }
        //set i-d->power'th quotient term to ratio
        ratio = r[i] / d->first_term->coef;
        current_q_term->coef = ratio;
        r[i] = 0;

        struct Node *temp_d_term;
        temp_d_term = d->first_term;
        double complex d_coef[d->power + 1];
        for (int j = 0; j <= d->power; ++j) {
            d_coef[d->power - j] = temp_d_term->coef;
            temp_d_term = temp_d_term->next;
        }

        for (int j = d->power; j > 0; j--) {
            r[i - d->power + j] -= d_coef[j] * ratio;
        }
    }
    struct Node *first_remain_term;
    first_remain_term = malloc(sizeof(Node_t));
    current_p_term = first_remain_term;
    for (int i = 0; i < p->power; i++) {
        current_p_term->coef = r[i];
        if (i != p->power) {
            current_p_term->next = malloc(sizeof(Node_t));
            current_p_term = current_p_term->next;
        } else {
            current_p_term->next = NULL;
        }
    }
    remaind = first_remain_term;
    return q;
}


int main() {
    int deg;
    printf("please input degree of dividend\n");
    scanf("%d", &deg);

    poly p = create_polynomial(deg);
    printf("please input degree of divisor\n");
    scanf("%d", &deg);

    poly d = create_polynomial(deg);
    poly q = divide(p, d);

    printf("dividend: ");
    print_polynomial(p);
    printf("divisor:  ");
    print_polynomial(d);
    printf("quotient: ");
    print_polynomial(q);
    printf("remainder:  ");
    double real;
    double imag;
    struct Node *n0de = remaind;
    for (int i = 0; i <= p->power; ++i) {
        imag = cimag(n0de->coef);
        real = creal(n0de->coef);
        printf("(%lf + %lf * I)*x^%i ", real, imag, p->power - i);
        if (i < p->power) {
            printf("+ ");
        }
        if (n0de->next != NULL) {
            n0de = n0de->next;
        }
    }
    return 0;
}
