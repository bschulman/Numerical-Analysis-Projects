#include <stdio.h>

double f(double x){
    double value, denominator;
    denominator=x*x+1;
    value = x/denominator;
    return value;
}

double find_area(int n, double width, double x){
    double area;
    area=0;
    for (int i = 0; i < n; i++) {
        area+=f(x)*width;
        x+=width;
    }
    return area;
}

int main() {
    double a,b;
    int n;
    printf("Input a, then b, then n please\n");
    scanf("%lf %lf %d", &a, &b, &n);
    printf("%lf", find_area(n,(b-a)/n, a));
    return 0;
}
