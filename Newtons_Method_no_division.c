#include <stdio.h>



double newton(double guess) {

    for (int i = 0; i < 50; ++i) {
        //printf("%lf + %lfI - ", creal(guess),cimag(guess));
        guess = 2*guess - 7*guess*guess;
        printf("%20.16lf\n",guess);
    }
    return guess;
}

int main() {
    newton(.2);
    return 0;
}
