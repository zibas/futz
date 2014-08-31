#if FUTZ_PLATFORM_DREAMCAST
#include "DreamcastRenderer.h"



#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <png/png.h>
#include <jpeg/jpeg.h>

#include <stdio.h>
#include <vector>
#include "../../models/Model.h"
#include "../../models/Triangle.h"
#include "../../Futz.h"

void DreamcastRenderer::Initialize(int width, int height){
    Futz::Log("Initializing PVR/OpenGL");


    glKosInit();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,640.0f/480.0f,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    DefaultLighting();
}
void DreamcastRenderer::StartFrame(){
	glKosBeginFrame();
	glLoadIdentity();
}

void DreamcastRenderer::FinishFrame(){
        glKosFinishFrame();
}
void DreamcastRenderer::ApplyCamera(Camera camera){
	glMultMatrixf(camera.transform.values);
}

void DreamcastRenderer::DrawModel(Model model, float* transformValues){
	glPushMatrix();
	glMultMatrixf(transformValues);
	glFrontFace(GL_CCW);
	DrawImmediate(model);
	glPopMatrix();
}



void DreamcastRenderer::DrawImmediate(Model model){
    //Futz* futz = Futz::Instance();
	currentTextureIndex = -1;

	glBegin(GL_TRIANGLES);
    r = g = b = a = 1;
    hasTexture = false;
    textureIndex = -1;

	for (int i = 0; i < model.triangles.size(); i++) {
		t = model.triangles[i];
        textureIndex = model.materials[t.materialName].textureIndex;
        hasTexture = model.materials[t.materialName].hasTexture;

        v1.x = model.vertexArray[i * 9];
        v1.y = model.vertexArray[i * 9 + 1];
        v1.z = model.vertexArray[i * 9 + 2];

        v2.x = model.vertexArray[i * 9 + 3];
        v2.y = model.vertexArray[i * 9 + 4];
        v2.z = model.vertexArray[i * 9 + 5];

        v3.x = model.vertexArray[i * 9 + 6];
        v3.y = model.vertexArray[i * 9 + 7];
        v3.z = model.vertexArray[i * 9 + 8];

        n1.x = model.normalArray[i * 9];
        n1.y = model.normalArray[i * 9 + 1];
        n1.z = model.normalArray[i * 9 + 2];

        n2.x = model.normalArray[i * 9 + 3];
        n2.y = model.normalArray[i * 9 + 4];
        n2.z = model.normalArray[i * 9 + 5];

        n3.x = model.normalArray[i * 9 + 6];
        n3.y = model.normalArray[i * 9 + 7];
        n3.z = model.normalArray[i * 9 + 8];


        r = model.colorArray[i * 12];
        g = model.colorArray[i * 12 + 1];
        b = model.colorArray[i * 12 + 2];
        a = model.colorArray[i * 12 + 3];

        if(hasTexture){
            t1x = model.textureCoordsArray[i * 6 + 0];
            t1y = model.textureCoordsArray[i * 6 + 1];
            t2x = model.textureCoordsArray[i * 6 + 2];
            t2y = model.textureCoordsArray[i * 6 + 3];
            t3x = model.textureCoordsArray[i * 6 + 4];
            t3y = model.textureCoordsArray[i * 6 + 5];
        }

        if(textureIndex != currentTextureIndex){
            if(hasTexture){
                currentTextureIndex = textureIndex;
                glEnd();
                glEnable ( GL_TEXTURE_2D );
                glBindTexture(GL_TEXTURE_2D, model.textureIDs[currentTextureIndex]);
                glBegin(GL_TRIANGLES);
            } else {
                glEnd();
                glDisable ( GL_TEXTURE_2D );
                glBegin(GL_TRIANGLES);
            }
        }

		glNormal3f(n1.x, n1.y, n1.z);
		if(hasTexture)
			glTexCoord2f(t1x, t1y);
        glColor4f(r,g,b,a);
		glVertex3f(v1.x, v1.y, v1.z);

		glNormal3f(n2.x, n2.y, n2.z);
		if(hasTexture)
			glTexCoord2f(t2x, t2y);
		glColor4f(r,g,b,a);
		glVertex3f(v2.x, v2.y, v2.z);

		glNormal3f(n3.x, n3.y, n3.z);
		if(hasTexture)
			glTexCoord2f(t3x, t3y);
		glColor4f(r,g,b,a);
		glVertex3f(v3.x, v3.y, v3.z);
	}
	glEnd();
}

void DreamcastRenderer::LoadImage(Model* model, string filename, int textureIndex){
	kos_img_t img;
	pvr_ptr_t txaddr;

        uint32 mask = PNG_NO_ALPHA;
	filename = Futz::Instance()->platform->ResolveFilename(filename);
	Futz::Log("[renderer] Loading Image: "+filename);
	if(filename.substr(filename.find_last_of(".") + 1) == "png") {
		if (png_to_img(filename.c_str(), mask, &img) < 0) {
			printf("can't load %s\n", filename.c_str());
			return;
		}
	} else if (filename.substr(filename.find_last_of(".") + 1) == "jpg") {
		if (jpeg_to_img(filename.c_str(), 1, &img) < 0) {
			printf("can't load %s\n", filename.c_str());
			return;
		}
	} else {
		Futz::Log("[renderer] Unrecognized image extension: "+filename);
	}

	txaddr = pvr_mem_malloc(img.w * img.h * 2);
	pvr_txr_load_kimg(&img, txaddr, PVR_TXRLOAD_INVERT_Y);
	kos_img_free(&img, 0);

	glGenTextures(1, &(model->textureIDs[textureIndex]));
	glBindTexture(GL_TEXTURE_2D, model->textureIDs[textureIndex]);
	glKosTex2D(GL_RGB565_TWID, img.w, img.h, txaddr);
/*
	int x, y;
//	model->imageData = Futz::Instance()->platform->LoadImage(filename, &x, &y);
	glGenTextures(1, &(model->textureIDs[textureIndex]));
	glBindTexture(GL_TEXTURE_2D, model->textureIDs[textureIndex]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, model->imageData);
*/
}

void DreamcastRenderer::DefaultLighting(){
}

void DreamcastRenderer::DisableLighting(){
}

void DreamcastRenderer::EnableLighting(){
}
#endif
