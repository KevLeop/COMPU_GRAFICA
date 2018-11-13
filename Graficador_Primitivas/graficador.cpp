# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <map>
#include <string >
#include <vector >

using namespace std;

Ventana_Total Ventana_Ancho , Ventana_Largo; // Variables para establecer el tamanho inicial de la pantalla
int xi; 
int xf;
int xt;
int yi; 
int yf;
int yt;
int var_Fondo = 0;
int var_Dibujo = 3;
int var_Fig = 6;

typedef enum {FONDONEGRO ,FONDOVERDE ,FONDOAZUL ,DIBUJOBLANCO ,DIBUJOVERDE ,DIBUJOAZUL ,LINEA ,CIRCULO ,CUADRADO ,ELIPSE} opcionesMenu;

void set_pixel(int x, int y)
{
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void Dibuja_lineas (int x1,int y1,int x2,int y2)
{
	float ax,ay,x,y,orientacion;
	abs(x2-x1) >= abs(y2-y1)?orientacion = abs(x2-x1):orientacion=abs(y2-y1);
	ax = (x2-x1)/orientacion;
	ay = (y2-y1)/orientacion;
	x = (float)x1;
	y = (float)y1;
	for (int i = 0; i <= orientacion; ++i){
		set_pixel(floor(x),floor(y));
		x = x+ax;
		y = y+ay;
	}
}

void Cuadrado(int x1,int y1,int x2,int y2)
{
	int tam;
	bool def_axis;
	abs(x2-x1)>=abs(y2-y1)?def_axis = true:def_axis = false;
	if(def_axis) tam = abs(x2-x1);
	else tam = abs(y2-y1);
	
	if(x2-x1>=0 && y2-y1 >=0)
		D_Cuadrado(x1,y1,x1+tam,y1+tam);
	else if(x2-x1>0 && y2-y1<0)
		D_Cuadrado(x1,y1,x1+tam,y1-tam);
	else if(x2-x1<0 && y2-y1<0)
		D_Cuadrado(x1,y1,x1-tam,y1-tam);
	else if(x2-x1<0 && y2-y1>0)
		D_Cuadrado(x1,y1,x1-tam,y1+tam);
}

void D_Cuadrado(int x1, int y1, int x2, int y2)
{
	Dibuja_lineas(x1,y1,x2,y1);
	Dibuja_lineas(x1,y2,x2,y2);
	Dibuja_lineas(x1,y1,x1,y2);
	Dibuja_lineas(x2,y2,x2,y1);
}

void D_p_circulo (int x1, int y1, int x2, int y2)
{
	set_pixel (x1 + x2, y1 + y2);
	set_pixel (x1 - x2, y1 + y2);
	set_pixel (x1 + x2, y1 - y2);
	set_pixel (x1 - x2, y1 - y2);
	set_pixel (x1 + y2, y1 + x2);
	set_pixel (x1 - y2, y1 + x2);
	set_pixel (x1 + y2, y1 - x2);
	set_pixel (x1 - y2, y1 - x2);
}

void circulo(int x1, int y1, int x2, int y2)
{
	GLint r = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
	P_medio_Circulo(x1,y1,r);
}

void P_medio_Circulo (int x, int y, GLint radio)
{
	GLint x1, y1;
	GLint p = 1 - radio; // Parametro de vAlor inicial para punto medio
	x1 = 0;
	y1 = radio;
	D_p_circulo(x, y, x1, y1); // Dibuja punto inicial en cada quadrante del circulo
	
	D_p_circulo (x, y, x1, y1); 
	
	// CAlculamos el sgte punto y ploteamos en cada octante
	while (x1 < y1) 
	{
		x1++;
		if (p < 0)
			p += 2 * x1 + 1;
		else 
		{
			y1--;
			p += 2 * (x1-y1) + 1;
		}
		D_p_circulo (x, y, x1, y1);
	}
}


void D_puntos(int xc,int yc, int x, int y)
{
	set_pixel(xc+x,yc+y);
	set_pixel(xc-x,yc+y);
	set_pixel(xc+x,yc-y);
	set_pixel(xc-x,yc-y);
}


void Elipse(int x1, int y1, int x2, int y2)
{
	GLint rx = abs(x2-x1);
	GLint ry = abs(y2-y1);
	P_medio_Elipse(x1,y1,rx,ry);
}

void P_medio_Elipse(int xc, int yc, int rx, int ry)
{
	float x,y,rx2,ry2,p1,p2;
	x = 0;
	y = ry;
	rx2 = pow(rx,2);
	ry2 = pow(ry,2);
	p1 = ry2-(rx2*ry)+(0.25*rx2);
	while((ry2*x)<(rx2*y))
	{
		if(p1 < 0)
		{ 
			x++;
			p1 = p1+(2*ry2*x)+ry2;
		}
		else
		{
			x++; 
			y--;
			p1 = p1+(2*ry2*x)-(2*rx2*y)+ry2;
		}
		D_puntos(xc,yc,x,y);
	}
	p2 = (ry2)*pow((x+0.5) ,2)+(rx2)*pow((y-1) ,2)-(rx2*ry2);
	while(y>0)
	{
		if (p2>0)
		{
			y--;
			p2 = p2-(2*rx2*y) +rx2;
		}
		else
		{
			x++; 
			y--;
			p2 = p2+ (2*ry2*x)-(2*rx2*y)+rx2;
		}
		D_puntos(xc,yc,x,y);
	}
}

void Pintar(int figuras)
{
	switch(figuras)
	{
		case LINEA: Dibuja_lineas(xi,yi,xf,yf); break;
		case CUADRADO: Cuadrado(xi,yi,xf,yf); break;
		case CIRCULO: circulo(xi,yi,xf,yf); break;
		case ELIPSE: Elipse(xi,yi,xf,yf); break;
	}
}

void onMenu(int opcion)
{
	switch(opcion)}
	{
		case FONDONEGRO: var_Fondo = 0; break;
		case FONDOVERDE: var_Fondo = 1; break;
		case FONDOAZUL: var_Fondo = 2; break;
		case DIBUJOBLANCO: var_Dibujo = 3; break;
		case DIBUJOVERDE: var_Dibujo = 4; break;
		case DIBUJOAZUL: var_Dibujo = 5; break;
		case LINEA: var_Fig = 6; break;
		case CIRCULO: var_Fig = 7; break;
		case CUADRADO: var_Fig = 8; break;
		case ELIPSE: var_Fig = 9; break;
	}
	glutPostRedisplay();
}

