#ifndef GL3RENDERER_H_
#define GL3RENDERER_H_

#include "../RendererBase.h"
#include "../../models/Model.h"
//#include "../../models/Triangle.h"

using namespace std;

class GL3Renderer: public RendererBase {
	
public:
	//DummyRenderer();
	//virtual ~DummyRenderer();
    void Initialize(int width,int height){
		printf("GL3 Renderer Unimplemented: Initialize\n");
	};
	void DrawModel(Model model, float* transformValues);
	void LoadImage(Model* model, string filename, int textureIndex);
};

#endif
