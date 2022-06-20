#include <stdio.h>
//#include "Taylor_header_info.txt"

#include "TaylorS.c"
#include <math.h>
#include <stdlib.h>


        int Tdegree;

int copy_T(double dest[], const double source[])
{
    int k;
    for (k = 0; k <= Tdegree; k++) {
        dest[k] = source[k];
    }
    return 1;
}


int make_constant_T(double t[], double v) {
    int k;
    for (k = 0; k <= Tdegree; k++) t[k] = 0;
    t[0] = v;
    return 1;
}


int make_variable_T(double t[], double v)
// essentially makes a linear with value, v
{
    int k;
    for (k = 0; k <= Tdegree; k++) t[k] = 0;

    t[0] = v;
    t[1] = 1;
    return 1;
}


int print_T(char before[], char control[], double t[], char after[])
// control is the control string for the doubles
// that will be printed
{
    int k;

    printf("%s", before);
    printf("[");
    for (k = 0; k <= Tdegree; k++) {
        printf(control, t[k]);
        if (k != Tdegree) { printf(","); }
    }
    printf("]");
    printf("%s", after);
    return 1;
}


int scan_T(double t[]) {
    int k, i;
    char s[100];
    double x;

    k = -1;
    i = scanf("%s", s);// [

    while (1) {
        i = scanf("%lf", &x);
        t[++k] = x;

        i = scanf("%s", s); // comma or ]
        if (s[0] == ']') break;
    }

    Tdegree = k;

}



//////////////////////////////////////////////////////////
// should be safe for any and all of these parameter
// pointers to point to same things



int Add_cons_T(double r[], double constant)
// r =  r + constant
{
    r[0] += constant;
    return 1;
}


int Mul_cons_T(double r[], double constant)
// r =  r * constant
{
    int n;

    for (n = 0; n <= Tdegree; n++) {
        r[n] *= constant;
    }
    return 1;
}


int Add_T(double r[], double u[], double v[])
// r = u + v
{
    int k;

    for (k = 0; k <= Tdegree; k++) {
        r[k] = u[k] + v[k];
    }

    return 1;
}


int Sub_T(double r[], double u[], double v[])
// r = u - v
{
    int k;

    for (k = 0; k <= Tdegree; k++) {
        r[k] = u[k] - v[k];
    }

    return 1;
}


int Mul_T(double r[], double u[], double v[])
// r = u * v
{
    int n, k;
    double sum;
    double p[1000];

    for (n = 0; n <= Tdegree; n++) {

        sum = 0.0;
        for (k = 0; k <= n; k++) {
            sum = sum + u[k] * v[n - k];
        }

        p[n] = sum;
    }

    copy_T(r, p);
    return 1;

}

int exp_T (double r[],  double u[]) {
    int n, k;
    double sum;
    double p[1000];
    p[0]= exp(u[0]);
    for (n = 1; n < Tdegree; n++) {
        sum=0.0;
        for ( k = 1; k < n; k++) {
           sum+=k*u[k]*p[n-k];
        }
        p[n] = sum;
    }
    copy_T(r, p);
    return 1;
}

int ln_T  (double r[],  double u[]){
    int n, k;
    double sum;
    double p[1000];
    p[0]= log(u[0]);
    for (n = 1; n < Tdegree; n++) {
        sum=0.0;
        for ( k = 1; k < n-1; k++) {
            sum+=k*u[n-k]*p[k];
        }
        p[n] =(n*u[n]- sum)/(n*u[0]);
    }
    copy_T(r, p);
    return 1;
}
//return r, divide u by v
void Div_T(double r[], double u[], double v[]) {
    double p[Tdegree];
    p[0]=u[0]/v[0];
    //u = r* v
    Mul_T(u,p,v);
    copy_T(r, p);
}


int cossin_T (double c[], double s[], double u[]){
    double sum_s;
    double sum_c;
    c[0]= cos(u[0]);
    s[0]= sin(u[0]);
    for (int n = 1; n < Tdegree; n++) {
        sum_s=0.0;
        sum_c=0.0;
        for (int k = 1; k < n; ++k) {
            sum_s+=k*c[n-k]*u[k];
            sum_c+=k*s[n-k]*u[k];
        }
        s[n]=sum_s/n;
        c[n]=-1*sum_c/n;
    }
}
// c = cos(u) , s = sin(u)


int cos_T (double r[],  double u[]){


}
// r = cos(u)


int sin_T (double r[],  double u[])
// r = sin(u)


int tan_T (double r[],  double u[]){
    double temp[Tdegree];
    copy_T(temp,r);
    double s[Tdegree];
    double c[Tdegree];
    cossin_T(c,s,u);
    div_t(temp,s,c);
    copy_T(r,temp);
}
// r = tan(u)


int sqrt_T (double r[],  double u[]){


}
// r = sqrt(u)


int cpow_T (double r[], double u[], double cpow){
    int n, k;
    double sum;
    double p[Tdegree];
    p[0]=pow(u[0],cpow);
    for (int i = 1; i < Tdegree; ++i) {
        sum=0.0;
        for (int j = 0; j < i; ++j) {
            sum+=(cpow-i+1)*pow(u[j+1],i-j);
        }
        p[i]=cpow*pow(u[0],cpow-i)*sum;
    }
    copy_T(r, p);
    return 1;
}
// r = u^cpow    where cpow is constant


int cbrt_T (double r[],  double u[]);
// r = cbrt(u)




int atan_T (double r[], double u[]);
// r = atan(u)

int main()
//  Find the Taylor sequence for
//  exp(2x) / (1 + x^2)
//  with x = 2.5 through degree 10.
{
    double x[100], A[100], B[100], C[100];

    Tdegree = 10;

    make_variable_T(x, 2.5);
    copy_T(A, x); // A = x
    Mul_cons_T(A, 2.0); // A = 2x
    exp_T(A, A); // A = exp(2x)
    Mul_T(B, x, x); // B = x^2
    Add_cons_T(B, 1.0); // B = 1 + x^2
    Div_T(C, A, B); // C = exp(2x) / (1 + x^2)

    print_T("The answer is ", " %e", C, "\n");
}

