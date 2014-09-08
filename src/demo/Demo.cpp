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
	asteroids.Start();
	ships.Start();


	Node* space = new Node();
	Model* spaceModel = Futz::Instance()->LoadModel((char*)"assets/space_sphere.obj");
	spaceModel->Load();
	space->AddModel(spaceModel);
	space->transform.SetScale(300);
	space->useLighting = false;
	Futz::Instance()->scene.AddNode(space);
	/*
	cameraCenter = new Node();
	Model* cameraCenterModel = Futz::Instance()->LoadModel((char*)"assets/asteroid.obj");
	cameraCenterModel->Load();
	cameraCenter->AddModel(cameraCenterModel);
	cameraCenter->transform.SetScale(2);
	cameraCenter->useLighting = false;
	Futz::Instance()->scene.AddNode(cameraCenter);


	cameraEye = new Node();
	Model* cameraEyeModel = Futz::Instance()->LoadModel((char*)"assets/cell.obj");
	cameraEyeModel->Load();
	cameraEye->AddModel(cameraEyeModel);
	cameraEye->transform.SetScale(2);
	cameraEye->useLighting = false;
	Futz::Instance()->scene.AddNode(cameraEye);
	*/

}

void Demo::UpdateLoop(){
	this->HandleInput();
	//cameraCenter->transform.SetPosition(Futz::Instance()->camera.center);
	//cameraEye->transform.SetPosition(Futz::Instance()->camera.eye);
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
	DrawAxis(5, 2);
	futz->renderer->DefaultLighting();
}

void Demo::DrawAxis(float interval, int emphasis){
	Vector3 color;
	Vector3 v1, v2;
	Vector3 x;
	Vector3 y;
	Vector3 z;
	x.x = 1000;
	y.y = 1000;
	z.z = 1000;
	float width = 5;


	Futz* futz = Futz::Instance();
	futz->renderer->DisableLighting();

	color.x = 1; color.y = 0; color.z = 0;
	futz->renderer->DrawLine(x * -1, x, color);

	for (int i = -x.x; i < x.x; i += interval){
		v1.x = v2.x = i;
		v1.y = v2.y = 0;
		v1.z = -width/2; v2.z = width/2;
		color.x = 0.5; color.y = 0; color.z = 0;
		if (i % (int)(interval * emphasis) == 0)
		{
			color.x = 1;
			v1.z = -width; v2.z = width;
		}
		futz->renderer->DrawLine(v1, v2, color);
	}

	color.x = 0; color.y = 1; color.z = 0;
	futz->renderer->DrawLine(y * -1, y, color);

	for (int i = -y.y; i < y.y; i += interval){
		v1.y = v2.y = i;
		v1.x = v2.x = 0;
		v1.z = -width / 2; v2.z = width / 2;
		color.x = 0; color.y = 0.5; color.z = 0;
		if (i % (int)(interval * emphasis) == 0)
		{
			color.y = 1;
			v1.z = -width; v2.z = width;
		}
		futz->renderer->DrawLine(v1, v2, color);
	}


	color.x = 0.5; color.y = 0.5; color.z = 1;
	futz->renderer->DrawLine(z * -1, z, color);

	for (int i = -z.z; i < z.z; i += interval){
		v1.z = v2.z = i;
		v1.y = v2.y = 0;
		v1.x = -width / 2; v2.x = width / 2;
		color.x = 0.5; color.y = 0.5; color.z = 0.5;
		if (i % (int)(interval * emphasis) == 0)
		{
			color.z = 1;
			v1.x = -width; v2.x = width;
		}
		futz->renderer->DrawLine(v1, v2, color);
	}

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
