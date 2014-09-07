/*
 * FutzSDL.cpp
 *
 *  Created on: Nov 3, 2010
 *      Author: ziba
 */

#if FUTZ_PLATFORM_SDL

#include "../Futz.h"
#include "FutzSDL.h"
//#include "SDL/SDL.h"


void FutzSDL::Initialize(int argc, char** argv){
	Futz* futz = Futz::Instance();
	screen = NULL;
	SDL_Init( SDL_INIT_EVERYTHING );
	SDL_EnableKeyRepeat(50,50);
	const SDL_VideoInfo* bestVideoInfo = SDL_GetVideoInfo(); 
	desktopWidth = bestVideoInfo->current_w;
	desktopHeight = bestVideoInfo->current_h;
	screen = SDL_SetVideoMode( futz->platform->width, futz->platform->height, 32, SDL_OPENGL );
	SDL_WM_SetCaption( "Futz - SDL", NULL );
	Futz::Instance()->camera->SetViewport(futz->platform->width, futz->platform->height);

	Futz::Instance()->renderer->Initialize(futz->platform->width,futz->platform->height);

	Resize(futz->platform->width, futz->platform->height);

	futz->gameObject->Start();
	MainLoop();
}

void FutzSDL::Resize(int width, int height){
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

void FutzSDL::MainLoop(){
	Futz* futz = Futz::Instance();
	 SDL_Event event;

	 while(1){
	//While there are events to handle
		 SDL_EnableUNICODE(SDL_ENABLE);
	while( SDL_PollEvent( &event ) ) {

        char ch;
		//Handle user quit
		 switch (event.type) {
			 case SDL_MOUSEMOTION:
                futz->input.SetMouse(event.motion.x,event.motion.y);
			break;
		        case SDL_KEYDOWN:
		        	if ( (event.key.keysym.unicode & 0xFF80) == 0 ) {
		        	  ch = event.key.keysym.unicode & 0x7F;
                      futz->input.SetDown(ch);
		        	}

		            break;
                case SDL_KEYUP:
                    char key =  '\0';
                    if(event.key.keysym.sym == SDLK_a){ key = 'a';}
                    else if(event.key.keysym.sym == SDLK_b){ key = 'b';}
                    else if(event.key.keysym.sym == SDLK_c){ key = 'c';}
                    else if(event.key.keysym.sym == SDLK_d){ key = 'd';}
                    else if(event.key.keysym.sym == SDLK_e){ key = 'e';}
                    else if(event.key.keysym.sym == SDLK_f){ key = 'f';}
                    else if(event.key.keysym.sym == SDLK_g){ key = 'g';}
                    else if(event.key.keysym.sym == SDLK_h){ key = 'h';}
                    else if(event.key.keysym.sym == SDLK_i){ key = 'i';}
                    else if(event.key.keysym.sym == SDLK_n){ key = 'n';}
                    else if(event.key.keysym.sym == SDLK_r){ key = 'r';}
                    else if(event.key.keysym.sym == SDLK_s){ key = 's';}
                    else if(event.key.keysym.sym == SDLK_w){ key = 'w';}

                    if(key != '\0'){
                       futz->input.SetUp(key);
                    } else {
                        // what the hell sdl? they decided to not give unicode on keyup
                        // this may work on some platforms
                        if ( (event.key.keysym.unicode & 0xFF80) == 0 ) {
                            ch = event.key.keysym.unicode & 0x7F;
                            futz->input.SetUp(ch);
                        }
                    }
                    //futz->input.SetUp(event.key.keysym.unicode);
                    break;
		    }

		}

	futz->Update();
	futz->Render();
	futz->gameObject->RenderLoop();

			//Update screen
	SDL_GL_SwapBuffers();
	//Cap the frame rate
	//if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
	//{ SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() ); }
	 }
}

void FutzSDL::ToggleFullscreen(){
	Futz* futz = Futz::Instance();
	if(!futz->platform->isFullscreen){
		screen = SDL_SetVideoMode( desktopWidth, desktopHeight, 32, SDL_OPENGL);
		Resize(desktopWidth, desktopHeight);
	} else {
		screen = SDL_SetVideoMode( futz->platform->width, futz->platform->height, 32, SDL_OPENGL);
		Resize(futz->platform->width, futz->platform->height);
	}
	futz->platform->isFullscreen = !futz->platform->isFullscreen;
}
FutzSDL::~FutzSDL() {
	// TODO Auto-generated destructor stub
}
#endif
