/*
 * Matrix4.cpp
 *
 *  Created on: Oct 29, 2010
 *      Author: ziba
 */

#include "Matrix4.h"
#include <math.h>
#include <stdio.h>
Matrix4::Matrix4() {
	for(int i = 0; i < 16; i++){
		this->values[i] = 0;
	}
}

void Matrix4::Print()
{
	int i = 0;
	for(i = 0; i < 16; i++){
		printf("%g,%f\t",values[i],valuesf[i]);
		if((i+1)%4 == 0){
			printf("\n");
		}
	}
	printf("\n");
}

void Matrix4::SetIdentity()
{
    this->values[0] = 1;
    this->values[1] = 0;
    this->values[2] = 0;
    this->values[3] = 0;
    this->values[4] = 0;
    this->values[5] = 1;
    this->values[6] = 0;
    this->values[7] = 0;
    this->values[8] = 0;
    this->values[9] = 0;
    this->values[10] = 1;
    this->values[11] = 0;
    this->values[12] = 0;
    this->values[13] = 0;
    this->values[14] = 0;
    this->values[15] = 1;
}

void Matrix4::SetScale(float size){
	SetIdentity();
	values[0] = size;
	values[5] = size;
	values[10] = size;
}

void Matrix4::SetRotX(float radians){
	SetIdentity();
    values[5] = cos(radians);
    values[6] = sin(radians);
    values[9] = -sin(radians);
    values[10] = cos(radians);
}
void Matrix4::SetRotY(float radians){
	SetIdentity();
    values[0] = cos(radians);
    values[2] = -sin(radians);
    values[8] = sin(radians);
    values[10] = cos(radians);
}
void Matrix4::SetRotZ(float radians){
	SetIdentity();
    values[0] = cos(radians);
    values[1] = sin(radians);
    values[4] = -sin(radians);
    values[5] = cos(radians);
}

void Matrix4::Set(int row, int column, float value){
    values[row*4 + column] = value;
}

void Matrix4::SetRight(float x, float y,  float z){
    values[0] = x;
    values[1] = y;
    values[2] = z;
}

void Matrix4::SetUp(float x, float y, float z){
    values[4] = x;
    values[5] = y;
    values[6] = z;
}

void Matrix4::SetBackward(float x, float y, float z){
    values[8] = x;
    values[9] = y;
    values[10] = z;
}

void Matrix4::SetTranslation(float x, float y, float z) {
        values[12] = x;
        values[13] = y;
        values[14] = z;
}


Matrix4 Matrix4::operator*(const Matrix4& m2){
	Matrix4 out = Matrix4();
	 // Column 1
	    out.values[0] = (values[0] * m2.values[0]) + (values[1] * m2.values[4]) + (values[2] * m2.values[8]) + (values[3] * m2.values[12]);
	    out.values[4] = (values[4] * m2.values[0]) + (values[5] * m2.values[4]) + (values[6] * m2.values[8]) + (values[7] * m2.values[12]);
	    out.values[8] = (values[8] * m2.values[0]) + (values[9] * m2.values[4]) + (values[10] * m2.values[8]) + (values[11] * m2.values[12]);
	    out.values[12] = (values[12] * m2.values[0]) + (values[13] * m2.values[4]) + (values[14] * m2.values[8]) + (values[15] * m2.values[12]);

	    // Column 2
	    out.values[1] = (values[0] * m2.values[1]) + (values[1] * m2.values[5]) + (values[2] * m2.values[9]) + (values[3] * m2.values[13]);
	    out.values[5] = (values[4] * m2.values[1]) + (values[5] * m2.values[5]) + (values[6] * m2.values[9]) + (values[7] * m2.values[13]);
	    out.values[9] = (values[8] * m2.values[1]) + (values[9] * m2.values[5]) + (values[10] * m2.values[9]) + (values[11] * m2.values[13]);
	    out.values[13] = (values[12] * m2.values[1]) + (values[13] * m2.values[5]) + (values[14] * m2.values[9]) + (values[15] * m2.values[13]);

	    // Column 3
	    out.values[2] = (values[0] * m2.values[2]) + (values[1] * m2.values[6]) + (values[2] * m2.values[10]) + (values[3] * m2.values[14]);
	    out.values[6] = (values[4] * m2.values[2]) + (values[5] * m2.values[6]) + (values[6] * m2.values[10]) + (values[7] * m2.values[14]);
	    out.values[10] = (values[8] * m2.values[2]) + (values[9] * m2.values[6]) + (values[10] * m2.values[10]) + (values[11] * m2.values[14]);
	    out.values[14] = (values[12] * m2.values[2]) + (values[13] * m2.values[6]) + (values[14] * m2.values[10]) + (values[15] * m2.values[14]);

	    // Column 4
	    out.values[3] = (values[0] * m2.values[3]) + (values[1] * m2.values[7]) + (values[2] * m2.values[11]) + (values[3] * m2.values[15]);
	    out.values[7] = (values[4] * m2.values[3]) + (values[5] * m2.values[7]) + (values[6] * m2.values[11]) + (values[7] * m2.values[15]);
	    out.values[11] = (values[8] * m2.values[3]) + (values[9] * m2.values[7]) + (values[10] * m2.values[11]) + (values[11] * m2.values[15]);
	    out.values[15] = (values[12] * m2.values[3]) + (values[13] * m2.values[7]) + (values[14] * m2.values[11]) + (values[15] * m2.values[15]);


	return out;
}

