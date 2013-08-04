#include "DummyRenderer.h"
#include <stdio.h>

#include <vector>
#include "../../models/Model.h"
#include "../../models/Triangle.h"

void DummyRenderer::DrawModel(Model model, float* transformValues){
//	printf("Dummy renderer: Draw Model\n");
}

void DummyRenderer::LoadImage(Model* model, string filename, int textureIndex){
	printf("Dummy renderer: Load Image\n");
}

