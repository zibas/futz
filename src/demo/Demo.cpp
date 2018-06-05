#include "Demo.h"

#include <stdio.h>
#include <stdlib.h>
#include "Futz.h"
#include "input/InputEventQueue.h"

Demo::Demo() {
	speed = 0.5;
	turnSpeed = 20;
	idleDelay = 5.0;
	idleClock = 0;
}

void Demo::Start(){
	Futz* futz = Futz::Instance();
	asteroids.Start();
	ships.Start();


	Node* center = new Node();
	drawAxis = new DrawAxis();
	center->AddComponent((Component*) drawAxis);
	Futz::Instance()->scene.AddNode(center);

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
	if (idleClock >= idleDelay){
		//futz->camera.RotY(futz->time.delta * 10);
	}
	idleClock += futz->time.delta;
}

void Demo::RenderLoop()
{
	Futz* futz = Futz::Instance();
	futz->renderer->DefaultLighting();
}

void Demo::HandleInput(){

	Futz* futz = Futz::Instance();
	futzInputEvent* event = futz->inputEventQueue.Pop();



	Vector3 rotateDelta;
	rotateDelta.x = 1;
	rotateDelta.y = 0;
	rotateDelta.z = 0;

	double deltaX = 0;
	double deltaY = 0;

    if(futz->input.OnMouseMove()){
        idleClock = 0;
        deltaX = futz->input.mouseState.pixelX - futz->input.lastMouseState.pixelX;
        deltaY = futz->input.mouseState.pixelY - futz->input.lastMouseState.pixelY;
     
		rotateDelta.x = -deltaY * futz->time.delta * turnSpeed;
		rotateDelta.y = -deltaX * futz->time.delta * turnSpeed;
		futz->camera.Rotate(rotateDelta);
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
        futz->camera.MoveForward(speed);
    }

    if(futz->input.IsDown(FUTZ_DOWN)){
        idleClock = 0;
        futz->camera.MoveForward(-speed);
    }


	if (futz->input.IsDown('q')){
		idleClock = 0;
		futz->camera.RotX(speed);
	}

	if (futz->input.IsDown('e')){
		idleClock = 0;
		futz->camera.RotX(-speed);
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
	if (futz->input.OnDown('1')){
		rotateDelta.x = 1;
		rotateDelta.y = 0;
		rotateDelta.z = 0;
		futz->camera.Rotate(rotateDelta * futz->time.delta * turnSpeed);
	}
	if (futz->input.OnDown('2')){
		rotateDelta.x = -1;
		rotateDelta.y = 0;
		rotateDelta.z = 0;
		futz->camera.Rotate(rotateDelta * futz->time.delta * turnSpeed);
	}

	if (futz->input.OnDown('3')){
		rotateDelta.x = 0;
		rotateDelta.y = 1;
		rotateDelta.z = 0;
		futz->camera.Rotate(rotateDelta * futz->time.delta * turnSpeed);
	}

	if (futz->input.OnDown('4')){
		rotateDelta.x = 0;
		rotateDelta.y =-1;
		rotateDelta.z = 0;
		futz->camera.Rotate(rotateDelta * futz->time.delta * turnSpeed);
	}
	if (futz->input.OnDown('v')){
		futz->camera.SetFieldOfView(futz->camera.GetFieldOfView() + 1);
	}
	if (futz->input.OnDown('b')){
		futz->camera.SetFieldOfView(futz->camera.GetFieldOfView() - 1);
	}
    if(futz->input.OnDown(FUTZ_BACK)){
        exit(0);
    }
}

Demo::~Demo() {}