void Matrix4::Invert(){
	Matrix4 tmp = Matrix4();
	tmp.SetIdentity();

	tmp.values[0]  = (values[5] * values[10] * values[15]) + (values[6] * values[11] * values[13]) + (values[7] * values[9] * values[14]) - (values[5] * values[11] * values[14]) - (values[6] * values[9] * values[15]) - (values[7] * values[10] * values[13]);
	tmp.values[1]  = (values[1] * values[11] * values[14]) + (values[2] * values[9] * values[15]) + (values[3] * values[10] * values[13]) - (values[1] * values[10] * values[15]) - (values[2] * values[11] * values[13]) - (values[3] * values[9] * values[14]);
	tmp.values[2]  = (values[1] * values[6] * values[15]) + (values[2] * values[7] * values[13]) + (values[3] * values[5] * values[14]) - (values[1] * values[7] * values[14]) - (values[2] * values[5] * values[15]) - (values[3] * values[6] * values[13]);
	tmp.values[3]  = (values[1] * values[7] * values[10]) + (values[2] * values[5] * values[11]) + (values[3] * values[6] * values[9]) - (values[1] * values[6] * values[11]) - (values[2] * values[7] * values[9]) - (values[3] * values[5] * values[10]);

	tmp.values[4]  = (values[4] * values[11] * values[14]) + (values[6] * values[8] * values[15]) + (values[7] * values[10] * values[12]) - (values[4] * values[10] * values[15]) - (values[6] * values[11] * values[12]) - (values[7] * values[8] * values[14]);
	tmp.values[5]  = (values[0] * values[10] * values[15]) + (values[2] * values[11] * values[12]) + (values[3] * values[8] * values[14]) - (values[0] * values[11] * values[14]) - (values[2] * values[8] * values[15]) - (values[3] * values[10] * values[12]);
	tmp.values[6]  = (values[0] * values[7] * values[14]) + (values[2] * values[4] * values[15]) + (values[3] * values[6] * values[12]) - (values[0] * values[6] * values[15]) - (values[2] * values[7] * values[12]) - (values[3] * values[4] * values[14]);
	tmp.values[7]  = (values[0] * values[6] * values[11]) + (values[2] * values[7] * values[8]) + (values[3] * values[4] * values[10]) - (values[0] * values[7] * values[10]) - (values[2] * values[4] * values[11]) - (values[3] * values[6] * values[8]);

	tmp.values[8]  = (values[4] * values[9] * values[15]) + (values[5] * values[11] * values[12]) + (values[7] * values[8] * values[13]) - (values[4] * values[11] * values[13]) - (values[5] * values[8] * values[15]) - (values[7] * values[9] * values[12]);
	tmp.values[9]  = (values[0] * values[11] * values[13]) + (values[1] * values[8] * values[15]) + (values[3] * values[9] * values[12]) - (values[0] * values[9] * values[15]) - (values[1] * values[11] * values[12]) - (values[3] * values[8] * values[13]);
	tmp.values[10] = (values[0] * values[5] * values[15]) + (values[1] * values[7] * values[12]) + (values[3] * values[4] * values[13]) - (values[0] * values[7] * values[13]) - (values[1] * values[4] * values[15]) - (values[3] * values[5] * values[12]);
	tmp.values[11] = (values[0] * values[7] * values[9]) + (values[1] * values[4] * values[11]) + (values[3] * values[5] * values[8]) - (values[0] * values[5] * values[11]) - (values[1] * values[7] * values[8]) - (values[3] * values[4] * values[9]);

	tmp.values[12] = (values[4] * values[10] * values[13]) + (values[5] * values[8] * values[14]) + (values[6] * values[9] * values[12]) - (values[4] * values[9] * values[14]) - (values[5] * values[10] * values[12]) - (values[6] * values[8] * values[13]);
	tmp.values[13] = (values[0] * values[9] * values[14]) + (values[1] * values[10] * values[12]) + (values[2] * values[8] * values[13]) - (values[0] * values[10] * values[13]) - (values[1] * values[8] * values[14]) - (values[2] * values[9] * values[12]);
	tmp.values[14] = (values[0] * values[6] * values[13]) + (values[1] * values[4] * values[14]) + (values[2] * values[5] * values[12]) - (values[0] * values[5] * values[14]) - (values[1] * values[6] * values[12]) - (values[2] * values[4] * values[13]);
	tmp.values[15] = (values[0] * values[5] * values[10]) + (values[1] * values[6] * values[8]) + (values[2] * values[4] * values[9]) - (values[0] * values[6] * values[9]) - (values[1] * values[4] * values[10]) - (values[2] * values[5] * values[8]);

	float determinant = Determinant();
	int i = 0;
	for(i = 0; i < 16; i++){
		values[i] = tmp.values[i] / determinant;
	}
}

