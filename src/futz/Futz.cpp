/*
 * Futz.cpp
 *
 *  Created on: Feb 25, 2010
 *      Author: ziba
 */


/*

Define the appropriate variables in your compile phase

FUTZ_RENDERER_GL1
FUTZ_RENDERER_GLES1
FUTZ_RENDERER_GL3

FUTZ_PLATFORM_SDL
FUTZ_PLATFORM_SDL2
FUTZ_PLATFORM_GLUT
FUTZ_PLATFORM_IOS
FUTZ_PLATFORM_DREAMCAST
FUTZ_PLATFORM_ANDROID
*/

#ifdef _WIN32
#include <Windows.h>
#endif

#include <stdio.h>
#include "Futz.h"
#include "models/Model.h"
#include "models/wavefront/WavefrontModel.h"

#if FUTZ_PLATFORM_GLUT
#include "platforms/FutzGlut.h"
#elif FUTZ_PLATFORM_SDL
#include "platforms/FutzSDL.h"
#elif FUTZ_PLATFORM_SDL2
#include "platforms/FutzSDL2.h"
#elif FUTZ_PLATFORM_ANDROID
#include "platforms/FutzAndroid.h"
#elif IOS
#include "platforms/IOS/FutzIOS.h"
#elif FUTZ_PLATFORM_DREAMCAST
#include "platforms/FutzDreamcast.h"
#include "renderers/dreamcast/DreamcastRenderer.h"
#else
#include "platforms/FutzLayer.h"
#endif

#if FUTZ_RENDERER_GL1
#include "renderers/gl1/GL1Renderer.h"
#elif FUTZ_RENDERER_GLES1
#include "renderers/gles1/GLES1Renderer.h"
#endif

#include "renderers/RendererBase.h"
#include "renderers/dummy/DummyRenderer.h"

/*
 Futz constructor
	construct proper platform
 Futz->Start
	platform->Initialize
 */

Futz::Futz()
{
	Futz::Log("Setting platform");
#if FUTZ_PLATFORM_GLUT
	this->platform = (SystemLayerBase *)new FutzGlut();
#elif FUTZ_PLATFORM_SDL
	this->platform = (SystemLayerBase *)new FutzSDL();
#elif FUTZ_PLATFORM_SDL2
	this->platform = (SystemLayerBase *)new FutzSDL2();
#elif FUTZ_PLATFORM_ANDROID
	this->platform = (SystemLayerBase *)new FutzAndroid();
#elif FUTZ_PLATFORM_IOS
	this->platform = (SystemLayerBase *)new FutzIOS();
#elif FUTZ_PLATFORM_DREAMCAST
	this->platform = (SystemLayerBase *)new FutzDreamcast();
	this->renderer = (RendererBase *)new DreamcastRenderer();
#else
	this->platform = (SystemLayerBase *)new FutzLayer();
	this->renderer = (RendererBase *)new DummyRenderer();
#endif

#if FUTZ_RENDERER_GL1
	this->renderer = new GL1Renderer();
#elif FUTZ_RENDERER_GLES1
	this->renderer = (RendererBase *)new GLES1Renderer();
#endif
}

void Futz::Start(int argc, char **argv)
{
	platform->Initialize(argc, argv);
}

// Global static pointer used to ensure a single instance of the class.
Futz *Futz::_instance = NULL;

Futz *Futz::Instance()
{
	// Only allow one instance of class to be generated.
	if (!_instance)
	{
		_instance = new Futz;
	}

	return _instance;
}

void Futz::Update()
{
	time.UpdateLoop();
	profiler.Start("Update");
	gameObject->UpdateLoop();
	input.Update(); // Input after game object, to wipe events
	scene.Update();
	profiler.End();
}

void Futz::Render()
{
	profiler.Start("Render");

	this->renderer->StartFrame();

	camera.ComputeTransform();

	this->renderer->ApplyCamera(camera);

	scene.Render();

	time.RenderLoop();
	this->renderer->FinishFrame();
	profiler.End();
}

Model *Futz::LoadModel(char *filename)
{
	return new WavefrontModel(filename);
}

Futz::~Futz()
{
}

void Futz::Log(string mesg)
{
#ifdef ANDROID
	LOGI(mesg.c_str());
#else
	printf("Futz: %s\n", mesg.c_str());
//cout << "Futz: " << mesg << endl;
#endif
}
