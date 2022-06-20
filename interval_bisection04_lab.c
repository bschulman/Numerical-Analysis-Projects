/*

The interval bisection method works iff
the function is continuous and you can
establish an initial left & right guess,
such that:
   f(left) and f(right) have different signs
(i.e.: one is positive and the other negative)

COMPILE THIS CODE BY RUNNING:

gcc interval_bisection04_lab.c -lm

The -lm links with the math library

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

double f1 (double x)
{
  double y ;
  y = x*x - 2 ;
  return y ;
}

double f2 (double x)
{
  double y ;
  y = x*x*x - 30*x - 36 ;
  return y ;
}

// f points at a function with one double input and a double output
double * interval_bisection(double (*f)(double x),
		       double left, double right,
		       double epsilon, int maxreps)
{
  //printf("f(%f)=%f\n", left,f(left));
  //printf("f(%f)=%f\n", right,f(right));
  static double output[3];
  //output[0] stores current x value;
  //output[1] stores current y value;
  //output[2] stores number of repititions
  if ((f(right)>0 && f(left) >0) || (f(right)<0 && f(left)<0)) {
    // return 0 failure, else 'numreps' (>= 1)
    output[2]=0;
    return output;
  }
  bool is_r_neg;
  bool is_m_neg;
  int i=0;//number of repititions
  while (i < maxreps) {
    output[2]=i;
    // 'maxreps' is the maximum iterations through the loop
    double interval=right-left;
    if (interval<=epsilon) {
      return output;
    }
    // The algorithm should continue until 'maxreps' iterations have been
    // performed or the width of the interval is within 'epsilon'
    else {
      //printf("%d\n", i);
      output[0]=(right+left)/2;//output[0] is always midpoint
      output[1]=f(output[0]);
      is_r_neg=f(right)<0;
      is_m_neg=output[1]<0;
      //output[1] is always function evaluated at midpoint
      //printf("f(%f)=%f, %f, %f, %d\n", output[0],output[1], left,right, i);
      if (is_r_neg&&is_m_neg) {
        //printf("here\n" );
        //if both right and midpoint negative, set right to midpoint
        right=output[0];
      }
      else if(is_r_neg&&!is_m_neg){
        left=output[0];
      }//if right is negative and midpoint is positive then set left to midpoint
      else if (!is_r_neg&&is_m_neg) {
        left=output[0];
      }//if right is positive and midpoint is negative set left to midpoint
      else if (!is_r_neg&&!is_m_neg) {
        right=output[0];
      }//if right is positive and midpoint is positive set right to midpoint
    }
    i++;
  }
  //printf("%f\n",output[2] );
  return output;
  }

int main()
{
  int maxreps, numr;
  double left_guess,right_guess;
  double * res;

  // test #1:

  left_guess  = 1 ;
  right_guess = 2 ;

  maxreps = 100 ;
  res = interval_bisection(f1, left_guess,right_guess,  1e-12, maxreps) ;
  if (res[2] == 0) {
    printf("Failure to find a root.\n") ;
  } else {
    numr=res[2];
    printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",res[0],res[1],numr,maxreps) ;
  }

  //////////////////////////////////////////////////////////////


  // test #2 :

  res = interval_bisection(sin, 3,4,  1e-12, 50) ;
  if (res[2] == 0) {
    printf("Failure to find a root.\n") ;
  } else {
    numr=res[2];
    printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",*(res + 0),*(res + 1),numr,maxreps) ;
  }

  /////////////////////////////////////////////////////////////

  // test #3:

  printf("Enter left,right for root search : ") ;
  scanf("%lf %lf",&left_guess,&right_guess) ;

  maxreps = 100 ;
  res = interval_bisection(f2, left_guess,right_guess,  1e-12, maxreps) ;

  if (res[2] == 0) {
    printf("Failure to find a root.\n") ;
  } else {
    numr=res[2];
    printf("f(%lf) = %lf, numreps/maxreps = %d/%d\n",res[0],res[1],numr,maxreps) ;
  }

}
