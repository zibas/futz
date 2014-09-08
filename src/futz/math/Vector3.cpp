/*
 * Vector3.cpp
 *
 *  Created on: Oct 29, 2010
 *      Author: ziba
 */

#include "Vector3.h"
#include <stdio.h>
#include <math.h>

Vector3::Vector3() {
	// TODO Auto-generated constructor stub
	x = y = z = 0;
}

void Vector3::Print()
{
	printf("%g,%g,%g\n",x,y,z);
}

Vector3 Vector3::operator -(const Vector3 & v)
{
	Vector3 v3 = Vector3();
	        v3.x = x - v.x;
	        v3.y = y - v.y;
	        v3.z = z - v.z;
	return v3;
}

Vector3 Vector3::operator +(const Vector3 & v)
{
	Vector3 v3 = Vector3();
	        v3.x = x + v.x;
	        v3.y = y + v.y;
	        v3.z = z + v.z;
	return v3;
}

// Cross product
Vector3 Vector3::operator *(const Vector3 & v2)
{
	Vector3 v3 = Vector3();
	        v3.x = y*v2.z - z*v2.y;
	        v3.y = z*v2.x - x*v2.z;
	        v3.z = x*v2.y - y*v2.x;
	return v3;
}

Vector3 Vector3::operator *(const double & scaler)
{
	Vector3 v3 = Vector3();
	        v3.x = x * scaler;
	        v3.y = y * scaler;
	        v3.z = z * scaler;
	return v3;
}



Vector3 Vector3::Transform(Matrix4 m){
    Matrix4 mat = Matrix4();
    Vector3 tv;
    mat.SetIdentity();
    mat.SetTranslation(x,y,z);
    mat = mat * m;
    tv.x = mat.values[12];
    tv.y = mat.values[13];
    tv.z = mat.values[14];
    return tv;
}

float Vector3::RadiansBetween(const Vector3 & v1, const Vector3 &v2){
	return acos(Vector3::Dot(v1, v2));
}

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif
float Vector3::DegreesBetween(const Vector3 & v1, const Vector3 &v2){
	return 360 * Vector3::RadiansBetween(v1, v2) / (2 * M_PI);
}

float Vector3::Dot(const Vector3 & v1, const Vector3 &v2)
{
	Vector3 nv1 = v1;
	Vector3 nv2 = v2;
	nv1.Normalize(); 
	nv2.Normalize(); 
	return nv1.x*nv2.x + nv1.y*nv2.y + nv1.z*nv2.z;
}

float Vector3::Dot(const Vector3 & v2)
{
	return Vector3::Dot(*this, v2);
}

float Vector3::Length(){
    return sqrt(x*x + y*y + z*z);
}

void Vector3::Normalize(){
        float length = Length();
        if(length != 0){
            x = x/length;
            y = y/length;
            z = z/length;
        }
}



Vector3::~Vector3() {
	// TODO Auto-generated destructor stub
}
