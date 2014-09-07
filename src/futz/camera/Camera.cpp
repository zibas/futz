#include "Camera.h"
#include "../Futz.h"
#include <stdio.h>


Camera::Camera() {
	mode = FUTZ_FREE_CAM;
	transform = Matrix4();
	rotation = Quaternion();

	fieldOfView = 60;

	up.x = 0;
	up.y = 1;
	up.z = 0;

	eye.x = 0;
	eye.y = 0;
	eye.z = 10;

	followDistance = 10;
	center.x = center.y = center.z = 0;
	
	panX = panY = panZ = 0;
	rotX = rotY = rotZ = 0;

	center.x = center.y = center.z = 0;

	rotation.SetFromEuler(rotX, rotY, rotZ);
	transform.SetIdentity();
}

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

void Camera::ComputeTransformOrbitCenter(){
	rotation.SetFromEuler(rotX, rotY, rotZ);
	Matrix4 rotMat = Matrix4();
	rotMat.Set(rotation);

	transform.SetIdentity();
	transform.SetTranslation(0, 0, eye.z);
	transform = transform * rotMat;
	transform.Invert();
}

void Camera::ComputeTransform(){
	switch(mode){
		case FUTZ_FOLLOW_CENTER_CAM:
			this->ComputeTransformFollowCenter();
			break;
		case FUTZ_ORBIT_CENTER_CAM:
			this->ComputeTransformOrbitCenter();
			break;
	}
}

void Camera::MoveRight(double amount){
	switch(mode){
		case FUTZ_FOLLOW_CENTER_CAM:
			center.x += amount;
			break;
		case FUTZ_ORBIT_CENTER_CAM:
			eye.x += amount;
			break;
	}
}

void Camera::MoveForward(double amount){
	switch(mode){
		case FUTZ_FOLLOW_CENTER_CAM:
			center.z += amount;
			break;
		case FUTZ_ORBIT_CENTER_CAM:
			eye.z += amount;
			break;
	}
}

void Camera::PanX(double amount)
{
	panX += amount;
}

void Camera::MoveUp(double amount)
{
	switch(mode){
		case FUTZ_FOLLOW_CENTER_CAM:
			center.y += amount;
			break;
		case FUTZ_ORBIT_CENTER_CAM:
			eye.y += amount;
			break;
	}
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
	Futz::Instance()->renderer->SetCameraParameters(this);
}

void Camera::SetFollowCenter(){
	mode = FUTZ_FOLLOW_CENTER_CAM;
}

void Camera::SetOrbit(){
	mode = FUTZ_ORBIT_CENTER_CAM;
}

void Camera::Print(){
    printf("Camera:\n");
    printf("Transform:\n");
    transform.Print();
    printf("Eye:\n");
    eye.Print();
    printf("Center:\n");
    center.Print();
    printf("Rotation:\n");
    printf("RotX: %f,\tRotY: %f,\tRotZ: %f,\n",rotX, rotY, rotZ);
	printf("Field of view: %f\n", fieldOfView);
    printf("--------\n");
}

Camera::~Camera() {}