void crear_Menu()
{
	int menuFigura , menuFondo , menuDibujo , menuPrincipal;
	menuFigura = glutCreateMenu(onMenu);
	glutAddMenuEntry("Linea", LINEA);
	glutAddMenuEntry("Circulo", CIRCULO);
	glutAddMenuEntry("Cuadrado", CUADRADO);
	glutAddMenuEntry("Elipse", ELIPSE);
	menuFondo = glutCreateMenu(onMenu);
	glutAddMenuEntry("Negro",FONDONEGRO);
	glutAddMenuEntry("Verde Oscuro",FONDOVERDE);
	glutAddMenuEntry("Azul Oscuro",FONDOAZUL);
	menuDibujo = glutCreateMenu(onMenu);
	glutAddMenuEntry("Blanco",DIBUJOBLANCO);
	glutAddMenuEntry("Verde Claro",DIBUJOVERDE);
	glutAddMenuEntry("Azul Claro",DIBUJOAZUL);
	menuPrincipal = glutCreateMenu(onMenu);
	glutAddSubMenu("Figura",menuFigura);
	glutAddSubMenu("Color de Fondo",menuFondo);
	glutAddSubMenu("Color de Dibujo",menuDibujo);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void resize(Ventana_Total w, Ventana_Total h)
{
	Ventana_Ancho = w;
	Ventana_Largo = h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,w,0,h,1.f,-1.f);
	printf("Resize:: %dx%d\n",w,h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void)
{
	int i;
	float colores[6][3] = {
		{0.00f, 0.00f, 0.00f}, // negro
	{0.06f, 0.25f, 0.13f}, // verde 
		{0.10f, 0.07f, 0.33f}, // azul 
	{1.00f, 1.00f, 1.00f}, //  blanco
		{0.12f, 0.50f, 0.26f}, // verde
	{0.20f, 0.14f, 0.66f}, // azul claro
	};
	glClearColor (colores[var_Fondo][0],colores[var_Fondo][1],colores[var_Fondo][2], 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(colores[var_Dibujo][0],colores[var_Dibujo][1],colores[var_Dibujo][2]);
	Pintar(var_Fig);
	glBegin(GL_POINTS);
	glColor3f(1,0,0);
	for (i = -5; i <= 5; i++){
		glVertex2i(xi+i,yi);
		glVertex2i(xi,yi-i);
	}
	glEnd();
	glutSwapBuffers();
}

//Acciones mouse
void mouse_mover(int x, int y)
{
	xt = x;
	yt = Ventana_Largo -y;
	glutPostRedisplay();
}

void mouse_arrastrar(int x, int y)
{
	xf = x;
	yf = Ventana_Largo - y;
	glutPostRedisplay();
}

typedef GLubyte Color[3];
void getPixel(int x, int y, Color rgb)
{
	glReadPixels(x, y, 1, 1, GL_RGB , GL_UNSIGNED_BYTE , rgb);
}

void mouse_click(int button , int state , int x, int y)
{
	Color c;
	if(state== GLUT_DOWN){
		xi=x;
		yi=Ventana_Largo - y;
		xf=xi;
		yf=yi;
		getPixel(xi, yi, c);
		printf("Pos inicial: %3d, %3d\n",xi,yi);
	}
	if(state==GLUT_UP){
		printf("Pos final: %3d, %3d\n",xf,yf);
	}
	glutPostRedisplay();
}

void normal_key(GLubyte key, int x, int y)
{
	char s[80] = "";
	if(glutGetModifiers() & GLUT_ACTIVE_SHIFT) sprintf(s, "%s SHIFT ", s);
	if(glutGetModifiers() & GLUT_ACTIVE_CTRL) sprintf(s, "%s CTRL ", s);
	if(glutGetModifiers() & GLUT_ACTIVE_ALT) sprintf(s, "%s ALT ", s);
	if(key >= 32 && key <= 128)
		printf("normal key: ’%c’ dec:%d %s\n", key, key, s);
	else
		printf("normal key: dec:%d %s\n",key,s);
	if(key==27)
		exit(0);
}

void special_key(int key, int x, int y)
{
	printf("special key # %d\n",key);
}

void timer_function(int value)
{
	printf("Pos puntero %d, %d\n",xt,yt);
	glutTimerFunc(8000, timer_function , 1);
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(800,0);
	glutCreateWindow("GRAFICA");
	glutDisplayFunc(display);
	crear_Menu();
	glutReshapeFunc(resize);
	glutPassiveMotionFunc(mouse_mover);
	glutMotionFunc(mouse_arrastrar);
	glutMouseFunc(mouse_click);
	glutKeyboardFunc(normal_key);
	glutSpecialFunc(special_key);
	glutTimerFunc(33,timer_function ,1);
	glutMainLoop();
	return 0;
}