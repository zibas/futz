#if FUTZ_RENDERER_GL3

#include "GL3Renderer.h"
#include <stdio.h>

#include <vector>
#include "../../models/Model.h"
#include "../../models/Triangle.h"

void GL3Renderer::DrawModel(Model model, float* transformValues){
	printf("GL3 renderer: Draw Model\n");
}

void GL3Renderer::LoadImage(Model* model, string filename, int textureIndex){
	printf("GL3 renderer: Load Image\n");
}
#endif

