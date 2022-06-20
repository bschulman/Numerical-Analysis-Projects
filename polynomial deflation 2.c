#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdlib.h>

//struct Node {
//    double power;
//    complex double coefficient;
//    struct Node* next;
//};
//
//static double complex sum;
//
//__unused double complex f(double complex x){
//  return 2*x*x*x-9*x*x+32*x+75;
//}
//
//double complex evaluate_polynomial(double complex value, struct Node *current_term){
//    sum=0;
//    while(current_term->next!=NULL){
//        sum=sum+pow(value,current_term->power)*current_term->coefficient;
//        current_term=current_term->next;
//    }
//    printf("%20.16lf + %20.16lf*I, ", creal(sum),cimag(sum));
//    return sum;
//}
//
//double complex evaluate_derivative(double complex value, struct Node *current_term){
//    sum=0;
//    while(current_term->next!=NULL){
//        sum=sum+pow(value,current_term->power-1)*current_term->coefficient*current_term->power;
//        current_term=current_term->next;
//    }
//    return sum;
//}
//
//double complex newton(double complex value, struct Node *first_term) {
//    double complex ep, ed;
//    ep = evaluate_polynomial(value, first_term);
//    ed = evaluate_derivative(value, first_term);
//    return value - ep / ed;
//}
//
//struct Node * define_new_node(struct Node node){
//    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
//    node.next=&new_node;
//    new_node->next=NULL;
//    return new_node;
//}
//
// int main(){
//     static struct Node first_term;
//    struct Node current_term;
//
//  double real, imaginary;
//  real=0;
//  first_term.coefficient=0;
//  char doneness='n';
//     (struct Node *) malloc(sizeof(struct Node));
//     printf("Enter real component of power: ");
//          scanf("%lf\n", &first_term.power);
//          printf("Enter real component of coefficient: ");
//          scanf("%lf\n", &real);
//          printf("Enter imaginary component of coefficient: ");
//          scanf("%lf\n", &imaginary);
//          first_term.coefficient = real + imaginary * I;
//          printf("Done, y or n?");
//          scanf("%s \n", &doneness);
//     first_term.next=&current_term;
//     while(doneness=='n'){
//         current_term.next = define_new_node(current_term);
//          printf("Enter power: ");
//          scanf("%lf\n", &current_term.power);
//          printf("Enter real component of coefficient: ");
//          scanf("%lf\n", &real);
//          printf("Enter imaginary component of coefficient: ");
//          scanf("%lf\n", &imaginary);
//          current_term.coefficient = real + imaginary * I;
//          printf("Done, y or n?");
//          scanf("%c\n", &doneness);
//         struct Node* new_node = (struct Node*)malloc(sizeof(struct Node) );
//         current_term.next=new_node;
//      }
//current_term.next=NULL;
//  double complex x;
//  int count;
//  printf("Enter real component of guess, imaginary component of guess, then desired iterations:");
//  fflush (stdin);
//  scanf(" %lf %lf %i",&real, &imaginary, &count);
//  x=real+imaginary*I;
//  for (int i = 0; i < count; i++) {
//    //double complex f1;
//    //x=x-f1/dfdx(x);
//    printf("%3d: ", i);
//    x=newton(x, &first_term);
//    // double f1c;
//    // f1c=cimag(f1);
//    // double f1r;
//    // f1r=creal(f1);
//    real=creal(x);
//    imaginary=cimag(x);
//    printf("%20.16lf + %20.16lf*I\n", real,imaginary);
//  }
//}
//// int take_input(){
////   current_term&=first_term;
////   char doneness='n';
////   while(doneness=='n'){
////   current_term=current_term->next;
////   printf("Enter real component of power: ");
//// 	scanf("%lf", &real);
////
////   printf("Enter imaginary component of power: ");
//// 	scanf("%lf", &imaginary);
////   current_term->power=real+imaginary*I;
////
////   printf("Enter real component of coefficient: ");
//// 	scanf("%lf", &real);
////   printf("Enter imaginary component of coefficient: ");
////   scanf("%lf", &imaginary);
////   current_term->coefficient=real+imaginary*I;
////   printf("Done, y or n?");
////   scanf("%c\n", &doneness);
//// }
//// current_term->next=NULL;
//// return 0;
//// }
int main() {
//    double x;
//    for (x = 0; x < 1.0; x = x + 0.1) {
//        printf("%lf\n", x);
//    }
//    x=0;
//    while(x<1){
//        printf("%lf\n", x);
//        x+=0.25;
//        }
    /*unsigned*/ int x, y, z;
    x=2000000000;
    y=1000000001;
    z=x+y;
    //printf("%u\n", z);
    printf("%d\n", z);
    }
