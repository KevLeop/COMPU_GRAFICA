#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <unistd.h>

using namespace std;

class punto
{
	public:
		GLfloat x;
		GLfloat y;
		punto(){};
		punto(double x_,double y_);
};


punto::punto(double x_,double y_){
	x=x_;
	y=y_;
}


void Inicio()
{
	glMatrixMode(GL_PROJECTION); //Activamos la matriz de proyeccion
	glClearColor(0.0,0.0,0.0,0.0); // Color de fondo para la ventana negro
	gluOrtho2D(-20,20,-20,20); // Plano de proyeccion
}

//void drawCircle()

void drawPoligono(int lados, int radio, GLfloat x, GLfloat y)
{
	GLfloat i;
	int j;
	punto p;
	punto * pt = new punto[lados+1];
	for(i=0.0,j=0;i<360.0;i+=360/lados*1.0,j++)
	{
		p.x = radio*cos((i*M_PI)/180);
		p.y = radio*sin((i*M_PI)/180);
		pt[j]=p;
			
	}
	
	pt[j]=pt[0];	
	for(int i=0; i<lados;i++)
	{
		glBegin ( GL_LINES ) ;
			glVertex2f ( pt[i].x + x , pt[i].y+y) ;
			glVertex2f ( pt[i+1].x + x , pt[i+1].y + y) ;
					
			//glVertex2f ( pt[i].x,pt[i].y) ;
			//glVertex2f ( pt[i+1].x,pt[i+1].y);	
		glEnd ();
		
	}
	
}


void drawTortuga()
{
	drawPoligono(6,7,0,0); // cuerpo
	drawPoligono(6,3,0,8.6);// cabeza
	drawPoligono(20,2,7.0,3.9); // pata superior derecha
	drawPoligono(20,2,7.0,-3.9); // pata inferior derecha
	drawPoligono(20,2,-7.0,-3.9); // pata inferior izquierda
	drawPoligono(20,2,-7.0,3.9); // para superior izquierda
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	
	drawTortuga();
	
	
	glEnd();
	
	glFlush();
}

int main ( int argc , char ** argv )
{
	glutInit (&argc,argv ) ;
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB ) ;
	glutInitWindowPosition (10 , 10) ;
	glutInitWindowSize ( 600,600 ) ;
	glutCreateWindow ( " Tortuga " ) ;
	Inicio() ;
	glutDisplayFunc (display) ;
	glutMainLoop () ;
	return EXIT_SUCCESS;
}