#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <unistd.h>

#define NUM_LADOS 4
#define RADIO 10


using namespace std;


class point
{
	public:
		double x;
		double y;
		point(){};
		point(double x_,double y_);
};


point :: point(double x_,double y_)
{
		x = x_;
		y = y_;
}


void Iniciar()
{
	glMatrixMode(GL_PROJECTION); // Activando la matriz de proyeccion
	glClearColor(0.0, 0.0, 0.0, 0.0); // Color de fondo para la ventana azul.
	gluOrtho2D(-20,20,-20,20); 
}

void mostrar()
{
	int tam = NUM_LADOS+1;
	point * pt = new point[tam];
	
	glBegin(GL_POINTS);
		glClear(GL_COLOR_BUFFER_BIT); //Limpiamos el frame buffer con el color de "Clear" - NEGRO
		glColor3f(0.0,1.0,0.0);  // Verde
	glEnd();

	point p;
	double i;
	int j;
	if (NUM_LADOS==3){
		for(i=90.0,j=0;i<360.0;i+=360/NUM_LADOS*1.0,j++){
			p.x=RADIO*cos((i*M_PI)/180);
			p.y=RADIO*sin((i*M_PI)/180);
			pt[j]=p;
		}
		pt[j]=pt[0];
		for(int i=0;i<tam-1;i++){
			glBegin ( GL_LINES ) ;
				glVertex2f ( pt[i+1].x,pt[i+1].y) ;
				glVertex2f ( pt[i].x,pt[i].y) ;
			glEnd ( ) ;
		}
	}
	if(NUM_LADOS>3){
		for(i=0.0,j=0;i<360.0;i+=360.0/NUM_LADOS*1.0,j++){
			p.x=RADIO*cos((i*M_PI)/180);
			p.y=RADIO*sin((i*M_PI)/180);
			pt[j]=p;
		}
		pt[j]=pt[0];
		for(int i=0;i<tam-1;i++){
			glBegin ( GL_LINES ) ;
				glVertex2f ( pt[i].x,pt[i].y) ;
				glVertex2f ( pt[i+1].x,pt[i+1].y) ;
				
			glEnd ( ) ;
		}


	}	
	glFlush();
}


int main ( int argc , char ** argv )
{
	glutInit (&argc,argv ) ;
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB ) ;
	glutInitWindowPosition (10 , 10) ;
	glutInitWindowSize ( 600,600 ) ;
	glutCreateWindow ( " POLIGONO " ) ;
	Iniciar() ;
	glutDisplayFunc (mostrar) ;
	glutMainLoop () ;
	return EXIT_SUCCESS;
}

