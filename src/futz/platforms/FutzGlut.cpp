/*
 * FutzGlut.cpp
 *
 *  Created on: Nov 3, 2010
 *      Author: ziba
 */
#ifdef _WIN32
#include <Windows.h>
#endif
#ifdef OSX
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#ifdef _WIN32
#include <glut.h>
#else
#include <GL/glut.h>
#endif
#endif
#include "../Futz.h"

#include <stdio.h>

#include "FutzGlut.h"


void FutzGlut::Initialize(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(1024, 700);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
	glutCreateWindow("Futz - GLUT");

	glutKeyboardFunc(FutzGlut::KeyPressFunc);
	glutKeyboardUpFunc(FutzGlut::KeyUpFunc);

	glutDisplayFunc(FutzGlut::RenderScene);
	glutReshapeFunc(FutzGlut::Reshape);
	//glutMouseFunc(MouseFunc);
	glutPassiveMotionFunc(FutzGlut::PassiveMotion);

	glutTimerFunc(500, FutzGlut::Timer, 1);

	Futz* futz = Futz::Instance();
	Futz::Instance()->renderer->Initialize(1024,700);

	futz->gameObject->Start();

	glutMainLoop();
}

void FutzGlut::Resize(int width, int height){
	if (height==0)
		height=1;
#ifndef OPENGLES1
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,0.1f,500.0f);
	glMatrixMode(GL_MODELVIEW);
#endif
}

void FutzGlut::KeyPressFunc(unsigned char key, int x, int y) {
	Futz* futz = Futz::Instance();
	//futz->inputEventQueue.Push(key);
    futz->input.SetDown(key);
}

void FutzGlut::KeyUpFunc(unsigned char key, int x, int y) {
	Futz* futz = Futz::Instance();
    futz->input.SetUp(key);
}

void FutzGlut::PassiveMotion(int x, int y) {
	Futz* futz = Futz::Instance();
	//futz->inputEventQueue.PushMouse(x, y);
    futz->input.SetMouse(x,y);
}

void FutzGlut::RenderScene(void) {

	Futz* futz = Futz::Instance();
	futz->Render();
	futz->gameObject->RenderLoop();
	glutSwapBuffers();
}

void FutzGlut::Timer(int value) {
	Futz* futz = Futz::Instance();
	futz->Update();

	glutPostRedisplay();
	glutTimerFunc(5, FutzGlut::Timer, 1);
}

void FutzGlut::Reshape(int Width, int Height) {
	Futz* futz = Futz::Instance();
	futz->platform->Resize(Width, Height);
}

void FutzGlut::ToggleFullscreen(){
	Futz* futz = Futz::Instance();
	if(!futz->platform->isFullscreen){
		glutFullScreen();
	} else {
		glutReshapeWindow(futz->platform->width, futz->platform->height);
	}
	futz->platform->isFullscreen = !futz->platform->isFullscreen;
}

FutzGlut::~FutzGlut() {
	// TODO Auto-generated destructor stub
}
