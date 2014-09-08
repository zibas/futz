/*
* FutzSDL.cpp
*
*  Created on: August 31, 2014
*      Author: ziba
*/

#if FUTZ_PLATFORM_SDL2

#include "../Futz.h"
#include "FutzSDL2.h"
//#include "SDL/SDL.h"


void checkSDLError(int line = -1)
{
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		printf("SDL Error: %s\n", error);
		if (line != -1)
			printf(" + line: %i\n", line);
		SDL_ClearError();
	}
}

void FutzSDL2::Initialize(int argc, char** argv){
	
	Futz* futz = Futz::Instance();
	screen = NULL;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		futz->Log("Error: Unable to initialize SDL2");
	}


	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	/* Turn on double buffering with a 24bit Z buffer.
	* You may need to change this to 16 or 32 for your system */
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

	displayWindow = SDL_CreateWindow("Futz - SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, futz->platform->width, futz->platform->height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	
	if (!displayWindow){
		futz->Log("Error: Unable to initialize SDL2 display window");
	}

	checkSDLError(__LINE__);
	context = SDL_GL_CreateContext(displayWindow);
	checkSDLError(__LINE__);
	/* This makes our buffer swap syncronized with the monitor's vertical refresh */
	//SDL_GL_SetSwapInterval(1);
	Futz::Instance()->camera.SetViewport(futz->platform->width, futz->platform->height);
	Futz::Instance()->renderer->Initialize(futz->platform->width, futz->platform->height);

	Resize(futz->platform->width, futz->platform->height);
	futz->Log("Initialized SDL2");
	futz->gameObject->Start();
	MainLoop();
	
}

void FutzSDL2::Resize(int width, int height){

	if (height == 0){
		height = 1;
	}
	Futz::Instance()->camera.SetViewport(width, height);

	Futz::Instance()->renderer->Resize(width, height);

}

char FutzSDL2::EventToChar(SDL_Event event){
	char key = '\0';
	if (event.key.keysym.sym == SDLK_a){ key = 'a'; }
	else if (event.key.keysym.sym == SDLK_b){ key = 'b'; }
	else if (event.key.keysym.sym == SDLK_c){ key = 'c'; }
	else if (event.key.keysym.sym == SDLK_d){ key = 'd'; }
	else if (event.key.keysym.sym == SDLK_e){ key = 'e'; }
	else if (event.key.keysym.sym == SDLK_f){ key = 'f'; }
	else if (event.key.keysym.sym == SDLK_g){ key = 'g'; }
	else if (event.key.keysym.sym == SDLK_h){ key = 'h'; }
	else if (event.key.keysym.sym == SDLK_i){ key = 'i'; }

	else if (event.key.keysym.sym == SDLK_n){ key = 'n'; }
	else if (event.key.keysym.sym == SDLK_o){ key = 'o'; }
	else if (event.key.keysym.sym == SDLK_p){ key = 'p'; }
	else if (event.key.keysym.sym == SDLK_q){ key = 'q'; }
	else if (event.key.keysym.sym == SDLK_r){ key = 'r'; }
	else if (event.key.keysym.sym == SDLK_s){ key = 's'; }


	else if (event.key.keysym.sym == SDLK_v){ key = 'v'; }
	else if (event.key.keysym.sym == SDLK_w){ key = 'w'; }



	else if (event.key.keysym.sym == SDLK_0){ key = '0'; }
	else if (event.key.keysym.sym == SDLK_1){ key = '1'; }
	else if (event.key.keysym.sym == SDLK_2){ key = '2'; }
	else if (event.key.keysym.sym == SDLK_3){ key = '3'; }
	else if (event.key.keysym.sym == SDLK_4){ key = '4'; }
	else if (event.key.keysym.sym == SDLK_5){ key = '5'; }
	else if (event.key.keysym.sym == SDLK_6){ key = '6'; }
	else if (event.key.keysym.sym == SDLK_7){ key = '7'; }
	else if (event.key.keysym.sym == SDLK_8){ key = '8'; }
	else if (event.key.keysym.sym == SDLK_9){ key = '9'; }
	else if (event.key.keysym.sym == SDLK_ESCAPE){ key = 27; }

	return key;
}

void FutzSDL2::MainLoop(){
	Futz* futz = Futz::Instance();
	
	SDL_Event event;
	//SDL_StartTextInput();
	while (1){
		//While there are events to handle
		
		//SDL_EnableUNICODE(SDL_ENABLE);
		while (SDL_PollEvent(&event)) {

			char ch;
			//Handle user quit
			switch (event.type) {
			case SDL_MOUSEMOTION:
				futz->input.SetMouse(event.motion.x, event.motion.y);
				break;
			case SDL_TEXTINPUT:
				break;
			case SDL_KEYDOWN:
				futz->input.SetDown(this->EventToChar(event));
				break;
			case SDL_KEYUP:
				futz->input.SetUp(this->EventToChar(event));
				break;
			}

		}

		futz->Update();
		futz->Render();
		futz->gameObject->RenderLoop();

		//Update screen
		SDL_GL_SwapWindow(displayWindow);
		//Cap the frame rate
		//if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
		//{ SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() ); }
	}
	
}

void FutzSDL2::ToggleFullscreen(){
	Futz* futz = Futz::Instance();
	if (!futz->platform->isFullscreen){
		SDL_DisplayMode displayMode;
		SDL_SetWindowFullscreen(displayWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
		int should_be_zero = SDL_GetCurrentDisplayMode(0, &displayMode);
		Resize(displayMode.w, displayMode.h);
	}
	else {
		SDL_SetWindowFullscreen(displayWindow, 0);
		Resize(futz->platform->width, futz->platform->height);
	}
	futz->platform->isFullscreen = !futz->platform->isFullscreen;
}
FutzSDL2::~FutzSDL2() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(displayWindow);
	SDL_Quit();
}
#endif
