#if FUTZ_PLATFORM_DREAMCAST
#ifndef DREAMCASTRENDERER_H_
#define DREAMCASTRENDERER_H_


#include "../RendererBase.h"
#include "../../models/Model.h"

using namespace std;

class DreamcastRenderer: public RendererBase {
	
public:
	//DummyRenderer();
	//virtual ~DummyRenderer();
	void Initialize(int, int);
	void StartFrame();
	void FinishFrame();
	void ApplyCamera(Camera);
	void DrawModel(Model, float*);
	void LoadImage(Model* model, string filename, int textureIndex);
	void DefaultLighting();
	void DisableLighting();
	void EnableLighting();
private:
	int currentTextureIndex;
    bool hasTexture;
    float r,g,b,a;
    Vector3 v1,v2,v3;
    Vector3 n1,n2,n3;
    float t1x,t1y,t2x,t2y,t3x,t3y;
    int textureIndex;
    Triangle t;
	void DrawWithArrays(Model);
	void DrawImmediate(Model);

};

#endif
#endif
