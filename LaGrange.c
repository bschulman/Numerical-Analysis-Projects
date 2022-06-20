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

//data type for terms
struct Node {
    double x, y;
    struct Node *next;
} Node_t;
int numpoints=0;
#include  "FPToolkit.c"
//double quotes means look in same directory as the file
int    swidth, sheight;
double evaluate(double x, struct Node* node){
    double return_value;
    struct Node *current_node;
    current_node = node;
        for (int i = 0; i < numpoints; i++) {
            double temp=current_node->y;
             //current node is the term we're on
            struct Node *temp_node=NULL; //temp node is the value within the term
            temp_node=node;
            for (int j = 1; j < numpoints; j++) { //multiply in the (x_i-x_j)... and (x-x_i)
                if(temp_node->x!=current_node->x){
                    temp*=(x-temp_node->x)/(current_node->x-temp_node->x);
                }
                temp_node->next = malloc(sizeof(Node_t));
                temp_node=temp_node->next;
            }
            current_node->next = malloc(sizeof(Node_t));
            current_node=current_node->next;
            return_value+=temp;
        }
    return return_value;
}

int lagrange(struct Node* node){ // draws function and chooses point to evaluate
    G_rgb (0.0, 0.0, 1.0) ; // change color
    for (int i = 0; i < 400; ++i) {
        G_point (i, evaluate(i,node));
    }
    return 0;
}

int main()
{

//   double lowleftx, lowlefty, width, height ;
//   double x[10], y[10], numxy ;
//   double a[20], b[20], numab ;

   swidth = 400 ;  sheight = 600 ; // 600x600 is about the largest Repl supports
		//graphic window 400x600
   G_init_graphics (swidth,sheight) ;  // interactive graphics
	 //first thing you do to do graphics, gives huge array of pixels with 0,0
   //at the lower left corner
   
   // clear the screen in a given color
   G_rgb (0.3, 0.3, 0.3) ; // dark gray
   G_clear () ;//gray pixels over entire screen
   
//   // draw a point
//   G_rgb (1.0, 0.0, 0.0) ; // change color to red
//   G_point (200, 580) ; // plot point at 200(halfway across),580 (almost all the
//   //way up)
//
//   // draw a line
//   G_rgb (0.0, 1.0, 0.0) ; // green
//   G_line (0,0, swidth-1, sheight-1) ; //draw green diagonal line from 0,0 (lower left corner) to upper right corner
//
//   // aligned rectangles
//   G_rgb (0.0, 0.0, 1.0) ; // change color to blue
//   lowleftx = 200 ; lowlefty = 50 ; width = 10 ; height = 30 ;
//   G_rectangle (lowleftx/*coordinate of lower left x and so on*/, lowlefty, width, height) ; //use variables reminiscient of purpose of those variables
//   lowleftx = 250 ;
//   G_fill_rectangle (lowleftx, lowlefty, width, height) ;
   
//   // triangles
//   G_rgb (1.0, 1.0, 0.0) ; // yellow
//   G_triangle (10, 300,  40,300,  60,250) ;
//   G_fill_triangle (10,100,  40,100,  60,150) ;
//
//   // circles
//   G_rgb (1.0, 0.5, 0.0) ; // orange
//   G_circle (100, 300, 75) ;
//   G_fill_circle (370, 200, 50) ;
//
//   // polygons
//   G_rgb (0.0, 0.0, 0.0) ; // black
//   x[0] = 100 ;   y[0] = 100 ;
//   x[1] = 100 ;   y[1] = 300 ;
//   x[2] = 300 ;   y[2] = 300 ;
//   x[3] = 300 ;   y[3] = 100 ;
//   x[4] = 200 ;   y[4] = 175 ;
//   numxy = 5 ;
//   G_polygon (x,y,numxy) ; //give x array and y array and how many slots you're using

//   G_rgb (0.4, 0.2, 0.1) ; // brown
//   a[0] = 300 ;   b[0] = 400 ;
//   a[1] = 350 ;   b[1] = 450 ;
//   a[2] = 275 ;   b[2] = 500 ;
//   a[3] = 125 ;   b[3] = 400 ;
//   numab = 4 ;
//   G_fill_polygon (a,b,numab) ;

   //===============================================
    struct Node *current_node;
    struct Node *first_node;
    int last_point=0;
    first_node = malloc(sizeof(Node_t));
    current_node = first_node;
    int p[2];
    G_rgb(1,0,0) ;
    while (!last_point){
   G_wait_click((double *) p) ; //wait for user to move mouse and click point
   // x and y coordinates of point are stored in array p
   numpoints++;
   G_fill_circle(p[0],p[1],2) ;
   current_node->x=p[0];
   current_node->y=p[1];
   current_node->next = malloc(sizeof(Node_t));
   current_node=current_node->next;

   last_point =  G_wait_key() ; // pause so user can see results
	//when you hit a key, the ASCII code of the key will be stored in variable called key.
	//the wait keys allows the user one last chance to see the picture
        }
    G_save_to_bmp_file("demo.bmp") ;
    return lagrange(first_node);
}