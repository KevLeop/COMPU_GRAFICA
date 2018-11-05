
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdio>

#include "camera.h"
#include "vector_tools.h"

static camera *LOCAL_MyCamera;
static int old_x, old_y;


static void SpecialKey ( int key, int x, int y )
{
	switch(key) {
		case GLUT_KEY_F1:
			glutPassiveMotionFunc(MouseMotion);
			LOCAL_MyCamera->camMovimiento = CAM_STOP;
			break;
		case GLUT_KEY_F2:
			glutPassiveMotionFunc(Examinar);
			LOCAL_MyCamera->camMovimiento = CAM_EXAMINAR;
			break;
		case GLUT_KEY_F3:
			glutPassiveMotionFunc(MouseMotion);
			LOCAL_MyCamera->camMovimiento = CAM_PASEAR;
			LOCAL_MyCamera->camAtY = 0;
			LOCAL_MyCamera->camViewY = 0;
			SetDependentParametersCamera( LOCAL_MyCamera );
			break;
		case GLUT_KEY_HOME: //Reset Camera
			LOCAL_MyCamera->camAtX =0;
			LOCAL_MyCamera->camAtY =0;
			LOCAL_MyCamera->camAtZ =0;
			LOCAL_MyCamera->camViewX = 0;
			LOCAL_MyCamera->camViewY = 1;
			LOCAL_MyCamera->camViewZ = -3;
			SetDependentParametersCamera( LOCAL_MyCamera );
			break;
		default:
		printf("key %d %c X %d Y %d\n", key, key, x, y );
	}
	glutPostRedisplay();
}			
	
void MouseMotion(int x, int y)
{
	old_y = y;
	old_x = x;
}

void Examinar(int x, int y)
{
	float rot_x, rot_y;
	rot_y = (float)(old_y - y);
	rot_x = (float)(x - old_x);
	Rotar_Latitud( LOCAL_MyCamera, rot_y * DEGREE_TO_RAD );
	Rotar_Longitud( LOCAL_MyCamera, rot_x * DEGREE_TO_RAD );
	
	old_y = y;
	old_x = x;
	
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	old_x = x;
	old_y = y;
	switch(button){
	case GLUT_LEFT_BUTTON:
		switch(LOCAL_MyCamera->camMovimiento){
		case CAM_EXAMINAR:
			if (state == GLUT_DOWN) glutMotionFunc(Zoom);
			if (state == GLUT_UP){
				glutPassiveMotionFunc(Examinar);
				glutMotionFunc(NULL);
			}
			break;
		case CAM_PASEAR:
			if (state == GLUT_DOWN) glutMotionFunc(Andar);
			if (state == GLUT_UP) glutMotionFunc(NULL);
			break;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) ;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void Zoom(int x, int y)
{
	float zoom;
	zoom = (float) ((y - old_y) * DEGREE_TO_RAD);
	old_y = y;
	switch(LOCAL_MyCamera->camMovimiento){
	case CAM_EXAMINAR:
		if (LOCAL_MyCamera->camAperture + zoom > (5 * DEGREE_TO_RAD) &&
			LOCAL_MyCamera->camAperture + zoom < 175 * DEGREE_TO_RAD)
			LOCAL_MyCamera->camAperture=LOCAL_MyCamera->camAperture + zoom;
		break;
	}
	glutPostRedisplay();
}
			
void Andar(int x, int y)
{
	float rotacion_x, avance_y;
	avance_y = (float)(y - old_y) / 10;
	rotacion_x = (float)(old_x - x) * DEGREE_TO_RAD / 5;
	YawCamera( LOCAL_MyCamera, rotacion_x );
	AvanceFreeCamera( LOCAL_MyCamera, avance_y);
	old_y = y;
	old_x = x;
	glutPostRedisplay();
}			
			
void reshape(int width, int height) 
{
	glViewport(0, 0, width, height);
	SetGLAspectRatioCamera( LOCAL_MyCamera );
}	


