#include <printf.h>

/**
 * function to be evaluated
 * @param x: value at which to evaluate function
 * @return function value at specified input
 */

double f(double x){
    return x/(x*x+1);
}

/**
 * ** method stores left y-value in one variable (value_left) and right y-value in another (value_right)
 * ** once function uses value_left, value_left is reassigned to the valued store in value_right
 * ** and value_right is reassigned to function evaluated at x+=width.
 * @param n: number of rectangles
 * @param width: size of rectangles
 * @param x: starting point (on left)
 * @return area under curve using trapezoid method
 */
double find_area(int n, double width, double x){
    double value_left,
           value_right=f(x), //left and right y-values
           area=-0.5*value_right*width;
    for (int i = 0; i < n; i++) {
        value_left = value_right;
        area+=value_left*width;
        x+=width;
        value_right=f(x);
    }
    return area + 0.5 * width * value_right;
}

/**
 * scan for input: left endpoint, right endpoint, then number of trapezoids
 * then print area
 * @return 0 if it runs successfully
 */

int main() {
    double a,b;
    int n;
    printf("Input a, then b, then n please\n");
    scanf("%lf %lf %d", &a, &b, &n);
    printf("%lf", find_area(n,(b-a)/n, a));
    return 0;
}