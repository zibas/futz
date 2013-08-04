#ifndef DUMMYRENDERER_H_
#define DUMMYRENDERER_H_

#include "../RendererBase.h"
#include "../../models/Model.h"
//#include "../../models/Triangle.h"

using namespace std;

class DummyRenderer: public RendererBase {
	
public:
	//DummyRenderer();
	//virtual ~DummyRenderer();
	void DrawModel(Model model, float* transformValues);
	void LoadImage(Model* model, string filename, int textureIndex);
};

#endif
