/*
 * Matrix4.h
 *
 *  Created on: Oct 29, 2010
 *      Author: ziba
 */

#ifndef MATRIX4_H_
#define MATRIX4_H_

#include "Quaternion.h"

class Matrix4 {
public:
	Matrix4();
	float values[16];
	float valuesf[16];

	// Methods that change the object
	void SetIdentity();
	void SetScale(float scale);
	void SetRotX(float radians);
	void SetRotY(float radians);
	void SetRotZ(float radians);
	void Set(int row, int column, float value);
	void SetRight(float, float, float);
	void SetUp(float, float, float);
	void SetBackward(float, float, float);
	void SetTranslation(float, float, float);
	void Set(Quaternion q); 
	void Invert();

	// Methods that produce a new object
	Matrix4 operator*(const Matrix4&);

	// Methods that don't change or produce objects
	float Determinant();
	void Print();
	void UpdateFloats();

	virtual ~Matrix4();
};

#endif /* MATRIX4_H_ */
