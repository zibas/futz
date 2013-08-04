/*
 * Vector3.h
 *
 *  Created on: Oct 29, 2010
 *      Author: ziba
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_
#include "Matrix4.h"

class Vector3 {
public:
	float x;
	float y;
	float z;

	static float Dot(const Vector3&, const Vector3&);
	static float RadiansBetween(const Vector3&, const Vector3&);
	static float DegreesBetween(const Vector3&, const Vector3&);
	float Dot(const Vector3&);

	// Methods that produce a new object
	Vector3 operator-(const Vector3&);
	Vector3 operator+(const Vector3&);
	Vector3 operator*(const Vector3&);
	Vector3 operator*(const double&);

    Vector3 Transform(Matrix4);

	// Methods that modify the object
	void Normalize();

	float Length();
	void Print();
	Vector3();
	virtual ~Vector3();
};

#endif /* VECTOR3_H_ */
