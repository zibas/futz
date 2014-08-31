/*
* FutzSDL.h
*
*  Created on: Nov 3, 2010
*      Author: ziba
*/
#if FUTZ_PLATFORM_SDL2
#ifndef FUTZSDL_H_
#define FUTZSDL_H_

#include "SystemLayerBase.h"
#ifdef _WIN32
#include "SDL.h"
#include "SDL_opengl.h"
#else
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#endif

class FutzSDL2 : public SystemLayerBase {
	SDL_Surface* screen;
	int desktopHeight;
	int desktopWidth;
	SDL_GLContext context;
	SDL_Window* displayWindow;

public:
	void Initialize(int argc, char** argv);
	void Resize(int, int);
	void MainLoop();
	void ToggleFullscreen();
	virtual ~FutzSDL2();
};

#endif /* FUTZSDL_H_ */
#endif
