#ifndef RENDERERBASE_H_
#define RENDERERBASE_H_

#include <vector>
#include "../camera/Camera.h"
#include "../models/Model.h"
#include "../math/Vector3.h"
#include <stdio.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace std;

class RendererBase
{
	//protected:
	//virtual void glhPerspectivef2(float *matrix, float fovyInDegrees, float aspectRatio, float znear, float zfar);
	//virtual void glhFrustumf2(float *matrix, float left, float right, float bottom, float top, float znear, float zfar);

  public:

	virtual void Initialize(int width, int height){
		//printf("Renderer Unimplemented: Initialize\n");
	};

	virtual void DefaultLighting(){
		//printf("Renderer Unimplemented: DefaultLighting\n");
	};
	virtual void DisableLighting(){
		//printf("Renderer Unimplemented: DisableLighting\n");
	};
	virtual void EnableLighting(){
		//printf("Renderer Unimplemented: EnableLighting\n");
	};
	virtual void StartFrame(){
		//printf("Renderer Unimplemented: StartFrame\n");
	};
	virtual void FinishFrame(){
		//printf("Renderer Unimplemented: StartFrame\n");
	};
	virtual void ApplyCamera(Camera camera){
		//printf("Renderer Unimplemented: ApplyCamera\n");
	};

	virtual void SetCameraParameters(Camera *camera)
	{
		printf("Renderer Unimplemented: SetCameraParameters\n");
	};

	virtual void DrawSphere(Vector3 center, float radius){};
	virtual void DrawLine(Vector3, Vector3){};
	virtual void DrawLine(Vector3, Vector3, Vector3){};
	void DrawLine(float x, float y, float z, float x2, float y2, float z2)
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
	virtual void DrawModel(){};
	virtual void StartTransform(float *transformValues){};
	virtual void EndTransform(){};
	virtual void DrawModel(Model model){};
	virtual void DrawModel(Model *model){};
	virtual void LoadImage(Model *model, string filename, int textureIndex){};
	virtual void Resize(int width, int height){};

		
	virtual void TestFunction()
	{
		//printf("parent test function");
	};

	void glhPerspectivef2(float *matrix, float fovyInDegrees, float aspectRatio, float znear, float zfar);
	void glhFrustumf2(float *matrix, float left, float right, float bottom, float top, float znear, float zfar);
};

#endif
