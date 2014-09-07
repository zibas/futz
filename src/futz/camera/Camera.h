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

enum futzCameraModes {FUTZ_FOLLOW_CENTER_CAM, FUTZ_ORBIT_CENTER_CAM, FUTZ_FREE_CAM};
class Camera {
public:
	futzCameraModes mode; 
	Matrix4 transform;
	Quaternion rotation;

	Vector3 velocity;
	
	Vector3 eye;
	Vector3 center;
	Vector3 up;

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

	void ComputeTransform();
	void ComputeTransformOrbitCenter();
	void ComputeTransformFollowCenter();

	void SetViewport(float width, float height){
		viewportHeight = height;
		viewportWidth = width;
	};
	void SetFieldOfView(float newFOV);
	double GetFieldOfView(){ return fieldOfView; }
	void SetFollowCenter();
	void SetOrbit();

	void Print();

private:

	float fieldOfView;

	double panX;
	double panY;
	double panZ;

	double rotX;
	double rotY;
	double rotZ;

};

#endif /* CAMERA_H_ */
