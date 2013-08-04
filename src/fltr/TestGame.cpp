#include "TestGame.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Futz.h"
#include "input/InputEventQueue.h"

TestGame::TestGame() {
	speed = 0.5;
	turnSpeed = 100;
	srand (time(NULL));
	Futz::Log("Game Constructor done");
}

void TestGame::Start(){
	Futz* futz = Futz::Instance();

    fish1 = new Fish();
    fish1->Load();

	futz->camera.SetOrbit();
	glClearColor(1.0,1.0,1.0,0.0);
	Futz::Log("Started game object");
}

void TestGame::UpdateLoop(){
	Futz* futz = Futz::Instance();
	this->HandleInput();
    fish1->Update();
    deltaZ = 0;
}


void TestGame::RenderLoop()
{
	//Futz::Instance()->renderer->DefaultLighting();
	GLfloat light_ambient[] = {1.0, 1.0, 1.0, 1.0}; 
	GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0}; 
	GLfloat light_position[] = {0.0, 0.0, 2.0, 1.0};  /* Infinite light location. */
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
}


void TestGame::HandleInput(){

	Futz* futz = Futz::Instance();

	double deltaX = 0;
	double deltaY = 0;

    if(futz->input.IsDown(FUTZ_UP, FUTZ_PLAYER_ONE)){
        fish1->ThrustOn(0,1);
    }
    if(futz->input.IsDown(FUTZ_DOWN, FUTZ_PLAYER_TWO)){
        fish1->ThrustOn(0,-1);
    }
    if(futz->input.IsDown(FUTZ_LEFT)){
        fish1->ThrustOn(-1,0);
    }
    if(futz->input.IsDown(FUTZ_RIGHT)){
        fish1->ThrustOn(1,0);
    }

    if(futz->input.IsDown(FUTZ_BACK)){
        exit(0);
    }

    if(futz->input.OnUp('f')){
         futz->platform->ToggleFullscreen();
    }

        /*
        if(*key == 'p'){
                futz->camera.Print();
        }
        */

    if(futz->input.OnMouseMove()){
        deltaX = futz->input.mouseState.pixelX - futz->input.lastMouseState.pixelX;
        deltaY = futz->input.mouseState.pixelY - futz->input.lastMouseState.pixelY;
        futz->camera.RotY(-deltaX * futz->time.delta * turnSpeed);
        futz->camera.RotRightAxis(deltaY * futz->time.delta * turnSpeed);
    }




}

TestGame::~TestGame() {}
