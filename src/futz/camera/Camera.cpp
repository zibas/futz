#include "Camera.h"
#include "../Futz.h"
#include <stdio.h>
#include <math.h>
#define PI 3.14159265


Camera::Camera() {
	transform = Matrix4();
	rotation = Quaternion();
	

	up.x = 0;
	up.y = 1;
	up.z = 0;

	eye.x = 0;
	eye.y = 0;
	eye.z = 10;

	followDistance = 10;
	
	panX = panY = panZ = 0;
	rotX = rotY = rotZ = 0;

	

	center.x = center.y = center.z = 0;
	center.z = 30;

	centerRelativeToEye = center - eye;


	nearDistance = 0.1f;
	farDistance = 500;
	fieldOfView = 60;
	rotation.SetFromEuler(rotX, rotY, rotZ);
	transform.SetIdentity();
	CalculateFrustum();

}

/*
void Camera::ComputeTransformFollowCenter(){
	rotation.SetFromEuler(rotX, rotY, rotZ);
	Matrix4 rotMat = Matrix4();
	rotMat.Set(rotation);

	Matrix4 centerMat = Matrix4();
	centerMat.SetTranslation(center.x, center.y, center.z);
	centerMat = rotMat * centerMat;
	Vector3 c;
	c.x = centerMat.values[12]; 
	c.y = centerMat.values[13]; 
	c.z = centerMat.values[14]; 

	//eye.x = center.x; eye.y = center.y; eye.z = center.z;
	eye.x = c.x; eye.y = c.y; eye.z = c.z;
	eye.z += followDistance;

	transform.SetTranslation(eye.x, eye.y, eye.z);

	Vector3 vx = Vector3();
	Vector3 vy = Vector3();
	Vector3 vz = Vector3();

	// Face center
	//vz = eye - center;
	vz = eye - c;
	vz.Normalize();
	
	vx = up * vz;
	vx.Normalize();

	vy = vz * vx;
	vy.Normalize();

	transform.SetRight(vx.x, vx.y, vx.z);
	transform.SetUp(vy.x, vy.y, vy.z);
	transform.SetBackward(vz.x, vz.y, vz.z);

	transform = transform;
	//In OpenGL, we are actually going to move everything BUT the "camera"
	transform.Invert();
}
*/


/*
void Camera::ComputeTransformOrbitCenter(){
	rotation.SetFromEuler(rotX, rotY, rotZ);
	Matrix4 rotMat = Matrix4();
	rotMat.Set(rotation);

	transform.SetIdentity();
	transform.SetTranslation(0, 0, eye.z);
	transform = transform * rotMat;
	transform.Invert();
}
*/

void Camera::ComputeTransform(){

	bool debugCamera = false;
	


	Vector3 vx = Vector3();
	Vector3 vy = Vector3();
	Vector3 vz = Vector3();


	transform.SetTranslation(eye.x, eye.y, eye.z);


	if (debugCamera){
		transform.SetTranslation(-50,10,5);

		vz.x = -0.5; vz.y = 0; vz.z = 0;
	}
	else {
		// Face center
		vz = eye - center;
	}

	vz.Normalize();


	vx = up * vz;
	vx.Normalize();

	vy = vz * vx;
	vy.Normalize();

	transform.SetRight(vx.x, vx.y, vx.z);
	transform.SetUp(vy.x, vy.y, vy.z);
	transform.SetBackward(vz.x, vz.y, vz.z);

	//transform = transform;
	//In OpenGL, we are actually going to move everything BUT the "camera"
	transform.Invert();
}




void Camera::MoveRight(double amount){

	Vector3 forward = center - eye;
	forward.Normalize();
	Vector3 right = forward * up;
	right.Normalize();

	eye = eye + (right * amount);
	center = center + (right * amount);
}

void Camera::MoveForward(double amount){

	Vector3 direction = center - eye;

	direction.Normalize();

	eye = eye + (direction * amount);
	center = center + (direction * amount);

}


void Camera::MoveUp(double amount)
{
	eye = eye + (up * amount);
	center = center + (up * amount);
}

