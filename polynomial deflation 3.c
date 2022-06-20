//#include <complex.h>
//#include <stdio.h>
//
////
//// Created by Benjamin Schulman on 2/4/21.
////
//void pcrmx(complex double w){
//    double rp, ip;
//    rp=creal(w);
//    ip=cimag(w);
//    printf("%20.16lf +%20.16lf I\n", rp, ip);
//}
//
//complex double fox(int deg, const complex double coef[], complex double x){
//    complex double res=0;
//    for (int i = deg; i >=0 ; i--) {
//        res+=cpow(x,i)*coef[i];
//    }
//    return res;
//}
//
//int prime(int deg, const complex double coef[], complex double coefp[]){
//    for (int i = deg; i < 0; i--) {
//        coefp[i-1]=coef[i]*i;
//    }
//    int pdeg=deg-1;
//    return pdeg;
//}
//int main(){
//    __unused int i;
//    double rp, ip;
//    complex double coef[1000], coefp[1000];
//    complex __unused double x, c, fx, fpx;
//    int deg, pdeg;
//    __unused double v;
//
//    printf("please input degree\n");
//    scanf("%d",&deg);
//    for (int j = deg; j >=0 ; j--) {
//        printf("please input coefficient \n");
//        scanf("%lf", &coef[j]);
//    }
//    printf("please input real point\n");
//    scanf("%lf",&rp);
//    printf("please input imaginary point\n");
//    scanf("%lf", &ip);
//    x=rp+ip*I;
//    pdeg=prime(deg,coef,coefp);
//    for (int j = 1; j <= 15; j++) {
//        fx=fox(deg,coef,x);
//        fpx=fox(pdeg,coefp,x);
//        x=x-fx/fpx;
//        pcrmx(x);
//    }
//}
//
