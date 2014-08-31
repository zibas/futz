#if FUTZ_RENDERER_GLES1
#ifndef GLES1RENDERER_H_
#define GLES1RENDERER_H_

#ifdef IOS
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#else
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif

#include "../RendererBase.h"
#include "../../models/Model.h"

using namespace std;

//TODO: inherit from GL1Renderer
class GLES1Renderer: public RendererBase {
	
public:
	//DummyRenderer();
	//virtual ~DummyRenderer();
	void Initialize(int, int);
	void StartFrame();
	void ApplyCamera(Camera);
	void DrawModel(Model);
	void LoadImage(Model* model, string filename, int textureIndex);
	void DefaultLighting();
	void DisableLighting();
	void EnableLighting();
	void StartTransform(float* transformValues);
	void EndTransform();
    void DrawLine(Vector3 a, Vector3 b, Vector3 c);
    void DrawLine(Vector3 a, Vector3 b);
private:
	void DrawWithArrays(Model);
};

#endif
#endif