float Matrix4::Determinant()
{
    //a12 a15 a2 a5 - a11 a16 a2 a5 - a12 a14 a3 a5 + a10 a16 a3 a5 +
  return   (values[11] * values[14] * values[1] * values[4])
         - (values[10] * values[15] * values[1] * values[4])
         - (values[11] * values[13] * values[2] * values[4])
         + (values[9] * values[15] * values[2] * values[4])

         //a11 a14 a4 a5 - a10 a15 a4 a5 - a1 a12 a15 a6 + a1 a11 a16 a6 +
         + (values[10] * values[13] * values[3] * values[4])
         - (values[9] * values[14] * values[3] * values[4])
         - (values[0] * values[11] * values[14] * values[5])
         + (values[0] * values[10] * values[15] * values[5])

         //a12 a13 a3 a6 - a11 a13 a4 a6 + a1 a12 a14 a7 - a1 a10 a16 a7 -
         + (values[11] * values[12] * values[2] * values[5])
         - (values[10] * values[12] * values[3] * values[5])
         + (values[0] * values[11] * values[13] * values[6])
         - (values[0] * values[9] * values[15] * values[6])

         //a12 a13 a2 a7 + a10 a13 a4 a7 - a1 a11 a14 a8 + a1 a10 a15 a8 +
         - (values[11] * values[12] * values[1] * values[6])
         + (values[9] * values[12] * values[3] * values[7])
         - (values[0] * values[10] * values[13] * values[7])
         + (values[0] * values[9] * values[14] * values[7])

         //a11 a13 a2 a8 - a10 a13 a3 a8 - a16 a3 a6 a9 + a15 a4 a6 a9 +
         + (values[10] * values[12] * values[1] * values[7])
         - (values[9] * values[12] * values[2] * values[7])
         - (values[15] * values[2] * values[5] * values[8])
         + (values[14] * values[3] * values[5] * values[8])

         //a16 a2 a7 a9 - a14 a4 a7 a9 - a15 a2 a8 a9 + a14 a3 a8 a9
         + (values[15] * values[1] * values[6] * values[8])
         - (values[13] * values[3] * values[6] * values[8])
         - (values[14] * values[1] * values[7] * values[8])
         + (values[13] * values[2] * values[7] * values[8]);

}

void Matrix4::Set(Quaternion q){
	if(q.IsNAN()){
		printf("Quaternion has a nan!\n");
		q.Print();
		return;
	}
    values[0] = 1.0f - 2.0f * ( q.y * q.y + q.z * q.z ); 
    values[1] = 2.0f * (q.x * q.y + q.z * q.w);                      
    values[2] = 2.0f * (q.x * q.z - q.y * q.w);
    values[3] = 0.0f;                 

    values[4] = 2.0f * ( q.x * q.y - q.z * q.w );
    values[5] = 1.0f - 2.0f * ( q.x * q.x + q.z * q.z );
    values[6] = 2.0f * (q.z * q.y + q.x * q.w );
    values[7] = 0.0f;

    values[8] = 2.0f * ( q.x * q.z + q.y * q.w );
    values[9] = 2.0f * ( q.y * q.z - q.x * q.w );
    values[10] = 1.0f - 2.0f * ( q.x * q.x + q.y * q.y );
    values[11] = 0.0f;  

    values[12] = 0;  
    values[13] = 0;                                   
    values[14] = 0;                               
    values[15] = 1.0f;     
}

void Matrix4::UpdateFloats(){
	for(int i = 0; i < 16; i++){
		this->valuesf[i] = (float)this->values[i];
	}
}

Matrix4::~Matrix4() {
}
