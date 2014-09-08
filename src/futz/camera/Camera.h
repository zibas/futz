/*
 * Camera.h
 *
 *  Created on: Oct 29, 2010
 *      Author: ziba
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include "../math/Matrix4.h"
#include "../math/Vector3.h"

class Camera {
public:
	Matrix4 transform;
	Quaternion rotation;

	Vector3 velocity;
	
	Vector3 eye;
	Vector3 center;


	Vector3 up;
	Vector3 forward;
	Vector3 right;

	float viewportWidth;
	float viewportHeight;

	double followDistance;

	Camera();
	virtual ~Camera();

	void MoveForward(double);
	void MoveRight(double);
	void MoveUp(double);

	void PanX(double);
	void PanZ(double);

	void RotRightAxis(double);
	void RotX(double);
	void RotY(double);
	void RotZ(double);

	void RotateCenter(Vector3 eulerDelta);
	void Rotate(Vector3 eulerDelta);
	void LookAt(Vector3 newCenter);


	void ComputeTransform();


	void SetViewport(float width, float height){
		viewportHeight = height;
		viewportWidth = width;
	};
	void SetFieldOfView(float newFOV);
	float GetFieldOfView(){ return fieldOfView; }
	float GetNearDistance(){ return nearDistance; }
	float GetFarDistance(){ return farDistance; }

	void Print();

private:

	Vector3 centerRelativeToEye;

	float fieldOfView;
	float nearDistance;
	float farDistance;

	float heightNear;
	float widthNear;
	float heightFar;
	float widthFar;

	double panX;
	double panY;
	double panZ;

	double rotX;
	double rotY;
	double rotZ;

	void CalculateFrustum();

};

#endif /* CAMERA_H_ */
