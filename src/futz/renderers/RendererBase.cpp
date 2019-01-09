#include "RendererBase.h"

void RendererBase::Initialize(int width, int height){
	//printf("Renderer Unimplemented: Initialize\n");
};
void RendererBase::DefaultLighting(){
	//printf("Renderer Unimplemented: DefaultLighting\n");
};
void RendererBase::DisableLighting(){
	//printf("Renderer Unimplemented: DisableLighting\n");
};
void RendererBase::EnableLighting(){
	//printf("Renderer Unimplemented: EnableLighting\n");
};
void RendererBase::StartFrame(){
	//printf("Renderer Unimplemented: StartFrame\n");
};
void RendererBase::FinishFrame(){
	//printf("Renderer Unimplemented: StartFrame\n");
};
void RendererBase::ApplyCamera(Camera camera){
	//printf("Renderer Unimplemented: ApplyCamera\n");
};

void RendererBase::SetCameraParameters(Camera *camera)
{
	printf("Renderer Unimplemented: SetCameraParameters\n");
};

void RendererBase::DrawSphere(Vector3 center, float radius){};

void RendererBase::DrawLine(Vector3, Vector3){};
void RendererBase::DrawLine(Vector3, Vector3, Vector3){};
void RendererBase::DrawLine(float x, float y, float z, float x2, float y2, float z2)
{
	Vector3 v1;
	v1.x = x;
	v1.y = y;
	v1.z = z;

	Vector3 v2;
	v2.x = x2;
	v2.y = y2;
	v2.z = z2;

	DrawLine(v1, v2);
}
void RendererBase::DrawModel(){};
void RendererBase::StartTransform(float *transformValues){};
void RendererBase::EndTransform(){};
void RendererBase::DrawModel(Model model){};
void RendererBase::DrawModel(Model *model){};
void RendererBase::LoadImage(Model *model, string filename, int textureIndex){};
void RendererBase::Resize(int width, int height){};

//https://www.khronos.org/opengl/wiki/GluPerspective_code
// Replacing a gluPerspective because glu is old and ageing
void RendererBase::glhPerspectivef2(float *matrix, float fovyInDegrees, float aspectRatio, float znear, float zfar)
{
	float ymax, xmax;
	float temp, temp2, temp3, temp4;
	ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
	// ymin = -ymax;
	// xmin = -ymax * aspectRatio;
	xmax = ymax * aspectRatio;
	glhFrustumf2(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}

void RendererBase::glhFrustumf2(float *matrix, float left, float right, float bottom, float top, float znear, float zfar)
{
	float temp, temp2, temp3, temp4;
	temp = 2.0 * znear;
	temp2 = right - left;
	temp3 = top - bottom;
	temp4 = zfar - znear;
	matrix[0] = temp / temp2;
	matrix[1] = 0.0;
	matrix[2] = 0.0;
	matrix[3] = 0.0;
	matrix[4] = 0.0;
	matrix[5] = temp / temp3;
	matrix[6] = 0.0;
	matrix[7] = 0.0;
	matrix[8] = (right + left) / temp2;
	matrix[9] = (top + bottom) / temp3;
	matrix[10] = (-zfar - znear) / temp4;
	matrix[11] = -1.0;
	matrix[12] = 0.0;
	matrix[13] = 0.0;
	matrix[14] = (-temp * zfar) / temp4;
	matrix[15] = 0.0;
}

RendererBase::~RendererBase()
{
	printf("[RendererBase] Destructing\n");
}