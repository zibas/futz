#include "Transform.h"
#include "Node.h"
#include <stdio.h>

Transform::Transform(){
	matrix = Matrix4();
	matrix.SetIdentity();
	rotation = Quaternion();
	scale = 1;
}

void Transform::Print(){
	printf("Transform:\n");
	position.Print();
	matrix.Print();
	rotation.Print();
}

void Transform::SetOrbit(Vector3 center, double distance, Quaternion qrot){
	Matrix4 rot = Matrix4();
	Matrix4 pos = Matrix4();
	Matrix4 centerpos = Matrix4();
	Matrix4 m_scale = Matrix4();
	
	m_scale.SetScale(scale);
	pos.SetIdentity();
	pos.SetTranslation(distance,0,0);

	centerpos.SetIdentity();
	centerpos.SetTranslation(center.x,center.y,center.z);

	rot.Set(qrot);

	matrix = m_scale * pos * rot * centerpos;

	position.x = matrix.values[12];
	position.y = matrix.values[13];
	position.z = matrix.values[14];
}

void Transform::SetPosition(double x, double y, double z){
	position.x = x;
	position.y = y;
	position.z = z;
	RecalculateMatrix();
}

void Transform::SetRotation(double x, double y, double z){
	euler.x = x;
	euler.y = y;
	euler.z = z;
	RecalculateMatrix();
}

void Transform::LookAt(Vector3 target){
	Vector3 up;
	up.x = 0; up.y = 1; up.z = 0;

	Vector3 vx = Vector3();
	Vector3 vy = Vector3();
	Vector3 vz = Vector3();

	// Face center
	//vz = eye - center;
	vz = position - target;
	vz.Normalize();

	vx = up * vz;
	vx.Normalize();

	vy = vz * vx;
	vy.Normalize();
	
	matrix.SetRight(vx.x, vx.y, vx.z);
	matrix.SetUp(vy.x, vy.y, vy.z);
	matrix.SetBackward(vz.x, vz.y, vz.z);
}

void Transform::AddRelativeTranslation(double x, double y, double z){
	Matrix4 rotMat = Matrix4();
	rotMat.Set(rotation);

	Matrix4 rotForward = Matrix4();
	rotForward.SetIdentity();
	rotForward.SetTranslation(x,y,z);
	rotForward = rotForward * rotMat;

	position.x += rotForward.values[12];
	position.y += rotForward.values[13];
	position.z += rotForward.values[14];

	RecalculateMatrix();
}

void Transform::SetScale(double newScale){
	scale = newScale;
	RecalculateMatrix();
}

void Transform::RecalculateMatrix(){
	rotation.SetFromEuler(euler.x,euler.y,euler.z);
	Matrix4 rot = Matrix4();
	Matrix4 pos = Matrix4();
	Matrix4 m_scale = Matrix4();
	
	m_scale.SetScale(scale);
	pos.SetIdentity();
	pos.SetTranslation(position.x,position.y,position.z);
	rot.Set(rotation);
	matrix = m_scale * rot * pos;
	Node* n = (Node*) node;
	if(n->parent != NULL){
		matrix = matrix * n->parent->transform.matrix;
	}
}

Transform::~Transform(){

}
