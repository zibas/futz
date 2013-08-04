#include "Quaternion.h"
#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846

Quaternion::Quaternion(){
	Reset();
}

Quaternion::~Quaternion(){
}


void Quaternion::SetAxis(double degrees, float xa, float ya, float za){
	float radians = degrees / 180 * PI; 
	float tmp = sin(radians / 2);
	w = cos(radians / 2);
	x = xa * tmp; 
	y = ya * tmp; 
	z = za * tmp; 
}

void Quaternion::Reset(){
	x = y = z = 0;
	w = 1;
}

Quaternion Quaternion::operator *(Quaternion q)
{                                      
    Quaternion result;
    result.w = w*q.w - x*q.x - y*q.y - z*q.z;
    result.x = w*q.x + x*q.w + y*q.z - z*q.y;
    result.y = w*q.y + y*q.w + z*q.x - x*q.z;
    result.z = w*q.z + z*q.w + x*q.y - y*q.x;
        
    return result;
}

void Quaternion::SetFromEuler(float x, float y, float z){
	Quaternion qx = Quaternion();
	Quaternion qy = Quaternion();
	Quaternion qz = Quaternion();

	qx.SetAxis(x, 1, 0 , 0);
	qy.SetAxis(y, 0, 1 , 0);
	qz.SetAxis(z, 0, 0 , 1);
	qz = qy * qz;
	*this = qx * qz;
}


bool Quaternion::IsNAN(){
#ifndef _WIN32
	if(isnan(x) || isnan(y) || isnan(z) || isnan(w)){
		return true;
	}
#endif
	return false;
}

void Quaternion::Print(){
	printf("x: %f, y: %f, z: %f, w: %f\n", x, y, z, w);

}

