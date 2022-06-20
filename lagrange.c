/*
In a Linux environment,
if this file and the file, FPToolkit.c, are in the
same directory that you are trying to compile in,
do the following :

cc  FPToolkitDemoQ.c   -lm  -lX11

lm links to math library

don't need to include math.h, stdio.h, etc because FPToolkit includes all those

note : the 'X' in -X11 is capitalized

after compiling, run as usual.
*/

int numpoints;
#include  "FPToolkit.c"
double x_values[20];
double y_values[20];
//double quotes means look in same directory as the file


double evaluate(double x){
  double return_value=0;
  //current_node is the term in the sum
  for (int i = 0; i < numpoints; i++) {
    // if(x==100){
    // //  printf("%lf, %lf\n", current_node->x, current_node->y );
    // //  printf("%lf\n", first_node->next->x);
    // printf("%d\n", i);
    // }
    double temp=y_values[i]; //each term
    for (int j = 0; j < numpoints; j++) { //multiply in the (x_i-x_j)... and (x-x_i)
      //    printf("I make it to hear\n");
      if(i!=j){
        temp*=(x-x_values[j])/(x_values[i]-x_values[j]);
      }
    }
    return_value+=temp;
  }
  //printf("%lf\n", return_value);
  return return_value;
}

void lagrange(){ // draws function and passes point to evaluate to evaluative function
  G_rgb (0.0, 1, 0.5) ; // green
  double second_y;
  double first_y=evaluate(0);
  for (int i = 1; i < 400; i++) {
    second_y=evaluate(i);
    if(second_y<550){
      G_line (i-1,first_y, i,second_y);
      G_fill_circle(i-1,second_y,0.5);
      first_y=second_y;
    }
  }
  return;
}

int main()
{

  //   double lowleftx, lowlefty, width, height ;
  //   double x[10], y[10], numxy ;
  //   double a[20], b[20], numab ;
  //graphic window 400x600
  G_init_graphics (400,600) ;  // interactive graphics
  //first thing you do to do graphics, gives huge array of pixels with 0,0
  //at the lower left corner

  // clear the screen in a given color
  G_rgb (0.3, 0.3, 0.3) ; // dark gray
  G_clear () ;//gray pixels over entire screen
  G_rgb (0.0, 0.0, 1.0) ; // blue
  G_fill_rectangle (0, 550, 400, 50) ;
  printf("click in blue rectangle when done clicking points plz\n" );
  //===============================================
  int last_point=0;
  numpoints=0;
  G_rgb(1,0,0);
  while (last_point==0){
    double p[2];
    G_wait_click(p) ; //wait for user to move mouse and click point
    // x and y coordinates of point are stored in array p
    printf("%lf, %lf\n", p[0],p[1]);
    G_fill_circle(p[0],p[1],2);
    x_values[numpoints]=p[0];
    y_values[numpoints]=p[1];
    numpoints++;
    if(p[1]>550){
      last_point=1;
      numpoints--;
      G_rgb (0.0, 0.0, 1.0) ;
      G_fill_circle(p[0],p[1],2);
    }
  }

  //return 0;
  lagrange();
  int key ;
  key =  G_wait_key() ; // pause so user can see results

  G_save_to_bmp_file("demo.bmp") ;
  return 0;

}
