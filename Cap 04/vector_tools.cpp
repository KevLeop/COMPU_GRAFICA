#include "Vector_tools.h"
#include <stdio.h>

void VectorNormalize( int *ierr, float *vx, float *vy, float *vz )
{
	float		 A, B, C;
	float		 modf;
	double		 mod;
	
	if( *ierr ) return;
	
	A = *vx;
	B = *vy;
	C = *vz;
	mod = A*A + B*B + C*C;

}


void UnitVectorPP( int *ierr, float *wx, float *wy, float *wz, 
				  float ax,  float ay,  float az, 
				  float bx,  float by,  float bz )
{
	// dados dos puntos genera un vector unitario que va de A a B

}

void UnitVectorVV( int *ierr, float *wx, float *wy, float *wz, 
				  float ux,  float uy,  float uz, 
				  float vx,  float vy,  float vz )
{
	// Producto vectorial : w = u ^ v

}


void VectorRotY( float *vIn, float inc )
{
	float	 alpha;
	float	 modZX;
	float	 mod;
	
	//         __________________> X          
	//        |*          
	//        | *           
	//        |  *         
	//        |   *        
	//        |    *       
	//        |     *      
	//        |      *     
	//        | alpha *    
	//        |        *    
	//        v           
	//       Z      
	
	mod = MOD( vIn[0], vIn[1], vIn[2] );
	if( mod < VECTOR_EPSILON ) return;
	vIn[0] = vIn[0] / mod;
	vIn[1] = vIn[1] / mod;
	vIn[2] = vIn[2] / mod;
	
	// si el vector es demasiado paralelo al eje "y" no haga nada

}

void VectorRotXZ( float *vIn, float inc, int flagStop )
{

	
	// if vector is too parallel to the "y" axis do nothing
	if( fabs( vIn[1] ) > sin( maxAngle ) ) return;
	
	// 1 Compute alpha & beta	
	alpha = (float) acos( vIn[2] / sqrt( vIn[0]*vIn[0] + vIn[2]*vIn[2] ) );
	if( vIn[0] < 0.0f ) alpha = 2.0f * PI_VALUE - alpha;
	
	// hypotenuse must be always 1.0 (because v is a unit vector)
	// first we measure beta from X-Z up to our vector
	// the result will be among -90 and +90
	beta = (float) asin( vIn[1] );
	
	// 2 ConstantIncrement beta (two possibilities)

}