/*
 * FutzSDL.h
 *
 *  Created on: Nov 3, 2010
 *      Author: ziba
 */
#if FUTZ_PLATFORM_SDL
#ifndef FUTZSDL_H_
#define FUTZSDL_H_

#include "SystemLayerBase.h"
#ifdef _WIN32
#include "SDL.h"
#include "SDL_opengl.h"
#else
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#endif

class FutzSDL: public SystemLayerBase {
	SDL_Surface* screen;
	int desktopHeight;
	int desktopWidth;
public:
	void Initialize(int argc, char** argv);
	void Resize(int, int);
	void MainLoop();
	void ToggleFullscreen();
	virtual ~FutzSDL();
};

#endif /* FUTZSDL_H_ */
#endif
