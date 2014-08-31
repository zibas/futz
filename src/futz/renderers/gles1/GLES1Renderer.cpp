#if FUTZ_RENDERER_GLES1
#include "GLES1Renderer.h"
#include <stdio.h>
#include <vector>
#include "../../models/Model.h"
#include "../../models/Triangle.h"
#include "../../Futz.h"

void GLES1Renderer::Initialize(int width, int height){
    Futz::Log("Initializing OpenGL");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    DefaultLighting();
}
void GLES1Renderer::StartFrame(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_MODELVIEW);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLoadIdentity();
}

void GLES1Renderer::ApplyCamera(Camera camera){
	glMultMatrixf(camera.transform.values);
}

void GLES1Renderer::StartTransform(float* transformValues){
	glPushMatrix();
	glMultMatrixf(transformValues);
}

void GLES1Renderer::EndTransform(){
	glPopMatrix();
}

void GLES1Renderer::DrawModel(Model model){
	glFrontFace(GL_CCW);
	DrawWithArrays(model);
	//DrawImmediate(model);
}

void GLES1Renderer::DrawWithArrays(Model model){
	int i;

	glTexCoordPointer(2, GL_FLOAT, 0, model.textureCoordsArray);
	glVertexPointer(3, GL_FLOAT, 0, model.vertexArray);
	glColorPointer(4, GL_FLOAT, 0, model.colorArray);
	glNormalPointer(GL_FLOAT, 0, model.normalArray);

	int pos = 0;
	for(std::vector< std::pair<Material*, int> >::iterator it = model.vertexGroups.begin(); it != model.vertexGroups.end(); ++it) {
		if(((*it).first)->hasTexture){
			glEnable ( GL_TEXTURE_2D );
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindTexture(GL_TEXTURE_2D, model.textureIDs[((*it).first)->textureIndex]);
			//printf("length, index, pos: %d, %d, %d\n",(*it).second,((*it).first)->textureIndex,pos);
		} else {
			//printf("length, index, pos: %d, NONE, %d\n",(*it).second,pos);
			glDisable ( GL_TEXTURE_2D );
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		glDrawElements(GL_TRIANGLES, (*it).second, GL_UNSIGNED_SHORT, &model.indexArray[pos]);
		pos += (*it).second;
	}
}


void GLES1Renderer::LoadImage(Model* model, string filename, int textureIndex){
	int x, y;
	model->imageData = Futz::Instance()->platform->LoadImage(filename, &x, &y);
	glGenTextures(1, &(model->textureIDs[textureIndex]));
	glBindTexture(GL_TEXTURE_2D, model->textureIDs[textureIndex]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, model->imageData);
}

void GLES1Renderer::DefaultLighting(){
	GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0}; 
	GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0}; 
	GLfloat light_position[] = {0.0, 0.0, 2.0, 1.0};  /* Infinite light location. */
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
}

void GLES1Renderer::DisableLighting(){
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);
}

void GLES1Renderer::EnableLighting(){
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
}

void GLES1Renderer::DrawLine(Vector3 a, Vector3 b){
    Vector3 c = Vector3();
    c.x = c.y = c.z = 1;
    DrawLine(a,b,c);
}
void GLES1Renderer::DrawLine(Vector3 a, Vector3 b, Vector3 color){
    
    /*
     Not in gles you don't
    glBegin(GL_LINES);
    glColor3f(color.x, color.y, color.z);
    glVertex3f(a.x, a.y, a.z);
    glVertex3f(b.x, b.y, b.z);
    glEnd( );
     */
}
#endif
