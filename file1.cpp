#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined(MACOSX)
#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else //linux
#include <GL/gl.h>
#include <GL/glut.h>
#endif

//other includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#define TRUE 1
#define FALSE 0

/****set in main()****/
//the number of pixels in the grid
FILE *fp = fopen("in.txt", "r+");
FILE *fp1;
int grid_width;
int grid_height;
int a1,b1,a2,b2;
int a;
int sum;
int multiply[3][1];
int m1[3][3],m2[3][1];
float d[10][20],e[20][20],f[10];
int npoly,npoly1;
int n,v,q=1,sq;
float alpha,beeta;
float angle,tx,ty;
double xmin,xmax,ymin,ymax;
typedef unsigned int outcode;
enum{TOP=0x1,BOTTOM=0x2,RIGHT=0x4,LEFT=0x8};
int xmin1,ymin1,xmax1,ymax1;
int inter[20],c;
//double xmin,xmax,ymin,ymax;
/****set in main()****/
//the number of pixels in the grid
//the size of pixels sets the inital window height and width
//don't make the pixels too large or the screen size will be larger than
//your display size
float pixel_size;
/*Window information*/
int win_height;
int win_width; 
void init();
void idle();
void display();
void draw_pix(int x, int y);
void reshape(int width, int height);
void key(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void check();
void CSLCAD(double x0,double y0,double x1,double y1,double xmin,double xmax,double ymin,double ymax);
 void read();
        void calcs();
        void display();
        void ints(float);
        void sort(int);
void dda(int x1,int y1,int x2,int y2)
{
float m; 
int dx=(x2-x1);
int dy=(y2-y1);
m=(dy * 1.0f/dx);
draw_pix(x1,y1);
draw_pix(x2,y2);
//printf("x: %f",m);
int y,x;
y=y1;
if(m<1 && m>0)
{
  for(int i=0;i<=(x2-x1);i++)
	{
		if(y<=y2)
		{ 
			 y=y1+round(m*i);
			 
			// printf("x{%d}: %d  y{%d}: %d ",i,i,i,y);
                          
			draw_pix(i,y);
		 }    	
	 }

}
else if(m>1)
{
for(int i=0;i<=(y2-y1);i++)
	{
		if(x<=x2)
		{ 
			 x=x1+round((1/m)*i);
			 
			 //printf("x{%d}: %d  y{%d}: %d ",i,x,i,i);
                          
			draw_pix(x,i);
		 }    	
	 }
}
/*else if(-1>m)
{
for(int i=(y2-y1);i<=0;i--)
	{
		if(x<=x2)
		{ 
			 x=x1+round((1/m)*i);
			 
			 //printf("x{%d}: %d  y{%d}: %d ",i,x,i,i);
                          
			draw_pix(x,i);
		 }    	
	 }
}
else if()*/
	
}
/*int mround (float a)
{ return int (a + 0.5); }*/
void lineBres (int x0, int y0, int xE, int yE)
{
int dx = fabs (xE - x0), dy = fabs(yE - y0);
int p = 2 * dy - dx;
int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
int x, y;
/* Determine which endpoint to use as start position.*/
if (x0 > xE) {
x = xE;
y = yE;
xE = x0;
}
else {
x = x0;
y = y0;
}
draw_pix (x, y);
while (x < xE) {
x++;
if (p < 0)
p += twoDy;
else {
y++;
p += twoDyMinusDx;
}
draw_pix (x, y);
}
}

void lineDDA (float x0, float y0, float xE, float yE)
{
float dx = xE - x0, dy = yE - y0, steps, k;
float xI, yI, x = x0, y = y0;
if (fabs (dx) > fabs (dy))
steps = fabs (dx);
else
steps = fabs (dy);
xI = float (dx) / float (steps);
yI = float (dy) / float (steps);
draw_pix(round (x), round (y));
for (k = 0; k < steps; k++) {
x += xI;
y += yI;
 draw_pix(round (x), round (y));
}
}
void poly()
{
if(q==1)
{
for(int i=0;i<n;i++)
	{
int j;

	
	for(j=0;j<(f[i])-1;j++)
		{
			lineDDA(d[i][j],e[i][j],d[i][j+1],e[i][j+1]);
		}
		lineDDA(d[i][j],e[i][j],d[i][0],e[i][0]);
	}
	}
 else  
{
for(int i=0;i<n;i++)
	{
int j;

	
	for(j=0;j<(f[i])-1;j++)
		{
			lineBres(d[i][j],e[i][j],d[i][j+1],e[i][j+1]);
		}
		 lineBres(d[i][j],e[i][j],d[i][0],e[i][0]);
	}
	} 	
}
void calcs()
{ //MAX,MIN
    for(int i=0;i<f[npoly1];i++)
    {
        if(xmin1>d[npoly1][i])
        xmin1=d[npoly1][i];
        if(xmax1<d[npoly1][i])
        xmax1=d[npoly1][i];
        if(ymin1>e[npoly1][i])
        ymin1=e[npoly1][i];
        if(ymax1<e[npoly1][i])
        ymax1=e[npoly1][i];
    }
}
void ints(float z) //DEFINE FUNCTION INTS
{
    int x1,x2,y1,y2,temp,x;
    c=0;
    for(int i=0;i<f[npoly1];i++)
    {
         x1=d[npoly1][i];
        y1=e[npoly1][i];
        x2=d[npoly1][i+1];
        y2=e[npoly1][i+1];
        if(y2<y1)
        {
            temp=x1;
            x1=x2;
            x2=temp;
            temp=y1;
            y1=y2;
            y2=temp;
        }
        if(z<=y2&&z>=y1)
        {
            if((y1-y2)==0)
            x=x1;
            else // used to make changes in x. so that we can fill our polygon after cerain distance
            {
                x=((x2-x1)*(z-y1))/(y2-y1);
                x=x+x1;
            }
            if(x<=xmax1 && x>=xmin1)
            inter[c++]=x;
        }
    }
}
void sort(int z) //SORT FUNCTION
{
    int temp,j,i;

        for(i=0;i<f[npoly1];i++)
        {
            lineDDA(d[npoly1][i],e[npoly1][i],d[npoly1][i+1],e[npoly1][i+1]); // used to make hollow outlines of a polygon
        }
       
        for(i=0; i<c;i+=2)
        {
           
            lineDDA(inter[i],z,inter[i+1],z);  // Used to fill the polygon ....
        }
}
outcode CompOutCode(double ,double ,double ,double ,double ,double );
void CSLCAD(double x0,double y0,double x1,double y1,double xmin,double xmax,double ymin,double ymax)
{
    outcode outcode0,outcode1,outcodeout;
    bool accept=FALSE, done=FALSE;
    outcode0=CompOutCode(x0,y0,xmin,xmax,ymin,ymax);
    outcode1=CompOutCode(x1,y1,xmin,xmax,ymin,ymax);
  //printf("%d  %d",outcode0,outcode1);
    do
    {
        if(outcode0==0 && outcode1==0)
        {
            accept=TRUE;
            done=TRUE;
        }
        else if(outcode0 & outcode1)
            {
                done=TRUE;
            }
            else
            {
                double x,y;
                int ocd=outcode0 ? outcode0:outcode1;
                if(ocd & TOP)
                {
                    x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
                    y=ymax;
                }
                else if(ocd & BOTTOM)
                {
                    x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
                    y=ymin;
                }
                else if(ocd & LEFT)
                {
                    y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
                    x=xmin;
                }
                else
                {
                    y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
                    x=xmax;
                }
                if(ocd==outcode0)
                {
                    x0=x;
                    y0=y;
                    outcode0=CompOutCode(x0,y0,xmin,xmax,ymin,ymax);
                }
                else
                {
                    x1=x;
                    y1=y;
                    outcode1=CompOutCode(x1,y1,xmin,xmax,ymin,ymax);
                }
            }

    }while(done==FALSE);

    if(accept==TRUE)
    {
        lineDDA(x0,y0,x1,y1);
    }
}

outcode CompOutCode(double x,double y,double xmin,double xmax,double ymin,double ymax)
{
    outcode code=0;
    if(y>ymax)
        code|=TOP;
    if(y<ymin)
        code|=BOTTOM;
    if(x>xmax)
        code|=RIGHT;
    if(x<xmin)
        code|=LEFT;
    return code;
}
void translate(float tx,float ty)
{
int x=f[npoly];
for(int i=0;i<x;i++)
	{	
	d[npoly][i]=d[npoly][i]+tx;
	e[npoly][i]=e[npoly][i]+ty;
	}
}
void rotate(float angle)
{
float value=angle*0.01745329252;
int x=f[npoly];
for(int i=0;i<x;i++)
	{	
	d[npoly][i]=((d[npoly][i])*(cos(value)))-((e[npoly][i])*(sin(value)));
	e[npoly][i]=((d[npoly][i])*(sin(value)))+((e[npoly][i])*(cos(value)));
	}
}
void scale(float alpha, float beeta)
{
int x=f[npoly];
for(int i=0;i<x;i++)
	{	
	d[npoly][i]=alpha*d[npoly][i];
	e[npoly][i]=e[npoly][i]*beeta;
	}
}
void poly1()
{
for(int i=0;i<n;i++)
	{
int j;

	
	for(j=0;j<(f[i])-1;j++)
		{
			CSLCAD(d[i][j],e[i][j],d[i][j+1],e[i][j+1],20,50,20,50);
	}
		CSLCAD(d[i][j],e[i][j],d[i][0],e[i][0],20,50,20,50);
	}
}
int main(int argc, char **argv)
{
    char ch;
    //the number of pixels in the grid
    grid_width = 100;
    grid_height = 100;  
int op;  
    //the size of pixels sets the inital window height and width
    //don't make the pixels too large or the screen size will be larger than
    //your display size
    pixel_size = 5;
    
    /*Window information*/
    win_height = grid_height*pixel_size;
    win_width = grid_width*pixel_size;
        float cx[10];
	float cy[10];
	int sumx =0 ,sumy = 0;
	 printf("enter 1>dda 2>bresnham ");
scanf("%d",&a);
/*	scanf("%d",&n);
	printf("enter the number of vertices for the respective  polygons");
	for(int i=0;i<n;i++)
		{
			scanf("%f",&f[i]);
		}
	printf("enter the values of vertices for the respective polygons");
  	for(int i=0;i<n;i++)
		{
		 for(int j=0;j<f[i];j++)
			{
				printf("x[%d][%d]:",i,j);
				scanf("%f",&d[i][j]);
				printf("y[%d][%d]:",i,j);
				scanf("%f",&e[i][j]);
			}
		}*/
        GLint nump;
	fscanf(fp,"%d",&nump);
	n=nump;
int j;
	for(int i=0;i<n;i++)
	{
	//printf("Enter the number of vertices in a %d polygon\n",i+1);
	GLint vertex;
	fscanf(fp,"%d",&vertex);
	f[i]=vertex;
	//scanf("%d",&v[i]);
	  for( j=0;j<f[i];j++)
	{
	    // printf("Enter the %d point x and y coordinate respectively\n",j+1);
	    GLfloat xcord,ycord;
	     fscanf(fp,"%f",&xcord);
	     fscanf(fp,"%f",&ycord);
	      d[i][j]=xcord;
	      e[i][j]=ycord;
	     printf("\n");
	}
	}
	fclose(fp);
//d[npoly1][j]=d[npoly1][0];
        //e[npoly1][j]=e[npoly1][0];
        xmin1=xmax1=d[npoly1][0];
        ymin1=ymax1=e[npoly1][0];
for(int i=0;i<n;i++)
	{
		for(int j=0;j<f[i];j++)
		{
		sumx=sumx+d[i][j];
		sumy=sumy+e[i][j];
		}
	cx[i]=(sumx)*(1/f[i]);
	cy[i]=(sumy)*(1/f[i]);
	}
/*for(int i=0; i<n ;i++)
{
printf("%f",cx[i]);
printf("%f",cy[i]);
}*/
printf("enter the option you want to choose \n");
printf("1>translation\n");
printf("2>rotation\n");
printf("3>scaling \n");
printf("4>rasterization and any other number for clipping");
scanf("%d",&op);
if(op==1)
{
printf("enter the polygon you want to translate \n");
scanf("%d",&npoly);
printf("please enter your translation vector\n");
scanf("%f %f",&tx,&ty);
translate(tx,ty);
}
else if(op==2) 
{
printf("enter the polygon you want to rotated against their respective center \n");
scanf("%d",&npoly);
printf("please enter the angle of rotation\n");
scanf("%f",&angle);
translate(-cx[npoly],-cy[npoly]);
rotate(angle);
translate(cx[npoly],cy[npoly]);
}
else if(op==3) 
{
printf("enter the polygon you want to scale \n");
scanf("%d",&npoly);
printf("please enter your scaling factors along x and y axis respectively\n");
scanf("%f %f",&alpha,&beeta);
translate(-cx[npoly],-cy[npoly]);
scale(alpha,beeta);
translate(cx[npoly],cy[npoly]);
}
else if(op==4)
{
printf("enter the polygon you want to rasterize");
scanf("%d",&npoly1);
d[npoly1][j]=d[npoly1][0];
        e[npoly1][j]=e[npoly1][0];
        xmin1=xmax1=d[npoly1][0];
        ymin1=ymax1=e[npoly1][0];
 //calcs(); 
sq=1;
}
else 
{
printf("enter the clipping region with x min to x max and y min to y max respectively");
scanf("%lf %lf %lf %lf",&xmin,&xmax,&ymin,&ymax);
sq=3;
}

/*to printf("enter the number THAT  polygon numeber to be translated");
	/*Set up glut functions*/
    /** See https://www.opengl.org/resources/libraries/glut/spec3/spec3.html ***/
    
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    /*initialize variables, allocate memory, create buffers, etc. */
    //create window of size (win_width x win_height
    glutInitWindowSize(win_width,win_height);
    //windown title is "glut demo"
	glutCreateWindow("glut demo");
    
	/*defined glut callback functions*/
	glutDisplayFunc(display); //rendering calls here
	glutReshapeFunc(reshape); //update GL on window size change
	glutMouseFunc(mouse);     //mouse button events
	glutMotionFunc(motion);   //mouse movement events
	glutKeyboardFunc(key);    //Keyboard events
	glutIdleFunc(idle); 
      //Function called while program is sitting "idle"
    
    //initialize opengl variables
    init();
    //start glut event loop
	glutMainLoop();

	return 0;
}
/*initialize gl stufff*/
void init()
{
    //set clear color (Default background to white)
	glClearColor(1.0,1.0,1.0,1.0);
    //checks for OpenGL errors
	check();
}

//called repeatedly when glut isn't doing anything else
void idle()
{
    //redraw the scene over and over again
	glutPostRedisplay();	
}

//this is where we render the screen
void display()
{
    //clears the screen
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    //clears the opengl Modelview transformation matrix
	glLoadIdentity();
if(sq==1)
{
calcs();
 int ch1;
    char ch='y';
    float s,s2;
   
        
            
                s=ymin1+0.01;
       
                //clears the screen
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
   // clears the opengl Modelview transformation matrix
	glLoadIdentity();
                while(s<=ymax1)
                {
                    ints(s);
                    sort(s);
                    s++;
                }
poly();
}
else if(sq==3)
{
poly1();
}
else
poly();

//CSLCAD(2,2,50,50,10,25,10,25);
fp1 =fopen("in.txt", "r+");    
	    
    if(fp1==NULL)
    {
        fprintf(stderr, "Can't open input file testFile\n");
        exit(1);
    }
 GLint a=n;
  fprintf(fp1,"%d\n",a);
  for(int i=0;i<a;i++)
  {
    GLint b=f[i];
    fprintf(fp1,"%d\n",b);
    for(int j=0;j<b;j++)
    {
     GLfloat p,w;
     p=d[i][j];
     w=e[i][j];
     fprintf(fp1,"%f\t",p);
     fprintf(fp1,"%f\n",w);
    }
  }


	
    //draws every other pixel on the screen
   
    //blits the current opengl framebuffer on the screen
    glutSwapBuffers();
    //checks for opengl errors
	check();
}


//Draws a single "pixel" given the current grid size
//don't change anything in this for project 1
void draw_pix(int x, int y){
    glBegin(GL_POINTS);
    glColor3f(.2,.2,1.0);
    glVertex3f(x+.5,y+.5,0);
    glEnd();
}

/*Gets called when display size changes, including initial craetion of the display*/
void reshape(int width, int height)
{
	/*set up projection matrix to define the view port*/
    //update the ne window width and height
	win_width = width;
	win_height = height;
    
    //creates a rendering area across the window
	glViewport(0,0,width,height);
    // up an orthogonal projection matrix so that
    // the pixel space is mapped to the grid space
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0,grid_width,0,grid_height,-10,10);
    
    //clear the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //set pixel size based on width, if the aspect ratio
    //changes this hack won't work as well
    pixel_size = width/(float)grid_width;
    
    //set pixel size relative to the grid cell size
    glPointSize(pixel_size);
    //check for opengl errors
	check();
}

