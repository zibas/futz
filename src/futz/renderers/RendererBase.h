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
#ifdef _WIN32
#include <memory>
#else
#include <tr1/memory>
#endif
using namespace std;

class RendererBase
{

  protected:
	void glhPerspectivef2(float *matrix, float fovyInDegrees, float aspectRatio, float znear, float zfar);
	void glhFrustumf2(float *matrix, float left, float right, float bottom, float top, float znear, float zfar);

  public:
	virtual void Initialize(int width, int height);

	virtual void DefaultLighting();
	virtual void DisableLighting();
	virtual void EnableLighting();
	virtual void StartFrame();
	virtual void FinishFrame();
	virtual void ApplyCamera(Camera camera);
	virtual void SetCameraParameters(Camera *camera);

	virtual void DrawSphere(Vector3 center, float radius);
	virtual void DrawLine(Vector3, Vector3);
	virtual void DrawLine(Vector3, Vector3, Vector3);
	void DrawLine(float x, float y, float z, float x2, float y2, float z2);
	virtual void DrawModel();
	virtual void StartTransform(float *transformValues);
	virtual void EndTransform();
	virtual void DrawModel(Model model);
	virtual void DrawModel(Model *model);
	virtual void LoadImage(Model *model, string filename, int textureIndex);
	virtual void Resize(int width, int height);
	typedef std::shared_ptr<RendererBase> RendererHandle;

	~RendererBase();
};

#endif
