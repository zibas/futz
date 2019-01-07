#ifndef GL1RENDERER_H_
#define GL1RENDERER_H_


#include "../RendererBase.h"
#include "../../models/Model.h"

using namespace std;

class GL1Renderer: public RendererBase {

public:
	//DummyRenderer();
	//virtual ~DummyRenderer();
	void Initialize(int, int);
	void StartFrame();
	void ApplyCamera(Camera);
	void DrawModel(Model);
	void DrawModel(Model*);
	void LoadImage(Model* model, string filename, int textureIndex);
	void DefaultLighting();
	void DisableLighting();
	void EnableLighting();
	void StartTransform(float* transformValues);
	void EndTransform();
	void DrawSphere(Vector3 center, float radius);
    void DrawLine(Vector3 a, Vector3 b, Vector3 c);
    void DrawLine(Vector3 a, Vector3 b);
	void Resize(int width, int height);
	void TestFunction();

	void SetCameraParameters(Camera* camera);

private:
	void DrawWithArrays(Model*);
	void DrawImmediate(Model);
};

#endif