void Camera::Rotate(Vector3 eulerDelta){
	Quaternion rotationToApply;

	rotX += eulerDelta.x;
	rotY += eulerDelta.y;
	rotZ += eulerDelta.z;



	Matrix4 rotMatX = Matrix4();
	rotMatX.SetIdentity();
	rotationToApply.SetFromEuler(rotX, 0, 0);

	rotMatX.Set(rotationToApply);

	Matrix4 rotMatY = Matrix4();
	rotMatY.SetIdentity();
	rotationToApply.SetFromEuler(0, rotY, 0);

	rotMatY.Set(rotationToApply);


	//TODO constrain rotation around y to operate against the global y, not the center's y
// otherwise it's like facing down in a pool. turning left will face you up.
	/*
	rotationToApply.SetFromEuler(0, rotY, 0);

	Matrix4 rotMatY = Matrix4();
	rotMatY.SetIdentity();
	rotMatY.Set(rotationToApply);
	*/

	Matrix4 translateToEye = Matrix4();
	translateToEye.SetIdentity();
	//translateToEye.SetTranslation(eye.x - center.x, eye.y - center.y, eye.z - center.z);
	//translateToEye.SetTranslation(eye.x, eye.y, eye.z);
	//translateToEye.SetTranslation(-centerRelativeToEye.x, -centerRelativeToEye.y, -centerRelativeToEye.z);
	//Matrix4 translateToEye = Matrix4();
	translateToEye.SetIdentity();
	translateToEye.SetTranslation(eye.x, eye.y, eye.z);

	Matrix4 translateAwayfromEye = Matrix4();
	translateAwayfromEye.SetIdentity();
	translateAwayfromEye.SetTranslation(center.x - eye.x, center.y - eye.y, center.z - eye.z);
	//translateAwayfromEye.SetTranslation(centerRelativeToEye.x, centerRelativeToEye.y, centerRelativeToEye.z);
	//translateAwayfromEye.SetTranslation(-eye.x, -eye.y, -eye.z);

	Matrix4 translateFromEyeToZero = Matrix4();
	translateFromEyeToZero.SetIdentity();
	translateFromEyeToZero.SetTranslation(-eye.x, -eye.y, -eye.z);

	

	Matrix4 translateMinus10z = Matrix4();
	translateMinus10z.SetIdentity();
	translateMinus10z.SetTranslation(0,0,-10);

	Matrix4 translatePlus10z = Matrix4();
	translatePlus10z.SetIdentity();
	translatePlus10z.SetTranslation(0, 0, 10);



	Matrix4 centerMat = Matrix4();
	centerMat.SetIdentity();
	centerMat.SetTranslation(centerRelativeToEye.x, centerRelativeToEye.y, centerRelativeToEye.z);
	//centerMat.SetTranslation(center.x, center.y, center.z);
	//printf("centerMat z: %f\n", centerMat.values[14]);

	Matrix4 resultMat = Matrix4();
	resultMat.SetIdentity();
	resultMat =  centerMat * rotMatX * translateToEye;


	center.x = resultMat.values[12];
	center.y = resultMat.values[13];
	center.z = resultMat.values[14];



	Matrix4 translateToY0 = Matrix4();
	translateToY0.SetIdentity();
	translateToY0.SetTranslation(0,  -center.y, 0);

	Matrix4 translateRestoreY = Matrix4();
	translateRestoreY.SetIdentity();
	translateRestoreY.SetTranslation(0, center.y, 0);


	resultMat = resultMat * translateFromEyeToZero * translateRestoreY * rotMatY * translateToEye * translateToY0;



	//printf("centerMat post transform z: %f\n", centerMat.values[14]);

	center.x = resultMat.values[12];
	center.y = resultMat.values[13];
	center.z = resultMat.values[14];





	

}

void Camera::RotateCenter(Vector3 eulerDelta){


}

void Camera::PanX(double amount)
{
	panX += amount;
}


void Camera::PanZ(double amount)
{
	panZ += amount;
}

void Camera::RotRightAxis(double amount)
{
	rotX+=amount;
}

void Camera::RotX(double amount)
{
	rotX += amount;
}

void Camera::RotY(double amount)
{
	rotY += amount;
}

void Camera::RotZ(double amount)
{
	rotZ += amount;
}

void Camera::SetFieldOfView(float newFOV){
	fieldOfView = newFOV;
	CalculateFrustum();
	Futz::Instance()->renderer->SetCameraParameters(this);
}

void Camera::CalculateFrustum(){
	heightNear = (float)2 * (float)tan(((float)fieldOfView / (float)2) * PI / 180.0) * nearDistance;
	widthNear = heightNear * (float)viewportWidth / (float)viewportHeight;

	heightFar = (float)2 * (float)tan(((float)fieldOfView / (float)2) * PI / 180.0) * farDistance;
	widthFar = heightFar * (float)viewportWidth / (float)viewportHeight;
}

void Camera::Print(){
    printf("Camera:\n");
    printf("Transform:\n");
    transform.Print();
	printf("Up:\t");
	up.Print();

		printf("Center:\t");
		center.Print();
		printf("Eye:\t");
		eye.Print();

		printf("Distance from center: %f\n",eye.z);
		printf("RotX: %f,\tRotY: %f,\tRotZ: %f,\n", rotX, rotY, rotZ);

	
    printf("Field of view: %f\n", fieldOfView);
	printf("Near: %g,%g\nFar:%g,%g\n", widthNear, heightNear, widthFar, heightFar);

    printf("--------\n");
}

Camera::~Camera() {}

