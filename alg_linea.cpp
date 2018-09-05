#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <unistd.h>

using namespace std;

void Iniciar()
{
	glMatrixMode(GL_PROJECTION); //Activando la matriz de proyeccion.
	glClearColor(0.0, 0.0, 1.0, 0.0); // Color de fondo para la ventana azul.
	gluOrtho2D(-100, 500 ,-100 , 500);
}

void writePixel_r(GLint x,GLint y) //funcion para pintar pixel rojo
{
	glBegin(GL_POINTS);
		glPointSize(1); // Tamanho del punto
		glColor3f(1.0,0.0,0.0); // Color rojo
		glVertex2i(x,y); // Establece coordenada del vertice
	glEnd();
}

void writePixel_g(GLint x,GLint y) //funcion para pintar pixel verde
{
	glBegin(GL_POINTS);
		glPointSize(1); // Tamanho del punto
		glColor3f(0.0,1.0,0.0); // Color rojo
		glVertex2i(x,y); // Establece coordenada del vertice
	glEnd();
}

void incremental_basico(GLint x0,GLint y0, GLint xf, GLint yf)
{
	int x = 0;
	int y = 0;
	float a;
	a = (yf - y0) / (xf - x0);
	for(x=x0 ; x<=xf ; x++)
	{
		y = (y0 + a * ( x - x0));
		writePixel_r(x,y);
	}
}


void punto_medio(GLint x0,GLint y0, GLint xf, GLint yf)
{
	int dx,dy,incE,incNE,d,x,y;
	
	dx=xf-x0;
	dy=yf-y0;
	d=2*dy-dx; /* Valor inicial de d*/
	incE=2*dy; /*Incremento de E*/
	incNE=2*(dy-dx);/* Incremento de NE*/
	x=x0;
	y=y0;
	writePixel_g(x,y);
	while (x < xf)
	{
		if(d <=0)
		{
			d=d+incE;
			x=x+1;
		}
		else
		{
		   d=d+incNE;
		   x=x+1;
		   y=y+1;
		}
		writePixel_g(x,y);
	}
}


void dibujar_linea(GLint x0,GLint y0, GLint xf, GLint yf) // Dibujar linea usando GL_LINES
{
	glBegin(GL_LINES);
		glColor3f(0.0,0.0,0.0); // Color de linea NEGRO
		glVertex2i(x0,y0);
		glVertex2i(xf,yf);
	glEnd();
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT); //Limpiamos el frame buffer con el color de "Clear", en este caso azul
	
	//Para dibujar_linea usando GL_LINES - NEGRO
	GLint x_0=-5,y_0=-5,x_f0=300,y_f0=200;
	dibujar_linea(x_0,y_0,x_f0,y_f0);
	
	//Para dibujar linea usando incremental basico - ROJO
	GLint x_1=-5,y_1=-5,x_f1=300,y_f1=100;
	incremental_basico( x_1, y_1,  x_f1,  y_f1);
	
	//Para dibujar linea usando punto medio - VERDE
	GLint x_2=-5,y_2=-5,x_f2=300,y_f2=100;
	punto_medio( x_2, y_2,  x_f2,  y_f2);
	glFlush();
}

int main ( int argc , char ** argv )
{
	glutInit (&argc,argv);
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB ); //Activamos buffer simple y colores del tipo RGB
	glutInitWindowSize (500,500); // Definimos medidas de la ventana
	glutInitWindowPosition (300 , 100);

	glutCreateWindow ( " Graficando Lineas " );
	
	Iniciar() ;
	glutDisplayFunc (draw) ;
	glutMainLoop () ;
	return 0;
}