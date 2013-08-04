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

	char* file = (char*)"assets/barn.obj";
	model = futz->LoadModel(file);
	model->Load();
	barn = new Node();
	barn->AddModel(model);
	barn->transform.SetScale(1);
	deltaZ = 0;
	barn->transform.SetPosition(0,0,0);
	futz->scene.AddNode(barn);
	
	modelShip = futz->LoadModel("assets/taxi_model.obj");
	modelShip->Load();
	ship = new Node();
	ship->AddModel(modelShip);
	ship->transform.SetScale(1);
	ship->transform.SetPosition(0,3,3);
	ship->parent = barn;
	futz->scene.AddNode(ship);
	
	char* file2 = (char*)"assets/terrain.obj";
	model2 = futz->LoadModel(file2);
	model2->Load();

	terrain = new Node();
	terrain->AddModel(model2);
	terrain->transform.SetScale(30);
	terrain->transform.SetPosition(1,-2,-7);
	futz->scene.AddNode(terrain);

	futz->camera.SetOrbit();
	glClearColor(0.6,0.6,0.8,0.0);
	Futz::Log("Started game object");

	barnYrot = 0;
	//barnRotation.SetFromEuler(0,barnYrot,0);

	barnPos.x = barnPos.y =  barnPos.z = 0;
}

void TestGame::UpdateLoop(){
	Futz* futz = Futz::Instance();
	this->HandleInput();

	barn->transform.SetRotation(0, barnYrot, 0);
	barn->transform.AddRelativeTranslation(0,0,deltaZ);
	ship->transform.LookAt(barn->transform.position);
	deltaZ = 0;
}


void TestGame::RenderLoop()
{
	Futz::Instance()->renderer->DefaultLighting();
}


void TestGame::HandleInput(){

	Futz* futz = Futz::Instance();

	double deltaX = 0;
	double deltaY = 0;

    if(futz->input.OnMouseMove()){
        deltaX = futz->input.mouseState.pixelX - futz->input.lastMouseState.pixelX;
        deltaY = futz->input.mouseState.pixelY - futz->input.lastMouseState.pixelY;
        futz->camera.RotY(-deltaX * futz->time.delta * turnSpeed);
        futz->camera.RotRightAxis(deltaY * futz->time.delta * turnSpeed);
    }

    if(futz->input.IsDown(FUTZ_LEFT)){
				barnYrot += futz->time.delta * 150;
    }

    if(futz->input.IsDown(FUTZ_RIGHT)){
				barnYrot -= futz->time.delta * 150;
    }

    if(futz->input.IsDown(FUTZ_UP)){
				deltaZ -= futz->time.delta * 20;
    }

    if(futz->input.IsDown(FUTZ_DOWN)){
				deltaZ += futz->time.delta * 20;
    }

    if(futz->input.OnDown(FUTZ_ASCEND)){
				futz->camera.MoveUp(speed);
    }
    if(futz->input.OnDown(FUTZ_DESCEND)){
				futz->camera.MoveUp(-speed);
    }
    if(futz->input.OnDown(FUTZ_BACK)){
        exit(0);
    }
    if(futz->input.OnDown('f')){
        futz->platform->ToggleFullscreen();
    }

}

TestGame::~TestGame() {}
