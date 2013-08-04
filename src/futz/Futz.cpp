/*
 * Futz.cpp
 *
 *  Created on: Feb 25, 2010
 *      Author: ziba
 */

#ifdef _WIN32
#include <Windows.h>
#endif

#include <stdio.h>
#include "Futz.h"
#include "models/Model.h"
#include "models/wavefront/WavefrontModel.h"

#if GLUT
#include "platforms/FutzGlut.h"
#include "renderers/gl1/GL1Renderer.h"
#elif SDL
#include "platforms/FutzSDL.h"
#include "renderers/gl1/GL1Renderer.h"
#elif ANDROID
#include "platforms/FutzAndroid.h"
#elif IOS
#include "platforms/IOS/FutzIOS.h"
#elif DREAMCAST
#include "platforms/FutzDreamcast.h"
#include "renderers/dreamcast/DreamcastRenderer.h"
#else
#include "platforms/FutzLayer.h"
#endif

#include "renderers/RendererBase.h"
#include "renderers/dummy/DummyRenderer.h"
//#include "renderers/gles1/GLES1Renderer.h"
//#include "renderers/gl1/GL1Renderer.h"

/*
 Futz constructor
	construct proper platform
 Futz->Start
	platform->Initialize
 */


Futz::Futz() {
	Futz::Log("Setting platform");
	#if GLUT
	this->platform = (SystemLayerBase*)new FutzGlut();
	this->renderer = (RendererBase*)new GL1Renderer();
	#elif SDL
	this->platform = (SystemLayerBase*)new FutzSDL();
	this->renderer = (RendererBase*)new GL1Renderer();
	#elif ANDROID
	this->platform = (SystemLayerBase*)new FutzAndroid();
	this->renderer = (RendererBase*)new GLES1Renderer();
	#elif IOS
	this->platform = (SystemLayerBase*)new FutzIOS();
	this->renderer = (RendererBase*)new GLES1Renderer();
	#elif DREAMCAST
	this->platform = (SystemLayerBase*)new FutzDreamcast();
	this->renderer = (RendererBase*)new DreamcastRenderer();
	#else
	this->platform = (SystemLayerBase*)new FutzLayer();
	this->renderer = (RendererBase*)new DummyRenderer();
	#endif

}

void Futz::Start(int argc, char** argv)
{
	platform->Initialize(argc, argv);
}

// Global static pointer used to ensure a single instance of the class.
Futz* Futz::_instance = NULL;

Futz* Futz::Instance()
{
   	// Only allow one instance of class to be generated.
	if (!_instance){
		_instance = new Futz;
	}

	return _instance;
}

void Futz::Update(){
	time.UpdateLoop();
    profiler.Start("Update");
	gameObject->UpdateLoop();
    input.Update(); // Input after game object, to wipe events
	scene.Update();
    profiler.End();
}

void Futz::Render(){
    profiler.Start("Render");
	this->renderer->StartFrame();
	camera.ComputeTransform();
	this->renderer->ApplyCamera(camera);
	scene.Render();
	time.RenderLoop();
	this->renderer->FinishFrame();
    profiler.End();
}

Model* Futz::LoadModel(char* filename){
	return new WavefrontModel(filename);
}

Futz::~Futz(){

}


void Futz::Log(string mesg){
	#ifdef ANDROID
	LOGI(mesg.c_str());
	#else
	printf("Futz: %s\n",mesg.c_str());
	//cout << "Futz: " << mesg << endl;
	#endif
}
