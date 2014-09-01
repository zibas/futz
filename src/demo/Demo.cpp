#include "Demo.h"

#include <stdio.h>
#include <stdlib.h>
#include "Futz.h"
#include "input/InputEventQueue.h"

Demo::Demo() {
	speed = 0.5;
	turnSpeed = 200;
	idleDelay = 5.0;
	idleClock = 0;
}

void Demo::Start(){
	Futz::Instance()->camera.SetOrbit();
	asteroids.Start();
	ships.Start();


	Node* space = new Node();
	Model* spaceModel = Futz::Instance()->LoadModel((char*)"assets/space_sphere.obj");
	spaceModel->Load();
	space->AddModel(spaceModel);
	space->transform.SetScale(300);
	space->useLighting = false;
	Futz::Instance()->scene.AddNode(space);


}

void Demo::UpdateLoop(){
	this->HandleInput();
	this->asteroids.Update();
	this->ships.Update();

	Futz* futz = Futz::Instance();
	if(idleClock >= idleDelay){
		futz->camera.RotY(futz->time.delta * 10);
	}
	idleClock += futz->time.delta;
}

void Demo::RenderLoop()
{
	Futz::Instance()->renderer->DefaultLighting();
}


void Demo::HandleInput(){

	Futz* futz = Futz::Instance();
	futzInputEvent* event = futz->inputEventQueue.Pop();

	double deltaX = 0;
	double deltaY = 0;

    if(futz->input.OnMouseMove()){
        idleClock = 0;
        deltaX = futz->input.mouseState.pixelX - futz->input.lastMouseState.pixelX;
        deltaY = futz->input.mouseState.pixelY - futz->input.lastMouseState.pixelY;
        futz->camera.RotY(-deltaX * futz->time.delta * turnSpeed);
        futz->camera.RotRightAxis(deltaY * futz->time.delta * turnSpeed);
    }

    if(futz->input.IsDown(FUTZ_LEFT)){
        idleClock = 0;
        futz->camera.MoveRight(-speed);
    }

    if(futz->input.IsDown(FUTZ_RIGHT)){
        idleClock = 0;
        futz->camera.MoveRight(speed);
    }

    if(futz->input.IsDown(FUTZ_UP)){
        idleClock = 0;
        futz->camera.MoveForward(-speed);
    }

    if(futz->input.IsDown(FUTZ_DOWN)){
        idleClock = 0;
        futz->camera.MoveForward(speed);
    }

    if(futz->input.OnDown('f')){
        futz->platform->ToggleFullscreen();
    }
    if(futz->input.OnDown('p')){
        futz->profiler.enabled = !futz->profiler.enabled;
    }
    if(futz->input.OnDown('c')){
        futz->camera.Print();
    }
    if(futz->input.OnDown(FUTZ_BACK)){
        exit(0);
    }
}

Demo::~Demo() {}