//gets called when a key is pressed on the keyboard
void key(unsigned char ch, int x, int y)
{
	switch(ch)
	{
		default:
            //prints out which key the user hit
            printf("User hit the \"%c\" key\n",ch);
			break;
	}
    //redraw the scene after keyboard input
	glutPostRedisplay();
}


//gets called when a mouse button is pressed
void mouse(int button, int state, int x, int y)
{
    //print the pixel location, and the grid location
    printf ("MOUSE AT PIXEL: %d %d, GRID: %d %d\n",x,y,(int)(x/pixel_size),(int)(y/pixel_size));
	switch(button)
	{
		case GLUT_LEFT_BUTTON: //left button
            printf("LEFT ");
            break;
		case GLUT_RIGHT_BUTTON: //right button
            printf("RIGHT ");
		default:
            printf("UNKNOWN "); //any other mouse button
			break;
	}
    if(state !=GLUT_DOWN)  //button released
        printf("BUTTON UP\n");
    else
        printf("BUTTON DOWN\n");  //button clicked
    
    //redraw the scene after mouse click
    glutPostRedisplay();
}

//gets called when the curser moves accross the scene
void motion(int x, int y)
{
    //redraw the scene after mouse movement
	glutPostRedisplay();
}

//checks for any opengl errors in the previous calls and
//outputs if they are present
void check()
{
	GLenum err = glGetError();
	if(err != GL_NO_ERROR)
	{
		printf("GLERROR: There was an error %s\n",gluErrorString(err) );
		exit(1);
	}
}
